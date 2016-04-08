#include <UTFT.h>
#include <Wire.h>

// Font sizes for the LCD
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

UTFT LCD(CTE32HR, 38, 39, 40, 41);

byte number = 0;
byte c;

void setup() {
  LCD.InitLCD();
  LCD.setFont(BigFont);
  LCD.clrScr();
  LCD.setColor(255, 0, 0);

  Serial.begin(115200);

  Wire.begin();
}

void loop() {
  LCD.printNumI(number, 0, 0);

  Wire.beginTransmission(0);
  Wire.write(number);
  Wire.endTransmission();

  Wire.requestFrom(0, 1);    //request one byte from slave 4
  while(Wire.available()>0)    // when data is received from slave to master
  {
    c = Wire.read();    //receive one byte from slave and assign to variable c
  }

  LCD.printChar(c,100,100);
  
  number = (number + 1) % 8;
  delay(1000);
}
