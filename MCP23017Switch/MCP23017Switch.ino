#include <Wire.h>
#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 MCP0;
Adafruit_MCP23017 MCP1;
  
void setup() {  
  MCP0.begin();
  MCP1.begin(1);

  MCP0.pinMode(0, OUTPUT);
  MCP1.pinMode(1, OUTPUT);

  pinMode(8, OUTPUT);
}

void loop() {
  digitalWrite(8, LOW);
  delay(1000);
  digitalWrite(8, HIGH);
  delay(1000);
}
