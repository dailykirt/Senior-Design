#include <Wire.h>

const int interruptPin = 3;
byte number;

void setup() {
  pinMode(interruptPin, OUTPUT);
  Wire.begin(4);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.begin(115200);
}

void loop() {
  delay(1);
}

void receiveEvent(int howMany) {
  number = Wire.read();
  Serial.println(number);
  digitalWrite(interruptPin, HIGH);
}

void requestEvent() {
  Wire.write(number + 4);
  digitalWrite(interruptPin, LOW);
}
