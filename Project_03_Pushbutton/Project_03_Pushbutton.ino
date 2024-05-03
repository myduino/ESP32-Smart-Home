// Define the Pushbutton 1 pin to 16
// Define the Pushbutton 2 pin to 27
#define pb1 16
#define pb2 27

void setup() {
  // Initialized hardware Serial communication
  // with baud rate 115.2 kbps
  Serial.begin(115200);
  
  // Set the pb1 and pb2 pin mode as INPUT
  pinMode(pb1, INPUT);
  pinMode(pb2, INPUT);
}

void loop() {
  // Read the pb1 and pb2 pin state
  // the state value stored in
  // the variable of pb1State and pb2State
  // with boolean data type.
  boolean pb1State = digitalRead(pb1);
  boolean pb2State = digitalRead(pb2);

  // Send the pb1State value to
  // Serial Monitor, with the
  // line new command
  Serial.print("Pushbutton 1: ");
  Serial.println(pb1State);

  // Send the pb2State value to
  // Serial Monitor, with the
  // line new command
  Serial.print("Pushbutton 2: ");
  Serial.println(pb2State);

  delay(100);
}
