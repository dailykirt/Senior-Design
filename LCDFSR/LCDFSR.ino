#include <UTFT.h>

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

int value;
UTFT LCD(CTE32HR, 38, 39, 40, 41);

void setup() {
  // put your setup code here, to run once:
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
  // put your main code here, to run repeatedly:
  value = analogRead(1);
  analogWrite(13, value);
  LCD.printNumI(value, 0, 0, 3, '0');
}
