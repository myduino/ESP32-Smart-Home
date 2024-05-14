/*  
 * Filename    : xht11
 * Description : Read the temperature and humidity values of XHT11.
*/
// Include the Wire library for I2C communication
// Include the LiquidCrystal_I2C library for the LCD
// Initialize the LCD with I2C address 0x27 and size 16x2
// Include the xht11 sensor library
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>  
LiquidCrystal_I2C mylcd(0x27, 16, 2);  
#include "xht11.h"  

// Initialize the xht11 sensor on pin 17
xht11 xht(17);  

// Array to store the temperature and 
// humidity data received from the sensor
// Only the first 32 bits of data are received, 
// not the parity bits
unsigned char dht[4] = {0, 0, 0, 0};  

// The setup function to run each code once
// from top to bottom within the setup function,
// once executed last code it exits the
// setup function, and continue to function loop
void setup() {
    // Start the serial port monitor and 
    // set the baud rate to 9600
    // Initialize the LCD
    // Turn on the LCD backlight
  Serial.begin(9600);  
  mylcd.init();  
  mylcd.backlight();  
}

void loop() {
    // Returns true when data is correctly 
    // received from the sensor
    // Print "RH:" to the serial monitor
    // Print the integral part of humidity to the 
    // serial monitor
    // Print "%" to indicate percentage
    // Print "Temp:" to the serial monitor
    // Print the integral part of temperature to the 
    // serial monitor
    // Print "C" to indicate Celsius and move to the next line
    if (xht.receive(dht)) {  
    Serial.print("RH:");  
    Serial.print(dht[0]);  
    Serial.print("%  ");  
    Serial.print("Temp:");  
    Serial.print(dht[2]);  
    Serial.println("C");  
    
    // Set the LCD cursor to the first column of the first row
    // Print "T = " to the LCD (Temperature)
    // Print the integral part of temperature to the LCD
    // Set the LCD cursor to the first column of the second row
    // Print "H = " to the LCD (Humidity)
    // Print the integral part of humidity to the LCD
    // mylcd.clear();  // Optional: 
    // Uncomment to clear the LCD after each reading
    // Delay for 200 milliseconds to allow the display to update
    // If there is a read error
    mylcd.setCursor(0, 0);  
    mylcd.print("T = ");  
    mylcd.print(dht[2]);  
    mylcd.setCursor(0, 1);  
    mylcd.print("H = ");  
    mylcd.print(dht[0]);  
    
    delay(200);  
  } 
    else {  
    // Print "sensor error" to the serial monitor
    Serial.println("sensor error");  
  }
  // Wait for 1000 milliseconds (1 second) before reading the sensor again
  delay(1000);  
}

