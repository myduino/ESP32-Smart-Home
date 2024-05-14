// Include Wire library for I2C communication
// Include LiquidCrystal_I2C library
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>  

// Initialize the LiquidCrystal_I2C object with 
// I2C address 0x27 and dimensions 16x2
LiquidCrystal_I2C mylcd(0x27, 16, 2);

// The setup function to run each code once
// from top to bottom within the setup function,
// once executed last code it exits the
// setup function, and continue to function loop
void setup() {
  // Initialize the LCD screen
  // Turn on the LCD backlight
  mylcd.init();  
  mylcd.backlight();  
}

void loop() {
  // Set the cursor to the first column of the first row
  // Print "hello" on the first row
  mylcd.setCursor(0, 0);  
  mylcd.print("hello");  

  // Set the cursor to the first column of the second row
  // Print "world" on the second row
  mylcd.setCursor(0, 1);  
  mylcd.print("world");  

  // Uncomment the next line if you want to clear the 
  // screen before updating the display
  // mylcd.clear();  // Clear the LCD screen
}
