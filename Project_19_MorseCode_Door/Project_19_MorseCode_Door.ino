// Include Wire library for I2C communication
// Include LiquidCrystal_I2C library for the LCD
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>  

// Initialize the LCD with I2C address 0x27 and size 16x2
LiquidCrystal_I2C mylcd(0x27,16,2);  

// Include OneButton library for handling button presses
// Setup a new OneButton on pin 16
#include "OneButton.h"  
// Initialize button1 on pin 16, with active low configuration
// Setup a new OneButton on pin 27
// Initialize button2 on pin 27, with active low configuration
OneButton button1(16, true);  
OneButton button2(27, true);  

// Include ESP32 Servo library
#include <ESP32_Servo.h>  

// Create a Servo object
// Define the pin for the servo
// Initialize an empty string for the password
// Define the correct password for the door
Servo myservo;  
int servoPin = 13;  
String password = "";  
String correct_p = "-.-";  

// setup code here, to run once:
// The setup function to run each code once
// from top to bottom within the setup function,
// once executed last code it exits the
// setup function, and continue to function loop
void setup() {
  // Initialize serial communication at 115200 baud
  // Initialize the LCD
  // Turn on the LCD backlight
  Serial.begin(115200);  
  mylcd.init();  
  mylcd.backlight();  
  
  // link the button 1 functions
  // Attach the click1 function to a single press of button1
  // Attach the longPressStop1 function to a long press release of button1
  button1.attachClick(click1);  
  button1.attachLongPressStop(longPressStop1);  
  
  // link the button 2 functions
  // Attach the click2 function to a single press of button2
  // Attach the longPressStop2 function to a long press release of button2
  button2.attachClick(click2);  
  button2.attachLongPressStop(longPressStop2);  

  // Attach the servo to the specified pin
  // Set the cursor to the first column of the first row
  // Print "Enter password" on the LCD
  myservo.attach(servoPin);  
  mylcd.setCursor(0, 0);  
  mylcd.print("Enter password");  
}

void loop() {
  // keep watching the push buttons
  // Continuously check the state of button1
  // Continuously check the state of button2
  // Small delay for debounce
  button1.tick();  
  button2.tick();  
  delay(10);  
}

// ----- button 1 callback functions
// This function will be called when button1 is pressed 1 time (and no 2nd button press followed)
void click1() {
  // Print a dot to the serial monitor
  // Append a dot to the password string
  // Set the cursor to the first column of the second row
  // Display the current password on the LCD
  Serial.print(".");  
  password = password + '.';  
  mylcd.setCursor(0, 1);  
  mylcd.print(password);  
} // click1

// This function will be called once, 
// when button1 is released after being pressed for a long time
void longPressStop1() {
  // Print a dash to the serial monitor
  // Append a dash to the password string
  // Set the cursor to the first column of the second row
  // Display the current password on the LCD
  Serial.print("-");  
  password = password + '-';  
  mylcd.setCursor(0, 1);  
  mylcd.print(password);  
} // longPressStop1

// ... and the same for button 2
void click2() {
    // Print the entered password to the serial monitor
    // If the entered password matches the correct password
    // Open the door by moving the servo to 180 degrees
    // Clear the LCD
    // Set the cursor to the first column of the first row
    // Print "open" on the LCD
    Serial.println(password);  
    if(password == correct_p) {  
    myservo.write(180);  
    mylcd.clear();  
    mylcd.setCursor(0, 0);  
    mylcd.print("open");  
} 
    // If the entered password is incorrect
    else {  
    // Clear the LCD
    // Set the cursor to the first column of the first row
    // Print "error" on the LCD
    // Wait for 2 seconds
    // Clear the LCD
    // Set the cursor to the first column of the first row
    // Prompt the user to input the password again
    mylcd.clear();  
    mylcd.setCursor(0, 0);  
    mylcd.print("error");  
    delay(2000);  
    mylcd.clear();  
    mylcd.setCursor(0, 0);  
    mylcd.print("input again");  
  }
  // Reset the password string
  password = "";  
} // click2

void longPressStop2() {
  // Close the door by moving the servo to 0 degrees
  // Clear the LCD
  // Set the cursor to the first column of the first row
  // Print "close" on the LCD
  myservo.write(0);  
  mylcd.clear();  
  mylcd.setCursor(0, 0);  
  mylcd.print("close");  
} // longPressStop2
