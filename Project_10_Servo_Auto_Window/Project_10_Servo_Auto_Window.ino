//please install the ESP32_Servo.h library
#include <ESP32_Servo.h>

// Create a servo object to control a servo
// Define the GPIO pin connected to the servo
// Define the GPIO pin connected to the water sensor
Servo myservo;        
#define servoPin 5    
#define waterPin 34   

// The setup function to run each code once
// from top to bottom within the setup function,
// once executed last code it exits the
// setup function, and continue to function loop
void setup() { 
  // Initialize serial communication at 9600 baud rate
  // Set the water sensor pin as INPUT
  // Attach the servo to the specified pin
  // Move the servo to the initial position (176 degrees)
  // Delay to allow the servo to reach the initial position
  Serial.begin(9600);        
  pinMode(waterPin, INPUT);  
  myservo.attach(servoPin);  
  myservo.write(176);        
  delay(200);                
}

void loop() {
  // Read the water sensor value
  // Print the water sensor value to serial monitor
  int water_val = analogRead(waterPin); 
  Serial.println(water_val);            

  // Check if the water level is above the threshold (1500 in this case)
  if(water_val > 1500) {
    // If the water level is above the threshold,
    // move the servo to close the valve
    // Command the servo to move to the closed position (0 degrees)
    // Delay to allow the servo to reach the closed position
    myservo.write(0);    
    delay(200);          

  } else {
    // If the water level is below the threshold, 
    // move the servo to open the valve
    // Command the servo to move to the open position (176 degrees)
    // Delay to allow the servo to reach the open position
    myservo.write(176);  
    delay(200);          
  }
}
