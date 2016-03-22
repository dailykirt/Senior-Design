#include <UTFT.h>
#include <Wire.h>

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

UTFT LCD(CTE32HR, 38, 39, 40, 41);

byte note;
byte velocity;
bool noteOn = false;

void setup() {
  Wire.begin();

  // Initialize the LCD
  LCD.InitLCD();
  // Set the font
  LCD.setFont(BigFont);
  // Clear the screen
  LCD.clrScr();
  // Set the color to be red
  LCD.setColor(255, 0, 0);
}

void loop() {
  note = random(128);
  velocity = random(128);
  noteOn = !noteOn;

  LCD.printNumI(note, 0, 0, 3, '0');
  LCD.printNumI(velocity, 0, 50, 3, '0');

  if (noteOn == true) {
    LCD.print("True ", 0, 100);
  }
  else {
    LCD.print("False", 0, 100);
  }

  Wire.beginTransmission(1);
  Wire.write(note);
  Wire.write(velocity);
  Wire.write(noteOn);
  Wire.endTransmission();

  delay(3000);
}
