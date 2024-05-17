#include <ESP32_Servo.h>
Servo myservo;
#define servoPin 5

void setup() {
  myservo.attach(servoPin);
  myservo.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
}
