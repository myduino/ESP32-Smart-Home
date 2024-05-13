// Define the frequencies of the musical notes
const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;

// Define pin assignments for buzzer and LEDs
const int buzzerPin = 25;
const int ledPin1 = 12;
const int ledPin2 = 13;

// Variable to keep track of LED blinking pattern
int counter = 0; 

void setup()
{
  // Set pin modes for buzzer and LEDs
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop()
{

  // Play the first section of the melody
  firstSection();

  // Play the second section of the melody
  secondSection();

  // Variant 1: Custom melody variation
  beep(f, 250);
  beep(gS, 500);
  beep(f, 350);
  beep(a, 125);
  beep(cH, 500);
  beep(a, 375);
  beep(cH, 125);
  beep(eH, 650);

  // Delay between melody variations
  delay(500);

  // Repeat the second section of the melody
  secondSection();

  // Variant 2: Custom melody variation
  beep(f, 250);
  beep(gS, 500);
  beep(f, 375);
  beep(cH, 125);
  beep(a, 500);
  beep(f, 375);
  beep(cH, 125);
  beep(a, 650);

  // Delay after the second melody variation
  delay(650);
}

// Function to play a note with LED blinking
void beep(int note, int duration)
{
  // Play tone on the buzzer
  tone(buzzerPin, note, duration);

  // Toggle between two LEDs based on the counter value
  if (counter % 2 == 0)
  {
    digitalWrite(ledPin1, HIGH);
    delay(duration);
    digitalWrite(ledPin1, LOW);
  }
  else
  {
    digitalWrite(ledPin2, HIGH);
    delay(duration);
    digitalWrite(ledPin2, LOW);
  }

  // Stop tone on the buzzer
  noTone(buzzerPin);

  // Delay between notes
  delay(50);

  // Increment the counter for LED blinking pattern
  counter++;
}

// Function to play the first section of the melody
void firstSection()
{
  // Play the first section of the melody
  beep(a, 500);
  beep(a, 500);
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);

  // Delay between sections
  delay(500);

  beep(eH, 500);
  beep(eH, 500);
  beep(eH, 500);
  beep(fH, 350);
  beep(cH, 150);
  beep(gS, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);

  // Delay between sections
  delay(500);
}

// Function to play the second section of the melody
void secondSection()
{
  // Play the second section of the melody
  beep(aH, 500);
  beep(a, 300);
  beep(a, 150);
  beep(aH, 500);
  beep(gSH, 325);
  beep(gH, 175);
  beep(fSH, 125);
  beep(fH, 125);
  beep(fSH, 250);

  // Delay between sections
  delay(325);

  beep(aS, 250);
  beep(dSH, 500);
  beep(dH, 325);
  beep(cSH, 175);
  beep(cH, 125);
  beep(b, 125);
  beep(cH, 250);

  // Delay between sections
  delay(350);
}
