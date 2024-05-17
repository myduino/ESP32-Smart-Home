// please install all the library that been used in this file
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
// Required for 16 MHz Adafruit Trinket
#include <avr/power.h> 
#endif

// Define the pin connected to the NeoPixels
// Define the number of NeoPixels
#define LED_PIN    26
#define LED_COUNT 4

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// The setup function to run each code once
// from top to bottom within the setup function,
// once executed last code it exits the
// setup function, and continue to function loop
void setup() {
// These lines are specifically to support the 
// Adafruit Trinket 5V 16 MHz.
// Any other board, you can remove this part 
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
clock_prescale_set(clock_div_1);
#endif
// END of Trinket-specific code.

  // INITIALIZE NeoPixel strip object (REQUIRED)
  // Turn OFF all pixels ASAP
  // Set BRIGHTNESS to about 1/5 (max = 255)
  strip.begin();           
  strip.show();            
  strip.setBrightness(50); 
}

// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {
  // Fill along the length of the strip in various colors...
  colorWipe(strip.Color(255,   0,   0), 50); // Red
  colorWipe(strip.Color(  0, 255,   0), 50); // Green
  colorWipe(strip.Color(  0,   0, 255), 50); // Blue

  // Do a theater marquee effect in various colors...
  theaterChase(strip.Color(127, 127, 127), 50); // White, half brightness
  theaterChase(strip.Color(127,   0,   0), 50); // Red, half brightness
  theaterChase(strip.Color(  0,   0, 127), 50); // Blue, half brightness

  // Flowing rainbow cycle along the whole strip
  rainbow(10);          
  // Rainbow-enhanced theaterChase variant   
  theaterChaseRainbow(50); 
}

// Some functions of our own for creating animated effects -----------------
// strip.Color(red, green, blue) as shown in the loop() function above),
void colorWipe(uint32_t color, int wait) {
  //  For each pixel in strip...
  //  Set pixel's color (in RAM)
  //  Update strip to match
  //  Pause for a moment
  for(int i=0; i<strip.numPixels(); i++) { 
    strip.setPixelColor(i, color);         
    strip.show();                          
    delay(wait);                           
  }
}

// Theater-marquee-style chasing lights. 
// Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), 
// and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {

    // Repeat 10 times...
    // 'b' counts from 0 to 2...
    // Set all pixels in RAM to 0 (off)
    for(int a=0; a<10; a++) {  
    for(int b=0; b<3; b++) { 
    strip.clear();         
    // 'c' counts up from 'b' to end 
    // of strip in steps of 3...
    for(int c=b; c<strip.numPixels(); c += 3) {
    // Set pixel 'c' to value 'color'  
    strip.setPixelColor(c, color); 
}
    // Update strip with new contents
    // Pause for a moment
    strip.show(); 
    delay(wait);  
    }
  }
}

// Rainbow cycle along whole strip. 
// Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
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
        // hue of pixel 'c' is offset by an amount to make one full
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
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
