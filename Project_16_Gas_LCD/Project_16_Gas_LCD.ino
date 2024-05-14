// Include Wire library for I2C communication
// Include LiquidCrystal_I2C library
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>  

// Initialize the LiquidCrystal_I2C object with 
// I2C address 0x27 and dimensions 16x2
LiquidCrystal_I2C mylcd(0x27, 16, 2);

// Define pin numbers for the gas sensor and buzzer
#define gasPin 23
#define buzPin 25

// Initialize boolean variables to manage state changes
boolean i = 1;
boolean j = 1;

// The setup function to run each code once
// from top to bottom within the setup function,
// once executed last code it exits the
// setup function, and continue to function loop
void setup() {

  // Initialize serial communication at 9600 baud
  // Initialize the LCD screen
  // Turn on the LCD backlight
  // Set buzzer pin as an output
  // Set gas sensor pin as an input
  // Set the cursor to the first column of the first row
  // Display "safety" on the LCD
  Serial.begin(9600);  
  mylcd.init();  
  mylcd.backlight();  
  pinMode(buzPin, OUTPUT);  
  pinMode(gasPin, INPUT);  
  mylcd.setCursor(0, 0);  
  mylcd.print("safety");  
}

void loop() {
  // Read the value from the gas sensor
  // Print the gas sensor value to the serial monitor
  boolean gasVal = digitalRead(gasPin);  
  Serial.println(gasVal);  

    // If hazardous gas is detected
    if (gasVal == 0) {  
    while (i == 1) {

      // Clear the LCD screen
      // Set the cursor to the first column of the first row
      // Display "dangerous" on the LCD
      // Set i to 0 to avoid repeating this block
      // Set j to 1 to allow the safety message to be displayed later
      mylcd.clear();  
      mylcd.setCursor(0, 0);  
      mylcd.print("dangerous");  
      i = 0;  
      j = 1;  
}
    // Turn on the buzzer
    // Short delay
    // Turn off the buzzer
    digitalWrite(buzPin, HIGH);  
    delay(1);  
    digitalWrite(buzPin, LOW);  
    // Short delay
    // If no hazardous gas is detected
    delay(1);  
  } else {  
    // Ensure the buzzer is off
    digitalWrite(buzPin, LOW);  
    while (j == 1) {
      // Clear the LCD screen
      // Set the cursor to the first column of the first row
      // Display "safety" on the LCD
      mylcd.clear();  
      mylcd.setCursor(0, 0);  
      mylcd.print("safety");  
      // Set i to 1 to allow the dangerous message 
      // to be displayed later
      // Set j to 0 to avoid repeating this block
      i = 1;  
      j = 0;  
    }
  }
}

