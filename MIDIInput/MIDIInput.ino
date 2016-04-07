#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

// Speaker pin
const int SPEAKER = 3;

void handleNoteOn(byte channel, byte pitch, byte velocity) {
  int note = (int) pitch;
  double frequency = 440.0 * pow(2.0, (note - 69.0) / 12.0);
  tone(SPEAKER, frequency);
}

void handleNoteOff(byte channel, byte pitch, byte velocity) {
  noTone(SPEAKER);
}

void setup() {
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.begin(MIDI_CHANNEL_OMNI);
  pinMode(SPEAKER, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  MIDI.read();
}
