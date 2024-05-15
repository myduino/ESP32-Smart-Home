// Please install all these library that has been used in this file
#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiClient.h>

// Global variable to store the item requested
String item = "0";

// WiFi credentials (insert WiFi ssid and WiFi password)
const char* ssid = "myinvententerprise";
const char* password = "04222682";

// Create a WiFiServer object to listen on port 80
WiFiServer server(80);

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Create an instance of the LCD object with 
// I2C address 0x27 and size 16x2
LiquidCrystal_I2C mylcd(0x27, 16, 2);

// Define fan pin 1
// Define fan pin 2
// Define the LED pin to 12
#define fanPin1 19
#define fanPin2 18
#define led 12

void setup() {
  // Initialize serial communication at 115200 baud rate
  Serial.begin(115200);

  // Initialize the LCD
  // Turn on the LCD backlight
  mylcd.init();
  mylcd.backlight();

  // Set the LED and fan pins as outputs
  pinMode(led, OUTPUT);
  pinMode(fanPin1, OUTPUT);
  pinMode(fanPin2, OUTPUT);
  
  // Begin WiFi connection using the provided SSID and password
  WiFi.begin(ssid, password);

  // Wait until the ESP32 is connected to the WiFi network
  while (WiFi.status() != WL_CONNECTED) {
  // Wait for 500 milliseconds
  // Print a dot to indicate connection attempt
  delay(500);  
  Serial.print(".");  
}

  // Once connected, print the network details
  // Newline for formatting
  // Print SSID of the network
  // Print IP address assigned to ESP32
  Serial.println("");  
  Serial.print("Connected to ");
  Serial.println(ssid);  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  

  // Start the TCP server
  server.begin();
  Serial.println("TCP server started");

  // Register the service with MDNS
  MDNS.addService("http", "tcp", 80);

  // Display the IP address on the LCD
  // Set cursor to first row, first column
  // Print "ip:" on LCD
  // Set cursor to second row, first column
  // Print the IP address on the LCD
  mylcd.setCursor(0, 0);  
  mylcd.print("ip:");  
  mylcd.setCursor(0, 1);  
  mylcd.print(WiFi.localIP());  
}

void loop() {
  // Check if a client has connected to the server
  WiFiClient client = server.available();
  if (!client) {
  // If no client is connected, exit the loop
  return;  
}

  // Wait until the client sends some data
  while(client.connected() && !client.available()) {
  delay(1);
}

  // Read the request from the client until a 
  // carriage return ('\r') character is encountered
  String req = client.readStringUntil('\r');

  // Extract the requested path from the HTTP request
  // Find the first space
  // Find the second space
  int addr_start = req.indexOf(' ');  
  int addr_end = req.indexOf(' ', addr_start + 1);  
  if (addr_start == -1 || addr_end == -1) {
  Serial.print("Invalid request: ");
  Serial.println(req);
  return;
}
  // Extract the path
  // Store the path in the 'item' variable
  // Print the path
  req = req.substring(addr_start + 1, addr_end);  
  item = req;  
  Serial.println(item);  

  // Prepare the response based on the requested path
  String s;
  // If the root path is requested
  if (req == "/") {  
  // Get the local IP address
  // Convert IP address to string
  // Append IP address to response
  // Log sending 200 OK status
  // Send the response
  IPAddress ip = WiFi.localIP();  
  String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);  
  s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>ESP32 ip:";
  s += ipStr;  
  s += "</html>\r\n\r\n";
  Serial.println("Sending 200");  
  client.println(s);  
}
  // Check if the request is to turn on the LED
  if(req == "/led/on") {
  // Send response to client
  // Turn on the LED
  client.println("turn on the LED");  
  digitalWrite(led, HIGH);  
}
  // Check if the request is to turn off the LED
  if(req == "/led/off") {
  // Send response to client
  // Turn off the LED
  client.println("turn off the LED");  
  digitalWrite(led, LOW);  
}
  // Check if the request is to turn on the fan
  if(req == "/fan/on") {
  // Send response to client
  // Set fan pin 1 to LOW (pwm = 0)
  // Set fan speed to 180 (pwm value)
  client.println("turn on the fan");  
  digitalWrite(fanPin1, LOW);  
  analogWrite(fanPin2, 180);  
}
  // Check if the request is to turn off the fan
  if(req == "/fan/off") {
  // Send response to client
  // Set fan pin 1 to LOW (pwm = 0)
  // Turn off the fan (pwm value = 0)
  client.println("turn off the fan");  
  digitalWrite(fanPin1, LOW);  
  analogWrite(fanPin2, 0);  
}
  // Close the client connection
  client.stop();
}
