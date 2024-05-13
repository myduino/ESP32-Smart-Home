// Define the pin for the Pyroelectric Sensor as pin 14
#define pyroelectric 14

// The setup function to run each code once
// from top to bottom within the setup function,
// once executed last code it exits the
// setup function, and continue to function loop
void setup() {
  // Initialize Serial communication with baud rate 9600
  Serial.begin(9600);
  // Set the pin mode for the Pyroelectric Sensor as INPUT
  pinMode(pyroelectric, INPUT);
}

void loop() {
  // Read the state of the Pyroelectric Sensor
  boolean pyroelectric_val = digitalRead(pyroelectric);
  // Print a message to Serial Monitor indicating the 
  // current state of the Pyroelectric Sensor
  Serial.print("Pyroelectric sensor value: ");
  Serial.println(pyroelectric_val);
  // Delay to stabilize readings
  delay(50);
}
