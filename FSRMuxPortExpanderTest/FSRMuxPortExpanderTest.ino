#include <EventManager.h>
#include <Wire.h>
#include "Adafruit_MCP23017.h"


///* C2 - B5 (36 - 83)
//*/
//
//#include <EventManager.h>
//#include <Wire.h>
//#include "Adafruit_MCP23017.h"
//
//Adafruit_MCP23017 MCP0;
//
//const int S0 = 6;
//const int S1 = 5;
//
//const int THRESHOLD = 250;
//
////const uint16_t RED1 = 0x0001;
////const uint16_t GREEN1 = 0x0002;
////const uint16_t BLUE1 = 0x0004;
////const uint16_t RED2 = 0x0008;
////const uint16_t GREEN2 = 0x0010;
////const uint16_t BLUE2 = 0x0020;
////const uint16_t RED3 = 0x0040;
////const uint16_t GREEN3 = 0x0080;
////const uint16_t BLUE3 = 0x0100;
////const uint16_t RED4 = 0x0200;
////const uint16_t GREEN4 = 0x0400;
////const uint16_t BLUE4 = 0x0800;
//const int RED1 = 0;
//const int GREEN1 = 1;
//const int BLUE1 = 2;
//const int RED2 = 3;
//const int GREEN2 = 4;
//const int BLUE2 = 5;
//const int RED3 = 6;
//const int GREEN3 = 7;
//const int BLUE3 = 8;
//const int RED4 = 9;
//const int GREEN4 = 10;
//const int BLUE4 = 11;
//
//bool notesOn[48];
//
//EventManager EventHandler;
//
//void setup() {
//  Serial.begin(115200);
//  Serial.println("Setup starting.");
//
//  for (int note = 36; note < 84; note++) {
//    EventHandler.addListener(note, noteOnListener);
//  }
//
//  MCP0.begin(0);
//
//  for (int i = 0; i < 16; i++) {
//    MCP0.pinMode(i, OUTPUT);
//  }
//
//  for (int i = 0; i < 48; i++) {
//    notesOn[i] = false;
//  }
//
//  pinMode(S0, OUTPUT);
//  pinMode(S1, OUTPUT);
//
//  Wire.begin();
//
//  Serial.println("Setup complete.");
//}
//
//void loop() {
//  EventHandler.processAllEvents();
//  sampleFSRs();
//}
//
//void noteOnListener(int note, int intensity) {
//  Serial.println(note);
//  switch (note) {
//    case 47:
//      Serial.print("FSR1 intensity: ");
//      Serial.println(intensity);
//
//      if (intensity < 400) {
//        MCP0.digitalWrite(RED1, HIGH);
//        MCP0.digitalWrite(GREEN1, LOW);
//        MCP0.digitalWrite(BLUE1, LOW);
//      }
//      else if (intensity < 550) {
//        MCP0.digitalWrite(RED1, LOW);
//        MCP0.digitalWrite(GREEN1, HIGH);
//        MCP0.digitalWrite(BLUE1, LOW);
//      }
//      else {
//        MCP0.digitalWrite(RED1, LOW);
//        MCP0.digitalWrite(GREEN1, LOW);
//        MCP0.digitalWrite(BLUE1, HIGH);
//      }
//
//      break;
//    case 59:
//      Serial.print("FSR2 intensity: ");
//      Serial.println(intensity);
//
//      if (intensity < 400) {
//        MCP0.digitalWrite(RED2, HIGH);
//        MCP0.digitalWrite(GREEN2, LOW);
//        MCP0.digitalWrite(BLUE2, LOW);
//      }
//      else if (intensity < 550) {
//        MCP0.digitalWrite(RED2, LOW);
//        MCP0.digitalWrite(GREEN2, HIGH);
//        MCP0.digitalWrite(BLUE2, LOW);
//      }
//      else {
//        MCP0.digitalWrite(RED2, LOW);
//        MCP0.digitalWrite(GREEN2, LOW);
//        MCP0.digitalWrite(BLUE2, HIGH);
//      }
//
//      break;
//    case 83:
//      Serial.print("FSR4 intensity: ");
//      Serial.println(intensity);
//
//      if (intensity < 400) {
//        MCP0.digitalWrite(RED4, HIGH);
//        MCP0.digitalWrite(GREEN4, LOW);
//        MCP0.digitalWrite(BLUE4, LOW);
//      }
//      else if (intensity < 550) {
//        MCP0.digitalWrite(RED4, LOW);
//        MCP0.digitalWrite(GREEN4, HIGH);
//        MCP0.digitalWrite(BLUE4, LOW);
//      }
//      else {
//        MCP0.digitalWrite(RED4, LOW);
//        MCP0.digitalWrite(GREEN4, LOW);
//        MCP0.digitalWrite(BLUE4, HIGH);
//      }
//
//      break;
//    case 71:
//      Serial.print("FSR3 intensity: ");
//      Serial.println(intensity);
//
//      if (intensity < 400) {
//        MCP0.digitalWrite(RED3, HIGH);
//        MCP0.digitalWrite(GREEN3, LOW);
//        MCP0.digitalWrite(BLUE3, LOW);
//      }
//      else if (intensity < 550) {
//        MCP0.digitalWrite(RED3, LOW);
//        MCP0.digitalWrite(GREEN3, HIGH);
//        MCP0.digitalWrite(BLUE3, LOW);
//      }
//      else {
//        MCP0.digitalWrite(RED3, LOW);
//        MCP0.digitalWrite(GREEN3, LOW);
//        MCP0.digitalWrite(BLUE3, HIGH);
//      }
//
//      break;
//    default:
//      break;
//  }
//}
//
//void sampleFSRs() {
//  int intensity;
//
//  digitalWrite(S1, LOW);
//  digitalWrite(S0, LOW);
//
//  // Sample through the first octave
//  for (int i = 0; i < 12; i++) {
//    intensity = analogRead(i);
//
//    if (intensity > THRESHOLD) {
//      if (i == 11) {
//        Serial.print("FSR 1 (B2) BROKE THE THRESHOLD: ");
//        Serial.println(intensity);
//
////        if (intensity < 400) {
////          MCP0.writeGPIOAB(RED1);
////        }
////        else if (intensity < 550) {
////          MCP0.writeGPIOAB(GREEN1);
////        }
////        else {
////          MCP0.writeGPIOAB(BLUE1);
////        }
//      }
//
//      notesOn[i] = true;
//      EventHandler.queueEvent(36, intensity);
//    }
//    else if (notesOn[i] == true) {
//      notesOn[i] = false;
//      MCP0.digitalWrite(RED1, LOW);
//      MCP0.digitalWrite(GREEN1, LOW);
//      MCP0.digitalWrite(BLUE1, LOW);
////      EventHandler.queueEvent(2 * (36 + i));
//    }
//  }
//
//  digitalWrite(S0, HIGH);
//
//  // Sample through the second octave
//  for (int i = 0; i < 12; i++) {
//    if (i == 11) {
//      digitalWrite(13, HIGH);
//    }
//
//    intensity = analogRead(i);
//
//    if (i == 11) {
//      digitalWrite(13, LOW);
//    }
//
//    if (intensity > THRESHOLD) {
//      if (i == 11) {
//        Serial.print("FSR 2 (B3) BROKE THE THRESHOLD: ");
//        Serial.println(intensity);
//
////        if (intensity < 400) {
////          MCP0.writeGPIOAB(RED2);
////        }
////        else if (intensity < 550) {
////          MCP0.writeGPIOAB(GREEN2);
////        }
////        else {
////          MCP0.writeGPIOAB(BLUE2);
////        }
//      }
//
//      notesOn[12 + i] = true;
//      EventHandler.queueEvent(48 + i, intensity);
//    }
//    else if (notesOn[i] == true) {
//      notesOn[i] = false;
//      MCP0.digitalWrite(RED2, LOW);
//      MCP0.digitalWrite(GREEN2, LOW);
//      MCP0.digitalWrite(BLUE2, LOW);
////      EventHandler.queueEvent(.......
//    }
//  }
//
//  digitalWrite(S1, HIGH);
//
//  // Sample through the fourth octave
//  for (int i = 0; i < 12; i++) {
//    intensity = analogRead(i);
//
//    if (intensity > THRESHOLD) {
//      if (i == 11) {
//        Serial.print("FSR 4 (B5) BROKE THE THRESHOLD: ");
//        Serial.println(intensity);
//
////        if (intensity < 400) {
////          MCP0.writeGPIOAB(RED4);
////        }
////        else if (intensity < 550) {
////          MCP0.writeGPIOAB(GREEN4);
////        }
////        else {
////          MCP0.writeGPIOAB(BLUE4);
////        }
//      }
//
//      notesOn[36 + i] = true;
//      EventHandler.queueEvent(72 + i, intensity);
//    }
//    else if (notesOn[i] == true) {
//      notesOn[i] = false;
//      MCP0.digitalWrite(RED4, LOW);
//      MCP0.digitalWrite(GREEN4, LOW);
//      MCP0.digitalWrite(BLUE4, LOW);
////      EventHandler.queueEvent(.......
//    }
//  }
//
//  digitalWrite(S0, LOW);
//
//  // Sample through the third octave
//  for (int i = 0; i < 12; i++) {
//    intensity = analogRead(i);
//
//    if (intensity > THRESHOLD) {
//      if (i == 11) {
//        Serial.print("FSR 3 (B4) BROKE THE THRESHOLD: ");
//        Serial.println(intensity);
//
////        if (intensity < 400) {
////          MCP0.writeGPIOAB(RED3);
////        }
////        else if (intensity < 550) {
////          MCP0.writeGPIOAB(GREEN3);
////        }
////        else {
////          MCP0.writeGPIOAB(BLUE3);
////        }
//      }
//
//      notesOn[36 + i] = true;
//      EventHandler.queueEvent(60 + i, intensity);
//    }
//    else if (notesOn[i] == true) {
//      notesOn[i] = false;
//      MCP0.digitalWrite(RED3, LOW);
//      MCP0.digitalWrite(GREEN3, LOW);
//      MCP0.digitalWrite(BLUE3, LOW);
////      EventHandler.queueEvent(......
//    }
//  }
//}
