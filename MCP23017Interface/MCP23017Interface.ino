#include <Wire.h>
#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 MCP0;
Adafruit_MCP23017 MCP1;

int i = 3;
  
void setup() {  
  MCP0.begin();
  MCP1.begin(1);

  MCP0.pinMode(0, OUTPUT);
  MCP1.pinMode(1, OUTPUT);
}

void loop() {
  i = (i + 1) % 4;

  if (i == 0) {
    MCP0.digitalWrite(0, LOW);
    MCP1.digitalWrite(1, LOW);
  }
  else if (i == 1) {
    MCP0.digitalWrite(0, HIGH);
    MCP1.digitalWrite(1, LOW);
  }
  else if (i == 2) {
    MCP0.digitalWrite(0, LOW);
    MCP1.digitalWrite(1, HIGH);
  }
  else {
    MCP0.digitalWrite(0, HIGH);
    MCP1.digitalWrite(1, HIGH);
  }

  delay(1000);
}
