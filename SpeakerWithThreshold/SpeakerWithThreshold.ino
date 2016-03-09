// The calculation of the tones is made following the mathematical operation:
// PWM = 1000000 / (2 * frequency) = 1000000 * period / 2

#include <UTFT.h>

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

// Musical note frequencies
#define c4    261.63
#define db4   277.18
#define d4    293.66
#define eb4   311.13
#define e4    329.63
#define f4    349.23
#define gb4   369.99
#define g4    392.00
#define ab4   415.30
#define a4    440.00
#define bb4   466.16
#define b4    493.88
#define c5    523.25

// Speaker pin
const int speaker = 11;
// LED pins
const int LED1 = 13;
const int LED2 = 12;
// FSR pins
const int FSR1 = 1;
const int FSR2 = 2;
// LCD display
UTFT LCD(CTE32HR, 38, 39, 40, 41);

// LED intensities
int intensity1;
int intensity2;
// Intensity thresholds
int threshold1 = 45;
int threshold2 = 45;
// FSR pressed
int pressed1 = false;
int pressed2 = false;
// Counters
int counter1 = 0;
int counter2 = 0;

int PWMValues[] = {c4, db4, d4, eb4, e4, f4, gb4, g4, ab4, a4, bb4, b4, c5};

void setup() {
  // Initialize the LCD
  LCD.InitLCD();
  // Set the font
  LCD.setFont(BigFont);
  // Clear the screen
  LCD.clrScr();
  // Set the color to be red
  LCD.setColor(255, 0, 0);

  // LED output pins
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  // Read the intensity of the FSR analog inputs
  intensity1 = analogRead(FSR1);
  intensity2 = analogRead(FSR2);

  // When the first FSR is pressed, decrease the first threshold
  if (pressed1 == true) {
    threshold1 = 10;
  // When the first FSR is not pressed, increase the first threshold
  } else {
    threshold1 = 45;
  }

  // When the second FSR is pressed, decrease the second threshold
  if (pressed2 == true) {
    threshold2 = 10;
  // When the second FSR is not pressed, increase the second threshold
  } else {
    threshold2 = 45;
  }

  // Set a threshold for the first LED intensity
  if (intensity1 < threshold1) {
    intensity1 = 0;
  }

  // Set a peak for the first LED intensity
  if (intensity1 > 255) {
    intensity1 = 255;
  }

  // Set a threshold for the second LED intensity
  if (intensity2 < threshold2) {
    intensity2 = 0;
  }

  // Set a peak for the second LED intensity
  if (intensity2 > 255) {
    intensity2 = 255;
  }

  // Write the intensities to the LEDS
  analogWrite(LED1, intensity1);
  analogWrite(LED2, intensity2);
  // Print the intensitys of the LEDs
  LCD.printNumI(intensity1, 0, 0, 3, '0');
  LCD.printNumI(intensity2, 300, 0, 3, '0');

  // If the intensity of the first LED is below its threshold
  if ((intensity1 == 0) && (pressed2 == false)) {
    // Set the first LED intensity to 0
    intensity1 = 0;
    // The first FSR is not pressed
    pressed1 = false;
    // Stop the speaker from playing
    noTone(speaker);
  }

  // If the intensity of the first LED passes its threshold
  if ((intensity1 > 0) && (pressed1 == false) && (pressed2 == false)) {
    // Increment the first counter
    counter1++;
    // The first FSR has been pressed
    pressed1 = true;
    // Play the note C4
    tone(speaker, c4);
  }

  // If the intensity of the second LED is below its threshold
  if ((intensity2 == 0) && (pressed1 == false)) {
    // Set the second LED intensity to 0
    intensity2 = 0;
    // The second FSR is not pressed
    pressed2 = false;
    // Stop the speaker from playing
    noTone(speaker);
  }

  // If the intensity of the second LED passes its threshold
  if ((intensity2 > 0) && (pressed1 == false) && (pressed2 == false)) {
    // Increment the second counter
    counter2++;
    // The second FSR has been pressed
    pressed2 = true;
    // Play the note C5
    tone(speaker, c5);
  }

  // Print the number of times the FSRs have been pressed
  LCD.printNumI(counter1, 0, 50);
  LCD.printNumI(counter2, 300, 50);
}
