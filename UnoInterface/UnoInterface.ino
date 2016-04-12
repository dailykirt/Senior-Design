#include <Wire.h>

// LED output pins
const int LED1 = 9;
const int LED2 = 10;

// LED intensities
int intensity1 = 0;
int intensity2 = 0;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  Serial.begin(115200);

  Wire.begin(1);
  Wire.onReceive(receiveEvent);
}

void loop() {
  delay(1);  
}

void receiveEvent(int howMany) {
  byte note = Wire.read();
  byte velocity = Wire.read();
  byte noteOn = Wire.read();

  if (note == 60) {
    intensity1 = map(velocity, 0, 127, 0, 255);
    Serial.println(intensity1);
    analogWrite(LED1, intensity1);
  }
  else {
    intensity2 = map(velocity, 0, 127, 0, 255);
    Serial.println(intensity2);
    analogWrite(LED2, intensity2);
  }
}
