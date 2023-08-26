#include <DifferentialSteering.h>
#include <SoftwareSerial.h>
#include <Joystick.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); 

int pinJoystickX = A1;
int pinJoystickY = A0;
int pinJoystickButton = 2;
int noActionLimit = 16;
int minRange = -255;
int maxRange = 255;
Joystick joystick(pinJoystickX, pinJoystickY, pinJoystickButton, noActionLimit, minRange, maxRange);

int lastL = 1000;
int lastR = 1000;

int fPivYLimit = 32;
DifferentialSteering DiffSteer;

SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  lcd.init(); 
  lcd.backlight();
  joystick.invertYAxis();
  DiffSteer.begin(fPivYLimit);
  
  Serial.begin(19200);

  mySerial.begin(9600);
}

void LCD(int l, int r) {
    int lp = map(l, -255, 255, -100, 100);
    int rp = map(r, -255, 255, -100, 100);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("L:");
    lcd.print(lp);
    lcd.print('%');
    lcd.setCursor(0,1);
    lcd.print("R:");
    lcd.print(rp);
    lcd.print('%');
}

void loop() {

    int XValue = joystick.getXValue();
    int YValue = joystick.getYValue();
    int lowLimit = joystick.getLowLimit();
    int highLimit = joystick.getHighLimit();

    int leftMotor = 0;
    int rightMotor = 0;

    if (!((XValue > lowLimit) && (XValue < highLimit) && (YValue > lowLimit) && (YValue < highLimit)))
    {
        DiffSteer.computeMotors(XValue, YValue);
        leftMotor = DiffSteer.computedLeftMotor();
        rightMotor = DiffSteer.computedRightMotor();
    }

    if (lastL != leftMotor && lastR != rightMotor) {
      mySerial.print(leftMotor);
      mySerial.print(" ");
      mySerial.println(rightMotor);
  
      LCD(leftMotor, rightMotor);
    }
    lastL = leftMotor;
    lastR = rightMotor;
    delay(100);
}
