#define led 12

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  // For loop statement increments the value of
  // brightness variable from 0 to 255, by +1 and
  // once the value reached 255 it exits the loop
  for (int brightness = 0; brightness < 255; brightness++) {
    // PWM output controls the brightness of the LED
    // based on the value of the brightness variable
    analogWrite(led, brightness);
    delay(3);
  }
  
  // For loop statement decrements the value of
  // brightness variable from 255 until 0, by -1 and
  // once the value reached 0 it exits the loop
  for (int brightness = 255; brightness > 0; brightness--) {
    analogWrite(led, brightness);
    delay(3);
  }
}