/*  
 * Filename    : RFID
 * Description : RFID reader UID
 * Author      : http://www.keyestudio.com
*/
// Include the Wire library for I2C communication
// Include the LiquidCrystal_I2C library for the LCD
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>  
// Initialize the LCD with I2C address 0x27 and size 16x2
LiquidCrystal_I2C mylcd(0x27,16,2);  

// Include the ESP32 Servo library
// Create a Servo object
#include <ESP32_Servo.h> 
Servo myservo;  

// Include the MFRC522 I2C library for the RFID reader
#include "MFRC522_I2C.h"  

// Create MFRC522 object with I2C address 0x28
MFRC522 mfrc522(0x28);  

// Define pin 13 for the servo
// Define pin 16 for the button
// Initialize button flag
#define servoPin  13  
#define btnPin 16  
boolean btnFlag = 0;  

// Initialize password string
String password = "";  

// The setup function to run each code once
// from top to bottom within the setup function,
// once executed last code it exits the
// setup function, and continue to function loop
void setup() {
// Initialize serial communication at 115200 baud
// Initialize the LCD
// Turn on the LCD backlight
// Initialize I2C communication
// Initialize MFRC522 RFID reader
// Display RFID reader details
// Print message to serial monitor
// Attach the servo to the specified pin
// Set the button pin as input
// Set the cursor to the first column of the first row
// Print "Card" on the LCD
  Serial.begin(115200);  
  mylcd.init();  
  mylcd.backlight();  
  Wire.begin();  
  mfrc522.PCD_Init();  
  ShowReaderDetails();  
  Serial.println(F("Scan PICC to see UID, type, and data blocks..."));  
  myservo.attach(servoPin);  
  pinMode(btnPin, INPUT);  
  mylcd.setCursor(0, 0);  
  mylcd.print("Card");  
}

void loop() {
    // Check if a new card is present and if its serial can be read
    if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    // Short delay
    // Reset password string
    // If the button flag is set
    // Read the button value
    // If the button is pressed
    // Print "close" to the serial monitor
    // Set the cursor to the first column of the first row
    // Print "close" on the LCD
    // Move the servo to 0 degrees (close position)
    // Reset button flag
    delay(50);  
    password = "";  
    if(btnFlag == 1) {  
    boolean btnVal = digitalRead(btnPin);  
    if(btnVal == 0) {  
    Serial.println("close");  
    mylcd.setCursor(0, 0);  
    mylcd.print("close");  
    myservo.write(0);  
    btnFlag = 0;  
    }
  }
    // Exit the function if no new card is present
    return;  
}

    // Save the UID of the detected card
    // Print "Card UID:" to the serial monitor
    Serial.print(F("Card UID:"));  
    for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i]);
    password = password + String(mfrc522.uid.uidByte[i]);
  }
  
    // Check if the card number is correct
    // If the card number is correct (Put the correct card UID!)
    if(password == "846148219") {  
    // Print "open" to the serial monitor
    // Set the cursor to the first column of the first row
    // Clear the LCD
    // Print "open" on the LCD
    // Move the servo to 180 degrees (open position)
    // Reset password string
    // Set button flag
    Serial.println("open");  
    mylcd.setCursor(0, 0);  
    mylcd.clear();  
    mylcd.print("open");  
    myservo.write(180);  
    password = "";  
    btnFlag = 1;  
}   
    // If the card number is incorrect
    else {  
    // Reset password string
    // Set the cursor to the first column of the first row
    // Print "error" on the LCD
    password = "";  
    mylcd.setCursor(0, 0);  
    mylcd.print("error");  
  }
}

void ShowReaderDetails() {
    // Get and print the MFRC522 software version
    byte v = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
    Serial.print(F("MFRC522 Software Version: 0x"));
    Serial.print(v, HEX);
    if (v == 0x91)
    Serial.print(F(" = v1.0"));
    else if (v == 0x92)
    Serial.print(F(" = v2.0"));
    else
    Serial.print(F(" (unknown)"));
    Serial.println("");
    // Check for communication failure
    if ((v == 0x00) || (v == 0xFF)) {
    Serial.println(F("WARNING: Communication failure, is the MFRC522 properly connected?"));
  }
}

