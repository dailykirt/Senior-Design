#include <Wire.h>

unsigned long duration[12];

void setup() {
  for (int i = 0; i < 12; i++) {
    duration[i] = 0;
  }

  Serial.begin(9600);
  Wire.begin(10);
  Wire.onReceive(receiveEvent);
}

void loop() {
  delay(1);
}

void receiveEvent(int howMany) {
  if (howMany == 3) {
    byte note = Wire.read();
    byte LSB = Wire.read();
    byte MSB = Wire.read();
    unsigned long noteDuration = (((unsigned long) MSB) << 8) + LSB;
    duration[note] = duration[note] + noteDuration;
    Serial.println(noteDuration);
  }
}
