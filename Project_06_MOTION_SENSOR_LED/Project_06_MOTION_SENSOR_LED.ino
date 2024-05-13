// Define the pin for the Pyroelectric Sensor as pin 14
// Define the pin for the Yellow LED as pin 12
#define pyroelectric 14
#define led 12  

// The setup function to run each code once
// from top to bottom within the setup function,
// once executed last code it exits the
// setup function, and continue to function loop
void setup() {
  // Initialize Serial communication with baud rate 9600
  Serial.begin(9600);
  // Set the pin mode for the Pyroelectric Sensor as INPUT
  pinMode(pyroelectric, INPUT);
  // Set the pin mode for the Yellow LED as OUTPUT
  pinMode(led, OUTPUT);  // Set the LED pin to output mode
}

void loop() {
  // Read the state of the Pyroelectric Sensor
  boolean pyroelectric_val = digitalRead(pyroelectric);
  // Print a message to Serial Monitor indicating the 
  // current state of the Pyroelectric Sensor
  Serial.print("Pyroelectric sensor value: ");
  Serial.println(pyroelectric_val);
  // Delay to stabilize the readings
  delay(50);
  
  // Check the state of the Pyroelectric Sensor
  if (pyroelectric_val == HIGH) {
    // If sensor detects motion, turn on the Yellow LED
    digitalWrite(led, HIGH);
  } else {
    // If sensor does not detect motion, 
    // turn off the Yellow LED
    digitalWrite(led, LOW);
  }
}
