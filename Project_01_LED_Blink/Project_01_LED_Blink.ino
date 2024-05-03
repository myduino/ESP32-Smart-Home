// Define the led pin to 12
#define led 13

// The setup function to run each code once
// from top to bottom within the setup function,
// once executed last code it exits the
// setup function, and continue to function loop
void setup() {
  // Set the led pin mode as OUTPUT
  pinMode(led, OUTPUT);
}

// The loop function to run each code repeatedly
// from top to bottom within the loop function,
// once executed last code it repeats from top again,
// there is no exits, unless there is code to
// stop the loop or no power supply to the microcontroller
void loop() {
  // Control the led pin output signal
  // State HIGH = 5V, result LED OFF
  digitalWrite(led, HIGH);
  // Wait for 0.2 seconds
  delay(200);
  // State LOW = 0V, result LED ON
  digitalWrite(led, LOW);
  // Wait for 0.2 seconds
  delay(200);
}
