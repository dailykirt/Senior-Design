#include <Wire.h>

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

// Serial function types
#define KEYCHANGE   0
#define MENUSELECT  1

unsigned long duration[12];

void setup() {
  for (int i = 0; i < 12; i++) {
    duration[i] = 0;
  }

  Serial.begin(115200);

  Wire.begin(4);
  Wire.onReceive(receiveDuration);
}

void loop() {
  int key = findMaxDuration();

  if (key != -1) {
    Serial.write(KEYCHANGE);
    Serial.write(key);
  }
}

void receiveDuration(int howMany) {
  while (Wire.available() > 0) {
    byte note = Wire.read();
    duration[note] = duration[note] + Wire.read();
    duration[note] = duration[note] + (Wire.read() << 8);
  }
}

int findMaxDuration() {
  int index = -1;
  unsigned long maxDuration = 0;

  for (int i = 0; i < 12; i++) {
    if (duration[i] > maxDuration) {
      index = i;
    }
  }

  return index;
}
