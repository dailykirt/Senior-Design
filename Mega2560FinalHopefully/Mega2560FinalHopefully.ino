/*
This is the final code for the Arduino Mega 2560.
The Mega 2560 is an I2C master, sending data to the Uno.
The Mega 2560 receives Serial data from the Uno.
The Mega 2560 controls all port expanders.
The Mega 2560 is responsible for MIDI processing.
*/

#include <Wire.h>
#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 MCP0;
Adafruit_MCP23017 MCP1;
Adafruit_MCP23017 MCP2;
Adafruit_MCP23017 MCP3;
Adafruit_MCP23017 MCP4;
Adafruit_MCP23017 MCP5;
Adafruit_MCP23017 MCP6;
Adafruit_MCP23017 MCP7;

byte sentByte = 0;
byte receivedByte = -1;
const uint16_t LEDOFF = 0x0000;
const uint16_t LEDON = 0xFFFF;

void setup() {
  MCP0.begin(0);
  MCP1.begin(1);
  MCP2.begin(2);
  MCP3.begin(3);
  MCP4.begin(4);
  MCP5.begin(5);
  MCP6.begin(6);
  MCP7.begin(7);

  Serial.begin(115200);
  Serial3.begin(115200);

  for (int i = 0; i < 16; i++) {
    MCP0.pinMode(i, OUTPUT);
    MCP1.pinMode(i, OUTPUT);
    MCP2.pinMode(i, OUTPUT);
    MCP3.pinMode(i, OUTPUT);
    MCP4.pinMode(i, OUTPUT);
    MCP5.pinMode(i, OUTPUT);
    MCP6.pinMode(i, OUTPUT);
    MCP7.pinMode(i, OUTPUT);
  }

  Wire.begin();
}

void loop() {
  Wire.beginTransmission(100);
  Wire.write(sentByte);
  Wire.endTransmission();
  Serial.print("Sent data: ");
  Serial.println(sentByte);

  switch (receivedByte) {
    case 0:
      MCP0.writeGPIOAB(LEDON);
      MCP1.writeGPIOAB(LEDOFF);
      MCP2.writeGPIOAB(LEDOFF);
      MCP3.writeGPIOAB(LEDOFF);
      MCP4.writeGPIOAB(LEDOFF);
      MCP5.writeGPIOAB(LEDOFF);
      MCP6.writeGPIOAB(LEDOFF);
      MCP7.writeGPIOAB(LEDOFF);
      break;
    case 1:
      MCP0.writeGPIOAB(LEDOFF);
      MCP1.writeGPIOAB(LEDON);
      MCP2.writeGPIOAB(LEDOFF);
      MCP3.writeGPIOAB(LEDOFF);
      MCP4.writeGPIOAB(LEDOFF);
      MCP5.writeGPIOAB(LEDOFF);
      MCP6.writeGPIOAB(LEDOFF);
      MCP7.writeGPIOAB(LEDOFF);
      break;
    case 2:
      MCP0.writeGPIOAB(LEDOFF);
      MCP1.writeGPIOAB(LEDOFF);
      MCP2.writeGPIOAB(LEDON);
      MCP3.writeGPIOAB(LEDOFF);
      MCP4.writeGPIOAB(LEDOFF);
      MCP5.writeGPIOAB(LEDOFF);
      MCP6.writeGPIOAB(LEDOFF);
      MCP7.writeGPIOAB(LEDOFF);
      break;
    case 3:
      MCP0.writeGPIOAB(LEDOFF);
      MCP1.writeGPIOAB(LEDOFF);
      MCP2.writeGPIOAB(LEDOFF);
      MCP3.writeGPIOAB(LEDON);
      MCP4.writeGPIOAB(LEDOFF);
      MCP5.writeGPIOAB(LEDOFF);
      MCP6.writeGPIOAB(LEDOFF);
      MCP7.writeGPIOAB(LEDOFF);
      break;
    case 4:
      MCP0.writeGPIOAB(LEDOFF);
      MCP1.writeGPIOAB(LEDOFF);
      MCP2.writeGPIOAB(LEDOFF);
      MCP3.writeGPIOAB(LEDOFF);
      MCP4.writeGPIOAB(LEDON);
      MCP5.writeGPIOAB(LEDOFF);
      MCP6.writeGPIOAB(LEDOFF);
      MCP7.writeGPIOAB(LEDOFF);
      break;
    case 5:
      MCP0.writeGPIOAB(LEDOFF);
      MCP1.writeGPIOAB(LEDOFF);
      MCP2.writeGPIOAB(LEDOFF);
      MCP3.writeGPIOAB(LEDOFF);
      MCP4.writeGPIOAB(LEDOFF);
      MCP5.writeGPIOAB(LEDON);
      MCP6.writeGPIOAB(LEDOFF);
      MCP7.writeGPIOAB(LEDOFF);
      break;
    case 6:
      MCP0.writeGPIOAB(LEDOFF);
      MCP1.writeGPIOAB(LEDOFF);
      MCP2.writeGPIOAB(LEDOFF);
      MCP3.writeGPIOAB(LEDOFF);
      MCP4.writeGPIOAB(LEDOFF);
      MCP5.writeGPIOAB(LEDOFF);
      MCP6.writeGPIOAB(LEDON);
      MCP7.writeGPIOAB(LEDOFF);
      break;
    case 7:
      MCP0.writeGPIOAB(LEDOFF);
      MCP1.writeGPIOAB(LEDOFF);
      MCP2.writeGPIOAB(LEDOFF);
      MCP3.writeGPIOAB(LEDOFF);
      MCP4.writeGPIOAB(LEDOFF);
      MCP5.writeGPIOAB(LEDOFF);
      MCP6.writeGPIOAB(LEDOFF);
      MCP7.writeGPIOAB(LEDON);
      break;
    default:
      MCP0.writeGPIOAB(LEDON);
      MCP1.writeGPIOAB(LEDON);
      MCP2.writeGPIOAB(LEDON);
      MCP3.writeGPIOAB(LEDON);
      MCP4.writeGPIOAB(LEDON);
      MCP5.writeGPIOAB(LEDON);
      MCP6.writeGPIOAB(LEDON);
      MCP7.writeGPIOAB(LEDON);
      break;
  }

  delay(1000);
}

void serialEvent3() {
  while (Serial3.available() > 0) {
    receivedByte = Serial3.read();
    Serial.print("Received data: ");
    Serial.println(receivedByte);
    sentByte = (receivedByte + 1) % 8;
  }
}

  
  


//#include <Wire.h>
//#include "Adafruit_MCP23017.h"
//
//Adafruit_MCP23017 MCP0;
//Adafruit_MCP23017 MCP1;
//Adafruit_MCP23017 MCP2;
//Adafruit_MCP23017 MCP3;
//Adafruit_MCP23017 MCP4;
//Adafruit_MCP23017 MCP5;
//Adafruit_MCP23017 MCP6;
//Adafruit_MCP23017 MCP7;
//
//byte sentData = 0;
//byte receivedByte = 255;
//uint16_t LEDON = LEDON;
//uint16_t LEDOFF = LEDOFF;
//
//void setup() {
//  MCP0.begin(0);
//  MCP1.begin(1);
//  MCP2.begin(2);
//  MCP3.begin(3);
//  MCP4.begin(4);
//  MCP5.begin(5);
//  MCP6.begin(6);
//  MCP7.begin(7);
//
//  for (int i = 0; i < 16; i++) {
//    MCP0.pinMode(i, OUTPUT);
//    MCP1.pinMode(i, OUTPUT);
//    MCP2.pinMode(i, OUTPUT);
//    MCP3.pinMode(i, OUTPUT);
//    MCP4.pinMode(i, OUTPUT);
//    MCP5.pinMode(i, OUTPUT);
//    MCP6.pinMode(i, OUTPUT);
//    MCP7.pinMode(i, OUTPUT);
//  }
//
//  Serial.begin(115200);
//  Serial3.begin(115200);
//
//  Wire.begin();
//  //Serial.println("Setup done.");
//}
//
//void loop() {
//  switch (receivedByte) {
//    case 0:
//      MCP0.writeGPIOAB(LEDON);
//      MCP1.writeGPIOAB(LEDOFF);
//      MCP2.writeGPIOAB(LEDOFF);
//      MCP3.writeGPIOAB(LEDOFF);
//      MCP4.writeGPIOAB(LEDOFF);
//      MCP5.writeGPIOAB(LEDOFF);
//      MCP6.writeGPIOAB(LEDOFF);
//      MCP7.writeGPIOAB(LEDOFF);
//      break;
//    case 1:
//      MCP0.writeGPIOAB(LEDOFF);
//      MCP1.writeGPIOAB(LEDON);
//      MCP2.writeGPIOAB(LEDOFF);
//      MCP3.writeGPIOAB(LEDOFF);
//      MCP4.writeGPIOAB(LEDOFF);
//      MCP5.writeGPIOAB(LEDOFF);
//      MCP6.writeGPIOAB(LEDOFF);
//      MCP7.writeGPIOAB(LEDOFF);
//      break;
//    case 2:
//      MCP0.writeGPIOAB(LEDOFF);
//      MCP1.writeGPIOAB(LEDOFF);
//      MCP2.writeGPIOAB(LEDON);
//      MCP3.writeGPIOAB(LEDOFF);
//      MCP4.writeGPIOAB(LEDOFF);
//      MCP5.writeGPIOAB(LEDOFF);
//      MCP6.writeGPIOAB(LEDOFF);
//      MCP7.writeGPIOAB(LEDOFF);
//      break;
//    case 3:
//      MCP0.writeGPIOAB(LEDOFF);
//      MCP1.writeGPIOAB(LEDOFF);
//      MCP2.writeGPIOAB(LEDOFF);
//      MCP3.writeGPIOAB(LEDON);
//      MCP4.writeGPIOAB(LEDOFF);
//      MCP5.writeGPIOAB(LEDOFF);
//      MCP6.writeGPIOAB(LEDOFF);
//      MCP7.writeGPIOAB(LEDOFF);
//      break;
//    case 4:
//      MCP0.writeGPIOAB(LEDOFF);
//      MCP1.writeGPIOAB(LEDOFF);
//      MCP2.writeGPIOAB(LEDOFF);
//      MCP3.writeGPIOAB(LEDOFF);
//      MCP4.writeGPIOAB(LEDON);
//      MCP5.writeGPIOAB(LEDOFF);
//      MCP6.writeGPIOAB(LEDOFF);
//      MCP7.writeGPIOAB(LEDOFF);
//      break;
//    case 5:
//      MCP0.writeGPIOAB(LEDOFF);
//      MCP1.writeGPIOAB(LEDOFF);
//      MCP2.writeGPIOAB(LEDOFF);
//      MCP3.writeGPIOAB(LEDOFF);
//      MCP4.writeGPIOAB(LEDOFF);
//      MCP5.writeGPIOAB(LEDON);
//      MCP6.writeGPIOAB(LEDOFF);
//      MCP7.writeGPIOAB(LEDOFF);
//      break;
//    case 6:
//      MCP0.writeGPIOAB(LEDOFF);
//      MCP1.writeGPIOAB(LEDOFF);
//      MCP2.writeGPIOAB(LEDOFF);
//      MCP3.writeGPIOAB(LEDOFF);
//      MCP4.writeGPIOAB(LEDOFF);
//      MCP5.writeGPIOAB(LEDOFF);
//      MCP6.writeGPIOAB(LEDON);
//      MCP7.writeGPIOAB(LEDOFF);
//      break;
//    case 7:
//      MCP0.writeGPIOAB(LEDOFF);
//      MCP1.writeGPIOAB(LEDOFF);
//      MCP2.writeGPIOAB(LEDOFF);
//      MCP3.writeGPIOAB(LEDOFF);
//      MCP4.writeGPIOAB(LEDOFF);
//      MCP5.writeGPIOAB(LEDOFF);
//      MCP6.writeGPIOAB(LEDOFF);
//      MCP7.writeGPIOAB(LEDON);
//      break;
//    default:
//      MCP0.writeGPIOAB(LEDON);
//      MCP1.writeGPIOAB(LEDON);
//      MCP2.writeGPIOAB(LEDON);
//      MCP3.writeGPIOAB(LEDON);
//      MCP4.writeGPIOAB(LEDON);
//      MCP5.writeGPIOAB(LEDON);
//      MCP6.writeGPIOAB(LEDON);
//      MCP7.writeGPIOAB(LEDON);
//      break;
//  }
//
//  Wire.beginTransmission(4);
//  Wire.write(sentData);
//  Wire.endTransmission();
//  sentData = (sentData + 1) % 8;
//  Serial.print("Sent data: ");
//  Serial.println(sentData);
//  delay(1000);
//}
//
//void serialEvent3() {
//  receivedByte = Serial3.read();
//  Serial.print("Received data: ");
//  Serial.println(receivedByte);
//}
