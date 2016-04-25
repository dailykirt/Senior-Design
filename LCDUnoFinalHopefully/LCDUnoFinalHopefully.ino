#include <Wire.h>

bool received = false;
byte receivedByte;

void setup() {
  Wire.begin(100);
  Wire.onReceive(receiveEvent);
  Serial.begin(115200);
}

void loop() {
  if (received == true) {
    Serial.write(receivedByte);
    //Serial.println(receivedByte);
    received = false;
  }
}

void receiveEvent(int howMany) {
  while (Wire.available()) {
    receivedByte = Wire.read();
    received = true;
  }
}
