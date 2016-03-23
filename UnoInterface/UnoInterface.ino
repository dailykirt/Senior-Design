#include <Wire.h>

// LED output pins
const int LED1 = 3;
const int LED2 = 5;
// SD card CS pin
const int SDCS = 10;
// Speaker pin
const int SPEAKER = 6;

// LED intensities
int intensity1 = 0;
int intensity2 = 0;
// Note durations
unsigned long duration1 = 0;
unsigned long duration2 = 0;
// Note starting times
unsigned long start1 = 0;
unsigned long start2 = 0;

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
  bool noteOn = Wire.read();

  if (note == 60) {
    intensity1 = map(velocity, 0, 127, 0, 255);
    Serial.print("Intensity 1: ");
    Serial.println(intensity1);
    analogWrite(LED1, intensity1);

    if (noteOn == true) {
      start1 = millis();
    }
    else {
      duration1 += millis() - start1;
    }

    Serial.print("Duration 1: ");
    Serial.println(duration1);
    Serial.println();
  }
  else {
    intensity2 = map(velocity, 0, 127, 0, 255);
    Serial.print("Intensity 2: ");
    Serial.println(intensity2);
    analogWrite(LED2, intensity2);

    if (noteOn == true) {
      start2 = millis();
    }
    else {
      duration2 += millis() - start2;
    }

    Serial.print("Duration 2: ");
    Serial.println(duration2);
    Serial.println();
  }
}
