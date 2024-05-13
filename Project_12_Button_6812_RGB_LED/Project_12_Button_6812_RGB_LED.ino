// Define the pins for the buttons
#define btn1 16
#define btn2 27

// Include the NeoPixel library
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
// Required for 16 MHz Adafruit Trinket
#include <avr/power.h> 
#endif

// Define the pin connected to the NeoPixels
// Define the number of NeoPixels
#define LED_PIN 26
#define LED_COUNT 4

// Declare the NeoPixel strip object
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Variable to count button presses
int btn_count = 0; 

// Setup function
void setup() {
  // Start serial communication
  // Set btn1 pin as INPUT
  // Set btn2 pin as INPUT
  Serial.begin(9600); 
  pinMode(btn1, INPUT); 
  pinMode(btn2, INPUT); 

// Support for the Adafruit Trinket 5V 16 MHz
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
clock_prescale_set(clock_div_1);
#endif

  // Initialize the NeoPixel strip
  // Turn off all pixels
  // Set brightness
  strip.begin();          
  strip.show();            
  strip.setBrightness(50); 
}

// Loop function
void loop() {
  // Read the state of the buttons
  boolean btn1_val = digitalRead(btn1);
  boolean btn2_val = digitalRead(btn2);

      // Check if btn1 is pressed
      if (btn1_val == LOW) {
      // Delay to debounce the button
      delay(10); 
      if (digitalRead(btn1) == LOW) {
      // Increment the button count and ensure it 
      // doesn't exceed the maximum value
      btn_count--;
      if (btn_count <= 0) {
        btn_count = 0;
      }
      // Print the button count to serial monitor
      // Wait until btn1 is released
      Serial.println(btn_count); 
      while (digitalRead(btn1) == LOW); 
    }
  }

      // Check if btn2 is pressed
      if (btn2_val == LOW) {
      // Delay to debounce the button
      delay(10); 
      if (digitalRead(btn2) == LOW) {
      // Increment the button count and ensure it 
      // doesn't exceed the maximum value
      btn_count++;
      if (btn_count >= 6) {
        btn_count = 6;
      }

      // Print the button count to serial monitor
      // Wait until btn2 is released
      Serial.println(btn_count); 
      while (digitalRead(btn2) == LOW); 
    }
  }

    // Set the NeoPixel color based on the button count
    switch (btn_count) {
    case 0: colorWipe(strip.Color(0, 0, 0), 50); break;
    case 1: colorWipe(strip.Color(255, 0, 0), 50); break;
    case 2: colorWipe(strip.Color(0, 255, 0), 50); break;
    case 3: colorWipe(strip.Color(0, 0, 255), 50); break;
    case 4: colorWipe(strip.Color(255, 255, 0), 50); break;
    case 5: colorWipe(strip.Color(255, 0, 255), 50); break;
    case 6: colorWipe(strip.Color(255, 255, 255), 50); break;
  }
}

// Function to fill the NeoPixel strip with a specific color
void colorWipe(uint32_t color, int wait) {
for (int i = 0; i < strip.numPixels(); i++) {
    // Set pixel color
    // Update strip
    // Pause
    strip.setPixelColor(i, color); 
    strip.show();                  
    delay(wait);                   
  }
}
