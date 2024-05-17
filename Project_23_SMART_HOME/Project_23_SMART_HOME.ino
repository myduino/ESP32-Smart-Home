// Please install all these library that has been used in this file
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiClient.h>
#include <Adafruit_NeoPixel.h>
// Define the led pin
#define LED_PIN 26
#define LED_COUNT 4
// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Global variable to store the item requested
String item = "0";
// WiFi credentials (Insert WiFi ssid and WiFi password)
const char* ssid = "myinvententerprise";
const char* password = "04222682";
// Create a WiFiServer object to listen on port 80
WiFiServer server(80);

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Create an instance of the LCD object with 
// I2C address 0x27 and size 16x2
LiquidCrystal_I2C mylcd(0x27,16,2);
#include "xht11.h"
xht11 xht(17);
// #include <ESP32_Servo.h>
// Servo Wservo;
// Servo Dservo;
#include <ESP32Tone.h>
#define buzzer_pin 25
// #define windowServo 5
// #define doorServo 13
#define waterPin 34
#define fanPin1 19
#define fanPin2 18
#define led 12  //Define the led pin to 12

#define waterPin 34
#define gasPin 23
#define pyroelectric 14

// Only the first 32 bits of data are received, not the parity bits
unsigned char dht[4] = {0, 0, 0, 0};

//Servo channel
int channel_PWM = 13;
int channel_PWM2 = 10;
int freq_PWM = 50; 
int resolution_PWM = 10;
const int PWM_Pin1 = 5;
const int PWM_Pin2 = 13;

// The setup function to run each code once
// from top to bottom within the setup function,
// once executed last code it exits the
// setup function, and continue to function loop
void setup() {
  // Initialize serial communication at 115200 baud rate
  Serial.begin(115200);
  // Initialize the LCD
  // Turn on the LCD backlight
  mylcd.init();
  mylcd.backlight();
  // Set the LED and fan pins as outputs
  pinMode(led_y, OUTPUT);
  pinMode(fanPin1, OUTPUT);
  pinMode(fanPin2, OUTPUT);
  // Set the frequency of LEDC channel 1 to 1200 and PWM resolution to 8, 
  // that is duty cycle to 256.
  // Bind the LEDC channel 1 to the specified left motor pin GPIO26 for output.  
  ledcSetup(5, 1200, 8);  
  ledcAttachPin(fanPin2, 5);  
  pinMode(waterPin, INPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(gasPin, INPUT);
  pinMode(pyroelectric, INPUT);
  //  Set servo channel and frequency as well as PWM resolution.
  ledcSetup(channel_PWM, freq_PWM, resolution_PWM); 
  ledcSetup(channel_PWM2, freq_PWM, resolution_PWM);
  //  Binds the LEDC channel to the specified IO port for output
  //  Binds the LEDC channel to the specified IO port for output
  ledcAttachPin(PWM_Pin1, channel_PWM);  
  ledcAttachPin(PWM_Pin2, channel_PWM2);  

//  Wservo.attach(windowServo);
//  Dservo.attach(doorServo);
//  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
//  clock_prescale_set(clock_div_1);
//  #endif
//  INITIALIZE NeoPixel strip object (REQUIRED)
//  Turn OFF all pixels ASAP
//  Set BRIGHTNESS to about 1/5 (max = 255)
//  strip.begin();           
//  strip.show();            
//  strip.setBrightness(50); 
  
  // Begin WiFi connection using the provided SSID and password
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}
  // Once connected, print the network details
  // Newline for formatting
  // Print SSID of the network
  // Print IP address assigned to ESP32
  // Start the TCP server
  // Register the service with MDNS
  // Display the IP address on the LCD
  // Set cursor to first row, first column
  // Print "ip:" on LCD
  // Set cursor to second row, first column
  // Print the IP address on the LCD
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
  // LCD displays ip adress
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
  while(client.connected() && !client.available()){
      delay(1);
  }
  // Read the request from the client until a 
  // carriage return ('\r') character is encountered
  // Extract the requested path from the HTTP request
  // Find the first space
  // Find the second space
  String req = client.readStringUntil('\r');
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
  item=req;
  Serial.println(item);
  // Prepare the response based on the requested path
  String s;
  // Get the local IP address
  // Convert IP address to string
  // Append IP address to response
  // Log sending 200 OK status
  // Send the response
  if (req == "/")  
  {
      IPAddress ip = WiFi.localIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>ESP32 ip:";
      s += ipStr;
      s += "</html>\r\n\r\n";
      Serial.println("Sending 200");
      // Send the string S, then you can read the information when visiting the 
      // address of E smart home using the browser.
      client.println(s);  
  }
  // Check if the request is to turn on the LED
  if(req == "/led/on") // Browser accesses address ip address/led/on
  {
    // Send response to client
    // Turn on the LED
    client.println("turn on the LED");
    digitalWrite(led, HIGH);
  }
  // Check if the request is to turn off the LED
  if(req == "/led/off") // Browser accesses address ip address/led/off
  {
    // Send response to client
    // Turn off the LED
    client.println("turn off the LED");
    digitalWrite(led, LOW);
  }
  if(req == "/window/on")
  {
    client.println("open the window");
    // The high level of 20ms is about 2.5ms, that is, 2.5/20*1024, 
    // at this time, the servo angle is 180°.  
    ledcWrite(channel_PWM, 100);  
    //Wservo.write(175);
  }
  if(req == "/window/off")
  {
    // The high level of 20ms is about 0.5ms，that is, 0.5/20*1024，
    // at this time, the servo angle is 0°.
    client.println("close the window");
    ledcWrite(channel_PWM, 60);  
    //Wservo.write(0);
  }

  // If request is to turn on music
  if(req == "/music/on") 
{
  // No action taken in this block
}
// If request is to turn off music
if(req == "/music/off") 
{
  // Send message to client indicating music is playing
  // Play birthday tune
  // Stop playing buzzer tone
  client.println("play music"); 
  birthday(); 
  noTone(buzzer_pin,0); 
}
// If request is to turn on buzzer
if(req == "/buz/on") 
{
  // Send message to client indicating buzzer is on
  // Play buzzer tone at 392 Hz for 250 milliseconds
  // Print message to serial monitor
  client.println("buzzer"); 
  tone(buzzer_pin,392,250,0); 
  Serial.println("1"); 
}
  // If request is to turn off buzzer
if(req == "/buz/off") 
{
  // Send message to client indicating buzzer is off
  // Stop playing buzzer tone
  client.println("off"); 
  noTone(buzzer_pin,0); 
}

  // If request is to open the door
  if(req == "/door/on") 
{
  // Send message to client indicating door is opening
  // Set PWM value to open the door (assumed)
  // Dservo.write(180); // Uncomment this line if using a servo to open the door
  client.println("open the door"); 
  ledcWrite(channel_PWM2, 120); 
  
}
  // If request is to close the door
if(req == "/door/off") 
{
  // Send message to client indicating door is closing
  // Set PWM value to close the door (assumed)
  // Dservo.write(0); // Uncomment this line if using a servo to close the door
  client.println("close the door"); 
  ledcWrite(channel_PWM2, 20); 
  
}
  // If request is to turn on the fan
if(req == "/fan/on") 
{
  // Send message to client indicating fan is turning on
  // Set fan PWM to low (assumed)
  // Set PWM value for fan to 100
  client.println("turn on the fan"); 
  digitalWrite(fanPin1, LOW); 
  ledcWrite(5, 100); 
}
// If request is to turn off the fan
if(req == "/fan/off") 
{
  // Send message to client indicating fan is turning off
  // Set fan PWM to low (assumed)
  // Set PWM value for fan to 0 to turn it off
  client.println("turn off the fan"); 
  digitalWrite(fanPin1, LOW); 
  ledcWrite(5, 0); 
}

  // If request is to turn on red color
  if(req == "/red/on") 
{
  // Send message to client indicating red is turning on
  // Set color to red with a delay of 50ms
  client.println("red on"); 
  colorWipe(strip.Color(255,   0,   0), 50); 
}
  // If request is to turn off red color
if(req == "/red/off") 
{
  // Send message to client indicating red is turning off
  // Set color to off with a delay of 50ms
  client.println("red off"); 
  colorWipe(strip.Color(0,   0,   0), 50); 
}

// Similar blocks for other colors
// Orange
if(req == "/orange/on")
{
  client.println("orange on");
  colorWipe(strip.Color(200,   100,   0), 50);
}
if(req == "/orange/off")
{
  client.println("orange off");
  colorWipe(strip.Color(0,   0,   0), 50);
}

// Yellow
if(req == "/yellow/on")
{
  client.println("yellow on");
  colorWipe(strip.Color(200,   200,   0), 50);
}
if(req == "/yellow/off")
{
  client.println("yellow off");
  colorWipe(strip.Color(0,   0,   0), 50);
}

// Green
if(req == "/green/on")
{
  client.println("green on");
  colorWipe(strip.Color(0,   255,   0), 50);
}
if(req == "/green/off")
{
  client.println("green off");
  colorWipe(strip.Color(0,   0,   0), 50);
}

// Cyan
if(req == "/cyan/on")
{
  client.println("cyan on");
  colorWipe(strip.Color(0,   100,   255), 50);
}
if(req == "/cyan/off")
{
  client.println("cyan off");
  colorWipe(strip.Color(0,   0,   0), 50);
}

// Blue
if(req == "/blue/on")
{
  client.println("blue on");
  colorWipe(strip.Color(0,   0,   255), 50);
}
if(req == "/blue/off")
{
  client.println("blue off");
  colorWipe(strip.Color(0,   0,   0), 50);
}

// Purple
if(req == "/purple/on")
{
  client.println("purple on");
  colorWipe(strip.Color(100,   0,   255), 50);
}
if(req == "/purple/off")
{
  client.println("purple off");
  colorWipe(strip.Color(0,   0,   0), 50);
}

// White
if(req == "/white/on")
{
  client.println("white on");
  colorWipe(strip.Color(255,   255,   255), 50);
}
if(req == "/white/off")
{
  client.println("white off");
  colorWipe(strip.Color(0,   0,   0), 50);
}

  // If request is to turn on special effect 1
  if(req == "/sfx1/on") 
{
  // Send message to client indicating special effect 1 is turning on
  // Activate rainbow effect with a delay of 10ms between frames
  client.println("sfx1 on"); 
  rainbow(10); 
}
  // If request is to turn off special effect 1
  if(req == "/sfx1/off") 
{
  // Send message to client indicating special effect 1 is turning off
  // Turn off LEDs by setting color to black with a delay of 50ms
  client.println("sfx1 off"); 
  colorWipe(strip.Color(0,   0,   0), 50); 
}

  // Similar blocks for special effect 2
  // If request is to turn on special effect 2
  if(req == "/sfx2/on") 
{
  // Send message to client indicating special effect 2 is turning on
  // Activate theater chase rainbow effect with a delay of 50ms between frames
  client.println("sfx2 on"); 
  theaterChaseRainbow(50); 
}
  // If request is to turn off special effect 2
  if(req == "/sfx2/off") 
{
  // Send message to client indicating special effect 2 is turning off
  // Turn off LEDs by setting color to black with a delay of 50ms
  client.println("sfx2 off"); 
  colorWipe(strip.Color(0,   0,   0), 50); 
}
  // If request is to turn on rain sensor
  if(req == "/rain/on") 
{
  // Read analog value from rain sensor
  // Send rain sensor value to client
  int rainVal = analogRead(waterPin); 
  client.println(rainVal); 
}
  // If request is to turn off rain sensor
  if(req == "/rain/off") 
{
  // Send message to client indicating rain sensor is off
  client.println("off"); 
}

  // Gas sensor control
  // If request is to turn on gas sensor
  if(req == "/gas/on") 
{
  // Read analog value from gas sensor
  // If gas level is low
  boolean gasVal = analogRead(gasPin); 
  if(gasVal == 0) 
  {
    // Send safety message to client
    client.println("safety"); 
  }
  // If gas level is high
  else 
  {
    // Send dangerous message to client 
    client.println("dangerous"); 
  }
}
  // If request is to turn off gas sensor
  if(req == "/gas/off") 
{
  // Send message to client indicating gas sensor is off
  client.println("off"); 
}

  // Body sensor control
  // If request is to turn on body sensor
  if(req == "/body/on") 
{
  // Read digital value from body sensor
  // If body is detected
  boolean pyroelectric_val = digitalRead(pyroelectric); 
  if(pyroelectric_val == 1) 
  {
    // Send message to client indicating someone is detected
    client.println("someone"); 
  }
  // If no body is detected
  else 
  {
    // Send message to client indicating no one is detected
    client.println("no one"); 
  }
}
  // If request is to turn off body sensor
  if(req == "/body/off") 
{
  // Send message to client indicating body sensor is off
  client.println("off"); 
}

  if(req == "/temp/on")
  {
      // Returns true when checked correctly
      if (xht.receive(dht)) { 
      Serial.print("Temp:");
      // The integral part of temperature, DHT [3] is the fractional part
      Serial.print(dht[2]); 
      Serial.println("C");
      delay(200);
    } else {  
      // Read error
      Serial.println("sensor error");
    }
    client.println(dht[2]);
    delay(1000);  // It takes 1000ms to wait for the device to read
  }
  if(req == "/temp/off")
  {
    client.println("off");
  }
  if(req == "/humidity/on")
  {
      // Returns true when checked correctly
      if (xht.receive(dht)) { 
      Serial.print("Temp:");
      // The integral part of temperature, DHT [3] is the fractional part
      Serial.print(dht[0]); 
      Serial.println("%");
      delay(200);
    } else {    //Read error
      Serial.println("sensor error");
    }
    client.println(dht[0]);
    // It takes 1000ms to wait for the device to read
    delay(1000);  
  }
  if(req == "/humidity/off")
  {
    client.println("off");
  }

  
  // client.stop();
} 


void birthday()
{
  tone(buzzer_pin,294,250,0);  // The four parameters are pin, frequency, delay and channel 
  tone(buzzer_pin,440,250,0);
  tone(buzzer_pin,392,250,0);
  tone(buzzer_pin,532,250,0);
  tone(buzzer_pin,494,250,0);
  tone(buzzer_pin,392,250,0);
  tone(buzzer_pin,440,250,0);
  tone(buzzer_pin,392,250,0);
  tone(buzzer_pin,587,250,0);
  tone(buzzer_pin,532,250,0);
  tone(buzzer_pin,392,250,0);
  tone(buzzer_pin,784,250,0);
  tone(buzzer_pin,659,250,0);
  tone(buzzer_pin,532,250,0);
  tone(buzzer_pin,494,250,0);
  tone(buzzer_pin,440,250,0);
  tone(buzzer_pin,698,250,0);
  tone(buzzer_pin,659,250,0);
  tone(buzzer_pin,532,250,0);
  tone(buzzer_pin,587,250,0);
  tone(buzzer_pin,532,500,0);
  noTone(buzzer_pin,0);  //关闭
}

void colorWipe(uint32_t color, int wait) {
  //  For each pixel in strip...
  //  Set pixel color (in RAM)
  //  Update strip to match
  //  Pause for a moment
  for(int i=0; i<strip.numPixels(); i++) { 
    strip.setPixelColor(i, color);         
    strip.show();                          
    delay(wait);                           
  }
}

// Rainbow cycle along whole strip. 
// Pass delay time (in ms) between frames.
void rainbow(int wait) {
    for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) {
    int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
  }
  // Update strip with new contents
  // Pause for a moment
    strip.show(); 
    delay(wait);  
}
}

// Rainbow-enhanced theater marquee. 
// Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  // First pixel starts at red (hue 0)
  // Repeat 30 times...
  // 'b' counts from 0 to 2...
  // Set all pixels in RAM to 0 (off)
  int firstPixelHue = 0;     
    for(int a=0; a<30; a++) {  
    for(int b=0; b<3; b++) { 
      strip.clear();         
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        int hue = firstPixelHue + c * 65536L / strip.numPixels();
        // hue -> RGB
        // Set pixel 'c' to value 'color'
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); 
        strip.setPixelColor(c, color); 
      }
      // Update strip with new contents
      // Pause for a moment
      // One cycle of color wheel over 90 frames
      strip.show();                
      delay(wait);                 
      firstPixelHue += 65536 / 90; 
    }
  }
}
