// Define the pins for the two fan motors
#define fanPin1 19
#define fanPin2 18

// Setup function
void setup() {
  // Set fanPin1 as an output pin
  // Set fanPin2 as an output pin
  pinMode(fanPin1, OUTPUT); 
  pinMode(fanPin2, OUTPUT); 
}

// Loop function
void loop() {
  // Turn off fanPin1 and 
  // set fanPin2 to 70% duty cycle (180/255)
  // Turn off fanPin1
  // Set fanPin2 to 70% duty cycle
  // Wait for 3 seconds
  digitalWrite(fanPin1, LOW);   
  analogWrite(fanPin2, 180);     
  delay(3000);                    
  
  // Turn off both fanPin1 and fanPin2
  // Turn off fanPin1
  // Turn off fanPin2
  // Wait for 1 second
  digitalWrite(fanPin1, LOW);    
  digitalWrite(fanPin2, LOW);    
  delay(1000);                    
  
  // Turn on fanPin1 and 
  // set fanPin2 to 82% duty cycle (210/255)
  // Turn on fanPin1
  // Set fanPin2 to 82% duty cycle
  // Wait for 3 seconds
  digitalWrite(fanPin1, HIGH);   
  analogWrite(fanPin2, 210);     
  delay(3000);                    
  
  // Turn off both fanPin1 and fanPin2
  // Turn off fanPin1
  // Turn off fanPin2
  // Wait for 1 second
  digitalWrite(fanPin1, LOW);    
  digitalWrite(fanPin2, LOW);    
  delay(1000);                    
}
