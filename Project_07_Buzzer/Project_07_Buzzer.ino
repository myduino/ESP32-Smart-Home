// include ESP32Tone.h library
#include <ESP32Tone.h>

// Define the pin for the buzzer
#define buzzer_pin 25

// The setup function to run each code once
// from top to bottom within the setup function,
// once executed last code it exits the
// setup function, and continue to function loop
void setup() {
  // Set the buzzer pin mode as OUTPUT
  pinMode(buzzer_pin, OUTPUT);
  // Call the function to play the birthday melody
  birthday();
}

void loop() {
  // Since we only play the melody once in setup, 
  // the loop is left empty
}

// Function to play the birthday melody
void birthday() {
  // Each tone() function call plays a note of 
  // the birthday melody.
  // The four parameters for tone() are:
  // 1. Pin: The pin number to which the buzzer 
  // is connected
  // 2. Frequency (Hz): The frequency of the 
  // note to be played
  // 3. Duration (ms): The duration for which the 
  // note should be played
  // 4. Channel: The channel to use for playing the 
  // tone (0 is the default channel)

  // Play the birthday melody note by note
  tone(buzzer_pin, 294, 250, 0);   // G4
  tone(buzzer_pin, 440, 250, 0);   // A4
  tone(buzzer_pin, 392, 250, 0);   // G#4/Ab4
  tone(buzzer_pin, 532, 250, 0);   // C5
  tone(buzzer_pin, 494, 250, 0);   // B4
  tone(buzzer_pin, 392, 250, 0);   // G#4/Ab4
  tone(buzzer_pin, 440, 250, 0);   // A4
  tone(buzzer_pin, 392, 250, 0);   // G#4/Ab4
  tone(buzzer_pin, 587, 250, 0);   // D5
  tone(buzzer_pin, 532, 250, 0);   // C5
  tone(buzzer_pin, 392, 250, 0);   // G#4/Ab4
  tone(buzzer_pin, 784, 250, 0);   // G5
  tone(buzzer_pin, 659, 250, 0);   // E5
  tone(buzzer_pin, 532, 250, 0);   // C5
  tone(buzzer_pin, 494, 250, 0);   // B4
  tone(buzzer_pin, 440, 250, 0);   // A4
  tone(buzzer_pin, 698, 250, 0);   // F#5/Gb5
  tone(buzzer_pin, 659, 250, 0);   // E5
  tone(buzzer_pin, 532, 250, 0);   // C5
  tone(buzzer_pin, 587, 250, 0);   // D5
  tone(buzzer_pin, 532, 500, 0);   // C5 (last note, played for a longer duration)

  // After playing the melody, silence the buzzer
  // The noTone() function stops the tone being played 
  // on the specified pin and channel
  // Specify the pin and the channel to 
  // top the tone
  noTone(buzzer_pin, 0);  
}
