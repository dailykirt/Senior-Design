#include <MIDI.h>
#include <UTFT.h>

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

MIDI_CREATE_DEFAULT_INSTANCE();

UTFT LCD(CTE32HR, 38, 39, 40, 41);

#define FSR1     1
#define FSR2     2
#define LED1     13
#define LED2     12
#define SPEAKER  11
#define CHANNEL  1

int intensity1 = 0;
int intensity2 = 0;
bool noteOn1 = false;
bool noteOn2 = false;

void setup() {
  // Initialize the LCD
  LCD.InitLCD();
  // Set the font
  LCD.setFont(BigFont);
  // Clear the screen
  LCD.clrScr();
  // Set the color to be red
  LCD.setColor(255, 0, 0);

  // LED output pins
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  MIDI.begin(1);
  Serial.begin(115200);
}

void loop() {
  intensity1 = analogRead(FSR1);
  intensity2 = analogRead(FSR2);

  LCD.printNumI(intensity1, 0, 0, 3, '0');
  LCD.printNumI(intensity2, 240, 0, 3, '0');

  if ((intensity1 > 40) && (noteOn1 == false)) {
    noteOn1 = true;
    MIDI.sendNoteOn(60, 127, CHANNEL);
  }

  if ((intensity1 <= 40) && (noteOn1 == true)) {
    noteOn1 = false;
    MIDI.sendNoteOff(60, 0, CHANNEL);
  }

  if ((intensity2 > 40) && (noteOn2 == false)) {
    noteOn2 = true;
    MIDI.sendNoteOn(67, 127, CHANNEL);
  }

  if ((intensity2 <= 40) && (noteOn2 == true)) {
    noteOn2 = false;
    MIDI.sendNoteOff(67, 0, CHANNEL);
  }
}
