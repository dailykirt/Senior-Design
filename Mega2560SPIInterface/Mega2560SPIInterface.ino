#include <SPI.h>
byte number = 0;

// LCD Uno slave select, active low
const int SS = 10;

void setup() {
  digitalWrite(SS, HIGH);
  SPI.begin();
}

void loop() {
  digitalWrite(SS, LOW);
  
}
