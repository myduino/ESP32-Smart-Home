// Please install all these library that has been used in this file
#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiClient.h>

// Initialize a string to store the requested item
// WiFi SSID
// WiFi password
// Create a WiFiServer object on port 80
String item = "0";  
const char* ssid = "myinvententerprise";  
const char* password = "04222682";  
WiFiServer server(80);  

// The setup function to run each code once
// from top to bottom within the setup function,
// once executed last code it exits the
// setup function, and continue to function loop
void setup() {
    // Start serial communication at 115200 baud
    // Connect to the specified WiFi network
    // Wait for 500ms before checking the connection status again
    // Print a dot to indicate an ongoing connection attempt
    Serial.begin(115200);  
    WiFi.begin(ssid, password);  
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);  
    Serial.print(".");  
}
  // Print a newline character after connection is established
  // Print the SSID of the connected network
  // Print the IP address assigned to the ESP32
  // Start the TCP server
  // Register the service with MDNS
  Serial.println("");  
  Serial.print("Connected to ");
  Serial.println(ssid);  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  
  server.begin();  
  Serial.println("TCP server started");
  MDNS.addService("http", "tcp", 80);  
}

void loop() {
  Serial.print("Connected to ");
  // Print the SSID of the connected network
  // Print the IP address assigned to the ESP32
  // Delay for 200ms
  Serial.println(ssid);  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  
  delay(200);  
  
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
  // If the requested path is the root
  // Get the local IP address
  String s;  
  if (req == "/") {  
    IPAddress ip = WiFi.localIP();  

    // Convert the IP address to a string
    // Start the HTTP response
    // Append the IP address to the response
    // End the HTML content
    // Print a message indicating that a 200 OK response is being sent
    // Send the response to the client
    // Close the connection
    String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);  
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>Hello from ESP32 at ";  
    s += ipStr;  
    s += "</html>\r\n\r\n";  
    Serial.println("Sending 200");  
    client.println(s);  
    client.stop();  
  }
}
