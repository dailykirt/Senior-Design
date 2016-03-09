#include <UTFT.h>

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

const int LED1 = 13;
const int LED2 = 12;
const int FSR1 = 1;
const int FSR2 = 2;
UTFT LCD(CTE32HR, 38, 39, 40, 41);

int intensity1;
int intensity2;
int pressed1 = false;
int pressed2 = false;
int counter1 = 0;
int counter2 = 0;

void setup() {
  // Initialize the LCD
  LCD.InitLCD();
  // Set the font
  LCD.setFont(SevenSegNumFont);
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

  if (intensity2 < 4) {
    intensity2 = 0;
  }

  // Write the intensities to the LEDS
  analogWrite(LED1, intensity1);
  analogWrite(LED2, intensity2);
  // Print the intensitys of the LEDs
  LCD.printNumI(intensity1, 0, 0, 3, '0');
  LCD.printNumI(intensity2, 300, 0, 3, '0');

  // If the intensity of the first LED is 0
  if (intensity1 == 0) {
    // The first FSR is not pressed
    pressed1 = false;
  // If the intensity of the first LED becomes nonzero
  } else if (pressed1 == false) {
    // Increment the first counter
    counter1++;
    // The first FSR has been pressed
    pressed1 = true;
  }

  // If the intensity of the second LED is 0
  if (intensity2 == 0) {
    // The second FSR is not pressed
    pressed2 = false;
  // If the intensity of the second LED becomes nonzero
  } else if (pressed2 == false) {
    // Increment the second counter
    counter2++;
    // The second FSR has been pressed
    pressed2 = true;
  }

  // Print the number of times the FSRs have been pressed
  LCD.printNumI(counter1, 0, 50);
  LCD.printNumI(counter2, 300, 50);
}
