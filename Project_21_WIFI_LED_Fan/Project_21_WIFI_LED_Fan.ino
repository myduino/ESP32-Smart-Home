// Please install all these library that has been used in this file
#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiClient.h>

// Initialize a string to store the requested item
String item = "0";  
// WiFi SSID
const char* ssid = "myinvententerprise";  
// WiFi password
const char* password = "04222682";  
// Create a WiFiServer object on port 80
WiFiServer server(80);  
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Create an LCD object with I2C address 0x27 and 16x2 display
LiquidCrystal_I2C mylcd(0x27, 16, 2);  

// Define fan pin 1
// Define fan pin 2
// Define the yellow LED pin to 12
#define fanPin1 19  
#define fanPin2 18  
#define led_y 12  

void setup() {
  // Start serial communication at 115200 baud
  // Initialize the LCD
  // Turn on the LCD backlight
  // Set the yellow LED pin as output
  // Set fan pin 1 as output
  // Set fan pin 2 as output
  Serial.begin(115200);  
  mylcd.init();  
  mylcd.backlight();  
  pinMode(led_y, OUTPUT);  
  pinMode(fanPin1, OUTPUT);  
  pinMode(fanPin2, OUTPUT);  
  
  // Connect to the specified WiFi network
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED) {
    // Wait for 500ms before checking the connection status again
    // Print a dot to indicate an ongoing connection attempt
    delay(500);  
    Serial.print(".");  
}
  // Print a newline character after connection is established
  // Print the SSID of the connected network
  // Print the IP address assigned to the ESP32
  // Start the TCP server
  // Register the service with MDNS
  // Set cursor to the first row, first column
  // Print "ip:" on the LCD
  // Set cursor to the second row, first column
  // Display the IP address on the LCD
  Serial.println("");  
  Serial.print("Connected to ");
  Serial.println(ssid);  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  
  server.begin();  
  Serial.println("TCP server started");
  MDNS.addService("http", "tcp", 80);  
  mylcd.setCursor(0, 0);  
  mylcd.print("ip:");  
  mylcd.setCursor(0, 1);  
  mylcd.print(WiFi.localIP());  
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();  
  if (!client) {
  // If no client is connected, return to the top of the loop
  return;  
}

  while (client.connected() && !client.available()) {
  // Wait for the client to send data
  delay(1);  
}

  // Read the request string until the carriage return character
  // Find the first space in the request
  // Find the second space in the request
  String req = client.readStringUntil('\r');  
  int addr_start = req.indexOf(' ');  
  int addr_end = req.indexOf(' ', addr_start + 1);  

  if (addr_start == -1 || addr_end == -1) {
  Serial.print("Invalid request: ");
  // If the request is invalid, print the request
  Serial.println(req);  
  return;
}

  // Extract the requested path from the request
  // Store the requested item in the 'item' variable
  // Print the requested item
  req = req.substring(addr_start + 1, addr_end);  
  item = req;  
  Serial.println(item);  

  // Initialize a string to hold the response
  String s;  
  if (req == "/") { 
  // If the requested path is the root
  // Get the local IP address
  // Convert the IP address to a string
  // Start the HTTP response
  // Append the IP address to the response
  // End the HTML content
  // Print a message indicating that a 200 OK response is being sent
  // Send the response to the client
  IPAddress ip = WiFi.localIP();  
  String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);  
  s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>Hello from ESP32 at ";  
  s += ipStr;  
  s += "</html>\r\n\r\n";  
  Serial.println("Sending 200");  
  client.println(s);  
}

  // If the requested path is "/led/on"
  if (req == "/led/on") {  
  // Send a response to turn on the LED
  // Turn on the yellow LED
  client.println("turn on the LED");  
  digitalWrite(led_y, HIGH);  
}
  // If the requested path is "/led/off"
  if (req == "/led/off") {  
  // Send a response to turn off the LED
  // Turn off the yellow LED
  client.println("turn off the LED");  
  digitalWrite(led_y, LOW);  
}
  // If the requested path is "/fan/on"
  if (req == "/fan/on") {  
  // Send a response to turn on the fan
  // Set fan pin 1 to LOW
  // Set fan speed to 180
  client.println("turn on the fan");  
  digitalWrite(fanPin1, LOW);  
  analogWrite(fanPin2, 180);  
}
  // If the requested path is "/fan/off"
  if (req == "/fan/off") {  
  // Send a response to turn off the fan
  // Set fan pin 1 to LOW
  // Set fan speed to 0
  client.println("turn off the fan");  
  digitalWrite(fanPin1, LOW);  
  analogWrite(fanPin2, 0);  
}

  client.stop();  // Close the connection
}
