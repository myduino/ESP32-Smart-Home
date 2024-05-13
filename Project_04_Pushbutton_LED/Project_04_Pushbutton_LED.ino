// Define the pin for the Button as 16
// Define the pin for the LED as 12
#define btn1 16
#define led 12

//Used to count the clicked button times 
//it will start count from 0 when the button is clicked
int btn_count = 0; 

// The setup function to run each code once
// from top to bottom within the setup function,
// once executed last code it exits the
// setup function, and continue to function loop
void setup() {
  // Initialize Serial communication with baud rate 9600
  Serial.begin(9600);
  // Set the pin mode for the button as INPUT
  // Set the pin mode for the LED as OUTPUT
  pinMode(btn1, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  // Read the state of the button
  boolean btn1_val = digitalRead(btn1);
  
    //If the button is pressed
    if(btn1_val == 0) {
    //Delay 10ms to eliminate button jitter
    delay(10);  
      //Make sure the button is pressed again 
      if(btn1_val == 0) {
      boolean btn_state = 1;
      //Loop indefinitely until the button is released
      while(btn_state == 1){
      boolean btn_val = digitalRead(btn1);
       
        //If the button is released
        if(btn_val == 1) {
        //Automatically increments by 1, account the clicked button times
        btn_count++;    
        Serial.println(btn_count);
        //The button is released and exits the loop
        btn_state = 0;  
        }
      }
    }

    //Take the remainder of the value, you will get 0 or 1
    boolean value = btn_count % 2; 
    if(value == 1){

    // Control the led pin output signal
    // State HIGH = 5V, result LED OFF
    digitalWrite(led, HIGH);
    }
    else{
    // State LOW = 0V, result LED ON
    digitalWrite(led, LOW);
    }
  }
}                                                                                                                                                            
