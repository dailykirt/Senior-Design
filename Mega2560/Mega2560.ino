// This is the code used for the Arduino Mega 2560
// to prototype using multiple Arduino microcontrollers.
// The Mega 2560 will read in analog inputs through two
// FSRs and output using PWM into an Arduino Uno. At this
// point, the Mega 2560 also controls the LCD since the
// LCD is only compatible with the Mega 2560.
//
// Circuit pin layout:
// FSR #1 --> A1
// FSR #2 --> A2
// PWM 5 --> Uno PWM 5
// PWM 6 --> Uno PWM 6
// Too many pins to count --> LCD

#include <UTFT.h>

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

// FSR pins
const int FSR1 = 1;
const int FSR2 = 2;
// Output pins
const int output1 = 6;
const int output2 = 5;
// LED intensities
int intensity1;
int intensity2;

// LCD display
UTFT LCD(CTE32HR, 38, 39, 40, 41);

void setup() {
  // Initialize the LCD
  LCD.InitLCD();
  // Set the font
  LCD.setFont(BigFont);
  // Clear the screen
  LCD.clrScr();
  // Set the color to be red
  LCD.setColor(255, 0, 0);

  // Output pins
  pinMode(output1, OUTPUT);
  pinMode(output2, OUTPUT);
}

void loop() {
  // Read the intensities of the FSR analog inputs
  intensity1 = map(analogRead(FSR1), 0, 333, 0, 255);
  intensity2 = map(analogRead(FSR2), 0, 1047, 0, 255);
  // Output the intensities
  analogWrite(output1, intensity1);
  analogWrite(output2, intensity2);
  // Print the intensities to the LCD
  LCD.printNumI(intensity1, 0, 0, 3, '0');
  LCD.printNumI(intensity2, 240, 0, 3, '0');
}

//// This is the code used for the Arduino Mega 2560
//// to prototype using multiple Arduino microcontrollers.
//// The Mega 2560 will read in analog inputs through two
//// FSRs and output using PWM into an Arduino Uno. At this
//// point, the Mega 2560 also controls the LCD since the
//// LCD is only compatible with the Mega 2560.
////
//// Circuit pin layout:
//// FSR #1 --> A1
//// FSR #2 --> A2
//// PWM 3 --> Uno A3
//// PWM 5 --> Uno A5
//// Too many pins to count --> LCD
//
//#include <UTFT.h>
//
//extern uint8_t SmallFont[];
//extern uint8_t BigFont[];
//extern uint8_t SevenSegNumFont[];
//
////// Speaker pin
////const int speaker = 11;
////// LED pins
////const int LED1 = 13;
////const int LED2 = 12;
//// FSR pins
//const int FSR1 = 1;
//const int FSR2 = 2;
//// LCD display
//UTFT LCD(CTE32HR, 38, 39, 40, 41);
//
//// LED intensities
//int intensity1;
//int intensity2;
//// Intensity thresholds
//int threshold1 = 45;
//int threshold2 = 45;
//// FSR pressed
//int pressed1 = false;
//int pressed2 = false;
//// Counters
//int counter1 = 0;
//int counter2 = 0;
//
//int PWMValues[] = {c4, db4, d4, eb4, e4, f4, gb4, g4, ab4, a4, bb4, b4, c5};
//
//void setup() {
//  // Initialize the LCD
//  LCD.InitLCD();
//  // Set the font
//  LCD.setFont(BigFont);
//  // Clear the screen
//  LCD.clrScr();
//  // Set the color to be red
//  LCD.setColor(255, 0, 0);
//
////  // LED output pins
////  pinMode(LED1, OUTPUT);
////  pinMode(LED2, OUTPUT);
//}
//
//void loop() {
//  // Read the intensity of the FSR analog inputs
//  intensity1 = analogRead(FSR1);
//  intensity2 = analogRead(FSR2);
//
//  // When the first FSR is pressed, decrease the first threshold
//  if (pressed1 == true) {
//    threshold1 = 10;
//  // When the first FSR is not pressed, increase the first threshold
//  } else {
//    threshold1 = 45;
//  }
//
//  // When the second FSR is pressed, decrease the second threshold
//  if (pressed2 == true) {
//    threshold2 = 10;
//  // When the second FSR is not pressed, increase the second threshold
//  } else {
//    threshold2 = 45;
//  }
//
//  // Set a threshold for the first LED intensity
//  if (intensity1 < threshold1) {
//    intensity1 = 0;
//  }
//
//  // Set a peak for the first LED intensity
//  if (intensity1 > 255) {
//    intensity1 = 255;
//  }
//
//  // Set a threshold for the second LED intensity
//  if (intensity2 < threshold2) {
//    intensity2 = 0;
//  }
//
//  // Set a peak for the second LED intensity
//  if (intensity2 > 255) {
//    intensity2 = 255;
//  }
//
////  // Write the intensities to the LEDS
////  analogWrite(LED1, intensity1);
////  analogWrite(LED2, intensity2);
//  // Print the intensitys of the LEDs
//  LCD.printNumI(intensity1, 0, 0, 3, '0');
//  LCD.printNumI(intensity2, 300, 0, 3, '0');
//
//  // If the intensity of the first LED is below its threshold
//  if ((intensity1 == 0) && (pressed2 == false)) {
//    // Set the first LED intensity to 0
//    intensity1 = 0;
//    // The first FSR is not pressed
//    pressed1 = false;
////    // Stop the speaker from playing
////    noTone(speaker);
//  }
//
//  // If the intensity of the first LED passes its threshold
//  if ((intensity1 > 0) && (pressed1 == false) && (pressed2 == false)) {
//    // Increment the first counter
//    counter1++;
//    // The first FSR has been pressed
//    pressed1 = true;
////    // Play the note C4
////    tone(speaker, c4);
//  }
//
//  // If the intensity of the second LED is below its threshold
//  if ((intensity2 == 0) && (pressed1 == false)) {
//    // Set the second LED intensity to 0
//    intensity2 = 0;
//    // The second FSR is not pressed
//    pressed2 = false;
//    // Stop the speaker from playing
//    noTone(speaker);
//  }
//
//  // If the intensity of the second LED passes its threshold
//  if ((intensity2 > 0) && (pressed1 == false) && (pressed2 == false)) {
//    // Increment the second counter
//    counter2++;
//    // The second FSR has been pressed
//    pressed2 = true;
////    // Play the note C5
////    tone(speaker, c5);
//  }
//
//  // Print the number of times the FSRs have been pressed
//  LCD.printNumI(counter1, 0, 50);
//  LCD.printNumI(counter2, 300, 50);
//}
