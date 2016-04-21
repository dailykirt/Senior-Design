#include <MIDI.h>

//taken from:  http://www.notesandvolts.com/2012/01/fun-with-arduino-midi-input-basics.html

#define LED 13    // Arduino Board LED is on Pin 13

MIDI_CREATE_DEFAULT_INSTANCE();

//store notes to play back. 
byte pitchData[6];
int index = 0;

// Below is my function that will be called by the Midi Library
// when a MIDI NOTE ON message is received.
// It will be passed bytes for Channel, Pitch, and Velocity
void MyHandleNoteOn(byte channel, byte pitch, byte velocity) {
  if (velocity == 0) {//A NOTE ON message with a velocity = Zero is actualy a NOTE OFF
    //digitalWrite(LED,LOW);//Turn LED off
  }else{
      //digitalWrite(LED,HIGH);  //Turn LED on
      MIDI.sendNoteOn(pitch, velocity, 10);
      MIDI.sendNoteOff(pitch, 0, 10);
      //pitchData[index] = pitch;
      //index++;
     // if (index >= 6){
      //  index = 0; 
    //  }
  }
}

void setup() {
  pinMode (LED, OUTPUT); // Set Arduino board pin 13 to output
   pinMode(2, INPUT_PULLUP); //used to playback MIDI 
  MIDI.begin(1); // Initialize the Midi Library.
// OMNI sets it to listen to all channels.. MIDI.begin(2) would set it
// to respond to channel 2 notes only.
  Serial.begin(115200);
  MIDI.setHandleNoteOn(MIDI_CHANNEL_OMNI); // This is important!! This command
  // tells the Midi Library which function I want called when a Note ON command
  // is received. in this case it's "MyHandleNoteOn".
}

void loop() { // Main loop
  //pullup button on digital input 2
  //int sensorVal = digitalRead(2);
  //if button is presssed, play back previous 6 MIDI notess
  /*
  if (sensorVal == HIGH) {
        digitalWrite(LED,LOW);
   } else {
          digitalWrite(LED,HIGH);
          for(int i=0; i<6; i++){
             MIDI.sendNoteOn(pitchData[i], 90, 2);
             delay(500);
             MIDI.sendNoteOff(pitchData[i],0,2);
          }
  } */
    // Continually check what Midi Commands have been received.
  MIDI.read();
}
