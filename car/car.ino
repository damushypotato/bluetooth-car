#include <SoftwareSerial.h>

int enL = 3;
int in1L = 4;
int in2L = 5;

int enR = 6;
int in1R = 9;
int in2R = 8;

SoftwareSerial mySerial(10, 11);

void setup() {
  Serial.begin(19200);

  pinMode(enL, OUTPUT);
  pinMode(in1L, OUTPUT);
  pinMode(in2L, OUTPUT);
  pinMode(enR, OUTPUT);
  pinMode(in1R, OUTPUT);
  pinMode(in2R, OUTPUT);
  setL(0);
  setR(0);

  mySerial.begin(9600);
}

void loop() {
  if (mySerial.available()) {
    String in = mySerial.readStringUntil('\n');
    int index = in.indexOf(' ');
    int l = in.substring(0,index).toInt();
    int length = in.length();
    int r = in.substring(index, length).toInt();
    Serial.print('l');
    Serial.print(l);
    Serial.print(" r");
    Serial.println(r);
    setL(l);
    setR(r);
  }
}

int setL(int val) {
  val = min(255, max(-255, val));
  if (val == 0) {
    setLH(LOW, LOW);
  }
  else if (val > 0) {
    setLH(HIGH, LOW);
  }
  else if (val < 0) {
    setLH(LOW, HIGH);
  }
  analogWrite(enL, abs(val));
  return val;
}

void setLH(byte a, byte b) {
  digitalWrite(in1L, a);
  digitalWrite(in2L, b);
}

int setR(int val) {
  val = min(255, max(-255, val));
  if (val == 0) {
    setRH(LOW, LOW);
  }
  else if (val > 0) {
    setRH(HIGH, LOW);
  }
  else if (val < 0) {
    setRH(LOW, HIGH);
  }
  analogWrite(enR, abs(val));
  return val;
}

void setRH(byte a, byte b) {
  digitalWrite(in1R, a);
  digitalWrite(in2R, b);
}
