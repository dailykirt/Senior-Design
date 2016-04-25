/* C2 - B5 (36 - 83)
*/

#include <EventManager.h>
#include <Wire.h>
#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 MCP0;
Adafruit_MCP23017 MCP1;
Adafruit_MCP23017 MCP2;

const int S0 = 6;
const int S1 = 5;
const int EN = 7;

const int THRESHOLD = 250;

//const uint16_t RED1 = 0x0001;
//const uint16_t GREEN1 = 0x0002;
//const uint16_t BLUE1 = 0x0004;
//const uint16_t RED2 = 0x0008;
//const uint16_t GREEN2 = 0x0010;
//const uint16_t BLUE2 = 0x0020;
//const uint16_t RED3 = 0x0040;
//const uint16_t GREEN3 = 0x0080;
//const uint16_t BLUE3 = 0x0100;
//const uint16_t RED4 = 0x0200;
//const uint16_t GREEN4 = 0x0400;
//const uint16_t BLUE4 = 0x0800;
const int RED1 = 0;
const int GREEN1 = 1;
const int BLUE1 = 2;
const int RED2 = 3;
const int GREEN2 = 4;
const int BLUE2 = 5;
const int RED3 = 6;
const int GREEN3 = 7;
const int BLUE3 = 8;
const int RED4 = 9;
const int GREEN4 = 10;
const int BLUE4 = 11;

bool notesOn[48];

EventManager EventHandler;

void setup() {
  Serial.begin(115200);
  Serial.println("Setup starting.");

  for (int note = 36; note < 84; note++) {
    //EventHandler.addListener(note, noteOnListener);
    //EventHandler.addListener(note + 48, noteOffListener);
  }

//  for (int i = 84; i < 132; i++) {
//    EventHandler.addListener(i, noteOff);
//  }

  MCP0.begin(0);
  MCP1.begin(1);
  MCP2.begin(2);

  for (int i = 0; i < 16; i++) {
    MCP0.pinMode(i, OUTPUT);
    MCP1.pinMode(i, OUTPUT);
    MCP2.pinMode(i, OUTPUT);
  }

  for (int i = 0; i < 48; i++) {
    notesOn[i] = false;
  }

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
//  pinMode(EN, OUTPUT);
//  pinMode(13, OUTPUT);

//  digitalWrite(EN, LOW);
//  digitalWrite(13, HIGH);

  Wire.begin();

  Serial.println("Setup complete.");
}

void loop() {
//  EventHandler.processAllEvents();
  sampleFSRs();

//  int intensity1 = analogRead(FSR1);
//  int intensity2 = analogRead(FSR2);
//
//  if (intensity1 > THRESHOLD) {
//    EventHandler.queueEvent(12, intensity1);
//  }
//  else {
//    MCP0.digitalWrite(7, LOW);
//    MCP0.digitalWrite(6, LOW);
//    MCP0.digitalWrite(5, LOW);
//  }
//
//  if (intensity2 > THRESHOLD) {
//    EventHandler.queueEvent(15, intensity2);
//  }
//  else {
//    MCP0.digitalWrite(8, LOW);
//    MCP0.digitalWrite(9, LOW);
//    MCP0.digitalWrite(10, LOW);
//  }
}

//void noteOnListener(int note, int intensity) {
//  switch (note) {
//    case 47:
//      Serial.print("FSR1 intensity: ");
//      Serial.println(intensity);
//
//      if (intensity < 400) {
//        MCP0.writeGPIOAB(RED1);
//      }
//      else if (intensity < 550) {
//        MCP0.writeGPIOAB(GREEN1);
//      }
//      else {
//        MCP0.writeGPIOAB(BLUE1);
//      }
//
//      break;
//    case 59:
//      Serial.print("FSR2 intensity: ");
//      Serial.println(intensity);
//
//      if (intensity < 400) {
//        MCP0.writeGPIOAB(RED2);
//      }
//      else if (intensity < 550) {
//        MCP0.writeGPIOAB(GREEN2);
//      }
//      else {
//        MCP0.writeGPIOAB(BLUE2);
//      }
//
//      break;
//    case 83:
//      Serial.print("FSR4 intensity: ");
//      Serial.println(intensity);
//
//      if (intensity < 400) {
//        MCP0.writeGPIOAB(RED4);
//      }
//      else if (intensity < 550) {
//        MCP0.writeGPIOAB(GREEN4);
//      }
//      else {
//        MCP0.writeGPIOAB(BLUE4);
//      }
//
//      break;
//    case 71:
//      Serial.print("FSR3 intensity: ");
//      Serial.println(intensity);
//
//      if (intensity < 400) {
//        MCP0.writeGPIOAB(RED3);
//      }
//      else if (intensity < 550) {
//        MCP0.writeGPIOAB(GREEN3);
//      }
//      else {
//        MCP0.writeGPIOAB(BLUE3);
//      }
//
//      break;
//    default:
//      break;
//  }
//}

//void noteOff(int note) {
//}

void sampleFSRs() {
  int intensity;

  digitalWrite(S1, LOW);
  digitalWrite(S0, LOW);

  // Sample through the first octave
  for (int i = 0; i < 12; i++) {
    intensity = analogRead(i);

    if (intensity > THRESHOLD) {
      if (i == 11) {
        Serial.print("FSR 1 BROKE THE THRESHOLD: ");
        Serial.println(intensity);

        MCP2.digitalWrite(13, HIGH);
//        if (intensity < 400) {
//          MCP0.writeGPIOAB(RED1);
//        }
//        else if (intensity < 550) {
//          MCP0.writeGPIOAB(GREEN1);
//        }
//        else {
//          MCP0.writeGPIOAB(BLUE1);
//        }
      }

      notesOn[i] = true;
//      EventHandler.queueEvent(36 + i, intensity);
    }
    else if (notesOn[i] == true) {
      notesOn[i] = false;
      MCP2.writeGPIOAB(0x0000);
//      EventHandler.queueEvent(2 * (36 + i));
    }
  }

  digitalWrite(S0, HIGH);

  // Sample through the second octave
  for (int i = 0; i < 12; i++) {
    intensity = analogRead(i);

    if (intensity > THRESHOLD) {
      if (i == 11) {
        Serial.print("FSR 2 BROKE THE THRESHOLD: ");
        Serial.println(intensity);

        MCP1.writeGPIOAB(0xFFFF);
//        if (intensity < 400) {
//          MCP0.writeGPIOAB(RED2);
//        }
//        else if (intensity < 550) {
//          MCP0.writeGPIOAB(GREEN2);
//        }
//        else {
//          MCP0.writeGPIOAB(BLUE2);
//        }
      }

      notesOn[12 + i] = true;
//      EventHandler.queueEvent(48 + i, intensity);
    }
    else if (notesOn[i] == true) {
      notesOn[i] = false;
      MCP1.writeGPIOAB(0x0000);
//      EventHandler.queueEvent(.......
    }
  }

  digitalWrite(S1, HIGH);

  // Sample through the fourth octave
  for (int i = 0; i < 12; i++) {
    intensity = analogRead(i);

    if (intensity > THRESHOLD) {
      if (i == 11) {
        Serial.print("FSR 4 BROKE THE THRESHOLD: ");
        Serial.println(intensity);

//        if (intensity < 400) {
//          MCP0.writeGPIOAB(RED4);
//        }
//        else if (intensity < 550) {
//          MCP0.writeGPIOAB(GREEN4);
//        }
//        else {
//          MCP0.writeGPIOAB(BLUE4);
//        }
      }

      notesOn[36 + i] = true;
//      EventHandler.queueEvent(72 + i, intensity);
    }
    else if (notesOn[i] == true) {
      notesOn[i] = false;
//      EventHandler.queueEvent(.......
    }
  }

  digitalWrite(S0, LOW);

  // Sample through the third octave
  for (int i = 0; i < 12; i++) {
    intensity = analogRead(i);

    if (intensity > THRESHOLD) {
      if (i == 11) {
        Serial.print("FSR 3 BROKE THE THRESHOLD: ");
        Serial.println(intensity);

//        if (intensity < 400) {
//          MCP0.writeGPIOAB(RED3);
//        }
//        else if (intensity < 550) {
//          MCP0.writeGPIOAB(GREEN3);
//        }
//        else {
//          MCP0.writeGPIOAB(BLUE3);
//        }
      }

      notesOn[36 + i] = true;
//      EventHandler.queueEvent(60 + i, intensity);
    }
    else if (notesOn[i] == true) {
      notesOn[i] = false;
//      EventHandler.queueEvent(......
    }
  }
}


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
//const int EN = 7;
//
//const int THRESHOLD = 250;
//
//const uint16_t RED1 = 0x0001;
//const uint16_t GREEN1 = 0x0002;
//const uint16_t BLUE1 = 0x0004;
//const uint16_t RED2 = 0x0008;
//const uint16_t GREEN2 = 0x0010;
//const uint16_t BLUE2 = 0x0020;
//const uint16_t RED3 = 0x0040;
//const uint16_t GREEN3 = 0x0080;
//const uint16_t BLUE3 = 0x0100;
//const uint16_t RED4 = 0x0200;
//const uint16_t GREEN4 = 0x0400;
//const uint16_t BLUE4 = 0x0800;
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
//    //EventHandler.addListener(note + 48, noteOffListener);
//  }
//
////  for (int i = 84; i < 132; i++) {
////    EventHandler.addListener(i, noteOff);
////  }
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
//  pinMode(EN, OUTPUT);
//  pinMode(13, OUTPUT);
//
//  digitalWrite(EN, LOW);
//  digitalWrite(13, HIGH);
//
//  Wire.begin();
//
//  Serial.println("Setup complete.");
//}
//
//void loop() {
////  EventHandler.processAllEvents();
//  sampleFSRs();
//
////  int intensity1 = analogRead(FSR1);
////  int intensity2 = analogRead(FSR2);
////
////  if (intensity1 > THRESHOLD) {
////    EventHandler.queueEvent(12, intensity1);
////  }
////  else {
////    MCP0.digitalWrite(7, LOW);
////    MCP0.digitalWrite(6, LOW);
////    MCP0.digitalWrite(5, LOW);
////  }
////
////  if (intensity2 > THRESHOLD) {
////    EventHandler.queueEvent(15, intensity2);
////  }
////  else {
////    MCP0.digitalWrite(8, LOW);
////    MCP0.digitalWrite(9, LOW);
////    MCP0.digitalWrite(10, LOW);
////  }
//}
//
//void noteOnListener(int note, int intensity) {
//  switch (note) {
//    case 47:
//      Serial.print("FSR1 intensity: ");
//      Serial.println(intensity);
//
//      if (intensity < 400) {
//        MCP0.writeGPIOAB(RED1);
//      }
//      else if (intensity < 550) {
//        MCP0.writeGPIOAB(GREEN1);
//      }
//      else {
//        MCP0.writeGPIOAB(BLUE1);
//      }
//
//      break;
//    case 59:
//      Serial.print("FSR2 intensity: ");
//      Serial.println(intensity);
//
//      if (intensity < 400) {
//        MCP0.writeGPIOAB(RED2);
//      }
//      else if (intensity < 550) {
//        MCP0.writeGPIOAB(GREEN2);
//      }
//      else {
//        MCP0.writeGPIOAB(BLUE2);
//      }
//
//      break;
//    case 83:
//      Serial.print("FSR4 intensity: ");
//      Serial.println(intensity);
//
//      if (intensity < 400) {
//        MCP0.writeGPIOAB(RED4);
//      }
//      else if (intensity < 550) {
//        MCP0.writeGPIOAB(GREEN4);
//      }
//      else {
//        MCP0.writeGPIOAB(BLUE4);
//      }
//
//      break;
//    case 71:
//      Serial.print("FSR3 intensity: ");
//      Serial.println(intensity);
//
//      if (intensity < 400) {
//        MCP0.writeGPIOAB(RED3);
//      }
//      else if (intensity < 550) {
//        MCP0.writeGPIOAB(GREEN3);
//      }
//      else {
//        MCP0.writeGPIOAB(BLUE3);
//      }
//
//      break;
//    default:
//      break;
//  }
//}
//
////void noteOff(int note) {
////}
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
//        Serial.print("FSR 1 BROKE THE THRESHOLD: ");
//        Serial.println(intensity);
//
//        if (intensity < 400) {
//          MCP0.writeGPIOAB(RED1);
//        }
//        else if (intensity < 550) {
//          MCP0.writeGPIOAB(GREEN1);
//        }
//        else {
//          MCP0.writeGPIOAB(BLUE1);
//        }
//      }
//
//      notesOn[i] = true;
//      EventHandler.queueEvent(36 + i, intensity);
//    }
//    else if (notesOn[i] == true) {
//      notesOn[i] = false;
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
//        Serial.print("FSR 2 BROKE THE THRESHOLD: ");
//        Serial.println(intensity);
//
//        if (intensity < 400) {
//          MCP0.writeGPIOAB(RED2);
//        }
//        else if (intensity < 550) {
//          MCP0.writeGPIOAB(GREEN2);
//        }
//        else {
//          MCP0.writeGPIOAB(BLUE2);
//        }
//      }
//
//      notesOn[12 + i] = true;
//      EventHandler.queueEvent(48 + i, intensity);
//    }
//    else if (notesOn[i] == true) {
//      notesOn[i] = false;
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
//        Serial.print("FSR 4 BROKE THE THRESHOLD: ");
//        Serial.println(intensity);
//
//        if (intensity < 400) {
//          MCP0.writeGPIOAB(RED4);
//        }
//        else if (intensity < 550) {
//          MCP0.writeGPIOAB(GREEN4);
//        }
//        else {
//          MCP0.writeGPIOAB(BLUE4);
//        }
//      }
//
//      notesOn[36 + i] = true;
//      EventHandler.queueEvent(72 + i, intensity);
//    }
//    else if (notesOn[i] == true) {
//      notesOn[i] = false;
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
//        Serial.print("FSR 3 BROKE THE THRESHOLD: ");
//        Serial.println(intensity);
//
//        if (intensity < 400) {
//          MCP0.writeGPIOAB(RED3);
//        }
//        else if (intensity < 550) {
//          MCP0.writeGPIOAB(GREEN3);
//        }
//        else {
//          MCP0.writeGPIOAB(BLUE3);
//        }
//      }
//
//      notesOn[36 + i] = true;
//      EventHandler.queueEvent(60 + i, intensity);
//    }
//    else if (notesOn[i] == true) {
//      notesOn[i] = false;
////      EventHandler.queueEvent(......
//    }
//  }
//}
