#include <MIDI.h>
#include <midi_Defs.h>
#include <midi_Message.h>
#include <midi_Namespace.h>
#include <midi_Settings.h>


// Simple tutorial on how to receive and send MIDI messages.
// Here, when receiving any message on channel 4, the Arduino
// will blink a led and play back a note for 1 second.
//this link gives documentation for MIDI library
//http://arduinomidilib.fortyseveneffects.com/a00014.html#a92150532e5720f95013e16a2f49a8df8

//use callbacks!!

MIDI_CREATE_DEFAULT_INSTANCE();

#define LED 13   		    // LED pin on Arduino Uno

typedef byte midi_data; 

//midi_data key;
//midi_data velocity;

byte commandByte;
byte noteByte;
byte velocityByte;

void setup()
{
    pinMode(LED, OUTPUT);
    pinMode(2, INPUT_PULLUP); //used to playback MIDI 
    MIDI.begin(4);          // Launch MIDI and listen to channel 4
    Serial.begin(115200);
}

void checkMIDI(){
  do{
    if (Serial.available()){
      commandByte = Serial.read();//read first byte
      noteByte = Serial.read();//read next byte
      velocityByte = Serial.read();//read final byte
    }
  }
  while (Serial.available() > 2);//when at least three bytes available
}

void loop()
{
   //array to store six midi notes
   int index = 0;
   int sensorVal = digitalRead(2);  

  //checkMIDI();
  //  if (MIDI.read())                // If we have received a message
   // {
      //midi_data key = (midi_data) MIDI.getData1();
      //midi_data velocity = (midi_data) MIDI.getData2();
   // }

  if (sensorVal == HIGH) {
        digitalWrite(LED,LOW);
  } else {
        digitalWrite(LED,HIGH);
          MIDI.sendNoteOn(noteByte, velocityByte,1);
          delay(1000);
          MIDI.sendNoteOff(noteByte,0,1);
  }
  
}
