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

unsigned long duration[12];
int key = -1;

void setup() {
  for (int i = 0; i < 12; i++) {
    duration[i] = 0;
  }

  Serial.begin(115200);
}

void loop() {
  int maxDuration = findMaxDuration();

  if (maxDuration != key) {
    key = maxDuration;
    Serial.write(key);
  }
}

void serialEvent() {
  byte note = Serial.read();
  byte LSB = Serial.read();
  byte MSB = Serial.read();
  unsigned long noteDuration = (((unsigned long) MSB) << 8) + LSB;
  duration[note] = duration[note] + noteDuration;

  Serial.print("Note: ");
  Serial.println(note);
  Serial.print("Duration: ");
  Serial.println(noteDuration);
}

int findMaxDuration() {
  int index = -1;
  unsigned long maxDuration = 0;

  for (int i = 0; i < 12; i++) {
    if (duration[i] > maxDuration) {
      index = i;
      maxDuration = duration[i];
    }
  }

  return index;
}
