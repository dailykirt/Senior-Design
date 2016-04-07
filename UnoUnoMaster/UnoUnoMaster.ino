#include <Wire.h>

void setup() {
  Serial.begin(115200);

  Wire.begin(0);
  Wire.onReceive(receiveEvent);
}

void loop() {
}

void receiveEvent(int howMany) {
  byte number = Wire.read();
  Serial.write(number);
}
