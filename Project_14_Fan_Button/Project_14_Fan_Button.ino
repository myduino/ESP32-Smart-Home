// Define the pins for the fan motors and buttons
// Pin for controlling the first fan
// Pin for controlling the second fan
// Pin for the first button
// Pin for the second button
#define fanPin1 19  
#define fanPin2 18  
#define btn1 16     
#define btn2 27     

// Used to count the clicked button times for btn1
// Used to count the clicked button times for btn2
// Define the initial speed variable
int btn_count = 0;    
int btn_count2 = 0;   
int speed_val = 130;  

// Setup function
// Initialize serial communication
// Set btn1 pin as input
// Set btn2 pin as input
// Set fanPin1 as output for controlling fan speed
// Set fanPin2 as output for controlling fan speed
void setup() {
  Serial.begin(9600);    
  pinMode(btn1, INPUT);  
  pinMode(btn2, INPUT);  
  pinMode(fanPin1, OUTPUT);  
  pinMode(fanPin2, OUTPUT);  
}

// Loop function
void loop() {
  // Check if btn1 is pressed
  boolean btn1_val = digitalRead(btn1);
    // If btn1 is pressed
    if (btn1_val == 0) {  
    delay(10);          
    // Check if btn1 is still pressed
    // Set btn_state to true
    // Loop indefinitely until btn1 is released
    // If btn1 is released
    // Increment btn_count to count the clicked button times
    // Print btn_count
    // Exit the loop
    if (btn1_val == 0) {  
    boolean btn_state = 1;  
    while (btn_state == 1) {  
    boolean btn_val = digitalRead(btn1);
    if (btn_val == 1)  
    btn_count++;     
    Serial.println(btn_count);  
    btn_state = 0;  
    }
  }
}
  
  // Determine fan operation based on btn_count
  // Check if btn_count is odd or even
  // If btn_count is odd
  // Turn off fanPin1
  // Set fanPin2 to desired speed
  boolean value = btn_count % 2;  
  while (value == 1) {  
  digitalWrite(fanPin1, LOW);  
  analogWrite(fanPin2, speed_val);  

    // Check if btn2 is pressed
    // If btn2 is pressed
    // Debounce delay
    // Check if btn2 is still pressed
    // Set btn_state2 to true
    // Loop indefinitely until btn2 is released
    // If btn2 is released
    // Increment btn_count2 to count the clicked button times
    // If btn_count2 exceeds 3
    // Reset btn_count2 to 1
    boolean btn2_val = digitalRead(btn2);
    if (btn2_val == 0) {  
    delay(10);  
    if (btn2_val == 0) {  
    boolean btn_state2 = 1;  
    while (btn_state2 == 1) {  
    boolean btn2_val = digitalRead(btn2);
    if (btn2_val == 1) {  
    btn_count2++;  
    if (btn_count2 > 3) {  
    btn_count2 = 1;  
}
      // Adjust the fan speed based on btn_count2
      switch (btn_count2) {
      case 1:
        // Set fan speed to 130
        // Print the speed value
        speed_val = 130;  
        Serial.println(speed_val);  
        break;
      case 2:
        // Set fan speed to 180
        // Print the speed value
        speed_val = 180;  
        Serial.println(speed_val);  
        break;
      case 3:
        // Set fan speed to 230
        // Print the speed value
        speed_val = 230;  
        Serial.println(speed_val);  
        break;
        }
        // Exit the loop
        btn_state2 = 0;  
         }
       }
    }
  }
    
    // Check if btn1 is pressed to stop the fans
    // If btn1 is pressed
    // Turn off fanPin1
    // Set fanPin2 to 0 (stop fan)
    boolean btn1_val = digitalRead(btn1);
    if (btn1_val == 0) {  
    digitalWrite(fanPin1, LOW);  
    analogWrite(fanPin2, 0);  
    // Exit the loop
    value = 0;  
    }
  }
}
