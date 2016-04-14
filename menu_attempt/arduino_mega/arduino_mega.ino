/*
 * This code is for the Arduino Mega. 
 * 1. Prepare MIDI protocol and show loading screen by telling uno over I2C
 * 2. Tell uno to show menu screen once MIDI loading is done. 
 * 3. Once user selects mode on UNO, the Mega will pick up a 1 on a digital line
 * 4. Begin to read incoming MIDI data
 * 5. Send MIDI data over I2C.
 * 6. Uno will process data and show predicted key on screen. 
 * 7. Once MIDI is processed, the digital line will be high to signify finished MIDI data (and recieve predicted key?)
 */

void MyHandleNoteOn(byte channel, byte pitch, byte velocity) {
//This function is called when a MIDI NOTE ON message is recieved
  }



void setup() {
  // put your setup code here, to run once:
  MIDI.begin(1); // Initialize the Midi Library on channel 1.
  MIDI.setHandleNoteOn(MyHandleNoteOn);
  Serial.begin(115200);


}

void loop() {
  // put your main code here, to run repeatedly:
  MIDI.read();

}
