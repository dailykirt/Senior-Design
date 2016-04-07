#include <UTFT.h>

// Font sizes for the LCD
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

UTFT LCD(CTE32HR, 38, 39, 40, 41);

byte i = 0;

void setup() {
  LCD.InitLCD();
  LCD.setFont(SevenSegNumFont);
  LCD.clrScr();
  LCD.setColor(255, 0, 0);

  Serial3.begin(115200);

  while(!Serial3) {
  }
}

void loop() {
  LCD.printNumI(i, 0, 0);
  Serial3.print(i++, DEC);
  delay(1000);
}
