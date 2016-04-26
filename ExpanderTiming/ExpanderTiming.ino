#include <Wire.h>
#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 MCP0;
Adafruit_MCP23017 MCP1;
Adafruit_MCP23017 MCP2;
Adafruit_MCP23017 MCP3;
Adafruit_MCP23017 MCP4;
Adafruit_MCP23017 MCP5;
Adafruit_MCP23017 MCP6;
Adafruit_MCP23017 MCP7;

const int SWITCH = 9;

uint16_t value = 0x0000;
bool bitValue = false;

void setup() {
  MCP0.begin(0);
  MCP1.begin(1);
  MCP2.begin(2);
  MCP3.begin(3);
  MCP4.begin(4);
  MCP5.begin(5);
  MCP6.begin(6);
  MCP7.begin(7);
//  MCP0.begin(0x40);
//  MCP1.begin(0x42);
//  MCP2.begin(0x44);
//  MCP3.begin(0x46);
//  MCP4.begin(0x48);
//  MCP5.begin(0x4A);
//  MCP6.begin(0x4C);
//  MCP7.begin(0x4E);

  Serial.begin(115200);
  pinMode(11, OUTPUT);

  for (int i = 0; i < 16; i++) {
    MCP0.pinMode(i, OUTPUT);
    delay(10);
    MCP1.pinMode(i, OUTPUT);
    delay(10);
    MCP2.pinMode(i, OUTPUT);
    delay(10);
    MCP3.pinMode(i, OUTPUT);
    delay(10);
    MCP4.pinMode(i, OUTPUT);
    delay(10);
    MCP5.pinMode(i, OUTPUT);
    delay(10);
    MCP6.pinMode(i, OUTPUT);
    delay(10);
    digitalWrite(11, LOW);
    MCP7.pinMode(i, OUTPUT);
    delay(10);
    digitalWrite(11, HIGH);
    MCP7.pinMode(i, OUTPUT);
    delay(10);
  }

  Wire.begin();
  //TWBR = 12;
  //Wire.setClock(400000L);
  //Wire.setClock(1700000L);
//  pinMode(SWITCH, OUTPUT);
//  digitalWrite(SWITCH, LOW);
}

void loop() {
  if (value == 0x0000) {
    value = 0xFFFF;
  }
  else {
    value = 0x0000;
  }

  unsigned long startTime = micros();

  MCP0.writeGPIOAB(value);
  MCP1.writeGPIOAB(value);
  MCP2.writeGPIOAB(value);
  MCP3.writeGPIOAB(value);
  MCP4.writeGPIOAB(value);
  MCP5.writeGPIOAB(value);
  MCP6.writeGPIOAB(value);
  digitalWrite(11, LOW);
  MCP7.writeGPIOAB(value);
  digitalWrite(11, HIGH);
  MCP7.writeGPIOAB(value);
//  digitalWrite(SWITCH, HIGH);
//  delay(1000);
//  MCP7.writeGPIOAB(value);
//  digitalWrite(SWITCH, LOW);

  //Serial.print("16-bit write: ");
  unsigned long stopTime = micros();
  Serial.println(stopTime - startTime);
  delay(2000);
//
//  bitValue = !bitValue;
//
//  startTime = micros();
//
//  for (int i = 0; i < 16; i++) {
//    MCP0.digitalWrite(i, bitValue);
//    MCP1.digitalWrite(i, bitValue);
//    MCP2.digitalWrite(i, bitValue);
//    MCP3.digitalWrite(i, bitValue);
//    MCP4.digitalWrite(i, bitValue);
//    MCP5.digitalWrite(i, bitValue);
//    MCP6.digitalWrite(i, bitValue);
//    MCP7.digitalWrite(i, bitValue);
//  }
//
//  Serial.print("Bit by bit write: ");
//  Serial.println(micros() - startTime);
//  delay(2000);
}
