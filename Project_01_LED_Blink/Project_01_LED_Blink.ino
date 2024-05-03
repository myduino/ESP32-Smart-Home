// Define the led pin to 12
#define led 13

void setup() {
  // Set the led pin mode as output
  pinMode(led, OUTPUT);
}

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
