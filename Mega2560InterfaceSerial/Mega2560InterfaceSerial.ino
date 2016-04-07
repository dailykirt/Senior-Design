#include <UTFT.h>

// Font sizes for the LCD
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

UTFT LCD(CTE32HR, 38, 39, 40, 41);

bool i = false;

void setup() {
  LCD.InitLCD();
  LCD.setFont(BigFont);
  LCD.clrScr();
  LCD.setColor(255, 0, 0);

  Serial3.begin(115200);

  while(!Serial3) {
  }
}

void loop() {
  i = !i;

  if (i == false) {
    LCD.print("False.", 0, 0);
  }
  else {
    LCD.print("True. ", 0, 0);
  }

  Serial3.write(i);
  delay(1000);
}
