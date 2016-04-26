#include <EventManager.h>
#include <Wire.h>
#include "Adafruit_MCP23017.h"

// MIDI note values
#define NOTE_C2   36
#define NOTE_CS2  37
#define NOTE_D2   38
#define NOTE_DS2  39
#define NOTE_E2   40
#define NOTE_F2   41
#define NOTE_FS2  42
#define NOTE_G2   43
#define NOTE_GS2  44
#define NOTE_A2   45
#define NOTE_AS2  46
#define NOTE_B2   47
#define NOTE_C3   48
#define NOTE_CS3  49
#define NOTE_D3   50
#define NOTE_DS3  51
#define NOTE_E3   52
#define NOTE_F3   53
#define NOTE_FS3  54
#define NOTE_G3   55
#define NOTE_GS3  56
#define NOTE_A3   57
#define NOTE_AS3  58
#define NOTE_B3   59
#define NOTE_C4   60
#define NOTE_CS4  61
#define NOTE_D4   62
#define NOTE_DS4  63
#define NOTE_E4   64
#define NOTE_F4   65
#define NOTE_FS4  66
#define NOTE_G4   67
#define NOTE_GS4  68
#define NOTE_A4   69
#define NOTE_AS4  70
#define NOTE_B4   71
#define NOTE_C5   72
#define NOTE_CS5  73
#define NOTE_D5   74
#define NOTE_DS5  75
#define NOTE_E5   76
#define NOTE_F5   77
#define NOTE_FS5  78
#define NOTE_G5   79
#define NOTE_GS5  80
#define NOTE_A5   81
#define NOTE_AS5  82
#define NOTE_B5   83

// Colors
#define BLACK     0
#define RED       1
#define GREEN     2
#define BLUE      3
#define YELLOW    4
#define MAGENTA   5
#define CYAN      6
#define WHITE     7

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

const int ONTHRESHOLD = 300;
const int OFFTHRESHOLD = 200;

const int S1 = 6;
const int S0 = 5;

const int I2CRESET = 12;

const int LED = 13;

bool noteOn[48];
int keyColors[48];


void setup() {
  //for debugging 
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  //initlize port expanders (I2C)
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
  
  //set all port I/O pins to output 
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
 //initlize note array so all leds are off 
  for (int i = 0; i < 48; i++) {
    noteOn[i] = false;
    keyColors[i] = BLACK;
  }

  pinMode(S1, OUTPUT);
  digitalWrite(S1, LOW);
  pinMode(S0, OUTPUT);
  digitalWrite(S0, LOW);
 // pinMode(MUXENABLE, OUTPUT);
  //digitalWrite(MUXENABLE, LOW);

  digitalWrite(LED, HIGH);
  delay(1000);

  Wire.begin();

  digitalWrite(LED, LOW);
  delay(1000);

  digitalWrite(LED, HIGH);
}

//The following is to get note durations 
class noteDuration {
public:  
  void startTime() {
    duration = millis();
  }

  void stopTime() {
    duration = millis() - duration;
    //send over I2C and typecast as unsigned int 
    Serial.println(duration);
    duration = 0; //reset value 
  }

private:
  unsigned long duration = 0;
};

// Create an array of note durations
noteDuration noteDurationArr[48]; 


void loop() {
  sampleFSRs();
}

void sampleFSRs() {
  int intensity;
  int setColorIndex = 36;
  int noteOnIndex = 0;
  
  for (int i = 0; i < 4; i++) {
    if (i == 0) {
      // Sample first octave
      digitalWrite(S1, LOW);
      digitalWrite(S0, LOW);
    }
    else if (i == 1) {
      // Sample second octave 
      digitalWrite(S0, HIGH);
    }
    else if (i == 2) {
      // Sample the third octave
      digitalWrite(S0, LOW);
      digitalWrite(S1,HIGH);      
    }
    else if (i == 3) {
      // Sample the fourth octave
      digitalWrite(S1, HIGH);
    }

    // Sample each note in the octave 
    for (int j = 0; j < 12; j++) {
      intensity = analogRead(j);

      // If the note breaks the threshold
      if (intensity > ONTHRESHOLD) {
        // Get note start time
        if (noteOn[j + noteOnIndex] == false) {
          noteDurationArr[j + noteOnIndex].startTime();
          noteOn[j + noteOnIndex] = true;
        }

        setColor(setColorIndex + j, WHITE);

//        if (intensity < 450) {
//          setColor(setColorIndex + j, RED);
//        }
//        else if (intensity < 600) {
//          setColor(setColorIndex + j, GREEN);
//        }
//        else {
//          setColor(setColorIndex + j, BLUE);
//        }
      }
      // If the note was originally on
      else if ((noteOn[j + noteOnIndex] == true) && (intensity < OFFTHRESHOLD)) {
        noteDurationArr[j + noteOnIndex].stopTime();
        noteOn[j + noteOnIndex] = false;
        setColor(setColorIndex + j, keyColors[j + noteOnIndex]);
      }
    }

    // Increment setColor and note on index to the next octave
    setColorIndex = setColorIndex + 12;
    noteOnIndex = noteOnIndex + 12;
  }
}



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
