#include <EventManager.h>
#include <Wire.h>
#include "Adafruit_MCP23017.h"

// MIDI note values
#define NOTE_C2     36
#define NOTE_CS2    37
#define NOTE_D2     38
#define NOTE_DS2    39
#define NOTE_E2     40
#define NOTE_F2     41
#define NOTE_FS2    42
#define NOTE_G2     43
#define NOTE_GS2    44
#define NOTE_A2     45
#define NOTE_AS2    46
#define NOTE_B2     47
#define NOTE_C3     48
#define NOTE_CS3    49
#define NOTE_D3     50
#define NOTE_DS3    51
#define NOTE_E3     52
#define NOTE_F3     53
#define NOTE_FS3    54
#define NOTE_G3     55
#define NOTE_GS3    56
#define NOTE_A3     57
#define NOTE_AS3    58
#define NOTE_B3     59
#define NOTE_C4     60
#define NOTE_CS4    61
#define NOTE_D4     62
#define NOTE_DS4    63
#define NOTE_E4     64
#define NOTE_F4     65
#define NOTE_FS4    66
#define NOTE_G4     67
#define NOTE_GS4    68
#define NOTE_A4     69
#define NOTE_AS4    70
#define NOTE_B4     71
#define NOTE_C5     72
#define NOTE_CS5    73
#define NOTE_D5     74
#define NOTE_DS5    75
#define NOTE_E5     76
#define NOTE_F5     77
#define NOTE_FS5    78
#define NOTE_G5     79
#define NOTE_GS5    80
#define NOTE_A5     81
#define NOTE_AS5    82
#define NOTE_B5     83

// Colors
#define BLACK       0
#define RED         1
#define GREEN       2
#define BLUE        3
#define YELLOW      4
#define MAGENTA     5
#define CYAN        6
#define WHITE       7

// Musical keys
#define CMAJOR      0
#define DFMAJOR     1
#define DMAJOR      2
#define EFMAJOR     3
#define EMAJOR      4
#define FMAJOR      5
#define FSMAJOR     6
#define GMAJOR      7
#define AFMAJOR     8
#define AMAJOR      9
#define BFMAJOR     10
#define BMAJOR      11
#define CMINOR      12
#define CSMINOR     13
#define DMINOR      14
#define DSMINOR     15
#define EMINOR      16
#define FMINOR      17
#define FSMINOR     18
#define GMINOR      19
#define GSMINOR     20
#define AMINOR      21
#define BFMINOR     22
#define BMINOR      23

// MCP23017 port expanders
Adafruit_MCP23017 MCP0;
Adafruit_MCP23017 MCP1;
Adafruit_MCP23017 MCP2;
Adafruit_MCP23017 MCP3;
Adafruit_MCP23017 MCP4;
Adafruit_MCP23017 MCP5;
Adafruit_MCP23017 MCP6;
Adafruit_MCP23017 MCP7;

const int THRESHOLD = 300;

const int S1 = 6;
const int S0 = 5;
const int MUXENABLE = 7;

const int I2CRESET = 12;

const int LED = 13;

const int MUXSWITCH = 11;

bool noteOn[48];
int keyColors[48];

//EventManager EventHandler;

void setup() {
  pinMode(LED, OUTPUT);

  MCP0.begin(0);
  MCP1.begin(1);
  MCP2.begin(2);
  MCP3.begin(3);
  MCP4.begin(4);
  MCP5.begin(5);
  MCP6.begin(6);
  MCP7.begin(7);

  digitalWrite(LED, HIGH);
  delay(1000);

  for (int i = 0; i < 16; i++) {
    MCP0.pinMode(i, OUTPUT);
    delay(10);
    MCP1.pinMode(i, OUTPUT);
    delay(10);
    MCP2.pinMode(i, OUTPUT);
    delay(10);
    MCP3.pinMode(i, OUTPUT);
    delay(10);
    MCP4.pinMode(i, OUTPUT);
    delay(10);
    MCP5.pinMode(i, OUTPUT);
    delay(10);
    MCP6.pinMode(i, OUTPUT);
    delay(10);
    MCP7.pinMode(i, OUTPUT);
    delay(10);
  }

  digitalWrite(LED, LOW);
  delay(1000);

  for (int i = 0; i < 48; i++) {
    noteOn[i] = false;
    keyColors[i] = BLACK;
  }

  pinMode(S1, OUTPUT);
  digitalWrite(S1, LOW);
  pinMode(S0, OUTPUT);
  digitalWrite(S0, LOW);
  pinMode(MUXENABLE, OUTPUT);
  digitalWrite(MUXENABLE, LOW);

  digitalWrite(LED, HIGH);
  delay(1000);

//  pinMode(I2CRESET, OUTPUT);
//  digitalWrite(I2CRESET, LOW);
//  delay(1000);
//  digitalWrite(I2CRESET, HIGH);

  Wire.begin();

  digitalWrite(LED, LOW);
  delay(1000);

  MCP0.writeGPIOAB(0xFFFF);
  MCP1.writeGPIOAB(0xFFFF);
  MCP2.writeGPIOAB(0xFFFF);
  MCP3.writeGPIOAB(0xFFFF);
  MCP4.writeGPIOAB(0xFFFF);
  MCP5.writeGPIOAB(0xFFFF);
  MCP6.writeGPIOAB(0xFFFF);
  MCP7.writeGPIOAB(0xFFFF);
  delay(1000);
  MCP0.writeGPIOAB(0x0000);
  MCP1.writeGPIOAB(0x0000);
  MCP2.writeGPIOAB(0x0000);
  MCP3.writeGPIOAB(0x0000);
  MCP4.writeGPIOAB(0x0000);
  MCP5.writeGPIOAB(0x0000);
  MCP6.writeGPIOAB(0x0000);
  MCP7.writeGPIOAB(0x0000);
  delay(1000);

  digitalWrite(LED, HIGH);
}

void loop() {
//  EventHandler.processAllEvents();
  sampleFSRs();
}

//void noteOnListener(int note, int intensity) {
//  if (intensity < 450) {
//    setColor(note, RED);
//  }
//  else if (intensity < 600) {
//    setColor(note, GREEN);
//  }
//  else {
//    setColor(note, BLUE);
//  }
//}

// Sets a corresponding RGB LED to the specified color
void setColor(int note, int color) {
  switch (note) {
    // C2
    case 36:
      switch (color) {
        case BLACK:
          MCP0.digitalWrite(8, LOW);
          MCP0.digitalWrite(9, LOW);
          MCP0.digitalWrite(10, LOW);
          break;
        case RED:
          MCP0.digitalWrite(8, HIGH);
          MCP0.digitalWrite(9, LOW);
          MCP0.digitalWrite(10, LOW);
          break;
        case GREEN:
          MCP0.digitalWrite(8, LOW);
          MCP0.digitalWrite(9, HIGH);
          MCP0.digitalWrite(10, LOW);
          break;
        case BLUE:
          MCP0.digitalWrite(8, LOW);
          MCP0.digitalWrite(9, LOW);
          MCP0.digitalWrite(10, HIGH);
          break;
        case YELLOW:
          MCP0.digitalWrite(8, HIGH);
          MCP0.digitalWrite(9, HIGH);
          MCP0.digitalWrite(10, LOW);
          break;
        case MAGENTA:
          MCP0.digitalWrite(8, HIGH);
          MCP0.digitalWrite(9, LOW);
          MCP0.digitalWrite(10, HIGH);
          break;
        case CYAN:
          MCP0.digitalWrite(8, LOW);
          MCP0.digitalWrite(9, HIGH);
          MCP0.digitalWrite(10, HIGH);
          break;
        case WHITE:
          MCP0.digitalWrite(8, HIGH);
          MCP0.digitalWrite(9, HIGH);
          MCP0.digitalWrite(10, HIGH);
          break;
        default:
          break;
      }

      break;
    // C#2
    case 37:
      switch (color) {
        case BLACK:
          MCP0.digitalWrite(11, LOW);
          MCP0.digitalWrite(12, LOW);
          MCP0.digitalWrite(13, LOW);
          break;
        case RED:
          MCP0.digitalWrite(11, HIGH);
          MCP0.digitalWrite(12, LOW);
          MCP0.digitalWrite(13, LOW);
          break;
        case GREEN:
          MCP0.digitalWrite(11, LOW);
          MCP0.digitalWrite(12, HIGH);
          MCP0.digitalWrite(13, LOW);
          break;
        case BLUE:
          MCP0.digitalWrite(11, LOW);
          MCP0.digitalWrite(12, LOW);
          MCP0.digitalWrite(13, HIGH);
          break;
        case YELLOW:
          MCP0.digitalWrite(11, HIGH);
          MCP0.digitalWrite(12, HIGH);
          MCP0.digitalWrite(13, LOW);
          break;
        case MAGENTA:
          MCP0.digitalWrite(11, HIGH);
          MCP0.digitalWrite(12, LOW);
          MCP0.digitalWrite(13, HIGH);
          break;
        case CYAN:
          MCP0.digitalWrite(11, LOW);
          MCP0.digitalWrite(12, HIGH);
          MCP0.digitalWrite(13, HIGH);
          break;
        case WHITE:
          MCP0.digitalWrite(11, HIGH);
          MCP0.digitalWrite(12, HIGH);
          MCP0.digitalWrite(13, HIGH);
          break;
        default:
          break;
      }

      break;
    // D2
    case 38:
      switch (color) {
        case BLACK:
          MCP0.digitalWrite(14, LOW);
          MCP0.digitalWrite(15, LOW);
          MCP0.digitalWrite(0, LOW);
          break;
        case RED:
          MCP0.digitalWrite(14, HIGH);
          MCP0.digitalWrite(15, LOW);
          MCP0.digitalWrite(0, LOW);
          break;
        case GREEN:
          MCP0.digitalWrite(14, LOW);
          MCP0.digitalWrite(15, HIGH);
          MCP0.digitalWrite(0, LOW);
          break;
        case BLUE:
          MCP0.digitalWrite(14, LOW);
          MCP0.digitalWrite(15, LOW);
          MCP0.digitalWrite(0, HIGH);
          break;
        case YELLOW:
          MCP0.digitalWrite(14, HIGH);
          MCP0.digitalWrite(15, HIGH);
          MCP0.digitalWrite(0, LOW);
          break;
        case MAGENTA:
          MCP0.digitalWrite(14, HIGH);
          MCP0.digitalWrite(15, LOW);
          MCP0.digitalWrite(0, HIGH);
          break;
        case CYAN:
          MCP0.digitalWrite(14, LOW);
          MCP0.digitalWrite(15, HIGH);
          MCP0.digitalWrite(0, HIGH);
          break;
        case WHITE:
          MCP0.digitalWrite(14, HIGH);
          MCP0.digitalWrite(15, HIGH);
          MCP0.digitalWrite(0, HIGH);
          break;
        default:
          break;
      }

      break;
    // D#2
    case 39:
      switch (color) {
        case BLACK:
          MCP0.digitalWrite(1, LOW);
          MCP0.digitalWrite(2, LOW);
          MCP0.digitalWrite(3, LOW);
          break;
        case RED:
          MCP0.digitalWrite(1, HIGH);
          MCP0.digitalWrite(2, LOW);
          MCP0.digitalWrite(3, LOW);
          break;
        case GREEN:
          MCP0.digitalWrite(1, LOW);
          MCP0.digitalWrite(2, HIGH);
          MCP0.digitalWrite(3, LOW);
          break;
        case BLUE:
          MCP0.digitalWrite(1, LOW);
          MCP0.digitalWrite(2, LOW);
          MCP0.digitalWrite(3, HIGH);
          break;
        case YELLOW:
          MCP0.digitalWrite(1, HIGH);
          MCP0.digitalWrite(2, HIGH);
          MCP0.digitalWrite(3, LOW);
          break;
        case MAGENTA:
          MCP0.digitalWrite(1, HIGH);
          MCP0.digitalWrite(2, LOW);
          MCP0.digitalWrite(3, HIGH);
          break;
        case CYAN:
          MCP0.digitalWrite(1, LOW);
          MCP0.digitalWrite(2, HIGH);
          MCP0.digitalWrite(3, HIGH);
          break;
        case WHITE:
          MCP0.digitalWrite(1, HIGH);
          MCP0.digitalWrite(2, HIGH);
          MCP0.digitalWrite(3, HIGH);
          break;
        default:
          break;
      }

      break;
    // E2
    case 40:
      switch (color) {
        case BLACK:
          MCP0.digitalWrite(4, LOW);
          MCP0.digitalWrite(5, LOW);
          MCP0.digitalWrite(6, LOW);
          break;
        case RED:
          MCP0.digitalWrite(4, HIGH);
          MCP0.digitalWrite(5, LOW);
          MCP0.digitalWrite(6, LOW);
          break;
        case GREEN:
          MCP0.digitalWrite(4, LOW);
          MCP0.digitalWrite(5, HIGH);
          MCP0.digitalWrite(6, LOW);
          break;
        case BLUE:
          MCP0.digitalWrite(4, LOW);
          MCP0.digitalWrite(5, LOW);
          MCP0.digitalWrite(6, HIGH);
          break;
        case YELLOW:
          MCP0.digitalWrite(4, HIGH);
          MCP0.digitalWrite(5, HIGH);
          MCP0.digitalWrite(6, LOW);
          break;
        case MAGENTA:
          MCP0.digitalWrite(4, HIGH);
          MCP0.digitalWrite(5, LOW);
          MCP0.digitalWrite(6, HIGH);
          break;
        case CYAN:
          MCP0.digitalWrite(4, LOW);
          MCP0.digitalWrite(5, HIGH);
          MCP0.digitalWrite(6, HIGH);
          break;
        case WHITE:
          MCP0.digitalWrite(4, HIGH);
          MCP0.digitalWrite(5, HIGH);
          MCP0.digitalWrite(6, HIGH);
          break;
        default:
          break;
      }

      break;
    // F2
    case 41:
      switch (color) {
        case BLACK:
          MCP0.digitalWrite(7, LOW);
          MCP4.digitalWrite(8, LOW);
          MCP4.digitalWrite(9, LOW);
          break;
        case RED:
          MCP0.digitalWrite(7, HIGH);
          MCP4.digitalWrite(8, LOW);
          MCP4.digitalWrite(9, LOW);
          break;
        case GREEN:
          MCP0.digitalWrite(7, LOW);
          MCP4.digitalWrite(8, HIGH);
          MCP4.digitalWrite(9, LOW);
          break;
        case BLUE:
          MCP0.digitalWrite(7, LOW);
          MCP4.digitalWrite(8, LOW);
          MCP4.digitalWrite(9, HIGH);
          break;
        case YELLOW:
          MCP0.digitalWrite(7, HIGH);
          MCP4.digitalWrite(8, HIGH);
          MCP4.digitalWrite(9, LOW);
          break;
        case MAGENTA:
          MCP0.digitalWrite(7, HIGH);
          MCP4.digitalWrite(8, LOW);
          MCP4.digitalWrite(9, HIGH);
          break;
        case CYAN:
          MCP0.digitalWrite(7, LOW);
          MCP4.digitalWrite(8, HIGH);
          MCP4.digitalWrite(9, HIGH);
          break;
        case WHITE:
          MCP0.digitalWrite(7, HIGH);
          MCP4.digitalWrite(8, HIGH);
          MCP4.digitalWrite(9, HIGH);
          break;
        default:
          break;
      }

      break;
    // F#2
    case 42:
      switch (color) {
        case BLACK:
          MCP4.digitalWrite(10, LOW);
          MCP4.digitalWrite(11, LOW);
          MCP4.digitalWrite(12, LOW);
          break;
        case RED:
          MCP4.digitalWrite(10, HIGH);
          MCP4.digitalWrite(11, LOW);
          MCP4.digitalWrite(12, LOW);
          break;
        case GREEN:
          MCP4.digitalWrite(10, LOW);
          MCP4.digitalWrite(11, HIGH);
          MCP4.digitalWrite(12, LOW);
          break;
        case BLUE:
          MCP4.digitalWrite(10, LOW);
          MCP4.digitalWrite(11, LOW);
          MCP4.digitalWrite(12, HIGH);
          break;
        case YELLOW:
          MCP4.digitalWrite(10, HIGH);
          MCP4.digitalWrite(11, HIGH);
          MCP4.digitalWrite(12, LOW);
          break;
        case MAGENTA:
          MCP4.digitalWrite(10, HIGH);
          MCP4.digitalWrite(11, LOW);
          MCP4.digitalWrite(12, HIGH);
          break;
        case CYAN:
          MCP4.digitalWrite(10, LOW);
          MCP4.digitalWrite(11, HIGH);
          MCP4.digitalWrite(12, HIGH);
          break;
        case WHITE:
          MCP4.digitalWrite(10, HIGH);
          MCP4.digitalWrite(11, HIGH);
          MCP4.digitalWrite(12, HIGH);
          break;
        default:
          break;
      }

      break;
    // G2
    case 43:
      switch (color) {
        case BLACK:
          MCP4.digitalWrite(13, LOW);
          MCP4.digitalWrite(14, LOW);
          MCP4.digitalWrite(15, LOW);
          break;
        case RED:
          MCP4.digitalWrite(13, HIGH);
          MCP4.digitalWrite(14, LOW);
          MCP4.digitalWrite(15, LOW);
          break;
        case GREEN:
          MCP4.digitalWrite(13, LOW);
          MCP4.digitalWrite(14, HIGH);
          MCP4.digitalWrite(15, LOW);
          break;
        case BLUE:
          MCP4.digitalWrite(13, LOW);
          MCP4.digitalWrite(14, LOW);
          MCP4.digitalWrite(15, HIGH);
          break;
        case YELLOW:
          MCP4.digitalWrite(13, HIGH);
          MCP4.digitalWrite(14, HIGH);
          MCP4.digitalWrite(15, LOW);
          break;
        case MAGENTA:
          MCP4.digitalWrite(13, HIGH);
          MCP4.digitalWrite(14, LOW);
          MCP4.digitalWrite(15, HIGH);
          break;
        case CYAN:
          MCP4.digitalWrite(13, LOW);
          MCP4.digitalWrite(14, HIGH);
          MCP4.digitalWrite(15, HIGH);
          break;
        case WHITE:
          MCP4.digitalWrite(13, HIGH);
          MCP4.digitalWrite(14, HIGH);
          MCP4.digitalWrite(15, HIGH);
          break;
        default:
          break;
      }

      break;
    // G#2
    case 44:
      switch (color) {
        case BLACK:
          MCP4.digitalWrite(0, LOW);
          MCP4.digitalWrite(1, LOW);
          MCP4.digitalWrite(2, LOW);
          break;
        case RED:
          MCP4.digitalWrite(0, HIGH);
          MCP4.digitalWrite(1, LOW);
          MCP4.digitalWrite(2, LOW);
          break;
        case GREEN:
          MCP4.digitalWrite(0, LOW);
          MCP4.digitalWrite(1, HIGH);
          MCP4.digitalWrite(2, LOW);
          break;
        case BLUE:
          MCP4.digitalWrite(0, LOW);
          MCP4.digitalWrite(1, LOW);
          MCP4.digitalWrite(2, HIGH);
          break;
        case YELLOW:
          MCP4.digitalWrite(0, HIGH);
          MCP4.digitalWrite(1, HIGH);
          MCP4.digitalWrite(2, LOW);
          break;
        case MAGENTA:
          MCP4.digitalWrite(0, HIGH);
          MCP4.digitalWrite(1, LOW);
          MCP4.digitalWrite(2, HIGH);
          break;
        case CYAN:
          MCP4.digitalWrite(0, LOW);
          MCP4.digitalWrite(1, HIGH);
          MCP4.digitalWrite(2, HIGH);
          break;
        case WHITE:
          MCP4.digitalWrite(0, HIGH);
          MCP4.digitalWrite(1, HIGH);
          MCP4.digitalWrite(2, HIGH);
          break;
        default:
          break;
      }

      break;
    // A2
    case 45:
      switch (color) {
        case BLACK:
          MCP4.digitalWrite(3, LOW);
          MCP4.digitalWrite(4, LOW);
          MCP4.digitalWrite(5, LOW);
          break;
        case RED:
          MCP4.digitalWrite(3, HIGH);
          MCP4.digitalWrite(4, LOW);
          MCP4.digitalWrite(5, LOW);
          break;
        case GREEN:
          MCP4.digitalWrite(3, LOW);
          MCP4.digitalWrite(4, HIGH);
          MCP4.digitalWrite(5, LOW);
          break;
        case BLUE:
          MCP4.digitalWrite(3, LOW);
          MCP4.digitalWrite(4, LOW);
          MCP4.digitalWrite(5, HIGH);
          break;
        case YELLOW:
          MCP4.digitalWrite(3, HIGH);
          MCP4.digitalWrite(4, HIGH);
          MCP4.digitalWrite(5, LOW);
          break;
        case MAGENTA:
          MCP4.digitalWrite(3, HIGH);
          MCP4.digitalWrite(4, LOW);
          MCP4.digitalWrite(5, HIGH);
          break;
        case CYAN:
          MCP4.digitalWrite(3, LOW);
          MCP4.digitalWrite(4, HIGH);
          MCP4.digitalWrite(5, HIGH);
          break;
        case WHITE:
          MCP4.digitalWrite(3, HIGH);
          MCP4.digitalWrite(4, HIGH);
          MCP4.digitalWrite(5, HIGH);
          break;
        default:
          break;
      }

      break;
    // A#2
    case 46:
      switch (color) {
        case BLACK:
          MCP4.digitalWrite(6, LOW);
          MCP4.digitalWrite(7, LOW);
          MCP2.digitalWrite(8, LOW);
          break;
        case RED:
          MCP4.digitalWrite(6, HIGH);
          MCP4.digitalWrite(7, LOW);
          MCP2.digitalWrite(8, LOW);
          break;
        case GREEN:
          MCP4.digitalWrite(6, LOW);
          MCP4.digitalWrite(7, HIGH);
          MCP2.digitalWrite(8, LOW);
          break;
        case BLUE:
          MCP4.digitalWrite(6, LOW);
          MCP4.digitalWrite(7, LOW);
          MCP2.digitalWrite(8, HIGH);
          break;
        case YELLOW:
          MCP4.digitalWrite(6, HIGH);
          MCP4.digitalWrite(7, HIGH);
          MCP2.digitalWrite(8, LOW);
          break;
        case MAGENTA:
          MCP4.digitalWrite(6, HIGH);
          MCP4.digitalWrite(7, LOW);
          MCP2.digitalWrite(8, HIGH);
          break;
        case CYAN:
          MCP4.digitalWrite(6, LOW);
          MCP4.digitalWrite(7, HIGH);
          MCP2.digitalWrite(8, HIGH);
          break;
        case WHITE:
          MCP4.digitalWrite(6, HIGH);
          MCP4.digitalWrite(7, HIGH);
          MCP2.digitalWrite(8, HIGH);
          break;
        default:
          break;
      }

      break;
    // B2
    case 47:
      switch (color) {
        case BLACK:
          MCP2.digitalWrite(9, LOW);
          MCP2.digitalWrite(10, LOW);
          MCP2.digitalWrite(11, LOW);
          break;
        case RED:
          MCP2.digitalWrite(9, HIGH);
          MCP2.digitalWrite(10, LOW);
          MCP2.digitalWrite(11, LOW);
          break;
        case GREEN:
          MCP2.digitalWrite(9, LOW);
          MCP2.digitalWrite(10, HIGH);
          MCP2.digitalWrite(11, LOW);
          break;
        case BLUE:
          MCP2.digitalWrite(9, LOW);
          MCP2.digitalWrite(10, LOW);
          MCP2.digitalWrite(11, HIGH);
          break;
        case YELLOW:
          MCP2.digitalWrite(9, HIGH);
          MCP2.digitalWrite(10, HIGH);
          MCP2.digitalWrite(11, LOW);
          break;
        case MAGENTA:
          MCP2.digitalWrite(9, HIGH);
          MCP2.digitalWrite(10, LOW);
          MCP2.digitalWrite(11, HIGH);
          break;
        case CYAN:
          MCP2.digitalWrite(9, LOW);
          MCP2.digitalWrite(10, HIGH);
          MCP2.digitalWrite(11, HIGH);
          break;
        case WHITE:
          MCP2.digitalWrite(9, HIGH);
          MCP2.digitalWrite(10, HIGH);
          MCP2.digitalWrite(11, HIGH);
          break;
        default:
          break;
      }

      break;
    // C3
    case 48:
      switch (color) {
        case BLACK:
          MCP2.digitalWrite(12, LOW);
          MCP2.digitalWrite(13, LOW);
          MCP2.digitalWrite(14, LOW);
          break;
        case RED:
          MCP2.digitalWrite(12, HIGH);
          MCP2.digitalWrite(13, LOW);
          MCP2.digitalWrite(14, LOW);
          break;
        case GREEN:
          MCP2.digitalWrite(12, LOW);
          MCP2.digitalWrite(13, HIGH);
          MCP2.digitalWrite(14, LOW);
          break;
        case BLUE:
          MCP2.digitalWrite(12, LOW);
          MCP2.digitalWrite(13, LOW);
          MCP2.digitalWrite(14, HIGH);
          break;
        case YELLOW:
          MCP2.digitalWrite(12, HIGH);
          MCP2.digitalWrite(13, HIGH);
          MCP2.digitalWrite(14, LOW);
          break;
        case MAGENTA:
          MCP2.digitalWrite(12, HIGH);
          MCP2.digitalWrite(13, LOW);
          MCP2.digitalWrite(14, HIGH);
          break;
        case CYAN:
          MCP2.digitalWrite(12, LOW);
          MCP2.digitalWrite(13, HIGH);
          MCP2.digitalWrite(14, HIGH);
          break;
        case WHITE:
          MCP2.digitalWrite(12, HIGH);
          MCP2.digitalWrite(13, HIGH);
          MCP2.digitalWrite(14, HIGH);
          break;
        default:
          break;
      }

      break;
    // C#3
    case 49:
      switch (color) {
        case BLACK:
          MCP2.digitalWrite(15, LOW);
          MCP2.digitalWrite(0, LOW);
          MCP2.digitalWrite(1, LOW);
          break;
        case RED:
          MCP2.digitalWrite(15, HIGH);
          MCP2.digitalWrite(0, LOW);
          MCP2.digitalWrite(1, LOW);
          break;
        case GREEN:
          MCP2.digitalWrite(15, LOW);
          MCP2.digitalWrite(0, HIGH);
          MCP2.digitalWrite(1, LOW);
          break;
        case BLUE:
          MCP2.digitalWrite(15, LOW);
          MCP2.digitalWrite(0, LOW);
          MCP2.digitalWrite(1, HIGH);
          break;
        case YELLOW:
          MCP2.digitalWrite(15, HIGH);
          MCP2.digitalWrite(0, HIGH);
          MCP2.digitalWrite(1, LOW);
          break;
        case MAGENTA:
          MCP2.digitalWrite(15, HIGH);
          MCP2.digitalWrite(0, LOW);
          MCP2.digitalWrite(1, HIGH);
          break;
        case CYAN:
          MCP2.digitalWrite(15, LOW);
          MCP2.digitalWrite(0, HIGH);
          MCP2.digitalWrite(1, HIGH);
          break;
        case WHITE:
          MCP2.digitalWrite(15, HIGH);
          MCP2.digitalWrite(0, HIGH);
          MCP2.digitalWrite(1, HIGH);
          break;
        default:
          break;
      }

      break;
    // D3
    case 50:
      switch (color) {
        case BLACK:
          MCP2.digitalWrite(2, LOW);
          MCP2.digitalWrite(3, LOW);
          MCP2.digitalWrite(4, LOW);
          break;
        case RED:
          MCP2.digitalWrite(2, HIGH);
          MCP2.digitalWrite(3, LOW);
          MCP2.digitalWrite(4, LOW);
          break;
        case GREEN:
          MCP2.digitalWrite(2, LOW);
          MCP2.digitalWrite(3, HIGH);
          MCP2.digitalWrite(4, LOW);
          break;
        case BLUE:
          MCP2.digitalWrite(2, LOW);
          MCP2.digitalWrite(3, LOW);
          MCP2.digitalWrite(4, HIGH);
          break;
        case YELLOW:
          MCP2.digitalWrite(2, HIGH);
          MCP2.digitalWrite(3, HIGH);
          MCP2.digitalWrite(4, LOW);
          break;
        case MAGENTA:
          MCP2.digitalWrite(2, HIGH);
          MCP2.digitalWrite(3, LOW);
          MCP2.digitalWrite(4, HIGH);
          break;
        case CYAN:
          MCP2.digitalWrite(2, LOW);
          MCP2.digitalWrite(3, HIGH);
          MCP2.digitalWrite(4, HIGH);
          break;
        case WHITE:
          MCP2.digitalWrite(2, HIGH);
          MCP2.digitalWrite(3, HIGH);
          MCP2.digitalWrite(4, HIGH);
          break;
        default:
          break;
      }

      break;
    // D#3
    case 51:
      switch (color) {
        case BLACK:
          MCP2.digitalWrite(5, LOW);
          MCP2.digitalWrite(6, LOW);
          MCP2.digitalWrite(7, LOW);
          break;
        case RED:
          MCP2.digitalWrite(5, HIGH);
          MCP2.digitalWrite(6, LOW);
          MCP2.digitalWrite(7, LOW);
          break;
        case GREEN:
          MCP2.digitalWrite(5, LOW);
          MCP2.digitalWrite(6, HIGH);
          MCP2.digitalWrite(7, LOW);
          break;
        case BLUE:
          MCP2.digitalWrite(5, LOW);
          MCP2.digitalWrite(6, LOW);
          MCP2.digitalWrite(7, HIGH);
          break;
        case YELLOW:
          MCP2.digitalWrite(5, HIGH);
          MCP2.digitalWrite(6, HIGH);
          MCP2.digitalWrite(7, LOW);
          break;
        case MAGENTA:
          MCP2.digitalWrite(5, HIGH);
          MCP2.digitalWrite(6, LOW);
          MCP2.digitalWrite(7, HIGH);
          break;
        case CYAN:
          MCP2.digitalWrite(5, LOW);
          MCP2.digitalWrite(6, HIGH);
          MCP2.digitalWrite(7, HIGH);
          break;
        case WHITE:
          MCP2.digitalWrite(5, HIGH);
          MCP2.digitalWrite(6, HIGH);
          MCP2.digitalWrite(7, HIGH);
          break;
        default:
          break;
      }

      break;
    // E3
    case 52:
      switch (color) {
        case BLACK:
          MCP6.digitalWrite(8, LOW);
          MCP6.digitalWrite(9, LOW);
          MCP6.digitalWrite(10, LOW);
          break;
        case RED:
          MCP6.digitalWrite(8, HIGH);
          MCP6.digitalWrite(9, LOW);
          MCP6.digitalWrite(10, LOW);
          break;
        case GREEN:
          MCP6.digitalWrite(8, LOW);
          MCP6.digitalWrite(9, HIGH);
          MCP6.digitalWrite(10, LOW);
          break;
        case BLUE:
          MCP6.digitalWrite(8, LOW);
          MCP6.digitalWrite(9, LOW);
          MCP6.digitalWrite(10, HIGH);
          break;
        case YELLOW:
          MCP6.digitalWrite(8, HIGH);
          MCP6.digitalWrite(9, HIGH);
          MCP6.digitalWrite(10, LOW);
          break;
        case MAGENTA:
          MCP6.digitalWrite(8, HIGH);
          MCP6.digitalWrite(9, LOW);
          MCP6.digitalWrite(10, HIGH);
          break;
        case CYAN:
          MCP6.digitalWrite(8, LOW);
          MCP6.digitalWrite(9, HIGH);
          MCP6.digitalWrite(10, HIGH);
          break;
        case WHITE:
          MCP6.digitalWrite(8, HIGH);
          MCP6.digitalWrite(9, HIGH);
          MCP6.digitalWrite(10, HIGH);
          break;
        default:
          break;
      }

      break;
    // F3
    case 53:
      switch (color) {
        case BLACK:
          MCP6.digitalWrite(11, LOW);
          MCP6.digitalWrite(12, LOW);
          MCP6.digitalWrite(13, LOW);
          break;
        case RED:
          MCP6.digitalWrite(11, HIGH);
          MCP6.digitalWrite(12, LOW);
          MCP6.digitalWrite(13, LOW);
          break;
        case GREEN:
          MCP6.digitalWrite(11, LOW);
          MCP6.digitalWrite(12, HIGH);
          MCP6.digitalWrite(13, LOW);
          break;
        case BLUE:
          MCP6.digitalWrite(11, LOW);
          MCP6.digitalWrite(12, LOW);
          MCP6.digitalWrite(13, HIGH);
          break;
        case YELLOW:
          MCP6.digitalWrite(11, HIGH);
          MCP6.digitalWrite(12, HIGH);
          MCP6.digitalWrite(13, LOW);
          break;
        case MAGENTA:
          MCP6.digitalWrite(11, HIGH);
          MCP6.digitalWrite(12, LOW);
          MCP6.digitalWrite(13, HIGH);
          break;
        case CYAN:
          MCP6.digitalWrite(11, LOW);
          MCP6.digitalWrite(12, HIGH);
          MCP6.digitalWrite(13, HIGH);
          break;
        case WHITE:
          MCP6.digitalWrite(11, HIGH);
          MCP6.digitalWrite(12, HIGH);
          MCP6.digitalWrite(13, HIGH);
          break;
        default:
          break;
      }

      break;
    // F#3
    case 54:
      switch (color) {
        case BLACK:
          MCP6.digitalWrite(14, LOW);
          MCP6.digitalWrite(15, LOW);
          MCP6.digitalWrite(0, LOW);
          break;
        case RED:
          MCP6.digitalWrite(14, HIGH);
          MCP6.digitalWrite(15, LOW);
          MCP6.digitalWrite(0, LOW);
          break;
        case GREEN:
          MCP6.digitalWrite(14, LOW);
          MCP6.digitalWrite(15, HIGH);
          MCP6.digitalWrite(0, LOW);
          break;
        case BLUE:
          MCP6.digitalWrite(14, LOW);
          MCP6.digitalWrite(15, LOW);
          MCP6.digitalWrite(0, HIGH);
          break;
        case YELLOW:
          MCP6.digitalWrite(14, HIGH);
          MCP6.digitalWrite(15, HIGH);
          MCP6.digitalWrite(0, LOW);
          break;
        case MAGENTA:
          MCP6.digitalWrite(14, HIGH);
          MCP6.digitalWrite(15, LOW);
          MCP6.digitalWrite(0, HIGH);
          break;
        case CYAN:
          MCP6.digitalWrite(14, LOW);
          MCP6.digitalWrite(15, HIGH);
          MCP6.digitalWrite(0, HIGH);
          break;
        case WHITE:
          MCP6.digitalWrite(14, HIGH);
          MCP6.digitalWrite(15, HIGH);
          MCP6.digitalWrite(0, HIGH);
          break;
        default:
          break;
      }

      break;
    // G3
    case 55:
      switch (color) {
        case BLACK:
          MCP6.digitalWrite(1, LOW);
          MCP6.digitalWrite(2, LOW);
          MCP6.digitalWrite(3, LOW);
          break;
        case RED:
          MCP6.digitalWrite(1, HIGH);
          MCP6.digitalWrite(2, LOW);
          MCP6.digitalWrite(3, LOW);
          break;
        case GREEN:
          MCP6.digitalWrite(1, LOW);
          MCP6.digitalWrite(2, HIGH);
          MCP6.digitalWrite(3, LOW);
          break;
        case BLUE:
          MCP6.digitalWrite(1, LOW);
          MCP6.digitalWrite(2, LOW);
          MCP6.digitalWrite(3, HIGH);
          break;
        case YELLOW:
          MCP6.digitalWrite(1, HIGH);
          MCP6.digitalWrite(2, HIGH);
          MCP6.digitalWrite(3, LOW);
          break;
        case MAGENTA:
          MCP6.digitalWrite(1, HIGH);
          MCP6.digitalWrite(2, LOW);
          MCP6.digitalWrite(3, HIGH);
          break;
        case CYAN:
          MCP6.digitalWrite(1, LOW);
          MCP6.digitalWrite(2, HIGH);
          MCP6.digitalWrite(3, HIGH);
          break;
        case WHITE:
          MCP6.digitalWrite(1, HIGH);
          MCP6.digitalWrite(2, HIGH);
          MCP6.digitalWrite(3, HIGH);
          break;
        default:
          break;
      }

      break;
    // G#3
    case 56:
      switch (color) {
        case BLACK:
          MCP6.digitalWrite(4, LOW);
          MCP6.digitalWrite(5, LOW);
          MCP6.digitalWrite(6, LOW);
          break;
        case RED:
          MCP6.digitalWrite(4, HIGH);
          MCP6.digitalWrite(5, LOW);
          MCP6.digitalWrite(6, LOW);
          break;
        case GREEN:
          MCP6.digitalWrite(4, LOW);
          MCP6.digitalWrite(5, HIGH);
          MCP6.digitalWrite(6, LOW);
          break;
        case BLUE:
          MCP6.digitalWrite(4, LOW);
          MCP6.digitalWrite(5, LOW);
          MCP6.digitalWrite(6, HIGH);
          break;
        case YELLOW:
          MCP6.digitalWrite(4, HIGH);
          MCP6.digitalWrite(5, HIGH);
          MCP6.digitalWrite(6, LOW);
          break;
        case MAGENTA:
          MCP6.digitalWrite(4, HIGH);
          MCP6.digitalWrite(5, LOW);
          MCP6.digitalWrite(6, HIGH);
          break;
        case CYAN:
          MCP6.digitalWrite(4, LOW);
          MCP6.digitalWrite(5, HIGH);
          MCP6.digitalWrite(6, HIGH);
          break;
        case WHITE:
          MCP6.digitalWrite(4, HIGH);
          MCP6.digitalWrite(5, HIGH);
          MCP6.digitalWrite(6, HIGH);
          break;
        default:
          break;
      }

      break;
    // A3
    case 57:
      switch (color) {
        case BLACK:
          MCP6.digitalWrite(7, LOW);
          MCP1.digitalWrite(8, LOW);
          MCP1.digitalWrite(9, LOW);
          break;
        case RED:
          MCP6.digitalWrite(7, HIGH);
          MCP1.digitalWrite(8, LOW);
          MCP1.digitalWrite(9, LOW);
          break;
        case GREEN:
          MCP6.digitalWrite(7, LOW);
          MCP1.digitalWrite(8, HIGH);
          MCP1.digitalWrite(9, LOW);
          break;
        case BLUE:
          MCP6.digitalWrite(7, LOW);
          MCP1.digitalWrite(8, LOW);
          MCP1.digitalWrite(9, HIGH);
          break;
        case YELLOW:
          MCP6.digitalWrite(7, HIGH);
          MCP1.digitalWrite(8, HIGH);
          MCP1.digitalWrite(9, LOW);
          break;
        case MAGENTA:
          MCP6.digitalWrite(7, HIGH);
          MCP1.digitalWrite(8, LOW);
          MCP1.digitalWrite(9, HIGH);
          break;
        case CYAN:
          MCP6.digitalWrite(7, LOW);
          MCP1.digitalWrite(8, HIGH);
          MCP1.digitalWrite(9, HIGH);
          break;
        case WHITE:
          MCP6.digitalWrite(7, HIGH);
          MCP1.digitalWrite(8, HIGH);
          MCP1.digitalWrite(9, HIGH);
          break;
        default:
          break;
      }

      break;
    // A#3
    case 58:
      switch (color) {
        case BLACK:
          MCP1.digitalWrite(10, LOW);
          MCP1.digitalWrite(11, LOW);
          MCP1.digitalWrite(12, LOW);
          break;
        case RED:
          MCP1.digitalWrite(10, HIGH);
          MCP1.digitalWrite(11, LOW);
          MCP1.digitalWrite(12, LOW);
          break;
        case GREEN:
          MCP1.digitalWrite(10, LOW);
          MCP1.digitalWrite(11, HIGH);
          MCP1.digitalWrite(12, LOW);
          break;
        case BLUE:
          MCP1.digitalWrite(10, LOW);
          MCP1.digitalWrite(11, LOW);
          MCP1.digitalWrite(12, HIGH);
          break;
        case YELLOW:
          MCP1.digitalWrite(10, HIGH);
          MCP1.digitalWrite(11, HIGH);
          MCP1.digitalWrite(12, LOW);
          break;
        case MAGENTA:
          MCP1.digitalWrite(10, HIGH);
          MCP1.digitalWrite(11, LOW);
          MCP1.digitalWrite(12, HIGH);
          break;
        case CYAN:
          MCP1.digitalWrite(10, LOW);
          MCP1.digitalWrite(11, HIGH);
          MCP1.digitalWrite(12, HIGH);
          break;
        case WHITE:
          MCP1.digitalWrite(10, HIGH);
          MCP1.digitalWrite(11, HIGH);
          MCP1.digitalWrite(12, HIGH);
          break;
        default:
          break;
      }

      break;
    // B3
    case 59:
      switch (color) {
        case BLACK:
          MCP1.digitalWrite(13, LOW);
          MCP1.digitalWrite(14, LOW);
          MCP1.digitalWrite(15, LOW);
          break;
        case RED:
          MCP1.digitalWrite(13, HIGH);
          MCP1.digitalWrite(14, LOW);
          MCP1.digitalWrite(15, LOW);
          break;
        case GREEN:
          MCP1.digitalWrite(13, LOW);
          MCP1.digitalWrite(14, HIGH);
          MCP1.digitalWrite(15, LOW);
          break;
        case BLUE:
          MCP1.digitalWrite(13, LOW);
          MCP1.digitalWrite(14, LOW);
          MCP1.digitalWrite(15, HIGH);
          break;
        case YELLOW:
          MCP1.digitalWrite(13, HIGH);
          MCP1.digitalWrite(14, HIGH);
          MCP1.digitalWrite(15, LOW);
          break;
        case MAGENTA:
          MCP1.digitalWrite(13, HIGH);
          MCP1.digitalWrite(14, LOW);
          MCP1.digitalWrite(15, HIGH);
          break;
        case CYAN:
          MCP1.digitalWrite(13, LOW);
          MCP1.digitalWrite(14, HIGH);
          MCP1.digitalWrite(15, HIGH);
          break;
        case WHITE:
          MCP1.digitalWrite(13, HIGH);
          MCP1.digitalWrite(14, HIGH);
          MCP1.digitalWrite(15, HIGH);
          break;
        default:
          break;
      }

      break;
    // C4
    case 60:
      switch (color) {
        case BLACK:
          MCP1.digitalWrite(0, LOW);
          MCP1.digitalWrite(1, LOW);
          MCP1.digitalWrite(2, LOW);
          break;
        case RED:
          MCP1.digitalWrite(0, HIGH);
          MCP1.digitalWrite(1, LOW);
          MCP1.digitalWrite(2, LOW);
          break;
        case GREEN:
          MCP1.digitalWrite(0, LOW);
          MCP1.digitalWrite(1, HIGH);
          MCP1.digitalWrite(2, LOW);
          break;
        case BLUE:
          MCP1.digitalWrite(0, LOW);
          MCP1.digitalWrite(1, LOW);
          MCP1.digitalWrite(2, HIGH);
          break;
        case YELLOW:
          MCP1.digitalWrite(0, HIGH);
          MCP1.digitalWrite(1, HIGH);
          MCP1.digitalWrite(2, LOW);
          break;
        case MAGENTA:
          MCP1.digitalWrite(0, HIGH);
          MCP1.digitalWrite(1, LOW);
          MCP1.digitalWrite(2, HIGH);
          break;
        case CYAN:
          MCP1.digitalWrite(0, LOW);
          MCP1.digitalWrite(1, HIGH);
          MCP1.digitalWrite(2, HIGH);
          break;
        case WHITE:
          MCP1.digitalWrite(0, HIGH);
          MCP1.digitalWrite(1, HIGH);
          MCP1.digitalWrite(2, HIGH);
          break;
        default:
          break;
      }

      break;
    // C#4
    case 61:
      switch (color) {
        case BLACK:
          MCP1.digitalWrite(3, LOW);
          MCP1.digitalWrite(4, LOW);
          MCP1.digitalWrite(5, LOW);
          break;
        case RED:
          MCP1.digitalWrite(3, HIGH);
          MCP1.digitalWrite(4, LOW);
          MCP1.digitalWrite(5, LOW);
          break;
        case GREEN:
          MCP1.digitalWrite(3, LOW);
          MCP1.digitalWrite(4, HIGH);
          MCP1.digitalWrite(5, LOW);
          break;
        case BLUE:
          MCP1.digitalWrite(3, LOW);
          MCP1.digitalWrite(4, LOW);
          MCP1.digitalWrite(5, HIGH);
          break;
        case YELLOW:
          MCP1.digitalWrite(3, HIGH);
          MCP1.digitalWrite(4, HIGH);
          MCP1.digitalWrite(5, LOW);
          break;
        case MAGENTA:
          MCP1.digitalWrite(3, HIGH);
          MCP1.digitalWrite(4, LOW);
          MCP1.digitalWrite(5, HIGH);
          break;
        case CYAN:
          MCP1.digitalWrite(3, LOW);
          MCP1.digitalWrite(4, HIGH);
          MCP1.digitalWrite(5, HIGH);
          break;
        case WHITE:
          MCP1.digitalWrite(3, HIGH);
          MCP1.digitalWrite(4, HIGH);
          MCP1.digitalWrite(5, HIGH);
          break;
        default:
          break;
      }

      break;
    // D4
    case 62:
      switch (color) {
        case BLACK:
          MCP1.digitalWrite(6, LOW);
          MCP1.digitalWrite(7, LOW);
          MCP5.digitalWrite(8, LOW);
          break;
        case RED:
          MCP1.digitalWrite(6, HIGH);
          MCP1.digitalWrite(7, LOW);
          MCP5.digitalWrite(8, LOW);
          break;
        case GREEN:
          MCP1.digitalWrite(6, LOW);
          MCP1.digitalWrite(7, HIGH);
          MCP5.digitalWrite(8, LOW);
          break;
        case BLUE:
          MCP1.digitalWrite(6, LOW);
          MCP1.digitalWrite(7, LOW);
          MCP5.digitalWrite(8, HIGH);
          break;
        case YELLOW:
          MCP1.digitalWrite(6, HIGH);
          MCP1.digitalWrite(7, HIGH);
          MCP5.digitalWrite(8, LOW);
          break;
        case MAGENTA:
          MCP1.digitalWrite(6, HIGH);
          MCP1.digitalWrite(7, LOW);
          MCP5.digitalWrite(8, HIGH);
          break;
        case CYAN:
          MCP1.digitalWrite(6, LOW);
          MCP1.digitalWrite(7, HIGH);
          MCP5.digitalWrite(8, HIGH);
          break;
        case WHITE:
          MCP1.digitalWrite(6, HIGH);
          MCP1.digitalWrite(7, HIGH);
          MCP5.digitalWrite(8, HIGH);
          break;
        default:
          break;
      }

      break;
    // D#4
    case 63:
      switch (color) {
        case BLACK:
          MCP5.digitalWrite(9, LOW);
          MCP5.digitalWrite(10, LOW);
          MCP5.digitalWrite(11, LOW);
          break;
        case RED:
          MCP5.digitalWrite(9, HIGH);
          MCP5.digitalWrite(10, LOW);
          MCP5.digitalWrite(11, LOW);
          break;
        case GREEN:
          MCP5.digitalWrite(9, LOW);
          MCP5.digitalWrite(10, HIGH);
          MCP5.digitalWrite(11, LOW);
          break;
        case BLUE:
          MCP5.digitalWrite(9, LOW);
          MCP5.digitalWrite(10, LOW);
          MCP5.digitalWrite(11, HIGH);
          break;
        case YELLOW:
          MCP5.digitalWrite(9, HIGH);
          MCP5.digitalWrite(10, HIGH);
          MCP5.digitalWrite(11, LOW);
          break;
        case MAGENTA:
          MCP5.digitalWrite(9, HIGH);
          MCP5.digitalWrite(10, LOW);
          MCP5.digitalWrite(11, HIGH);
          break;
        case CYAN:
          MCP5.digitalWrite(9, LOW);
          MCP5.digitalWrite(10, HIGH);
          MCP5.digitalWrite(11, HIGH);
          break;
        case WHITE:
          MCP5.digitalWrite(9, HIGH);
          MCP5.digitalWrite(10, HIGH);
          MCP5.digitalWrite(11, HIGH);
          break;
        default:
          break;
      }

      break;
    // E4
    case 64:
      switch (color) {
        case BLACK:
          MCP5.digitalWrite(12, LOW);
          MCP5.digitalWrite(13, LOW);
          MCP5.digitalWrite(14, LOW);
          break;
        case RED:
          MCP5.digitalWrite(12, HIGH);
          MCP5.digitalWrite(13, LOW);
          MCP5.digitalWrite(14, LOW);
          break;
        case GREEN:
          MCP5.digitalWrite(12, LOW);
          MCP5.digitalWrite(13, HIGH);
          MCP5.digitalWrite(14, LOW);
          break;
        case BLUE:
          MCP5.digitalWrite(12, LOW);
          MCP5.digitalWrite(13, LOW);
          MCP5.digitalWrite(14, HIGH);
          break;
        case YELLOW:
          MCP5.digitalWrite(12, HIGH);
          MCP5.digitalWrite(13, HIGH);
          MCP5.digitalWrite(14, LOW);
          break;
        case MAGENTA:
          MCP5.digitalWrite(12, HIGH);
          MCP5.digitalWrite(13, LOW);
          MCP5.digitalWrite(14, HIGH);
          break;
        case CYAN:
          MCP5.digitalWrite(12, LOW);
          MCP5.digitalWrite(13, HIGH);
          MCP5.digitalWrite(14, HIGH);
          break;
        case WHITE:
          MCP5.digitalWrite(12, HIGH);
          MCP5.digitalWrite(13, HIGH);
          MCP5.digitalWrite(14, HIGH);
          break;
        default:
          break;
      }

      break;
    // F4
    case 65:
      switch (color) {
        case BLACK:
          MCP5.digitalWrite(15, LOW);
          MCP5.digitalWrite(0, LOW);
          MCP5.digitalWrite(1, LOW);
          break;
        case RED:
          MCP5.digitalWrite(15, HIGH);
          MCP5.digitalWrite(0, LOW);
          MCP5.digitalWrite(1, LOW);
          break;
        case GREEN:
          MCP5.digitalWrite(15, LOW);
          MCP5.digitalWrite(0, HIGH);
          MCP5.digitalWrite(1, LOW);
          break;
        case BLUE:
          MCP5.digitalWrite(15, LOW);
          MCP5.digitalWrite(0, LOW);
          MCP5.digitalWrite(1, HIGH);
          break;
        case YELLOW:
          MCP5.digitalWrite(15, HIGH);
          MCP5.digitalWrite(0, HIGH);
          MCP5.digitalWrite(1, LOW);
          break;
        case MAGENTA:
          MCP5.digitalWrite(15, HIGH);
          MCP5.digitalWrite(0, LOW);
          MCP5.digitalWrite(1, HIGH);
          break;
        case CYAN:
          MCP5.digitalWrite(15, LOW);
          MCP5.digitalWrite(0, HIGH);
          MCP5.digitalWrite(1, HIGH);
          break;
        case WHITE:
          MCP5.digitalWrite(15, HIGH);
          MCP5.digitalWrite(0, HIGH);
          MCP5.digitalWrite(1, HIGH);
          break;
        default:
          break;
      }

      break;
    // F#4
    case 66:
      switch (color) {
        case BLACK:
          MCP5.digitalWrite(2, LOW);
          MCP5.digitalWrite(3, LOW);
          MCP5.digitalWrite(4, LOW);
          break;
        case RED:
          MCP5.digitalWrite(2, HIGH);
          MCP5.digitalWrite(3, LOW);
          MCP5.digitalWrite(4, LOW);
          break;
        case GREEN:
          MCP5.digitalWrite(2, LOW);
          MCP5.digitalWrite(3, HIGH);
          MCP5.digitalWrite(4, LOW);
          break;
        case BLUE:
          MCP5.digitalWrite(2, LOW);
          MCP5.digitalWrite(3, LOW);
          MCP5.digitalWrite(4, HIGH);
          break;
        case YELLOW:
          MCP5.digitalWrite(2, HIGH);
          MCP5.digitalWrite(3, HIGH);
          MCP5.digitalWrite(4, LOW);
          break;
        case MAGENTA:
          MCP5.digitalWrite(2, HIGH);
          MCP5.digitalWrite(3, LOW);
          MCP5.digitalWrite(4, HIGH);
          break;
        case CYAN:
          MCP5.digitalWrite(2, LOW);
          MCP5.digitalWrite(3, HIGH);
          MCP5.digitalWrite(4, HIGH);
          break;
        case WHITE:
          MCP5.digitalWrite(2, HIGH);
          MCP5.digitalWrite(3, HIGH);
          MCP5.digitalWrite(4, HIGH);
          break;
        default:
          break;
      }

      break;
    // G4
    case 67:
      switch (color) {
        case BLACK:
          MCP5.digitalWrite(5, LOW);
          MCP5.digitalWrite(6, LOW);
          MCP5.digitalWrite(7, LOW);
          break;
        case RED:
          MCP5.digitalWrite(5, HIGH);
          MCP5.digitalWrite(6, LOW);
          MCP5.digitalWrite(7, LOW);
          break;
        case GREEN:
          MCP5.digitalWrite(5, LOW);
          MCP5.digitalWrite(6, HIGH);
          MCP5.digitalWrite(7, LOW);
          break;
        case BLUE:
          MCP5.digitalWrite(5, LOW);
          MCP5.digitalWrite(6, LOW);
          MCP5.digitalWrite(7, HIGH);
          break;
        case YELLOW:
          MCP5.digitalWrite(5, HIGH);
          MCP5.digitalWrite(6, HIGH);
          MCP5.digitalWrite(7, LOW);
          break;
        case MAGENTA:
          MCP5.digitalWrite(5, HIGH);
          MCP5.digitalWrite(6, LOW);
          MCP5.digitalWrite(7, HIGH);
          break;
        case CYAN:
          MCP5.digitalWrite(5, LOW);
          MCP5.digitalWrite(6, HIGH);
          MCP5.digitalWrite(7, HIGH);
          break;
        case WHITE:
          MCP5.digitalWrite(5, HIGH);
          MCP5.digitalWrite(6, HIGH);
          MCP5.digitalWrite(7, HIGH);
          break;
        default:
          break;
      }

      break;
    // G#4
    case 68:
      switch (color) {
        case BLACK:
          MCP3.digitalWrite(8, LOW);
          MCP3.digitalWrite(9, LOW);
          MCP3.digitalWrite(10, LOW);
          break;
        case RED:
          MCP3.digitalWrite(8, HIGH);
          MCP3.digitalWrite(9, LOW);
          MCP3.digitalWrite(10, LOW);
          break;
        case GREEN:
          MCP3.digitalWrite(8, LOW);
          MCP3.digitalWrite(9, HIGH);
          MCP3.digitalWrite(10, LOW);
          break;
        case BLUE:
          MCP3.digitalWrite(8, LOW);
          MCP3.digitalWrite(9, LOW);
          MCP3.digitalWrite(10, HIGH);
          break;
        case YELLOW:
          MCP3.digitalWrite(8, HIGH);
          MCP3.digitalWrite(9, HIGH);
          MCP3.digitalWrite(10, LOW);
          break;
        case MAGENTA:
          MCP3.digitalWrite(8, HIGH);
          MCP3.digitalWrite(9, LOW);
          MCP3.digitalWrite(10, HIGH);
          break;
        case CYAN:
          MCP3.digitalWrite(8, LOW);
          MCP3.digitalWrite(9, HIGH);
          MCP3.digitalWrite(10, HIGH);
          break;
        case WHITE:
          MCP3.digitalWrite(8, HIGH);
          MCP3.digitalWrite(9, HIGH);
          MCP3.digitalWrite(10, HIGH);
          break;
        default:
          break;
      }

      break;
    // A4
    case 69:
      switch (color) {
        case BLACK:
          MCP3.digitalWrite(11, LOW);
          MCP3.digitalWrite(12, LOW);
          MCP3.digitalWrite(13, LOW);
          break;
        case RED:
          MCP3.digitalWrite(11, HIGH);
          MCP3.digitalWrite(12, LOW);
          MCP3.digitalWrite(13, LOW);
          break;
        case GREEN:
          MCP3.digitalWrite(11, LOW);
          MCP3.digitalWrite(12, HIGH);
          MCP3.digitalWrite(13, LOW);
          break;
        case BLUE:
          MCP3.digitalWrite(11, LOW);
          MCP3.digitalWrite(12, LOW);
          MCP3.digitalWrite(13, HIGH);
          break;
        case YELLOW:
          MCP3.digitalWrite(11, HIGH);
          MCP3.digitalWrite(12, HIGH);
          MCP3.digitalWrite(13, LOW);
          break;
        case MAGENTA:
          MCP3.digitalWrite(11, HIGH);
          MCP3.digitalWrite(12, LOW);
          MCP3.digitalWrite(13, HIGH);
          break;
        case CYAN:
          MCP3.digitalWrite(11, LOW);
          MCP3.digitalWrite(12, HIGH);
          MCP3.digitalWrite(13, HIGH);
          break;
        case WHITE:
          MCP3.digitalWrite(11, HIGH);
          MCP3.digitalWrite(12, HIGH);
          MCP3.digitalWrite(13, HIGH);
          break;
        default:
          break;
      }

      break;
    // A#4
    case 70:
      switch (color) {
        case BLACK:
          MCP3.digitalWrite(14, LOW);
          MCP3.digitalWrite(15, LOW);
          MCP3.digitalWrite(0, LOW);
          break;
        case RED:
          MCP3.digitalWrite(14, HIGH);
          MCP3.digitalWrite(15, LOW);
          MCP3.digitalWrite(0, LOW);
          break;
        case GREEN:
          MCP3.digitalWrite(14, LOW);
          MCP3.digitalWrite(15, HIGH);
          MCP3.digitalWrite(0, LOW);
          break;
        case BLUE:
          MCP3.digitalWrite(14, LOW);
          MCP3.digitalWrite(15, LOW);
          MCP3.digitalWrite(0, HIGH);
          break;
        case YELLOW:
          MCP3.digitalWrite(14, HIGH);
          MCP3.digitalWrite(15, HIGH);
          MCP3.digitalWrite(0, LOW);
          break;
        case MAGENTA:
          MCP3.digitalWrite(14, HIGH);
          MCP3.digitalWrite(15, LOW);
          MCP3.digitalWrite(0, HIGH);
          break;
        case CYAN:
          MCP3.digitalWrite(14, LOW);
          MCP3.digitalWrite(15, HIGH);
          MCP3.digitalWrite(0, HIGH);
          break;
        case WHITE:
          MCP3.digitalWrite(14, HIGH);
          MCP3.digitalWrite(15, HIGH);
          MCP3.digitalWrite(0, HIGH);
          break;
        default:
          break;
      }

      break;
    // B4
    case 71:
      switch (color) {
        case BLACK:
          MCP3.digitalWrite(1, LOW);
          MCP3.digitalWrite(2, LOW);
          MCP3.digitalWrite(3, LOW);
          break;
        case RED:
          MCP3.digitalWrite(1, HIGH);
          MCP3.digitalWrite(2, LOW);
          MCP3.digitalWrite(3, LOW);
          break;
        case GREEN:
          MCP3.digitalWrite(1, LOW);
          MCP3.digitalWrite(2, HIGH);
          MCP3.digitalWrite(3, LOW);
          break;
        case BLUE:
          MCP3.digitalWrite(1, LOW);
          MCP3.digitalWrite(2, LOW);
          MCP3.digitalWrite(3, HIGH);
          break;
        case YELLOW:
          MCP3.digitalWrite(1, HIGH);
          MCP3.digitalWrite(2, HIGH);
          MCP3.digitalWrite(3, LOW);
          break;
        case MAGENTA:
          MCP3.digitalWrite(1, HIGH);
          MCP3.digitalWrite(2, LOW);
          MCP3.digitalWrite(3, HIGH);
          break;
        case CYAN:
          MCP3.digitalWrite(1, LOW);
          MCP3.digitalWrite(2, HIGH);
          MCP3.digitalWrite(3, HIGH);
          break;
        case WHITE:
          MCP3.digitalWrite(1, HIGH);
          MCP3.digitalWrite(2, HIGH);
          MCP3.digitalWrite(3, HIGH);
          break;
        default:
          break;
      }

      break;
    // C5
    case 72:
      switch (color) {
        case BLACK:
          MCP3.digitalWrite(4, LOW);
          MCP3.digitalWrite(5, LOW);
          MCP3.digitalWrite(6, LOW);
          break;
        case RED:
          MCP3.digitalWrite(4, HIGH);
          MCP3.digitalWrite(5, LOW);
          MCP3.digitalWrite(6, LOW);
          break;
        case GREEN:
          MCP3.digitalWrite(4, LOW);
          MCP3.digitalWrite(5, HIGH);
          MCP3.digitalWrite(6, LOW);
          break;
        case BLUE:
          MCP3.digitalWrite(4, LOW);
          MCP3.digitalWrite(5, LOW);
          MCP3.digitalWrite(6, HIGH);
          break;
        case YELLOW:
          MCP3.digitalWrite(4, HIGH);
          MCP3.digitalWrite(5, HIGH);
          MCP3.digitalWrite(6, LOW);
          break;
        case MAGENTA:
          MCP3.digitalWrite(4, HIGH);
          MCP3.digitalWrite(5, LOW);
          MCP3.digitalWrite(6, HIGH);
          break;
        case CYAN:
          MCP3.digitalWrite(4, LOW);
          MCP3.digitalWrite(5, HIGH);
          MCP3.digitalWrite(6, HIGH);
          break;
        case WHITE:
          MCP3.digitalWrite(4, HIGH);
          MCP3.digitalWrite(5, HIGH);
          MCP3.digitalWrite(6, HIGH);
          break;
        default:
          break;
      }

      break;
    // C#5
    case 73:
      switch (color) {
        case BLACK:
          MCP3.digitalWrite(7, LOW);
          MCP7.digitalWrite(8, LOW);
          MCP7.digitalWrite(9, LOW);
          break;
        case RED:
          MCP3.digitalWrite(7, HIGH);
          MCP7.digitalWrite(8, LOW);
          MCP7.digitalWrite(9, LOW);
          break;
        case GREEN:
          MCP3.digitalWrite(7, LOW);
          MCP7.digitalWrite(8, HIGH);
          MCP7.digitalWrite(9, LOW);
          break;
        case BLUE:
          MCP3.digitalWrite(7, LOW);
          MCP7.digitalWrite(8, LOW);
          MCP7.digitalWrite(9, HIGH);
          break;
        case YELLOW:
          MCP3.digitalWrite(7, HIGH);
          MCP7.digitalWrite(8, HIGH);
          MCP7.digitalWrite(9, LOW);
          break;
        case MAGENTA:
          MCP3.digitalWrite(7, HIGH);
          MCP7.digitalWrite(8, LOW);
          MCP7.digitalWrite(9, HIGH);
          break;
        case CYAN:
          MCP3.digitalWrite(7, LOW);
          MCP7.digitalWrite(8, HIGH);
          MCP7.digitalWrite(9, HIGH);
          break;
        case WHITE:
          MCP3.digitalWrite(7, HIGH);
          MCP7.digitalWrite(8, HIGH);
          MCP7.digitalWrite(9, HIGH);
          break;
        default:
          break;
      }

      break;
    // D5
    case 74:
      switch (color) {
        case BLACK:
          MCP7.digitalWrite(10, LOW);
          MCP7.digitalWrite(11, LOW);
          MCP7.digitalWrite(12, LOW);
          break;
        case RED:
          MCP7.digitalWrite(10, HIGH);
          MCP7.digitalWrite(11, LOW);
          MCP7.digitalWrite(12, LOW);
          break;
        case GREEN:
          MCP7.digitalWrite(10, LOW);
          MCP7.digitalWrite(11, HIGH);
          MCP7.digitalWrite(12, LOW);
          break;
        case BLUE:
          MCP7.digitalWrite(10, LOW);
          MCP7.digitalWrite(11, LOW);
          MCP7.digitalWrite(12, HIGH);
          break;
        case YELLOW:
          MCP7.digitalWrite(10, HIGH);
          MCP7.digitalWrite(11, HIGH);
          MCP7.digitalWrite(12, LOW);
          break;
        case MAGENTA:
          MCP7.digitalWrite(10, HIGH);
          MCP7.digitalWrite(11, LOW);
          MCP7.digitalWrite(12, HIGH);
          break;
        case CYAN:
          MCP7.digitalWrite(10, LOW);
          MCP7.digitalWrite(11, HIGH);
          MCP7.digitalWrite(12, HIGH);
          break;
        case WHITE:
          MCP7.digitalWrite(10, HIGH);
          MCP7.digitalWrite(11, HIGH);
          MCP7.digitalWrite(12, HIGH);
          break;
        default:
          break;
      }

      break;
    // D#5
    case 75:
      switch (color) {
        case BLACK:
          MCP7.digitalWrite(13, LOW);
          MCP7.digitalWrite(14, LOW);
          MCP7.digitalWrite(15, LOW);
          break;
        case RED:
          MCP7.digitalWrite(13, HIGH);
          MCP7.digitalWrite(14, LOW);
          MCP7.digitalWrite(15, LOW);
          break;
        case GREEN:
          MCP7.digitalWrite(13, LOW);
          MCP7.digitalWrite(14, HIGH);
          MCP7.digitalWrite(15, LOW);
          break;
        case BLUE:
          MCP7.digitalWrite(13, LOW);
          MCP7.digitalWrite(14, LOW);
          MCP7.digitalWrite(15, HIGH);
          break;
        case YELLOW:
          MCP7.digitalWrite(13, HIGH);
          MCP7.digitalWrite(14, HIGH);
          MCP7.digitalWrite(15, LOW);
          break;
        case MAGENTA:
          MCP7.digitalWrite(13, HIGH);
          MCP7.digitalWrite(14, LOW);
          MCP7.digitalWrite(15, HIGH);
          break;
        case CYAN:
          MCP7.digitalWrite(13, LOW);
          MCP7.digitalWrite(14, HIGH);
          MCP7.digitalWrite(15, HIGH);
          break;
        case WHITE:
          MCP7.digitalWrite(13, HIGH);
          MCP7.digitalWrite(14, HIGH);
          MCP7.digitalWrite(15, HIGH);
          break;
        default:
          break;
      }

      break;
    // E5
    case 76:
      switch (color) {
        case BLACK:
          MCP7.digitalWrite(0, LOW);
          MCP7.digitalWrite(1, LOW);
          MCP7.digitalWrite(2, LOW);
          break;
        case RED:
          MCP7.digitalWrite(0, HIGH);
          MCP7.digitalWrite(1, LOW);
          MCP7.digitalWrite(2, LOW);
          break;
        case GREEN:
          MCP7.digitalWrite(0, LOW);
          MCP7.digitalWrite(1, HIGH);
          MCP7.digitalWrite(2, LOW);
          break;
        case BLUE:
          MCP7.digitalWrite(0, LOW);
          MCP7.digitalWrite(1, LOW);
          MCP7.digitalWrite(2, HIGH);
          break;
        case YELLOW:
          MCP7.digitalWrite(0, HIGH);
          MCP7.digitalWrite(1, HIGH);
          MCP7.digitalWrite(2, LOW);
          break;
        case MAGENTA:
          MCP7.digitalWrite(0, HIGH);
          MCP7.digitalWrite(1, LOW);
          MCP7.digitalWrite(2, HIGH);
          break;
        case CYAN:
          MCP7.digitalWrite(0, LOW);
          MCP7.digitalWrite(1, HIGH);
          MCP7.digitalWrite(2, HIGH);
          break;
        case WHITE:
          MCP7.digitalWrite(0, HIGH);
          MCP7.digitalWrite(1, HIGH);
          MCP7.digitalWrite(2, HIGH);
          break;
        default:
          break;
      }

      break;
    // F5
    case 77:
      switch (color) {
        case BLACK:
          MCP7.digitalWrite(3, LOW);
          MCP7.digitalWrite(4, LOW);
          MCP7.digitalWrite(5, LOW);
          break;
        case RED:
          MCP7.digitalWrite(3, HIGH);
          MCP7.digitalWrite(4, LOW);
          MCP7.digitalWrite(5, LOW);
          break;
        case GREEN:
          MCP7.digitalWrite(3, LOW);
          MCP7.digitalWrite(4, HIGH);
          MCP7.digitalWrite(5, LOW);
          break;
        case BLUE:
          MCP7.digitalWrite(3, LOW);
          MCP7.digitalWrite(4, LOW);
          MCP7.digitalWrite(5, HIGH);
          break;
        case YELLOW:
          MCP7.digitalWrite(3, HIGH);
          MCP7.digitalWrite(4, HIGH);
          MCP7.digitalWrite(5, LOW);
          break;
        case MAGENTA:
          MCP7.digitalWrite(3, HIGH);
          MCP7.digitalWrite(4, LOW);
          MCP7.digitalWrite(5, HIGH);
          break;
        case CYAN:
          MCP7.digitalWrite(3, LOW);
          MCP7.digitalWrite(4, HIGH);
          MCP7.digitalWrite(5, HIGH);
          break;
        case WHITE:
          MCP7.digitalWrite(3, HIGH);
          MCP7.digitalWrite(4, HIGH);
          MCP7.digitalWrite(5, HIGH);
          break;
        default:
          break;
      }

      break;
    // F#5
    case 78:
      switch (color) {
        case BLACK:
          MCP7.digitalWrite(6, LOW);
          MCP7.digitalWrite(7, LOW);
          MCP7.digitalWrite(8, LOW);
          break;
        case RED:
          MCP7.digitalWrite(6, HIGH);
          MCP7.digitalWrite(7, LOW);
          MCP7.digitalWrite(8, LOW);
          break;
        case GREEN:
          MCP7.digitalWrite(6, LOW);
          MCP7.digitalWrite(7, HIGH);
          MCP7.digitalWrite(8, LOW);
          break;
        case BLUE:
          MCP7.digitalWrite(6, LOW);
          MCP7.digitalWrite(7, LOW);
          MCP7.digitalWrite(8, HIGH);
          break;
        case YELLOW:
          MCP7.digitalWrite(6, HIGH);
          MCP7.digitalWrite(7, HIGH);
          MCP7.digitalWrite(8, LOW);
          break;
        case MAGENTA:
          MCP7.digitalWrite(6, HIGH);
          MCP7.digitalWrite(7, LOW);
          MCP7.digitalWrite(8, HIGH);
          break;
        case CYAN:
          MCP7.digitalWrite(6, LOW);
          MCP7.digitalWrite(7, HIGH);
          MCP7.digitalWrite(8, HIGH);
          break;
        case WHITE:
          MCP7.digitalWrite(6, HIGH);
          MCP7.digitalWrite(7, HIGH);
          MCP7.digitalWrite(8, HIGH);
          break;
        default:
          break;
      }

      break;
    // G5
    case 79:
      switch (color) {
        case BLACK:
          MCP7.digitalWrite(9, LOW);
          MCP7.digitalWrite(10, LOW);
          MCP7.digitalWrite(11, LOW);
          break;
        case RED:
          MCP7.digitalWrite(9, HIGH);
          MCP7.digitalWrite(10, LOW);
          MCP7.digitalWrite(11, LOW);
          break;
        case GREEN:
          MCP7.digitalWrite(9, LOW);
          MCP7.digitalWrite(10, HIGH);
          MCP7.digitalWrite(11, LOW);
          break;
        case BLUE:
          MCP7.digitalWrite(9, LOW);
          MCP7.digitalWrite(10, LOW);
          MCP7.digitalWrite(11, HIGH);
          break;
        case YELLOW:
          MCP7.digitalWrite(9, HIGH);
          MCP7.digitalWrite(10, HIGH);
          MCP7.digitalWrite(11, LOW);
          break;
        case MAGENTA:
          MCP7.digitalWrite(9, HIGH);
          MCP7.digitalWrite(10, LOW);
          MCP7.digitalWrite(11, HIGH);
          break;
        case CYAN:
          MCP7.digitalWrite(9, LOW);
          MCP7.digitalWrite(10, HIGH);
          MCP7.digitalWrite(11, HIGH);
          break;
        case WHITE:
          MCP7.digitalWrite(9, HIGH);
          MCP7.digitalWrite(10, HIGH);
          MCP7.digitalWrite(11, HIGH);
          break;
        default:
          break;
      }

      break;
    // G#5
    case 80:
      switch (color) {
        case BLACK:
          MCP7.digitalWrite(12, LOW);
          MCP7.digitalWrite(13, LOW);
          MCP7.digitalWrite(14, LOW);
          break;
        case RED:
          MCP7.digitalWrite(12, HIGH);
          MCP7.digitalWrite(13, LOW);
          MCP7.digitalWrite(14, LOW);
          break;
        case GREEN:
          MCP7.digitalWrite(12, LOW);
          MCP7.digitalWrite(13, HIGH);
          MCP7.digitalWrite(14, LOW);
          break;
        case BLUE:
          MCP7.digitalWrite(12, LOW);
          MCP7.digitalWrite(13, LOW);
          MCP7.digitalWrite(14, HIGH);
          break;
        case YELLOW:
          MCP7.digitalWrite(12, HIGH);
          MCP7.digitalWrite(13, HIGH);
          MCP7.digitalWrite(14, LOW);
          break;
        case MAGENTA:
          MCP7.digitalWrite(12, HIGH);
          MCP7.digitalWrite(13, LOW);
          MCP7.digitalWrite(14, HIGH);
          break;
        case CYAN:
          MCP7.digitalWrite(12, LOW);
          MCP7.digitalWrite(13, HIGH);
          MCP7.digitalWrite(14, HIGH);
          break;
        case WHITE:
          MCP7.digitalWrite(12, HIGH);
          MCP7.digitalWrite(13, HIGH);
          MCP7.digitalWrite(14, HIGH);
          break;
        default:
          break;
      }

      break;
    // A5
    case 81:
      switch (color) {
        case BLACK:
          MCP7.digitalWrite(15, LOW);
          MCP7.digitalWrite(0, LOW);
          MCP7.digitalWrite(1, LOW);
          break;
        case RED:
          MCP7.digitalWrite(15, HIGH);
          MCP7.digitalWrite(0, LOW);
          MCP7.digitalWrite(1, LOW);
          break;
        case GREEN:
          MCP7.digitalWrite(15, LOW);
          MCP7.digitalWrite(0, HIGH);
          MCP7.digitalWrite(1, LOW);
          break;
        case BLUE:
          MCP7.digitalWrite(15, LOW);
          MCP7.digitalWrite(0, LOW);
          MCP7.digitalWrite(1, HIGH);
          break;
        case YELLOW:
          MCP7.digitalWrite(15, HIGH);
          MCP7.digitalWrite(0, HIGH);
          MCP7.digitalWrite(1, LOW);
          break;
        case MAGENTA:
          MCP7.digitalWrite(15, HIGH);
          MCP7.digitalWrite(0, LOW);
          MCP7.digitalWrite(1, HIGH);
          break;
        case CYAN:
          MCP7.digitalWrite(15, LOW);
          MCP7.digitalWrite(0, HIGH);
          MCP7.digitalWrite(1, HIGH);
          break;
        case WHITE:
          MCP7.digitalWrite(15, HIGH);
          MCP7.digitalWrite(0, HIGH);
          MCP7.digitalWrite(1, HIGH);
          break;
        default:
          break;
      }

      break;
    // A#5
    case 82:
      switch (color) {
        case BLACK:
          MCP7.digitalWrite(2, LOW);
          MCP7.digitalWrite(3, LOW);
          MCP7.digitalWrite(4, LOW);
          break;
        case RED:
          MCP7.digitalWrite(2, HIGH);
          MCP7.digitalWrite(3, LOW);
          MCP7.digitalWrite(4, LOW);
          break;
        case GREEN:
          MCP7.digitalWrite(2, LOW);
          MCP7.digitalWrite(3, HIGH);
          MCP7.digitalWrite(4, LOW);
          break;
        case BLUE:
          MCP7.digitalWrite(2, LOW);
          MCP7.digitalWrite(3, LOW);
          MCP7.digitalWrite(4, HIGH);
          break;
        case YELLOW:
          MCP7.digitalWrite(2, HIGH);
          MCP7.digitalWrite(3, HIGH);
          MCP7.digitalWrite(4, LOW);
          break;
        case MAGENTA:
          MCP7.digitalWrite(2, HIGH);
          MCP7.digitalWrite(3, LOW);
          MCP7.digitalWrite(4, HIGH);
          break;
        case CYAN:
          MCP7.digitalWrite(2, LOW);
          MCP7.digitalWrite(3, HIGH);
          MCP7.digitalWrite(4, HIGH);
          break;
        case WHITE:
          MCP7.digitalWrite(2, HIGH);
          MCP7.digitalWrite(3, HIGH);
          MCP7.digitalWrite(4, HIGH);
          break;
        default:
          break;
      }

      break;
    // B5
    case 83:
      switch (color) {
        case BLACK:
          MCP7.digitalWrite(5, LOW);
          MCP7.digitalWrite(6, LOW);
          MCP7.digitalWrite(7, LOW);
          break;
        case RED:
          MCP7.digitalWrite(5, HIGH);
          MCP7.digitalWrite(6, LOW);
          MCP7.digitalWrite(7, LOW);
          break;
        case GREEN:
          MCP7.digitalWrite(5, LOW);
          MCP7.digitalWrite(6, HIGH);
          MCP7.digitalWrite(7, LOW);
          break;
        case BLUE:
          MCP7.digitalWrite(5, LOW);
          MCP7.digitalWrite(6, LOW);
          MCP7.digitalWrite(7, HIGH);
          break;
        case YELLOW:
          MCP7.digitalWrite(5, HIGH);
          MCP7.digitalWrite(6, HIGH);
          MCP7.digitalWrite(7, LOW);
          break;
        case MAGENTA:
          MCP7.digitalWrite(5, HIGH);
          MCP7.digitalWrite(6, LOW);
          MCP7.digitalWrite(7, HIGH);
          break;
        case CYAN:
          MCP7.digitalWrite(5, LOW);
          MCP7.digitalWrite(6, HIGH);
          MCP7.digitalWrite(7, HIGH);
          break;
        case WHITE:
          MCP7.digitalWrite(5, HIGH);
          MCP7.digitalWrite(6, HIGH);
          MCP7.digitalWrite(7, HIGH);
          break;
        default:
          break;
      }

      break;
    default:
      break;
  }
}

void sampleFSRs() {
  int intensity;

  // Sample the first octave
  digitalWrite(S1, LOW);
  digitalWrite(S0, LOW);

  for (int i = 0; i < 12; i++) {
    intensity = analogRead(i);

    // If the note breaks the threshold
    if (intensity > THRESHOLD) {
      noteOn[i] = true;
      setColor(36 + i, WHITE);
    }
    // If the note was originally on
    else if (noteOn[i] == true) {
      noteOn[i] = false;
      setColor(36 + i, keyColors[i]);
    }
  }

  // Sample the second octave
  digitalWrite(S0, HIGH);

  for (int i = 0; i < 12; i++) {
    intensity = analogRead(i);

    // If the note breaks the threshold
    if (intensity > THRESHOLD) {
      noteOn[12 + i] = true;
      setColor(48 + i, WHITE);
    }
    // If the note was originally on
    else if (noteOn[12 + i] == true) {
      noteOn[12 + i] = false;
      setColor(48 + i, keyColors[12 + i]);
    }
  }

  // Sample the fourth octave
  digitalWrite(S1, HIGH);

  for (int i = 0; i < 12; i++) {
    intensity = analogRead(i);

    // If the note breaks the threshold
    if (intensity > THRESHOLD) {
      noteOn[36 + i] = true;
      setColor(72 + i, WHITE);
    }
    // If the note was originally on
    else if (noteOn[36 + i] == true) {
      noteOn[36 + i] = false;
      setColor(72 + i, keyColors[36 + i]);
    }
  }

  // Sample the third octave
  digitalWrite(S0, LOW);

  for (int i = 0; i < 12; i++) {
    intensity = analogRead(i);

    // If the note breaks the threshold
    if (intensity > THRESHOLD) {
      noteOn[24 + i] = true;
      setColor(60 + i, WHITE);
    }
    // If the note was originally on
    else if (noteOn[24 + i] == true) {
      noteOn[24 + i] = false;
      setColor(60 + i, keyColors[24 + i]);
    }
  }
}

//#include <EventManager.h>
//#include <Wire.h>
//#include "Adafruit_MCP23017.h"
//
//// MIDI note values
//#define NOTE_C2     36
//#define NOTE_CS2    37
//#define NOTE_D2     38
//#define NOTE_DS2    39
//#define NOTE_E2     40
//#define NOTE_F2     41
//#define NOTE_FS2    42
//#define NOTE_G2     43
//#define NOTE_GS2    44
//#define NOTE_A2     45
//#define NOTE_AS2    46
//#define NOTE_B2     47
//#define NOTE_C3     48
//#define NOTE_CS3    49
//#define NOTE_D3     50
//#define NOTE_DS3    51
//#define NOTE_E3     52
//#define NOTE_F3     53
//#define NOTE_FS3    54
//#define NOTE_G3     55
//#define NOTE_GS3    56
//#define NOTE_A3     57
//#define NOTE_AS3    58
//#define NOTE_B3     59
//#define NOTE_C4     60
//#define NOTE_CS4    61
//#define NOTE_D4     62
//#define NOTE_DS4    63
//#define NOTE_E4     64
//#define NOTE_F4     65
//#define NOTE_FS4    66
//#define NOTE_G4     67
//#define NOTE_GS4    68
//#define NOTE_A4     69
//#define NOTE_AS4    70
//#define NOTE_B4     71
//#define NOTE_C5     72
//#define NOTE_CS5    73
//#define NOTE_D5     74
//#define NOTE_DS5    75
//#define NOTE_E5     76
//#define NOTE_F5     77
//#define NOTE_FS5    78
//#define NOTE_G5     79
//#define NOTE_GS5    80
//#define NOTE_A5     81
//#define NOTE_AS5    82
//#define NOTE_B5     83
//
//// Colors
//#define BLACK       0
//#define RED         1
//#define GREEN       2
//#define BLUE        3
//#define YELLOW      4
//#define MAGENTA     5
//#define CYAN        6
//#define WHITE       7
//
//// Musical keys
//#define CMAJOR      0
//#define DFMAJOR     1
//#define DMAJOR      2
//#define EFMAJOR     3
//#define EMAJOR      4
//#define FMAJOR      5
//#define FSMAJOR     6
//#define GMAJOR      7
//#define AFMAJOR     8
//#define AMAJOR      9
//#define BFMAJOR     10
//#define BMAJOR      11
//#define CMINOR      12
//#define CSMINOR     13
//#define DMINOR      14
//#define DSMINOR     15
//#define EMINOR      16
//#define FMINOR      17
//#define FSMINOR     18
//#define GMINOR      19
//#define GSMINOR     20
//#define AMINOR      21
//#define BFMINOR     22
//#define BMINOR      23
//
//// Serial function types
//#define KEYCHANGE   0
//#define MENUSELECT  1
//
//// MCP23017 port expanders
//Adafruit_MCP23017 MCP0;
//Adafruit_MCP23017 MCP1;
//Adafruit_MCP23017 MCP2;
//Adafruit_MCP23017 MCP3;
//Adafruit_MCP23017 MCP4;
//Adafruit_MCP23017 MCP5;
//Adafruit_MCP23017 MCP6;
//Adafruit_MCP23017 MCP7;
//
//const int THRESHOLD = 300;
//
//const int S1 = 6;
//const int S0 = 5;
//const int MUXENABLE = 7;
//
//bool noteOn[48];
//bool keyNoteOn[48];
//int keyColors[48];
//
//bool serialAvailable;
//byte serialFunction;
//byte serialData;
//
//int key;
//
//unsigned long duration[48];
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
//    delay(10);
//    MCP1.pinMode(i, OUTPUT);
//    delay(10);
//    MCP2.pinMode(i, OUTPUT);
//    delay(10);
//    MCP3.pinMode(i, OUTPUT);
//    delay(10);
//    MCP4.pinMode(i, OUTPUT);
//    delay(10);
//    MCP5.pinMode(i, OUTPUT);
//    delay(10);
//    MCP6.pinMode(i, OUTPUT);
//    delay(10);
//    MCP7.pinMode(i, OUTPUT);
//    delay(10);
//  }
//
//  for (int i = 0; i < 48; i++) {
//    noteOn[i] = false;
//    keyColors[i] = BLACK;
//    duration[i] = 0;
//  }
//
//  pinMode(S1, OUTPUT);
//  pinMode(S0, OUTPUT);
//  pinMode(MUXENABLE, OUTPUT);
//  digitalWrite(MUXENABLE, LOW);
//
//  Serial.begin(9600);
//  Serial3.begin(115200);
//  serialAvailable = false;
//
//  Wire.begin();
//
//  pinMode(13, OUTPUT);
//  digitalWrite(13, HIGH);
//}
//
//void loop() {
////  if (serialAvailable == true) {
////    serialAvailable = false;
////    processSerialData();
////  }
////
//  sampleFSRs();
//
////  for (int i = 0; i < 24; i++) {
////    MCP0.writeGPIOAB(0x0000);
////    MCP1.writeGPIOAB(0x0000);
////    MCP2.writeGPIOAB(0x0000);
////    MCP3.writeGPIOAB(0x0000);
////    MCP4.writeGPIOAB(0x0000);
////    MCP5.writeGPIOAB(0x0000);
////    MCP6.writeGPIOAB(0x0000);
////    MCP7.writeGPIOAB(0x0000);
////
////    for (int j = 0; j < 48; j++) {
////      keyColors[j] = BLACK;
////      keyNoteOn[j] = false;
////    }
////
////    serialData = i;
////    int tonic = serialData % 12;
////    int supertonic = (tonic + 2) % 12;
////    int mediant;
////    int subdominant = (tonic + 5) % 12;
////    int dominant = (tonic + 7) % 12;
////    int submediant;
////    int leadingTone;
////  
////    // If it is a major key
////    if (serialData < 12) {
////      mediant = (tonic + 4) % 12;
////      submediant = (tonic + 9) % 12;
////      leadingTone = (tonic + 11) % 12;
////    }
////    // If it is a minor key
////    else {
////      mediant = (tonic + 3) % 12;
////      submediant = (tonic + 8) % 12;
////      leadingTone = (tonic + 10) % 12;
////    }
////  
////    for (int j = 0; j < 4; j++) {
////      keyColors[12 * j + tonic] = RED;
////      keyColors[12 * j + supertonic] = BLUE;
////      keyColors[12 * j + mediant] = BLUE;
////      keyColors[12 * j + subdominant] = YELLOW;
////      keyColors[12 * j + dominant] = YELLOW;
////      keyColors[12 * j + submediant] = BLUE;
////      keyColors[12 * j + leadingTone] = GREEN;
////  
////      if (noteOn[12 * j + tonic] == false) {
////        setColor(12 * j + tonic, RED);
////      }
////  
////      if (noteOn[12 * j + supertonic] == false) {
////        setColor(12 * j + supertonic, BLUE);
////      }
////  
////      if (noteOn[12 * j + mediant] == false) {
////        setColor(12 * j + mediant, BLUE);
////      }
////  
////      if (noteOn[12 * j + subdominant] == false) {
////        setColor(12 * j + subdominant, YELLOW);
////      }
////  
////      if (noteOn[12 * j + dominant] == false) {
////        setColor(12 * j + dominant, YELLOW);
////      }
////  
////      if (noteOn[12 * j + submediant] == false) {
////        setColor(12 * j + submediant, BLUE);
////      }
////  
////      if (noteOn[12 * j + leadingTone] == false) {
////        setColor(12 * j + leadingTone, GREEN);
////      }
////    }
////
////    delay(5000);
////  }
//}
//
//// Sets a corresponding RGB LED to the specified color
//void setColor(int note, int color) {
//  switch (note) {
//    // C2
//    case 36:
//      switch (color) {
//        case BLACK:
//          MCP0.digitalWrite(8, LOW);
//          MCP0.digitalWrite(9, LOW);
//          MCP0.digitalWrite(10, LOW);
//          break;
//        case RED:
//          MCP0.digitalWrite(8, HIGH);
//          MCP0.digitalWrite(9, LOW);
//          MCP0.digitalWrite(10, LOW);
//          break;
//        case GREEN:
//          MCP0.digitalWrite(8, LOW);
//          MCP0.digitalWrite(9, HIGH);
//          MCP0.digitalWrite(10, LOW);
//          break;
//        case BLUE:
//          MCP0.digitalWrite(8, LOW);
//          MCP0.digitalWrite(9, LOW);
//          MCP0.digitalWrite(10, HIGH);
//          break;
//        case YELLOW:
//          MCP0.digitalWrite(8, HIGH);
//          MCP0.digitalWrite(9, HIGH);
//          MCP0.digitalWrite(10, LOW);
//          break;
//        case MAGENTA:
//          MCP0.digitalWrite(8, HIGH);
//          MCP0.digitalWrite(9, LOW);
//          MCP0.digitalWrite(10, HIGH);
//          break;
//        case CYAN:
//          MCP0.digitalWrite(8, LOW);
//          MCP0.digitalWrite(9, HIGH);
//          MCP0.digitalWrite(10, HIGH);
//          break;
//        case WHITE:
//          MCP0.digitalWrite(8, HIGH);
//          MCP0.digitalWrite(9, HIGH);
//          MCP0.digitalWrite(10, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // C#2
//    case 37:
//      switch (color) {
//        case BLACK:
//          MCP0.digitalWrite(11, LOW);
//          MCP0.digitalWrite(12, LOW);
//          MCP0.digitalWrite(13, LOW);
//          break;
//        case RED:
//          MCP0.digitalWrite(11, HIGH);
//          MCP0.digitalWrite(12, LOW);
//          MCP0.digitalWrite(13, LOW);
//          break;
//        case GREEN:
//          MCP0.digitalWrite(11, LOW);
//          MCP0.digitalWrite(12, HIGH);
//          MCP0.digitalWrite(13, LOW);
//          break;
//        case BLUE:
//          MCP0.digitalWrite(11, LOW);
//          MCP0.digitalWrite(12, LOW);
//          MCP0.digitalWrite(13, HIGH);
//          break;
//        case YELLOW:
//          MCP0.digitalWrite(11, HIGH);
//          MCP0.digitalWrite(12, HIGH);
//          MCP0.digitalWrite(13, LOW);
//          break;
//        case MAGENTA:
//          MCP0.digitalWrite(11, HIGH);
//          MCP0.digitalWrite(12, LOW);
//          MCP0.digitalWrite(13, HIGH);
//          break;
//        case CYAN:
//          MCP0.digitalWrite(11, LOW);
//          MCP0.digitalWrite(12, HIGH);
//          MCP0.digitalWrite(13, HIGH);
//          break;
//        case WHITE:
//          MCP0.digitalWrite(11, HIGH);
//          MCP0.digitalWrite(12, HIGH);
//          MCP0.digitalWrite(13, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // D2
//    case 38:
//      switch (color) {
//        case BLACK:
//          MCP0.digitalWrite(14, LOW);
//          MCP0.digitalWrite(15, LOW);
//          MCP0.digitalWrite(0, LOW);
//          break;
//        case RED:
//          MCP0.digitalWrite(14, HIGH);
//          MCP0.digitalWrite(15, LOW);
//          MCP0.digitalWrite(0, LOW);
//          break;
//        case GREEN:
//          MCP0.digitalWrite(14, LOW);
//          MCP0.digitalWrite(15, HIGH);
//          MCP0.digitalWrite(0, LOW);
//          break;
//        case BLUE:
//          MCP0.digitalWrite(14, LOW);
//          MCP0.digitalWrite(15, LOW);
//          MCP0.digitalWrite(0, HIGH);
//          break;
//        case YELLOW:
//          MCP0.digitalWrite(14, HIGH);
//          MCP0.digitalWrite(15, HIGH);
//          MCP0.digitalWrite(0, LOW);
//          break;
//        case MAGENTA:
//          MCP0.digitalWrite(14, HIGH);
//          MCP0.digitalWrite(15, LOW);
//          MCP0.digitalWrite(0, HIGH);
//          break;
//        case CYAN:
//          MCP0.digitalWrite(14, LOW);
//          MCP0.digitalWrite(15, HIGH);
//          MCP0.digitalWrite(0, HIGH);
//          break;
//        case WHITE:
//          MCP0.digitalWrite(14, HIGH);
//          MCP0.digitalWrite(15, HIGH);
//          MCP0.digitalWrite(0, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // D#2
//    case 39:
//      switch (color) {
//        case BLACK:
//          MCP0.digitalWrite(1, LOW);
//          MCP0.digitalWrite(2, LOW);
//          MCP0.digitalWrite(3, LOW);
//          break;
//        case RED:
//          MCP0.digitalWrite(1, HIGH);
//          MCP0.digitalWrite(2, LOW);
//          MCP0.digitalWrite(3, LOW);
//          break;
//        case GREEN:
//          MCP0.digitalWrite(1, LOW);
//          MCP0.digitalWrite(2, HIGH);
//          MCP0.digitalWrite(3, LOW);
//          break;
//        case BLUE:
//          MCP0.digitalWrite(1, LOW);
//          MCP0.digitalWrite(2, LOW);
//          MCP0.digitalWrite(3, HIGH);
//          break;
//        case YELLOW:
//          MCP0.digitalWrite(1, HIGH);
//          MCP0.digitalWrite(2, HIGH);
//          MCP0.digitalWrite(3, LOW);
//          break;
//        case MAGENTA:
//          MCP0.digitalWrite(1, HIGH);
//          MCP0.digitalWrite(2, LOW);
//          MCP0.digitalWrite(3, HIGH);
//          break;
//        case CYAN:
//          MCP0.digitalWrite(1, LOW);
//          MCP0.digitalWrite(2, HIGH);
//          MCP0.digitalWrite(3, HIGH);
//          break;
//        case WHITE:
//          MCP0.digitalWrite(1, HIGH);
//          MCP0.digitalWrite(2, HIGH);
//          MCP0.digitalWrite(3, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // E2
//    case 40:
//      switch (color) {
//        case BLACK:
//          MCP0.digitalWrite(4, LOW);
//          MCP0.digitalWrite(5, LOW);
//          MCP0.digitalWrite(6, LOW);
//          break;
//        case RED:
//          MCP0.digitalWrite(4, HIGH);
//          MCP0.digitalWrite(5, LOW);
//          MCP0.digitalWrite(6, LOW);
//          break;
//        case GREEN:
//          MCP0.digitalWrite(4, LOW);
//          MCP0.digitalWrite(5, HIGH);
//          MCP0.digitalWrite(6, LOW);
//          break;
//        case BLUE:
//          MCP0.digitalWrite(4, LOW);
//          MCP0.digitalWrite(5, LOW);
//          MCP0.digitalWrite(6, HIGH);
//          break;
//        case YELLOW:
//          MCP0.digitalWrite(4, HIGH);
//          MCP0.digitalWrite(5, HIGH);
//          MCP0.digitalWrite(6, LOW);
//          break;
//        case MAGENTA:
//          MCP0.digitalWrite(4, HIGH);
//          MCP0.digitalWrite(5, LOW);
//          MCP0.digitalWrite(6, HIGH);
//          break;
//        case CYAN:
//          MCP0.digitalWrite(4, LOW);
//          MCP0.digitalWrite(5, HIGH);
//          MCP0.digitalWrite(6, HIGH);
//          break;
//        case WHITE:
//          MCP0.digitalWrite(4, HIGH);
//          MCP0.digitalWrite(5, HIGH);
//          MCP0.digitalWrite(6, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // F2
//    case 41:
//      switch (color) {
//        case BLACK:
//          MCP0.digitalWrite(7, LOW);
//          MCP4.digitalWrite(8, LOW);
//          MCP4.digitalWrite(9, LOW);
//          break;
//        case RED:
//          MCP0.digitalWrite(7, HIGH);
//          MCP4.digitalWrite(8, LOW);
//          MCP4.digitalWrite(9, LOW);
//          break;
//        case GREEN:
//          MCP0.digitalWrite(7, LOW);
//          MCP4.digitalWrite(8, HIGH);
//          MCP4.digitalWrite(9, LOW);
//          break;
//        case BLUE:
//          MCP0.digitalWrite(7, LOW);
//          MCP4.digitalWrite(8, LOW);
//          MCP4.digitalWrite(9, HIGH);
//          break;
//        case YELLOW:
//          MCP0.digitalWrite(7, HIGH);
//          MCP4.digitalWrite(8, HIGH);
//          MCP4.digitalWrite(9, LOW);
//          break;
//        case MAGENTA:
//          MCP0.digitalWrite(7, HIGH);
//          MCP4.digitalWrite(8, LOW);
//          MCP4.digitalWrite(9, HIGH);
//          break;
//        case CYAN:
//          MCP0.digitalWrite(7, LOW);
//          MCP4.digitalWrite(8, HIGH);
//          MCP4.digitalWrite(9, HIGH);
//          break;
//        case WHITE:
//          MCP0.digitalWrite(7, HIGH);
//          MCP4.digitalWrite(8, HIGH);
//          MCP4.digitalWrite(9, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // F#2
//    case 42:
//      switch (color) {
//        case BLACK:
//          MCP4.digitalWrite(10, LOW);
//          MCP4.digitalWrite(11, LOW);
//          MCP4.digitalWrite(12, LOW);
//          break;
//        case RED:
//          MCP4.digitalWrite(10, HIGH);
//          MCP4.digitalWrite(11, LOW);
//          MCP4.digitalWrite(12, LOW);
//          break;
//        case GREEN:
//          MCP4.digitalWrite(10, LOW);
//          MCP4.digitalWrite(11, HIGH);
//          MCP4.digitalWrite(12, LOW);
//          break;
//        case BLUE:
//          MCP4.digitalWrite(10, LOW);
//          MCP4.digitalWrite(11, LOW);
//          MCP4.digitalWrite(12, HIGH);
//          break;
//        case YELLOW:
//          MCP4.digitalWrite(10, HIGH);
//          MCP4.digitalWrite(11, HIGH);
//          MCP4.digitalWrite(12, LOW);
//          break;
//        case MAGENTA:
//          MCP4.digitalWrite(10, HIGH);
//          MCP4.digitalWrite(11, LOW);
//          MCP4.digitalWrite(12, HIGH);
//          break;
//        case CYAN:
//          MCP4.digitalWrite(10, LOW);
//          MCP4.digitalWrite(11, HIGH);
//          MCP4.digitalWrite(12, HIGH);
//          break;
//        case WHITE:
//          MCP4.digitalWrite(10, HIGH);
//          MCP4.digitalWrite(11, HIGH);
//          MCP4.digitalWrite(12, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // G2
//    case 43:
//      switch (color) {
//        case BLACK:
//          MCP4.digitalWrite(13, LOW);
//          MCP4.digitalWrite(14, LOW);
//          MCP4.digitalWrite(15, LOW);
//          break;
//        case RED:
//          MCP4.digitalWrite(13, HIGH);
//          MCP4.digitalWrite(14, LOW);
//          MCP4.digitalWrite(15, LOW);
//          break;
//        case GREEN:
//          MCP4.digitalWrite(13, LOW);
//          MCP4.digitalWrite(14, HIGH);
//          MCP4.digitalWrite(15, LOW);
//          break;
//        case BLUE:
//          MCP4.digitalWrite(13, LOW);
//          MCP4.digitalWrite(14, LOW);
//          MCP4.digitalWrite(15, HIGH);
//          break;
//        case YELLOW:
//          MCP4.digitalWrite(13, HIGH);
//          MCP4.digitalWrite(14, HIGH);
//          MCP4.digitalWrite(15, LOW);
//          break;
//        case MAGENTA:
//          MCP4.digitalWrite(13, HIGH);
//          MCP4.digitalWrite(14, LOW);
//          MCP4.digitalWrite(15, HIGH);
//          break;
//        case CYAN:
//          MCP4.digitalWrite(13, LOW);
//          MCP4.digitalWrite(14, HIGH);
//          MCP4.digitalWrite(15, HIGH);
//          break;
//        case WHITE:
//          MCP4.digitalWrite(13, HIGH);
//          MCP4.digitalWrite(14, HIGH);
//          MCP4.digitalWrite(15, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // G#2
//    case 44:
//      switch (color) {
//        case BLACK:
//          MCP4.digitalWrite(0, LOW);
//          MCP4.digitalWrite(1, LOW);
//          MCP4.digitalWrite(2, LOW);
//          break;
//        case RED:
//          MCP4.digitalWrite(0, HIGH);
//          MCP4.digitalWrite(1, LOW);
//          MCP4.digitalWrite(2, LOW);
//          break;
//        case GREEN:
//          MCP4.digitalWrite(0, LOW);
//          MCP4.digitalWrite(1, HIGH);
//          MCP4.digitalWrite(2, LOW);
//          break;
//        case BLUE:
//          MCP4.digitalWrite(0, LOW);
//          MCP4.digitalWrite(1, LOW);
//          MCP4.digitalWrite(2, HIGH);
//          break;
//        case YELLOW:
//          MCP4.digitalWrite(0, HIGH);
//          MCP4.digitalWrite(1, HIGH);
//          MCP4.digitalWrite(2, LOW);
//          break;
//        case MAGENTA:
//          MCP4.digitalWrite(0, HIGH);
//          MCP4.digitalWrite(1, LOW);
//          MCP4.digitalWrite(2, HIGH);
//          break;
//        case CYAN:
//          MCP4.digitalWrite(0, LOW);
//          MCP4.digitalWrite(1, HIGH);
//          MCP4.digitalWrite(2, HIGH);
//          break;
//        case WHITE:
//          MCP4.digitalWrite(0, HIGH);
//          MCP4.digitalWrite(1, HIGH);
//          MCP4.digitalWrite(2, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // A2
//    case 45:
//      switch (color) {
//        case BLACK:
//          MCP4.digitalWrite(3, LOW);
//          MCP4.digitalWrite(4, LOW);
//          MCP4.digitalWrite(5, LOW);
//          break;
//        case RED:
//          MCP4.digitalWrite(3, HIGH);
//          MCP4.digitalWrite(4, LOW);
//          MCP4.digitalWrite(5, LOW);
//          break;
//        case GREEN:
//          MCP4.digitalWrite(3, LOW);
//          MCP4.digitalWrite(4, HIGH);
//          MCP4.digitalWrite(5, LOW);
//          break;
//        case BLUE:
//          MCP4.digitalWrite(3, LOW);
//          MCP4.digitalWrite(4, LOW);
//          MCP4.digitalWrite(5, HIGH);
//          break;
//        case YELLOW:
//          MCP4.digitalWrite(3, HIGH);
//          MCP4.digitalWrite(4, HIGH);
//          MCP4.digitalWrite(5, LOW);
//          break;
//        case MAGENTA:
//          MCP4.digitalWrite(3, HIGH);
//          MCP4.digitalWrite(4, LOW);
//          MCP4.digitalWrite(5, HIGH);
//          break;
//        case CYAN:
//          MCP4.digitalWrite(3, LOW);
//          MCP4.digitalWrite(4, HIGH);
//          MCP4.digitalWrite(5, HIGH);
//          break;
//        case WHITE:
//          MCP4.digitalWrite(3, HIGH);
//          MCP4.digitalWrite(4, HIGH);
//          MCP4.digitalWrite(5, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // A#2
//    case 46:
//      switch (color) {
//        case BLACK:
//          MCP4.digitalWrite(6, LOW);
//          MCP4.digitalWrite(7, LOW);
//          MCP2.digitalWrite(8, LOW);
//          break;
//        case RED:
//          MCP4.digitalWrite(6, HIGH);
//          MCP4.digitalWrite(7, LOW);
//          MCP2.digitalWrite(8, LOW);
//          break;
//        case GREEN:
//          MCP4.digitalWrite(6, LOW);
//          MCP4.digitalWrite(7, HIGH);
//          MCP2.digitalWrite(8, LOW);
//          break;
//        case BLUE:
//          MCP4.digitalWrite(6, LOW);
//          MCP4.digitalWrite(7, LOW);
//          MCP2.digitalWrite(8, HIGH);
//          break;
//        case YELLOW:
//          MCP4.digitalWrite(6, HIGH);
//          MCP4.digitalWrite(7, HIGH);
//          MCP2.digitalWrite(8, LOW);
//          break;
//        case MAGENTA:
//          MCP4.digitalWrite(6, HIGH);
//          MCP4.digitalWrite(7, LOW);
//          MCP2.digitalWrite(8, HIGH);
//          break;
//        case CYAN:
//          MCP4.digitalWrite(6, LOW);
//          MCP4.digitalWrite(7, HIGH);
//          MCP2.digitalWrite(8, HIGH);
//          break;
//        case WHITE:
//          MCP4.digitalWrite(6, HIGH);
//          MCP4.digitalWrite(7, HIGH);
//          MCP2.digitalWrite(8, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // B2
//    case 47:
//      switch (color) {
//        case BLACK:
//          MCP2.digitalWrite(9, LOW);
//          MCP2.digitalWrite(10, LOW);
//          MCP2.digitalWrite(11, LOW);
//          break;
//        case RED:
//          MCP2.digitalWrite(9, HIGH);
//          MCP2.digitalWrite(10, LOW);
//          MCP2.digitalWrite(11, LOW);
//          break;
//        case GREEN:
//          MCP2.digitalWrite(9, LOW);
//          MCP2.digitalWrite(10, HIGH);
//          MCP2.digitalWrite(11, LOW);
//          break;
//        case BLUE:
//          MCP2.digitalWrite(9, LOW);
//          MCP2.digitalWrite(10, LOW);
//          MCP2.digitalWrite(11, HIGH);
//          break;
//        case YELLOW:
//          MCP2.digitalWrite(9, HIGH);
//          MCP2.digitalWrite(10, HIGH);
//          MCP2.digitalWrite(11, LOW);
//          break;
//        case MAGENTA:
//          MCP2.digitalWrite(9, HIGH);
//          MCP2.digitalWrite(10, LOW);
//          MCP2.digitalWrite(11, HIGH);
//          break;
//        case CYAN:
//          MCP2.digitalWrite(9, LOW);
//          MCP2.digitalWrite(10, HIGH);
//          MCP2.digitalWrite(11, HIGH);
//          break;
//        case WHITE:
//          MCP2.digitalWrite(9, HIGH);
//          MCP2.digitalWrite(10, HIGH);
//          MCP2.digitalWrite(11, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // C3
//    case 48:
//      switch (color) {
//        case BLACK:
//          MCP2.digitalWrite(12, LOW);
//          MCP2.digitalWrite(13, LOW);
//          MCP2.digitalWrite(14, LOW);
//          break;
//        case RED:
//          MCP2.digitalWrite(12, HIGH);
//          MCP2.digitalWrite(13, LOW);
//          MCP2.digitalWrite(14, LOW);
//          break;
//        case GREEN:
//          MCP2.digitalWrite(12, LOW);
//          MCP2.digitalWrite(13, HIGH);
//          MCP2.digitalWrite(14, LOW);
//          break;
//        case BLUE:
//          MCP2.digitalWrite(12, LOW);
//          MCP2.digitalWrite(13, LOW);
//          MCP2.digitalWrite(14, HIGH);
//          break;
//        case YELLOW:
//          MCP2.digitalWrite(12, HIGH);
//          MCP2.digitalWrite(13, HIGH);
//          MCP2.digitalWrite(14, LOW);
//          break;
//        case MAGENTA:
//          MCP2.digitalWrite(12, HIGH);
//          MCP2.digitalWrite(13, LOW);
//          MCP2.digitalWrite(14, HIGH);
//          break;
//        case CYAN:
//          MCP2.digitalWrite(12, LOW);
//          MCP2.digitalWrite(13, HIGH);
//          MCP2.digitalWrite(14, HIGH);
//          break;
//        case WHITE:
//          MCP2.digitalWrite(12, HIGH);
//          MCP2.digitalWrite(13, HIGH);
//          MCP2.digitalWrite(14, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // C#3
//    case 49:
//      switch (color) {
//        case BLACK:
//          MCP2.digitalWrite(15, LOW);
//          MCP2.digitalWrite(0, LOW);
//          MCP2.digitalWrite(1, LOW);
//          break;
//        case RED:
//          MCP2.digitalWrite(15, HIGH);
//          MCP2.digitalWrite(0, LOW);
//          MCP2.digitalWrite(1, LOW);
//          break;
//        case GREEN:
//          MCP2.digitalWrite(15, LOW);
//          MCP2.digitalWrite(0, HIGH);
//          MCP2.digitalWrite(1, LOW);
//          break;
//        case BLUE:
//          MCP2.digitalWrite(15, LOW);
//          MCP2.digitalWrite(0, LOW);
//          MCP2.digitalWrite(1, HIGH);
//          break;
//        case YELLOW:
//          MCP2.digitalWrite(15, HIGH);
//          MCP2.digitalWrite(0, HIGH);
//          MCP2.digitalWrite(1, LOW);
//          break;
//        case MAGENTA:
//          MCP2.digitalWrite(15, HIGH);
//          MCP2.digitalWrite(0, LOW);
//          MCP2.digitalWrite(1, HIGH);
//          break;
//        case CYAN:
//          MCP2.digitalWrite(15, LOW);
//          MCP2.digitalWrite(0, HIGH);
//          MCP2.digitalWrite(1, HIGH);
//          break;
//        case WHITE:
//          MCP2.digitalWrite(15, HIGH);
//          MCP2.digitalWrite(0, HIGH);
//          MCP2.digitalWrite(1, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // D3
//    case 50:
//      switch (color) {
//        case BLACK:
//          MCP2.digitalWrite(2, LOW);
//          MCP2.digitalWrite(3, LOW);
//          MCP2.digitalWrite(4, LOW);
//          break;
//        case RED:
//          MCP2.digitalWrite(2, HIGH);
//          MCP2.digitalWrite(3, LOW);
//          MCP2.digitalWrite(4, LOW);
//          break;
//        case GREEN:
//          MCP2.digitalWrite(2, LOW);
//          MCP2.digitalWrite(3, HIGH);
//          MCP2.digitalWrite(4, LOW);
//          break;
//        case BLUE:
//          MCP2.digitalWrite(2, LOW);
//          MCP2.digitalWrite(3, LOW);
//          MCP2.digitalWrite(4, HIGH);
//          break;
//        case YELLOW:
//          MCP2.digitalWrite(2, HIGH);
//          MCP2.digitalWrite(3, HIGH);
//          MCP2.digitalWrite(4, LOW);
//          break;
//        case MAGENTA:
//          MCP2.digitalWrite(2, HIGH);
//          MCP2.digitalWrite(3, LOW);
//          MCP2.digitalWrite(4, HIGH);
//          break;
//        case CYAN:
//          MCP2.digitalWrite(2, LOW);
//          MCP2.digitalWrite(3, HIGH);
//          MCP2.digitalWrite(4, HIGH);
//          break;
//        case WHITE:
//          MCP2.digitalWrite(2, HIGH);
//          MCP2.digitalWrite(3, HIGH);
//          MCP2.digitalWrite(4, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // D#3
//    case 51:
//      switch (color) {
//        case BLACK:
//          MCP2.digitalWrite(5, LOW);
//          MCP2.digitalWrite(6, LOW);
//          MCP2.digitalWrite(7, LOW);
//          break;
//        case RED:
//          MCP2.digitalWrite(5, HIGH);
//          MCP2.digitalWrite(6, LOW);
//          MCP2.digitalWrite(7, LOW);
//          break;
//        case GREEN:
//          MCP2.digitalWrite(5, LOW);
//          MCP2.digitalWrite(6, HIGH);
//          MCP2.digitalWrite(7, LOW);
//          break;
//        case BLUE:
//          MCP2.digitalWrite(5, LOW);
//          MCP2.digitalWrite(6, LOW);
//          MCP2.digitalWrite(7, HIGH);
//          break;
//        case YELLOW:
//          MCP2.digitalWrite(5, HIGH);
//          MCP2.digitalWrite(6, HIGH);
//          MCP2.digitalWrite(7, LOW);
//          break;
//        case MAGENTA:
//          MCP2.digitalWrite(5, HIGH);
//          MCP2.digitalWrite(6, LOW);
//          MCP2.digitalWrite(7, HIGH);
//          break;
//        case CYAN:
//          MCP2.digitalWrite(5, LOW);
//          MCP2.digitalWrite(6, HIGH);
//          MCP2.digitalWrite(7, HIGH);
//          break;
//        case WHITE:
//          MCP2.digitalWrite(5, HIGH);
//          MCP2.digitalWrite(6, HIGH);
//          MCP2.digitalWrite(7, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // E3
//    case 52:
//      switch (color) {
//        case BLACK:
//          MCP6.digitalWrite(8, LOW);
//          MCP6.digitalWrite(9, LOW);
//          MCP6.digitalWrite(10, LOW);
//          break;
//        case RED:
//          MCP6.digitalWrite(8, HIGH);
//          MCP6.digitalWrite(9, LOW);
//          MCP6.digitalWrite(10, LOW);
//          break;
//        case GREEN:
//          MCP6.digitalWrite(8, LOW);
//          MCP6.digitalWrite(9, HIGH);
//          MCP6.digitalWrite(10, LOW);
//          break;
//        case BLUE:
//          MCP6.digitalWrite(8, LOW);
//          MCP6.digitalWrite(9, LOW);
//          MCP6.digitalWrite(10, HIGH);
//          break;
//        case YELLOW:
//          MCP6.digitalWrite(8, HIGH);
//          MCP6.digitalWrite(9, HIGH);
//          MCP6.digitalWrite(10, LOW);
//          break;
//        case MAGENTA:
//          MCP6.digitalWrite(8, HIGH);
//          MCP6.digitalWrite(9, LOW);
//          MCP6.digitalWrite(10, HIGH);
//          break;
//        case CYAN:
//          MCP6.digitalWrite(8, LOW);
//          MCP6.digitalWrite(9, HIGH);
//          MCP6.digitalWrite(10, HIGH);
//          break;
//        case WHITE:
//          MCP6.digitalWrite(8, HIGH);
//          MCP6.digitalWrite(9, HIGH);
//          MCP6.digitalWrite(10, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // F3
//    case 53:
//      switch (color) {
//        case BLACK:
//          MCP6.digitalWrite(11, LOW);
//          MCP6.digitalWrite(12, LOW);
//          MCP6.digitalWrite(13, LOW);
//          break;
//        case RED:
//          MCP6.digitalWrite(11, HIGH);
//          MCP6.digitalWrite(12, LOW);
//          MCP6.digitalWrite(13, LOW);
//          break;
//        case GREEN:
//          MCP6.digitalWrite(11, LOW);
//          MCP6.digitalWrite(12, HIGH);
//          MCP6.digitalWrite(13, LOW);
//          break;
//        case BLUE:
//          MCP6.digitalWrite(11, LOW);
//          MCP6.digitalWrite(12, LOW);
//          MCP6.digitalWrite(13, HIGH);
//          break;
//        case YELLOW:
//          MCP6.digitalWrite(11, HIGH);
//          MCP6.digitalWrite(12, HIGH);
//          MCP6.digitalWrite(13, LOW);
//          break;
//        case MAGENTA:
//          MCP6.digitalWrite(11, HIGH);
//          MCP6.digitalWrite(12, LOW);
//          MCP6.digitalWrite(13, HIGH);
//          break;
//        case CYAN:
//          MCP6.digitalWrite(11, LOW);
//          MCP6.digitalWrite(12, HIGH);
//          MCP6.digitalWrite(13, HIGH);
//          break;
//        case WHITE:
//          MCP6.digitalWrite(11, HIGH);
//          MCP6.digitalWrite(12, HIGH);
//          MCP6.digitalWrite(13, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // F#3
//    case 54:
//      switch (color) {
//        case BLACK:
//          MCP6.digitalWrite(14, LOW);
//          MCP6.digitalWrite(15, LOW);
//          MCP6.digitalWrite(0, LOW);
//          break;
//        case RED:
//          MCP6.digitalWrite(14, HIGH);
//          MCP6.digitalWrite(15, LOW);
//          MCP6.digitalWrite(0, LOW);
//          break;
//        case GREEN:
//          MCP6.digitalWrite(14, LOW);
//          MCP6.digitalWrite(15, HIGH);
//          MCP6.digitalWrite(0, LOW);
//          break;
//        case BLUE:
//          MCP6.digitalWrite(14, LOW);
//          MCP6.digitalWrite(15, LOW);
//          MCP6.digitalWrite(0, HIGH);
//          break;
//        case YELLOW:
//          MCP6.digitalWrite(14, HIGH);
//          MCP6.digitalWrite(15, HIGH);
//          MCP6.digitalWrite(0, LOW);
//          break;
//        case MAGENTA:
//          MCP6.digitalWrite(14, HIGH);
//          MCP6.digitalWrite(15, LOW);
//          MCP6.digitalWrite(0, HIGH);
//          break;
//        case CYAN:
//          MCP6.digitalWrite(14, LOW);
//          MCP6.digitalWrite(15, HIGH);
//          MCP6.digitalWrite(0, HIGH);
//          break;
//        case WHITE:
//          MCP6.digitalWrite(14, HIGH);
//          MCP6.digitalWrite(15, HIGH);
//          MCP6.digitalWrite(0, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // G3
//    case 55:
//      switch (color) {
//        case BLACK:
//          MCP6.digitalWrite(1, LOW);
//          MCP6.digitalWrite(2, LOW);
//          MCP6.digitalWrite(3, LOW);
//          break;
//        case RED:
//          MCP6.digitalWrite(1, HIGH);
//          MCP6.digitalWrite(2, LOW);
//          MCP6.digitalWrite(3, LOW);
//          break;
//        case GREEN:
//          MCP6.digitalWrite(1, LOW);
//          MCP6.digitalWrite(2, HIGH);
//          MCP6.digitalWrite(3, LOW);
//          break;
//        case BLUE:
//          MCP6.digitalWrite(1, LOW);
//          MCP6.digitalWrite(2, LOW);
//          MCP6.digitalWrite(3, HIGH);
//          break;
//        case YELLOW:
//          MCP6.digitalWrite(1, HIGH);
//          MCP6.digitalWrite(2, HIGH);
//          MCP6.digitalWrite(3, LOW);
//          break;
//        case MAGENTA:
//          MCP6.digitalWrite(1, HIGH);
//          MCP6.digitalWrite(2, LOW);
//          MCP6.digitalWrite(3, HIGH);
//          break;
//        case CYAN:
//          MCP6.digitalWrite(1, LOW);
//          MCP6.digitalWrite(2, HIGH);
//          MCP6.digitalWrite(3, HIGH);
//          break;
//        case WHITE:
//          MCP6.digitalWrite(1, HIGH);
//          MCP6.digitalWrite(2, HIGH);
//          MCP6.digitalWrite(3, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // G#3
//    case 56:
//      switch (color) {
//        case BLACK:
//          MCP6.digitalWrite(4, LOW);
//          MCP6.digitalWrite(5, LOW);
//          MCP6.digitalWrite(6, LOW);
//          break;
//        case RED:
//          MCP6.digitalWrite(4, HIGH);
//          MCP6.digitalWrite(5, LOW);
//          MCP6.digitalWrite(6, LOW);
//          break;
//        case GREEN:
//          MCP6.digitalWrite(4, LOW);
//          MCP6.digitalWrite(5, HIGH);
//          MCP6.digitalWrite(6, LOW);
//          break;
//        case BLUE:
//          MCP6.digitalWrite(4, LOW);
//          MCP6.digitalWrite(5, LOW);
//          MCP6.digitalWrite(6, HIGH);
//          break;
//        case YELLOW:
//          MCP6.digitalWrite(4, HIGH);
//          MCP6.digitalWrite(5, HIGH);
//          MCP6.digitalWrite(6, LOW);
//          break;
//        case MAGENTA:
//          MCP6.digitalWrite(4, HIGH);
//          MCP6.digitalWrite(5, LOW);
//          MCP6.digitalWrite(6, HIGH);
//          break;
//        case CYAN:
//          MCP6.digitalWrite(4, LOW);
//          MCP6.digitalWrite(5, HIGH);
//          MCP6.digitalWrite(6, HIGH);
//          break;
//        case WHITE:
//          MCP6.digitalWrite(4, HIGH);
//          MCP6.digitalWrite(5, HIGH);
//          MCP6.digitalWrite(6, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // A3
//    case 57:
//      switch (color) {
//        case BLACK:
//          MCP6.digitalWrite(7, LOW);
//          MCP1.digitalWrite(8, LOW);
//          MCP1.digitalWrite(9, LOW);
//          break;
//        case RED:
//          MCP6.digitalWrite(7, HIGH);
//          MCP1.digitalWrite(8, LOW);
//          MCP1.digitalWrite(9, LOW);
//          break;
//        case GREEN:
//          MCP6.digitalWrite(7, LOW);
//          MCP1.digitalWrite(8, HIGH);
//          MCP1.digitalWrite(9, LOW);
//          break;
//        case BLUE:
//          MCP6.digitalWrite(7, LOW);
//          MCP1.digitalWrite(8, LOW);
//          MCP1.digitalWrite(9, HIGH);
//          break;
//        case YELLOW:
//          MCP6.digitalWrite(7, HIGH);
//          MCP1.digitalWrite(8, HIGH);
//          MCP1.digitalWrite(9, LOW);
//          break;
//        case MAGENTA:
//          MCP6.digitalWrite(7, HIGH);
//          MCP1.digitalWrite(8, LOW);
//          MCP1.digitalWrite(9, HIGH);
//          break;
//        case CYAN:
//          MCP6.digitalWrite(7, LOW);
//          MCP1.digitalWrite(8, HIGH);
//          MCP1.digitalWrite(9, HIGH);
//          break;
//        case WHITE:
//          MCP6.digitalWrite(7, HIGH);
//          MCP1.digitalWrite(8, HIGH);
//          MCP1.digitalWrite(9, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // A#3
//    case 58:
//      switch (color) {
//        case BLACK:
//          MCP1.digitalWrite(10, LOW);
//          MCP1.digitalWrite(11, LOW);
//          MCP1.digitalWrite(12, LOW);
//          break;
//        case RED:
//          MCP1.digitalWrite(10, HIGH);
//          MCP1.digitalWrite(11, LOW);
//          MCP1.digitalWrite(12, LOW);
//          break;
//        case GREEN:
//          MCP1.digitalWrite(10, LOW);
//          MCP1.digitalWrite(11, HIGH);
//          MCP1.digitalWrite(12, LOW);
//          break;
//        case BLUE:
//          MCP1.digitalWrite(10, LOW);
//          MCP1.digitalWrite(11, LOW);
//          MCP1.digitalWrite(12, HIGH);
//          break;
//        case YELLOW:
//          MCP1.digitalWrite(10, HIGH);
//          MCP1.digitalWrite(11, HIGH);
//          MCP1.digitalWrite(12, LOW);
//          break;
//        case MAGENTA:
//          MCP1.digitalWrite(10, HIGH);
//          MCP1.digitalWrite(11, LOW);
//          MCP1.digitalWrite(12, HIGH);
//          break;
//        case CYAN:
//          MCP1.digitalWrite(10, LOW);
//          MCP1.digitalWrite(11, HIGH);
//          MCP1.digitalWrite(12, HIGH);
//          break;
//        case WHITE:
//          MCP1.digitalWrite(10, HIGH);
//          MCP1.digitalWrite(11, HIGH);
//          MCP1.digitalWrite(12, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // B3
//    case 59:
//      switch (color) {
//        case BLACK:
//          MCP1.digitalWrite(13, LOW);
//          MCP1.digitalWrite(14, LOW);
//          MCP1.digitalWrite(15, LOW);
//          break;
//        case RED:
//          MCP1.digitalWrite(13, HIGH);
//          MCP1.digitalWrite(14, LOW);
//          MCP1.digitalWrite(15, LOW);
//          break;
//        case GREEN:
//          MCP1.digitalWrite(13, LOW);
//          MCP1.digitalWrite(14, HIGH);
//          MCP1.digitalWrite(15, LOW);
//          break;
//        case BLUE:
//          MCP1.digitalWrite(13, LOW);
//          MCP1.digitalWrite(14, LOW);
//          MCP1.digitalWrite(15, HIGH);
//          break;
//        case YELLOW:
//          MCP1.digitalWrite(13, HIGH);
//          MCP1.digitalWrite(14, HIGH);
//          MCP1.digitalWrite(15, LOW);
//          break;
//        case MAGENTA:
//          MCP1.digitalWrite(13, HIGH);
//          MCP1.digitalWrite(14, LOW);
//          MCP1.digitalWrite(15, HIGH);
//          break;
//        case CYAN:
//          MCP1.digitalWrite(13, LOW);
//          MCP1.digitalWrite(14, HIGH);
//          MCP1.digitalWrite(15, HIGH);
//          break;
//        case WHITE:
//          MCP1.digitalWrite(13, HIGH);
//          MCP1.digitalWrite(14, HIGH);
//          MCP1.digitalWrite(15, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // C4
//    case 60:
//      switch (color) {
//        case BLACK:
//          MCP1.digitalWrite(0, LOW);
//          MCP1.digitalWrite(1, LOW);
//          MCP1.digitalWrite(2, LOW);
//          break;
//        case RED:
//          MCP1.digitalWrite(0, HIGH);
//          MCP1.digitalWrite(1, LOW);
//          MCP1.digitalWrite(2, LOW);
//          break;
//        case GREEN:
//          MCP1.digitalWrite(0, LOW);
//          MCP1.digitalWrite(1, HIGH);
//          MCP1.digitalWrite(2, LOW);
//          break;
//        case BLUE:
//          MCP1.digitalWrite(0, LOW);
//          MCP1.digitalWrite(1, LOW);
//          MCP1.digitalWrite(2, HIGH);
//          break;
//        case YELLOW:
//          MCP1.digitalWrite(0, HIGH);
//          MCP1.digitalWrite(1, HIGH);
//          MCP1.digitalWrite(2, LOW);
//          break;
//        case MAGENTA:
//          MCP1.digitalWrite(0, HIGH);
//          MCP1.digitalWrite(1, LOW);
//          MCP1.digitalWrite(2, HIGH);
//          break;
//        case CYAN:
//          MCP1.digitalWrite(0, LOW);
//          MCP1.digitalWrite(1, HIGH);
//          MCP1.digitalWrite(2, HIGH);
//          break;
//        case WHITE:
//          MCP1.digitalWrite(0, HIGH);
//          MCP1.digitalWrite(1, HIGH);
//          MCP1.digitalWrite(2, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // C#4
//    case 61:
//      switch (color) {
//        case BLACK:
//          MCP1.digitalWrite(3, LOW);
//          MCP1.digitalWrite(4, LOW);
//          MCP1.digitalWrite(5, LOW);
//          break;
//        case RED:
//          MCP1.digitalWrite(3, HIGH);
//          MCP1.digitalWrite(4, LOW);
//          MCP1.digitalWrite(5, LOW);
//          break;
//        case GREEN:
//          MCP1.digitalWrite(3, LOW);
//          MCP1.digitalWrite(4, HIGH);
//          MCP1.digitalWrite(5, LOW);
//          break;
//        case BLUE:
//          MCP1.digitalWrite(3, LOW);
//          MCP1.digitalWrite(4, LOW);
//          MCP1.digitalWrite(5, HIGH);
//          break;
//        case YELLOW:
//          MCP1.digitalWrite(3, HIGH);
//          MCP1.digitalWrite(4, HIGH);
//          MCP1.digitalWrite(5, LOW);
//          break;
//        case MAGENTA:
//          MCP1.digitalWrite(3, HIGH);
//          MCP1.digitalWrite(4, LOW);
//          MCP1.digitalWrite(5, HIGH);
//          break;
//        case CYAN:
//          MCP1.digitalWrite(3, LOW);
//          MCP1.digitalWrite(4, HIGH);
//          MCP1.digitalWrite(5, HIGH);
//          break;
//        case WHITE:
//          MCP1.digitalWrite(3, HIGH);
//          MCP1.digitalWrite(4, HIGH);
//          MCP1.digitalWrite(5, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // D4
//    case 62:
//      switch (color) {
//        case BLACK:
//          MCP1.digitalWrite(6, LOW);
//          MCP1.digitalWrite(7, LOW);
//          MCP5.digitalWrite(8, LOW);
//          break;
//        case RED:
//          MCP1.digitalWrite(6, HIGH);
//          MCP1.digitalWrite(7, LOW);
//          MCP5.digitalWrite(8, LOW);
//          break;
//        case GREEN:
//          MCP1.digitalWrite(6, LOW);
//          MCP1.digitalWrite(7, HIGH);
//          MCP5.digitalWrite(8, LOW);
//          break;
//        case BLUE:
//          MCP1.digitalWrite(6, LOW);
//          MCP1.digitalWrite(7, LOW);
//          MCP5.digitalWrite(8, HIGH);
//          break;
//        case YELLOW:
//          MCP1.digitalWrite(6, HIGH);
//          MCP1.digitalWrite(7, HIGH);
//          MCP5.digitalWrite(8, LOW);
//          break;
//        case MAGENTA:
//          MCP1.digitalWrite(6, HIGH);
//          MCP1.digitalWrite(7, LOW);
//          MCP5.digitalWrite(8, HIGH);
//          break;
//        case CYAN:
//          MCP1.digitalWrite(6, LOW);
//          MCP1.digitalWrite(7, HIGH);
//          MCP5.digitalWrite(8, HIGH);
//          break;
//        case WHITE:
//          MCP1.digitalWrite(6, HIGH);
//          MCP1.digitalWrite(7, HIGH);
//          MCP5.digitalWrite(8, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // D#4
//    case 63:
//      switch (color) {
//        case BLACK:
//          MCP5.digitalWrite(9, LOW);
//          MCP5.digitalWrite(10, LOW);
//          MCP5.digitalWrite(11, LOW);
//          break;
//        case RED:
//          MCP5.digitalWrite(9, HIGH);
//          MCP5.digitalWrite(10, LOW);
//          MCP5.digitalWrite(11, LOW);
//          break;
//        case GREEN:
//          MCP5.digitalWrite(9, LOW);
//          MCP5.digitalWrite(10, HIGH);
//          MCP5.digitalWrite(11, LOW);
//          break;
//        case BLUE:
//          MCP5.digitalWrite(9, LOW);
//          MCP5.digitalWrite(10, LOW);
//          MCP5.digitalWrite(11, HIGH);
//          break;
//        case YELLOW:
//          MCP5.digitalWrite(9, HIGH);
//          MCP5.digitalWrite(10, HIGH);
//          MCP5.digitalWrite(11, LOW);
//          break;
//        case MAGENTA:
//          MCP5.digitalWrite(9, HIGH);
//          MCP5.digitalWrite(10, LOW);
//          MCP5.digitalWrite(11, HIGH);
//          break;
//        case CYAN:
//          MCP5.digitalWrite(9, LOW);
//          MCP5.digitalWrite(10, HIGH);
//          MCP5.digitalWrite(11, HIGH);
//          break;
//        case WHITE:
//          MCP5.digitalWrite(9, HIGH);
//          MCP5.digitalWrite(10, HIGH);
//          MCP5.digitalWrite(11, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // E4
//    case 64:
//      switch (color) {
//        case BLACK:
//          MCP5.digitalWrite(12, LOW);
//          MCP5.digitalWrite(13, LOW);
//          MCP5.digitalWrite(14, LOW);
//          break;
//        case RED:
//          MCP5.digitalWrite(12, HIGH);
//          MCP5.digitalWrite(13, LOW);
//          MCP5.digitalWrite(14, LOW);
//          break;
//        case GREEN:
//          MCP5.digitalWrite(12, LOW);
//          MCP5.digitalWrite(13, HIGH);
//          MCP5.digitalWrite(14, LOW);
//          break;
//        case BLUE:
//          MCP5.digitalWrite(12, LOW);
//          MCP5.digitalWrite(13, LOW);
//          MCP5.digitalWrite(14, HIGH);
//          break;
//        case YELLOW:
//          MCP5.digitalWrite(12, HIGH);
//          MCP5.digitalWrite(13, HIGH);
//          MCP5.digitalWrite(14, LOW);
//          break;
//        case MAGENTA:
//          MCP5.digitalWrite(12, HIGH);
//          MCP5.digitalWrite(13, LOW);
//          MCP5.digitalWrite(14, HIGH);
//          break;
//        case CYAN:
//          MCP5.digitalWrite(12, LOW);
//          MCP5.digitalWrite(13, HIGH);
//          MCP5.digitalWrite(14, HIGH);
//          break;
//        case WHITE:
//          MCP5.digitalWrite(12, HIGH);
//          MCP5.digitalWrite(13, HIGH);
//          MCP5.digitalWrite(14, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // F4
//    case 65:
//      switch (color) {
//        case BLACK:
//          MCP5.digitalWrite(15, LOW);
//          MCP5.digitalWrite(0, LOW);
//          MCP5.digitalWrite(1, LOW);
//          break;
//        case RED:
//          MCP5.digitalWrite(15, HIGH);
//          MCP5.digitalWrite(0, LOW);
//          MCP5.digitalWrite(1, LOW);
//          break;
//        case GREEN:
//          MCP5.digitalWrite(15, LOW);
//          MCP5.digitalWrite(0, HIGH);
//          MCP5.digitalWrite(1, LOW);
//          break;
//        case BLUE:
//          MCP5.digitalWrite(15, LOW);
//          MCP5.digitalWrite(0, LOW);
//          MCP5.digitalWrite(1, HIGH);
//          break;
//        case YELLOW:
//          MCP5.digitalWrite(15, HIGH);
//          MCP5.digitalWrite(0, HIGH);
//          MCP5.digitalWrite(1, LOW);
//          break;
//        case MAGENTA:
//          MCP5.digitalWrite(15, HIGH);
//          MCP5.digitalWrite(0, LOW);
//          MCP5.digitalWrite(1, HIGH);
//          break;
//        case CYAN:
//          MCP5.digitalWrite(15, LOW);
//          MCP5.digitalWrite(0, HIGH);
//          MCP5.digitalWrite(1, HIGH);
//          break;
//        case WHITE:
//          MCP5.digitalWrite(15, HIGH);
//          MCP5.digitalWrite(0, HIGH);
//          MCP5.digitalWrite(1, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // F#4
//    case 66:
//      switch (color) {
//        case BLACK:
//          MCP5.digitalWrite(2, LOW);
//          MCP5.digitalWrite(3, LOW);
//          MCP5.digitalWrite(4, LOW);
//          break;
//        case RED:
//          MCP5.digitalWrite(2, HIGH);
//          MCP5.digitalWrite(3, LOW);
//          MCP5.digitalWrite(4, LOW);
//          break;
//        case GREEN:
//          MCP5.digitalWrite(2, LOW);
//          MCP5.digitalWrite(3, HIGH);
//          MCP5.digitalWrite(4, LOW);
//          break;
//        case BLUE:
//          MCP5.digitalWrite(2, LOW);
//          MCP5.digitalWrite(3, LOW);
//          MCP5.digitalWrite(4, HIGH);
//          break;
//        case YELLOW:
//          MCP5.digitalWrite(2, HIGH);
//          MCP5.digitalWrite(3, HIGH);
//          MCP5.digitalWrite(4, LOW);
//          break;
//        case MAGENTA:
//          MCP5.digitalWrite(2, HIGH);
//          MCP5.digitalWrite(3, LOW);
//          MCP5.digitalWrite(4, HIGH);
//          break;
//        case CYAN:
//          MCP5.digitalWrite(2, LOW);
//          MCP5.digitalWrite(3, HIGH);
//          MCP5.digitalWrite(4, HIGH);
//          break;
//        case WHITE:
//          MCP5.digitalWrite(2, HIGH);
//          MCP5.digitalWrite(3, HIGH);
//          MCP5.digitalWrite(4, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // G4
//    case 67:
//      switch (color) {
//        case BLACK:
//          MCP5.digitalWrite(5, LOW);
//          MCP5.digitalWrite(6, LOW);
//          MCP5.digitalWrite(7, LOW);
//          break;
//        case RED:
//          MCP5.digitalWrite(5, HIGH);
//          MCP5.digitalWrite(6, LOW);
//          MCP5.digitalWrite(7, LOW);
//          break;
//        case GREEN:
//          MCP5.digitalWrite(5, LOW);
//          MCP5.digitalWrite(6, HIGH);
//          MCP5.digitalWrite(7, LOW);
//          break;
//        case BLUE:
//          MCP5.digitalWrite(5, LOW);
//          MCP5.digitalWrite(6, LOW);
//          MCP5.digitalWrite(7, HIGH);
//          break;
//        case YELLOW:
//          MCP5.digitalWrite(5, HIGH);
//          MCP5.digitalWrite(6, HIGH);
//          MCP5.digitalWrite(7, LOW);
//          break;
//        case MAGENTA:
//          MCP5.digitalWrite(5, HIGH);
//          MCP5.digitalWrite(6, LOW);
//          MCP5.digitalWrite(7, HIGH);
//          break;
//        case CYAN:
//          MCP5.digitalWrite(5, LOW);
//          MCP5.digitalWrite(6, HIGH);
//          MCP5.digitalWrite(7, HIGH);
//          break;
//        case WHITE:
//          MCP5.digitalWrite(5, HIGH);
//          MCP5.digitalWrite(6, HIGH);
//          MCP5.digitalWrite(7, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // G#4
//    case 68:
//      switch (color) {
//        case BLACK:
//          MCP3.digitalWrite(8, LOW);
//          MCP3.digitalWrite(9, LOW);
//          MCP3.digitalWrite(10, LOW);
//          break;
//        case RED:
//          MCP3.digitalWrite(8, HIGH);
//          MCP3.digitalWrite(9, LOW);
//          MCP3.digitalWrite(10, LOW);
//          break;
//        case GREEN:
//          MCP3.digitalWrite(8, LOW);
//          MCP3.digitalWrite(9, HIGH);
//          MCP3.digitalWrite(10, LOW);
//          break;
//        case BLUE:
//          MCP3.digitalWrite(8, LOW);
//          MCP3.digitalWrite(9, LOW);
//          MCP3.digitalWrite(10, HIGH);
//          break;
//        case YELLOW:
//          MCP3.digitalWrite(8, HIGH);
//          MCP3.digitalWrite(9, HIGH);
//          MCP3.digitalWrite(10, LOW);
//          break;
//        case MAGENTA:
//          MCP3.digitalWrite(8, HIGH);
//          MCP3.digitalWrite(9, LOW);
//          MCP3.digitalWrite(10, HIGH);
//          break;
//        case CYAN:
//          MCP3.digitalWrite(8, LOW);
//          MCP3.digitalWrite(9, HIGH);
//          MCP3.digitalWrite(10, HIGH);
//          break;
//        case WHITE:
//          MCP3.digitalWrite(8, HIGH);
//          MCP3.digitalWrite(9, HIGH);
//          MCP3.digitalWrite(10, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // A4
//    case 69:
//      switch (color) {
//        case BLACK:
//          MCP3.digitalWrite(11, LOW);
//          MCP3.digitalWrite(12, LOW);
//          MCP3.digitalWrite(13, LOW);
//          break;
//        case RED:
//          MCP3.digitalWrite(11, HIGH);
//          MCP3.digitalWrite(12, LOW);
//          MCP3.digitalWrite(13, LOW);
//          break;
//        case GREEN:
//          MCP3.digitalWrite(11, LOW);
//          MCP3.digitalWrite(12, HIGH);
//          MCP3.digitalWrite(13, LOW);
//          break;
//        case BLUE:
//          MCP3.digitalWrite(11, LOW);
//          MCP3.digitalWrite(12, LOW);
//          MCP3.digitalWrite(13, HIGH);
//          break;
//        case YELLOW:
//          MCP3.digitalWrite(11, HIGH);
//          MCP3.digitalWrite(12, HIGH);
//          MCP3.digitalWrite(13, LOW);
//          break;
//        case MAGENTA:
//          MCP3.digitalWrite(11, HIGH);
//          MCP3.digitalWrite(12, LOW);
//          MCP3.digitalWrite(13, HIGH);
//          break;
//        case CYAN:
//          MCP3.digitalWrite(11, LOW);
//          MCP3.digitalWrite(12, HIGH);
//          MCP3.digitalWrite(13, HIGH);
//          break;
//        case WHITE:
//          MCP3.digitalWrite(11, HIGH);
//          MCP3.digitalWrite(12, HIGH);
//          MCP3.digitalWrite(13, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // A#4
//    case 70:
//      switch (color) {
//        case BLACK:
//          MCP3.digitalWrite(14, LOW);
//          MCP3.digitalWrite(15, LOW);
//          MCP3.digitalWrite(0, LOW);
//          break;
//        case RED:
//          MCP3.digitalWrite(14, HIGH);
//          MCP3.digitalWrite(15, LOW);
//          MCP3.digitalWrite(0, LOW);
//          break;
//        case GREEN:
//          MCP3.digitalWrite(14, LOW);
//          MCP3.digitalWrite(15, HIGH);
//          MCP3.digitalWrite(0, LOW);
//          break;
//        case BLUE:
//          MCP3.digitalWrite(14, LOW);
//          MCP3.digitalWrite(15, LOW);
//          MCP3.digitalWrite(0, HIGH);
//          break;
//        case YELLOW:
//          MCP3.digitalWrite(14, HIGH);
//          MCP3.digitalWrite(15, HIGH);
//          MCP3.digitalWrite(0, LOW);
//          break;
//        case MAGENTA:
//          MCP3.digitalWrite(14, HIGH);
//          MCP3.digitalWrite(15, LOW);
//          MCP3.digitalWrite(0, HIGH);
//          break;
//        case CYAN:
//          MCP3.digitalWrite(14, LOW);
//          MCP3.digitalWrite(15, HIGH);
//          MCP3.digitalWrite(0, HIGH);
//          break;
//        case WHITE:
//          MCP3.digitalWrite(14, HIGH);
//          MCP3.digitalWrite(15, HIGH);
//          MCP3.digitalWrite(0, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // B4
//    case 71:
//      switch (color) {
//        case BLACK:
//          MCP3.digitalWrite(1, LOW);
//          MCP3.digitalWrite(2, LOW);
//          MCP3.digitalWrite(3, LOW);
//          break;
//        case RED:
//          MCP3.digitalWrite(1, HIGH);
//          MCP3.digitalWrite(2, LOW);
//          MCP3.digitalWrite(3, LOW);
//          break;
//        case GREEN:
//          MCP3.digitalWrite(1, LOW);
//          MCP3.digitalWrite(2, HIGH);
//          MCP3.digitalWrite(3, LOW);
//          break;
//        case BLUE:
//          MCP3.digitalWrite(1, LOW);
//          MCP3.digitalWrite(2, LOW);
//          MCP3.digitalWrite(3, HIGH);
//          break;
//        case YELLOW:
//          MCP3.digitalWrite(1, HIGH);
//          MCP3.digitalWrite(2, HIGH);
//          MCP3.digitalWrite(3, LOW);
//          break;
//        case MAGENTA:
//          MCP3.digitalWrite(1, HIGH);
//          MCP3.digitalWrite(2, LOW);
//          MCP3.digitalWrite(3, HIGH);
//          break;
//        case CYAN:
//          MCP3.digitalWrite(1, LOW);
//          MCP3.digitalWrite(2, HIGH);
//          MCP3.digitalWrite(3, HIGH);
//          break;
//        case WHITE:
//          MCP3.digitalWrite(1, HIGH);
//          MCP3.digitalWrite(2, HIGH);
//          MCP3.digitalWrite(3, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // C5
//    case 72:
//      switch (color) {
//        case BLACK:
//          MCP3.digitalWrite(4, LOW);
//          MCP3.digitalWrite(5, LOW);
//          MCP3.digitalWrite(6, LOW);
//          break;
//        case RED:
//          MCP3.digitalWrite(4, HIGH);
//          MCP3.digitalWrite(5, LOW);
//          MCP3.digitalWrite(6, LOW);
//          break;
//        case GREEN:
//          MCP3.digitalWrite(4, LOW);
//          MCP3.digitalWrite(5, HIGH);
//          MCP3.digitalWrite(6, LOW);
//          break;
//        case BLUE:
//          MCP3.digitalWrite(4, LOW);
//          MCP3.digitalWrite(5, LOW);
//          MCP3.digitalWrite(6, HIGH);
//          break;
//        case YELLOW:
//          MCP3.digitalWrite(4, HIGH);
//          MCP3.digitalWrite(5, HIGH);
//          MCP3.digitalWrite(6, LOW);
//          break;
//        case MAGENTA:
//          MCP3.digitalWrite(4, HIGH);
//          MCP3.digitalWrite(5, LOW);
//          MCP3.digitalWrite(6, HIGH);
//          break;
//        case CYAN:
//          MCP3.digitalWrite(4, LOW);
//          MCP3.digitalWrite(5, HIGH);
//          MCP3.digitalWrite(6, HIGH);
//          break;
//        case WHITE:
//          MCP3.digitalWrite(4, HIGH);
//          MCP3.digitalWrite(5, HIGH);
//          MCP3.digitalWrite(6, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // C#5
//    case 73:
//      switch (color) {
//        case BLACK:
//          MCP3.digitalWrite(7, LOW);
//          MCP7.digitalWrite(8, LOW);
//          MCP7.digitalWrite(9, LOW);
//          break;
//        case RED:
//          MCP3.digitalWrite(7, HIGH);
//          MCP7.digitalWrite(8, LOW);
//          MCP7.digitalWrite(9, LOW);
//          break;
//        case GREEN:
//          MCP3.digitalWrite(7, LOW);
//          MCP7.digitalWrite(8, HIGH);
//          MCP7.digitalWrite(9, LOW);
//          break;
//        case BLUE:
//          MCP3.digitalWrite(7, LOW);
//          MCP7.digitalWrite(8, LOW);
//          MCP7.digitalWrite(9, HIGH);
//          break;
//        case YELLOW:
//          MCP3.digitalWrite(7, HIGH);
//          MCP7.digitalWrite(8, HIGH);
//          MCP7.digitalWrite(9, LOW);
//          break;
//        case MAGENTA:
//          MCP3.digitalWrite(7, HIGH);
//          MCP7.digitalWrite(8, LOW);
//          MCP7.digitalWrite(9, HIGH);
//          break;
//        case CYAN:
//          MCP3.digitalWrite(7, LOW);
//          MCP7.digitalWrite(8, HIGH);
//          MCP7.digitalWrite(9, HIGH);
//          break;
//        case WHITE:
//          MCP3.digitalWrite(7, HIGH);
//          MCP7.digitalWrite(8, HIGH);
//          MCP7.digitalWrite(9, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // D5
//    case 74:
//      switch (color) {
//        case BLACK:
//          MCP7.digitalWrite(10, LOW);
//          MCP7.digitalWrite(11, LOW);
//          MCP7.digitalWrite(12, LOW);
//          break;
//        case RED:
//          MCP7.digitalWrite(10, HIGH);
//          MCP7.digitalWrite(11, LOW);
//          MCP7.digitalWrite(12, LOW);
//          break;
//        case GREEN:
//          MCP7.digitalWrite(10, LOW);
//          MCP7.digitalWrite(11, HIGH);
//          MCP7.digitalWrite(12, LOW);
//          break;
//        case BLUE:
//          MCP7.digitalWrite(10, LOW);
//          MCP7.digitalWrite(11, LOW);
//          MCP7.digitalWrite(12, HIGH);
//          break;
//        case YELLOW:
//          MCP7.digitalWrite(10, HIGH);
//          MCP7.digitalWrite(11, HIGH);
//          MCP7.digitalWrite(12, LOW);
//          break;
//        case MAGENTA:
//          MCP7.digitalWrite(10, HIGH);
//          MCP7.digitalWrite(11, LOW);
//          MCP7.digitalWrite(12, HIGH);
//          break;
//        case CYAN:
//          MCP7.digitalWrite(10, LOW);
//          MCP7.digitalWrite(11, HIGH);
//          MCP7.digitalWrite(12, HIGH);
//          break;
//        case WHITE:
//          MCP7.digitalWrite(10, HIGH);
//          MCP7.digitalWrite(11, HIGH);
//          MCP7.digitalWrite(12, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // D#5
//    case 75:
//      switch (color) {
//        case BLACK:
//          MCP7.digitalWrite(13, LOW);
//          MCP7.digitalWrite(14, LOW);
//          MCP7.digitalWrite(15, LOW);
//          break;
//        case RED:
//          MCP7.digitalWrite(13, HIGH);
//          MCP7.digitalWrite(14, LOW);
//          MCP7.digitalWrite(15, LOW);
//          break;
//        case GREEN:
//          MCP7.digitalWrite(13, LOW);
//          MCP7.digitalWrite(14, HIGH);
//          MCP7.digitalWrite(15, LOW);
//          break;
//        case BLUE:
//          MCP7.digitalWrite(13, LOW);
//          MCP7.digitalWrite(14, LOW);
//          MCP7.digitalWrite(15, HIGH);
//          break;
//        case YELLOW:
//          MCP7.digitalWrite(13, HIGH);
//          MCP7.digitalWrite(14, HIGH);
//          MCP7.digitalWrite(15, LOW);
//          break;
//        case MAGENTA:
//          MCP7.digitalWrite(13, HIGH);
//          MCP7.digitalWrite(14, LOW);
//          MCP7.digitalWrite(15, HIGH);
//          break;
//        case CYAN:
//          MCP7.digitalWrite(13, LOW);
//          MCP7.digitalWrite(14, HIGH);
//          MCP7.digitalWrite(15, HIGH);
//          break;
//        case WHITE:
//          MCP7.digitalWrite(13, HIGH);
//          MCP7.digitalWrite(14, HIGH);
//          MCP7.digitalWrite(15, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // E5
//    case 76:
//      switch (color) {
//        case BLACK:
//          MCP7.digitalWrite(0, LOW);
//          MCP7.digitalWrite(1, LOW);
//          MCP7.digitalWrite(2, LOW);
//          break;
//        case RED:
//          MCP7.digitalWrite(0, HIGH);
//          MCP7.digitalWrite(1, LOW);
//          MCP7.digitalWrite(2, LOW);
//          break;
//        case GREEN:
//          MCP7.digitalWrite(0, LOW);
//          MCP7.digitalWrite(1, HIGH);
//          MCP7.digitalWrite(2, LOW);
//          break;
//        case BLUE:
//          MCP7.digitalWrite(0, LOW);
//          MCP7.digitalWrite(1, LOW);
//          MCP7.digitalWrite(2, HIGH);
//          break;
//        case YELLOW:
//          MCP7.digitalWrite(0, HIGH);
//          MCP7.digitalWrite(1, HIGH);
//          MCP7.digitalWrite(2, LOW);
//          break;
//        case MAGENTA:
//          MCP7.digitalWrite(0, HIGH);
//          MCP7.digitalWrite(1, LOW);
//          MCP7.digitalWrite(2, HIGH);
//          break;
//        case CYAN:
//          MCP7.digitalWrite(0, LOW);
//          MCP7.digitalWrite(1, HIGH);
//          MCP7.digitalWrite(2, HIGH);
//          break;
//        case WHITE:
//          MCP7.digitalWrite(0, HIGH);
//          MCP7.digitalWrite(1, HIGH);
//          MCP7.digitalWrite(2, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // F5
//    case 77:
//      switch (color) {
//        case BLACK:
//          MCP7.digitalWrite(3, LOW);
//          MCP7.digitalWrite(4, LOW);
//          MCP7.digitalWrite(5, LOW);
//          break;
//        case RED:
//          MCP7.digitalWrite(3, HIGH);
//          MCP7.digitalWrite(4, LOW);
//          MCP7.digitalWrite(5, LOW);
//          break;
//        case GREEN:
//          MCP7.digitalWrite(3, LOW);
//          MCP7.digitalWrite(4, HIGH);
//          MCP7.digitalWrite(5, LOW);
//          break;
//        case BLUE:
//          MCP7.digitalWrite(3, LOW);
//          MCP7.digitalWrite(4, LOW);
//          MCP7.digitalWrite(5, HIGH);
//          break;
//        case YELLOW:
//          MCP7.digitalWrite(3, HIGH);
//          MCP7.digitalWrite(4, HIGH);
//          MCP7.digitalWrite(5, LOW);
//          break;
//        case MAGENTA:
//          MCP7.digitalWrite(3, HIGH);
//          MCP7.digitalWrite(4, LOW);
//          MCP7.digitalWrite(5, HIGH);
//          break;
//        case CYAN:
//          MCP7.digitalWrite(3, LOW);
//          MCP7.digitalWrite(4, HIGH);
//          MCP7.digitalWrite(5, HIGH);
//          break;
//        case WHITE:
//          MCP7.digitalWrite(3, HIGH);
//          MCP7.digitalWrite(4, HIGH);
//          MCP7.digitalWrite(5, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // F#5
//    case 78:
//      switch (color) {
//        case BLACK:
//          MCP7.digitalWrite(6, LOW);
//          MCP7.digitalWrite(7, LOW);
//          MCP7.digitalWrite(8, LOW);
//          break;
//        case RED:
//          MCP7.digitalWrite(6, HIGH);
//          MCP7.digitalWrite(7, LOW);
//          MCP7.digitalWrite(8, LOW);
//          break;
//        case GREEN:
//          MCP7.digitalWrite(6, LOW);
//          MCP7.digitalWrite(7, HIGH);
//          MCP7.digitalWrite(8, LOW);
//          break;
//        case BLUE:
//          MCP7.digitalWrite(6, LOW);
//          MCP7.digitalWrite(7, LOW);
//          MCP7.digitalWrite(8, HIGH);
//          break;
//        case YELLOW:
//          MCP7.digitalWrite(6, HIGH);
//          MCP7.digitalWrite(7, HIGH);
//          MCP7.digitalWrite(8, LOW);
//          break;
//        case MAGENTA:
//          MCP7.digitalWrite(6, HIGH);
//          MCP7.digitalWrite(7, LOW);
//          MCP7.digitalWrite(8, HIGH);
//          break;
//        case CYAN:
//          MCP7.digitalWrite(6, LOW);
//          MCP7.digitalWrite(7, HIGH);
//          MCP7.digitalWrite(8, HIGH);
//          break;
//        case WHITE:
//          MCP7.digitalWrite(6, HIGH);
//          MCP7.digitalWrite(7, HIGH);
//          MCP7.digitalWrite(8, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // G5
//    case 79:
//      switch (color) {
//        case BLACK:
//          MCP7.digitalWrite(9, LOW);
//          MCP7.digitalWrite(10, LOW);
//          MCP7.digitalWrite(11, LOW);
//          break;
//        case RED:
//          MCP7.digitalWrite(9, HIGH);
//          MCP7.digitalWrite(10, LOW);
//          MCP7.digitalWrite(11, LOW);
//          break;
//        case GREEN:
//          MCP7.digitalWrite(9, LOW);
//          MCP7.digitalWrite(10, HIGH);
//          MCP7.digitalWrite(11, LOW);
//          break;
//        case BLUE:
//          MCP7.digitalWrite(9, LOW);
//          MCP7.digitalWrite(10, LOW);
//          MCP7.digitalWrite(11, HIGH);
//          break;
//        case YELLOW:
//          MCP7.digitalWrite(9, HIGH);
//          MCP7.digitalWrite(10, HIGH);
//          MCP7.digitalWrite(11, LOW);
//          break;
//        case MAGENTA:
//          MCP7.digitalWrite(9, HIGH);
//          MCP7.digitalWrite(10, LOW);
//          MCP7.digitalWrite(11, HIGH);
//          break;
//        case CYAN:
//          MCP7.digitalWrite(9, LOW);
//          MCP7.digitalWrite(10, HIGH);
//          MCP7.digitalWrite(11, HIGH);
//          break;
//        case WHITE:
//          MCP7.digitalWrite(9, HIGH);
//          MCP7.digitalWrite(10, HIGH);
//          MCP7.digitalWrite(11, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // G#5
//    case 80:
//      switch (color) {
//        case BLACK:
//          MCP7.digitalWrite(12, LOW);
//          MCP7.digitalWrite(13, LOW);
//          MCP7.digitalWrite(14, LOW);
//          break;
//        case RED:
//          MCP7.digitalWrite(12, HIGH);
//          MCP7.digitalWrite(13, LOW);
//          MCP7.digitalWrite(14, LOW);
//          break;
//        case GREEN:
//          MCP7.digitalWrite(12, LOW);
//          MCP7.digitalWrite(13, HIGH);
//          MCP7.digitalWrite(14, LOW);
//          break;
//        case BLUE:
//          MCP7.digitalWrite(12, LOW);
//          MCP7.digitalWrite(13, LOW);
//          MCP7.digitalWrite(14, HIGH);
//          break;
//        case YELLOW:
//          MCP7.digitalWrite(12, HIGH);
//          MCP7.digitalWrite(13, HIGH);
//          MCP7.digitalWrite(14, LOW);
//          break;
//        case MAGENTA:
//          MCP7.digitalWrite(12, HIGH);
//          MCP7.digitalWrite(13, LOW);
//          MCP7.digitalWrite(14, HIGH);
//          break;
//        case CYAN:
//          MCP7.digitalWrite(12, LOW);
//          MCP7.digitalWrite(13, HIGH);
//          MCP7.digitalWrite(14, HIGH);
//          break;
//        case WHITE:
//          MCP7.digitalWrite(12, HIGH);
//          MCP7.digitalWrite(13, HIGH);
//          MCP7.digitalWrite(14, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // A5
//    case 81:
//      switch (color) {
//        case BLACK:
//          MCP7.digitalWrite(15, LOW);
//          MCP7.digitalWrite(0, LOW);
//          MCP7.digitalWrite(1, LOW);
//          break;
//        case RED:
//          MCP7.digitalWrite(15, HIGH);
//          MCP7.digitalWrite(0, LOW);
//          MCP7.digitalWrite(1, LOW);
//          break;
//        case GREEN:
//          MCP7.digitalWrite(15, LOW);
//          MCP7.digitalWrite(0, HIGH);
//          MCP7.digitalWrite(1, LOW);
//          break;
//        case BLUE:
//          MCP7.digitalWrite(15, LOW);
//          MCP7.digitalWrite(0, LOW);
//          MCP7.digitalWrite(1, HIGH);
//          break;
//        case YELLOW:
//          MCP7.digitalWrite(15, HIGH);
//          MCP7.digitalWrite(0, HIGH);
//          MCP7.digitalWrite(1, LOW);
//          break;
//        case MAGENTA:
//          MCP7.digitalWrite(15, HIGH);
//          MCP7.digitalWrite(0, LOW);
//          MCP7.digitalWrite(1, HIGH);
//          break;
//        case CYAN:
//          MCP7.digitalWrite(15, LOW);
//          MCP7.digitalWrite(0, HIGH);
//          MCP7.digitalWrite(1, HIGH);
//          break;
//        case WHITE:
//          MCP7.digitalWrite(15, HIGH);
//          MCP7.digitalWrite(0, HIGH);
//          MCP7.digitalWrite(1, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // A#5
//    case 82:
//      switch (color) {
//        case BLACK:
//          MCP7.digitalWrite(2, LOW);
//          MCP7.digitalWrite(3, LOW);
//          MCP7.digitalWrite(4, LOW);
//          break;
//        case RED:
//          MCP7.digitalWrite(2, HIGH);
//          MCP7.digitalWrite(3, LOW);
//          MCP7.digitalWrite(4, LOW);
//          break;
//        case GREEN:
//          MCP7.digitalWrite(2, LOW);
//          MCP7.digitalWrite(3, HIGH);
//          MCP7.digitalWrite(4, LOW);
//          break;
//        case BLUE:
//          MCP7.digitalWrite(2, LOW);
//          MCP7.digitalWrite(3, LOW);
//          MCP7.digitalWrite(4, HIGH);
//          break;
//        case YELLOW:
//          MCP7.digitalWrite(2, HIGH);
//          MCP7.digitalWrite(3, HIGH);
//          MCP7.digitalWrite(4, LOW);
//          break;
//        case MAGENTA:
//          MCP7.digitalWrite(2, HIGH);
//          MCP7.digitalWrite(3, LOW);
//          MCP7.digitalWrite(4, HIGH);
//          break;
//        case CYAN:
//          MCP7.digitalWrite(2, LOW);
//          MCP7.digitalWrite(3, HIGH);
//          MCP7.digitalWrite(4, HIGH);
//          break;
//        case WHITE:
//          MCP7.digitalWrite(2, HIGH);
//          MCP7.digitalWrite(3, HIGH);
//          MCP7.digitalWrite(4, HIGH);
//          break;
//        default:
//          break;
//      }
//
//      break;
//    // B5
//    case 83:
//      switch (color) {
//        case BLACK:
//          MCP7.digitalWrite(5, LOW);
//          MCP7.digitalWrite(6, LOW);
//          MCP7.digitalWrite(7, LOW);
//          break;
//        case RED:
//          MCP7.digitalWrite(5, HIGH);
//          MCP7.digitalWrite(6, LOW);
//          MCP7.digitalWrite(7, LOW);
//          break;
//        case GREEN:
//          MCP7.digitalWrite(5, LOW);
//          MCP7.digitalWrite(6, HIGH);
//          MCP7.digitalWrite(7, LOW);
//          break;
//        case BLUE:
//          MCP7.digitalWrite(5, LOW);
//          MCP7.digitalWrite(6, LOW);
//          MCP7.digitalWrite(7, HIGH);
//          break;
//        case YELLOW:
//          MCP7.digitalWrite(5, HIGH);
//          MCP7.digitalWrite(6, HIGH);
//          MCP7.digitalWrite(7, LOW);
//          break;
//        case MAGENTA:
//          MCP7.digitalWrite(5, HIGH);
//          MCP7.digitalWrite(6, LOW);
//          MCP7.digitalWrite(7, HIGH);
//          break;
//        case CYAN:
//          MCP7.digitalWrite(5, LOW);
//          MCP7.digitalWrite(6, HIGH);
//          MCP7.digitalWrite(7, HIGH);
//          break;
//        case WHITE:
//          MCP7.digitalWrite(5, HIGH);
//          MCP7.digitalWrite(6, HIGH);
//          MCP7.digitalWrite(7, HIGH);
//          break;
//        default:
//          break;
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
//  // Sample the first octave
//  digitalWrite(S1, LOW);
//  digitalWrite(S0, LOW);
//
//  for (byte i = 0; i < 12; i++) {
//    intensity = analogRead(i);
//
//    // If the note breaks the threshold
//    if (intensity > THRESHOLD) {
//      duration[i] = millis();
//      noteOn[i] = true;
//      setColor(36 + i, WHITE);
//
////      if (intensity < 450) {
////        setColor(36 + i, RED);
////      }
////      else if (intensity < 600) {
////        setColor(36 + i, GREEN);
////      }
////      else {
////        setColor(36 + i, BLUE);
////      }
//    }
//    // If the note was originally on
//    else if (noteOn[i] == true) {
//      duration[i] = millis() - duration[i];
//      Serial.println(duration[i]);
//      Wire.beginTransmission(4);
//      Wire.write(i);
//      Wire.write(duration[i] & 0x11);
//      Wire.write(duration[i] >> 8);
//      Wire.endTransmission();
//      noteOn[i] = false;
//      setColor(36 + i, keyColors[i]);
//    }
//  }
//
//  // Sample the second octave
//  digitalWrite(S0, HIGH);
//
//  for (byte i = 0; i < 12; i++) {
//    intensity = analogRead(i);
//
//    // If the note breaks the threshold
//    if (intensity > THRESHOLD) {
//      duration[12 + i] = millis();
//      noteOn[12 + i] = true;
//      setColor(48 + i, WHITE);
//
////      if (intensity < 450) {
////        setColor(48 + i, RED);
////      }
////      else if (intensity < 600) {
////        setColor(48 + i, GREEN);
////      }
////      else {
////        setColor(48 + i, BLUE);
////      }
//    }
//    // If the note was originally on
//    else if (noteOn[12 + i] == true) {
//      duration[12 + i] = millis() - duration[12 + i];
//      Serial.println(duration[12 + i]);
//      Wire.beginTransmission(4);
//      Wire.write(i);
//      Wire.write(duration[12 + i] & 0x11);
//      Wire.write(duration[12 + i] >> 8);
//      Wire.endTransmission();
//      noteOn[12 + i] = false;
//      setColor(48 + i, keyColors[12 + i]);
//    }
//  }
//
//  // Sample the fourth octave
//  digitalWrite(S1, HIGH);
//
//  for (byte i = 0; i < 12; i++) {
//    intensity = analogRead(i);
//
//    // If the note breaks the threshold
//    if (intensity > THRESHOLD) {
//      duration[36 + i] = millis();
//      noteOn[36 + i] = true;
//      setColor(72 + i, WHITE);
//
////      if (intensity < 450) {
////        setColor(72 + i, RED);
////      }
////      else if (intensity < 600) {
////        setColor(72 + i, GREEN);
////      }
////      else {
////        setColor(72 + i, BLUE);
////      }
//    }
//    // If the note was originally on
//    else if (noteOn[36 + i] == true) {
//      duration[36 + i] = millis() - duration[36 + i];
//      Serial.println(duration[36 + i]);
//      Wire.beginTransmission(4);
//      Wire.write(i);
//      Wire.write(duration[36 + i] & 0x11);
//      Wire.write(duration[36 + i] >> 8);
//      Wire.endTransmission();
//      noteOn[36 + i] = false;
//      setColor(72 + i, keyColors[36 + i]);
//    }
//  }
//
//  // Sample the third octave
//  digitalWrite(S0, LOW);
//
//  for (byte i = 0; i < 12; i++) {
//    intensity = analogRead(i);
//
//    // If the note breaks the threshold
//    if (intensity > THRESHOLD) {
//      duration[24 + i] = millis();
//      noteOn[24 + i] = true;
//      setColor(60 + i, WHITE);
//
////      if (intensity < 450) {
////        setColor(60 + i, RED);
////      }
////      else if (intensity < 600) {
////        setColor(60 + i, GREEN);
////      }
////      else {
////        setColor(60 + i, BLUE);
////      }
//    }
//    // If the note was originally on
//    else if (noteOn[24 + i] == true) {
//      duration[24 + i] = millis() - duration[24 + i];
//      Serial.println(duration[24 + i]);
//      Wire.beginTransmission(4);
//      Wire.write(i);
//      Wire.write(duration[24 + i] & 0x11);
//      Wire.write(duration[24 + i] >> 8);
//      Wire.endTransmission();
//      noteOn[24 + i] = false;
//      setColor(60 + i, keyColors[24 + i]);
//    }
//  }
//}
//
//// Detect a serial event
//void serialEvent3() {
//  serialAvailable = true;
//
//  while (Serial3.available() > 0) {
//    serialFunction = Serial3.read();
//    serialData = Serial3.read();
//  }
//}
//
//// Process the data received from the serial port
//void processSerialData() {
//  serialAvailable = false;
//
//  if (serialFunction == KEYCHANGE) {
//    MCP0.writeGPIOAB(0x0000);
//    MCP1.writeGPIOAB(0x0000);
//    MCP2.writeGPIOAB(0x0000);
//    MCP3.writeGPIOAB(0x0000);
//    MCP4.writeGPIOAB(0x0000);
//    MCP5.writeGPIOAB(0x0000);
//    MCP6.writeGPIOAB(0x0000);
//    MCP7.writeGPIOAB(0x0000);
//
//    for (int i = 0; i < 48; i++) {
//      keyColors[i] = BLACK;
//      keyNoteOn[i] = false;
//    }
//
//    key = serialData;
//
//    int tonic = serialData % 12;
//    int supertonic = (tonic + 2) % 12;
//    int mediant;
//    int subdominant = (tonic + 5) % 12;
//    int dominant = (tonic + 7) % 12;
//    int submediant;
//    int leadingTone;
//
//    // If it is a major key
//    if (serialData < 12) {
//      mediant = (tonic + 4) % 12;
//      submediant = (tonic + 9) % 12;
//      leadingTone = (tonic + 11) % 12;
//    }
//    // If it is a minor key
//    else {
//      mediant = (tonic + 3) % 12;
//      submediant = (tonic + 8) % 12;
//      leadingTone = (tonic + 10) % 12;
//    }
//
//    for (int i = 0; i < 4; i++) {
//      keyColors[12 * i + tonic] = RED;
//      keyColors[12 * i + supertonic] = BLUE;
//      keyColors[12 * i + mediant] = BLUE;
//      keyColors[12 * i + subdominant] = YELLOW;
//      keyColors[12 * i + dominant] = YELLOW;
//      keyColors[12 * i + submediant] = BLUE;
//      keyColors[12 * i + leadingTone] = GREEN;
//
//      keyNoteOn[12 * i + tonic] = true;
//      keyNoteOn[12 * i + supertonic] = true;
//      keyNoteOn[12 * i + mediant] = true;
//      keyNoteOn[12 * i + subdominant] = true;
//      keyNoteOn[12 * i + dominant] = true;
//      keyNoteOn[12 * i + submediant] = true;
//      keyNoteOn[12 * i + leadingTone] = true;
//
//      if (noteOn[12 * i + tonic] == false) {
//        setColor(12 * i + tonic, RED);
//      }
//
//      if (noteOn[12 * i + supertonic] == false) {
//        setColor(12 * i + supertonic, BLUE);
//      }
//
//      if (noteOn[12 * i + mediant] == false) {
//        setColor(12 * i + mediant, BLUE);
//      }
//
//      if (noteOn[12 * i + subdominant] == false) {
//        setColor(12 * i + subdominant, YELLOW);
//      }
//
//      if (noteOn[12 * i + dominant] == false) {
//        setColor(12 * i + dominant, YELLOW);
//      }
//
//      if (noteOn[12 * i + submediant] == false) {
//        setColor(12 * i + submediant, BLUE);
//      }
//
//      if (noteOn[12 * i + leadingTone] == false) {
//        setColor(12 * i + leadingTone, GREEN);
//      }
//    }
//  }
//  else if (serialFunction == MENUSELECT) {
//  }
//}
