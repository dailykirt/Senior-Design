#include <UTFT.h>

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

int intensity;
bool pressed = false;
int counter = 0;
UTFT LCD(CTE32HR, 38, 39, 40, 41);

void setup() {
  // Initialize the LCD
  LCD.InitLCD();
  // Set the font
  LCD.setFont(SevenSegNumFont);
  // Clear the screen
  LCD.clrScr();
  // Set the color to be red
  LCD.setColor(255, 0, 0);

  // LED output pin
  pinMode(13, OUTPUT);
}

void loop() {
  // Read the intensity of the analog input signal
  intensity = analogRead(1);
  // Write the intensity to the LED
  analogWrite(13, intensity);
  // Print the intensity of the LED on the LCD
  LCD.printNumI(intensity, 0, 0, 3, '0');

  // If the intensity is 0
  if (intensity == 0) {
    // The FSR is not pressed
    pressed = false;
  // If the intensity was originally 0 and becomes nonzero
  } else if (pressed == false) {
    // Increment the counter
    counter++;
    // The FSR has been pressed
    pressed = true;
  }

  // Print the number of times the FSR has been pressed
  LCD.printNumI(counter, 0, 50);
}
