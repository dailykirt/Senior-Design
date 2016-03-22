#include <Wire.h>

void setup() {
  Wire.begin(1);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}

void loop() {
  delay(1000);
}

void receiveEvent(int howMany) {
  int note = Wire.read();
  Serial.print("The note is ");
  Serial.println(note);
  int velocity = Wire.read();
  Serial.print("The velocity is ");
  Serial.println(velocity);
  bool noteOn = Wire.read();

  if (noteOn == true) {
    Serial.println("The note is on");
  }
  else {
    Serial.println("The note is off");
  }

  Serial.println();
}
