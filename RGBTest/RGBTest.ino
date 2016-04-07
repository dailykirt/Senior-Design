#include <Wire.h>
#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 MCP;

const int LED1 = 0;
const int LED2 = 4;
const int RED = 5;
const int GREEN = 7;
const int BLUE = 6;
const int PERIOD = 2040;

void setup() {
  MCP.begin(0);

  MCP.pinMode(LED1, OUTPUT);
  MCP.pinMode(LED2, OUTPUT);
  MCP.pinMode(RED, OUTPUT);
  MCP.pinMode(GREEN, OUTPUT);
  MCP.pinMode(BLUE, OUTPUT);

  MCP.digitalWrite(RED, HIGH);
  MCP.digitalWrite(LED2, HIGH);
}

void loop() {
  for (int dutyCycle = 0; dutyCycle <= 100; dutyCycle += 10) {
    int timeHigh = dutyCycle * PERIOD / 100;
    int timeLow = (100 - dutyCycle) * PERIOD / 100;

    MCP.digitalWrite(LED1, HIGH);
    delay(2);
    MCP.digitalWrite(LED1, LOW);
    delay(8);
  }
}
