// please install the ESP32_Servo.h library 
#include <ESP32_Servo.h> 

// Create a servo object to control a servo
// Note: Up to 16 servo objects can be created on the ESP32
Servo myservo;  

// Variable to store the servo position                
int pos = 0;    

// Define the GPIO pin used to control the servo
// Recommended PWM GPIO pins on the ESP32 
// include 2, 4, 12-19, 21-23, 25-27, 32-33 
int servoPin = 13;

// The setup function to run each code once
// from top to bottom within the setup function,
// once executed last code it exits the
// setup function, and continue to function loop
void setup() {
  // Attach the servo to the specified pin
  // Attaches the servo on pin 13 to the servo object
 myservo.attach(servoPin);   
}

void loop() {
  // Move the servo from 0 to 360 degrees in steps of 1 degree
  // Command the servo to move to the current position
  // Wait for 15ms for the servo to reach the position
  for (pos = 0; pos <= 360; pos += 1) {
    myservo.write(pos);    
    delay(15);             
  }

  // Move the servo from 360 to 0 degrees in steps of 1 degree
  // Command the servo to move to the current position
  // Wait for 15ms for the servo to reach the position
  for (pos = 360; pos >= 0; pos -= 1) {
    myservo.write(pos);    
    delay(15);             
  }
}
