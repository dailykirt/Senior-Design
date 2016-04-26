#include <MIDI.h>
#include <Wire.h>

MIDI_CREATE_DEFAULT_INSTANCE();

// FSR input pins
const int FSR1 = A0;
const int FSR2 = A1;
// MIDI output channel
const int CHANNEL = 1;
// Note values (SUBJECT TO CHANGE)
const byte NOTE1 = 60;
const byte NOTE2 = 67;
// Velocity values (SUBJECT TO CHANGE)
const byte VELOCITY1 = 50;
const byte VELOCITY2 = 100;

int intensity1 = 0;
int intensity2 = 0;
bool noteOn1 = false;
bool noteOn2 = false;

void setup() {
  MIDI.begin(1);
  Wire.begin();
}

void loop() {
  // Read the intensities from the FSRs
  intensity1 = analogRead(FSR1);
  intensity2 = analogRead(FSR2);

  // If the intensity of the first FSR passes its threshold
  if ((intensity1 > 35) && (noteOn1 == false)) {
    noteOn1 = true;
    MIDI.sendNoteOn(NOTE1, VELOCITY1, CHANNEL);
    Wire.beginTransmission(1);
    Wire.write(NOTE1);
    Wire.write(VELOCITY1);
    Wire.write(noteOn1);
    Wire.endTransmission();
  }

  // If the intensity of the first FSR goes below its threshold
  if ((intensity1 <= 35) && (noteOn1 == true)) {
    noteOn1 = false;
    MIDI.sendNoteOff(NOTE1, 0, CHANNEL);
    Wire.beginTransmission(1);
    Wire.write(NOTE1);
    Wire.write(0);
    Wire.write(noteOn1);
    Wire.endTransmission();
  }

  // If the intensity of the second FSR passes its threshold
  if ((intensity2 > 40) && (noteOn2 == false)) {
    noteOn2 = true;
    MIDI.sendNoteOn(NOTE2, VELOCITY2, CHANNEL);
    Wire.beginTransmission(1);
    Wire.write(NOTE2);
    Wire.write(VELOCITY2);
    Wire.write(noteOn2);
    Wire.endTransmission();
  }

  // If the intensity of the second FSR goes below its threshold
  if ((intensity2 <= 40) && (noteOn2 == true)) {
    noteOn2 = false;
    MIDI.sendNoteOff(NOTE2, 0, CHANNEL);
    Wire.beginTransmission(1);
    Wire.write(NOTE2);
    Wire.write(0);
    Wire.write(noteOn2);
    Wire.endTransmission();
  }
}
