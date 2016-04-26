#include <UTFT.h>
#include <Wire.h>

// Font sizes for the LCD
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

UTFT LCD(CTE32HR, 38, 39, 40, 41);

const int interruptPin = 3;
const int LED1 = 6;
const int LED2 = 7;

byte number = 0;

void setup() {
  attachInterrupt(digitalPinToInterrupt(interruptPin), request, RISING);

  LCD.InitLCD();
  LCD.setFont(BigFont);
  LCD.clrScr();
  LCD.setColor(255, 0, 0);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(interruptPin, OUTPUT);

  Serial.begin(115200);

  Wire.begin();
}

void loop() {
  Wire.beginTransmission(4);
  Wire.write(number);
  LCD.printNumI(number, 0, 0);
  Wire.endTransmission();
  number++;
  delay(1000);
}

void request() {
  Wire.requestFrom(4, 1);
  byte received = Wire.read();
  LCD.printNumI(received, 150, 150);
}
