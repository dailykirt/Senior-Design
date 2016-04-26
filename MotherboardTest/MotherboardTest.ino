#include <EventManager.h>
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

const int S0 = 6;
const int S1 = 5;
const int MUXENABLE = 7;
const int RESET = 13;

const int THRESHOLD = 250;

void setup() {
  Serial.begin(115200);

  MCP0.begin(0);
  MCP1.begin(1);
  MCP2.begin(2);
  MCP3.begin(3);
  MCP4.begin(4);
  MCP5.begin(5);
  MCP6.begin(6);
  MCP7.begin(7);

  for (int i = 0; i < 16; i++) {
    MCP0.pinMode(i, OUTPUT);
    MCP1.pinMode(i, OUTPUT);
    MCP2.pinMode(i, OUTPUT);
    MCP3.pinMode(i, OUTPUT);
    MCP4.pinMode(i, OUTPUT);
    MCP5.pinMode(i, OUTPUT);
    MCP6.pinMode(i, OUTPUT);
    MCP7.pinMode(i, OUTPUT);
  }

  pinMode(S1, OUTPUT);
  pinMode(S0, OUTPUT);
//  pinMode(MUXENABLE, OUTPUT);
//  pinMode(RESET, OUTPUT);

  digitalWrite(S1, LOW);
  digitalWrite(S0, LOW);
//  digitalWrite(MUXENABLE, LOW);
//  digitalWrite(RESET, LOW);

  Wire.begin();
}

void loop() {
  for (int i = 0; i < 12; i++) {
    int intensity = analogRead(i);
  
    if (intensity > THRESHOLD) {
      MCP0.writeGPIOAB(0xFFFF);
      MCP1.writeGPIOAB(0xFFFF);
      MCP2.writeGPIOAB(0xFFFF);
      MCP3.writeGPIOAB(0xFFFF);
      MCP4.writeGPIOAB(0xFFFF);
      MCP5.writeGPIOAB(0xFFFF);
      MCP6.writeGPIOAB(0xFFFF);
      MCP7.writeGPIOAB(0xFFFF);
    }
    else {
      MCP0.writeGPIOAB(0x0000);
      MCP1.writeGPIOAB(0x0000);
      MCP2.writeGPIOAB(0x0000);
      MCP3.writeGPIOAB(0x0000);
      MCP4.writeGPIOAB(0x0000);
      MCP5.writeGPIOAB(0x0000);
      MCP6.writeGPIOAB(0x0000);
      MCP7.writeGPIOAB(0x0000);
    }
  }
}
