// This is the code used for the Arduino Uno to prototype
// using multiple Arduino microcontrollers. The Uno will
// receive data from the Arduino Mega 2560 and handle the
// LEDs, speaker(s), and SD card. At this point, the Uno is
// unable to handle the LCD since the LCD is only compatible
// with the Mega 2560.
//
// Circuit pin layout:
// Mega 2560 PWM 6 --> PWM 6
// Mega 2560 PWM 5 --> PWM 5
// PWM 10 --> LED #1
// PWM 9 --> LED #2
// PWM 11 --> Speaker transistor base
// 50 --> SD card MISO (DO)
// 51 --> SD card MOSI (DI)
// 52 --> SD card CLK (SCK)
// --> SD card CS

// Musical note frequencies
#define c4    261.63
#define db4   277.18
#define d4    293.66
#define eb4   311.13
#define e4    329.63
#define f4    349.23
#define gb4   369.99
#define g4    392.00
#define ab4   415.30
#define a4    440.00
#define bb4   466.16
#define b4    493.88
#define c5    523.25

// Input pins
const int input1 = 6;
const int input2 = 5;
// LED pins
const int LED1 = 9;
const int LED2 = 10;
// Speaker pin
const int speaker = 11;
// LED intensities
int intensity1;
int intensity2;

void setup() {
  // Set up serial connection
  Serial.begin(9600);

  // Input pins
  pinMode(input1, INPUT);
  pinMode(input2, INPUT);
  // Output pins
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  intensity1 = map(pulseIn(input1, HIGH, 2050), 0, 2040, 0, 255);
  intensity2 = map(pulseIn(input2, HIGH, 2050), 0, 2040, 0, 255);

  Serial.print("LED #1 intensity: ");
  Serial.println(intensity1);
  Serial.print("LED #2 intensity: ");
  Serial.println(intensity2);
  Serial.println();

  analogWrite(LED1, intensity1);
  analogWrite(LED2, intensity2);

  if ((intensity1 <= 10) && (intensity2 <= 10)) {
    noTone(speaker);
  }
  else if ((intensity1 > 10) && (intensity2 <= 10)) {
    tone(speaker, c4);
  }
  else if ((intensity1 <= 10) && (intensity2 > 10)) {
    tone(speaker, c5);
  }
    
}
