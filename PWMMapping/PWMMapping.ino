const int PWMOut = 3;
const int PWMIn = 10;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int output = random(256);
  analogWrite(PWMOut, output);
  delay(2);
  int timeHigh = pulseIn(PWMIn, HIGH);
  int input = map(timeHigh, 0, 2040, 0, 255);
  Serial.print("The output value is ");
  Serial.println(output);
  Serial.print("The high time is ");
  Serial.print(timeHigh);
  Serial.println(" us");
  Serial.print("The input value is ");
  Serial.println(input);
  Serial.println();

  if ((output - input) / output * 1.0 > 0.1) {
    Serial.println("THE VALUES ARE NOT THE SAME!!!!!");
    delay(4000);
  }

  delay(1000);
}

//// This is the code used for the Arduino Uno to prototype
//// using multiple Arduino microcontrollers. The Uno will
//// receive data from the Arduino Mega 2560 and handle the
//// LEDs, speaker(s), and SD card. At this point, the Uno is
//// unable to handle the LCD since the LCD is only compatible
//// with the Mega 2560.
////
//// Circuit pin layout:
//// Mega 2560 PWM 3 --> A3
//// Mega 2560 PWM 5 --> A5
//// PWM 3 --> LED #1
//// PWM 5 --> LED #2
//// PWM 9 --> Speaker transistor base
//// 50 --> SD card MISO (DO)
//// 51 --> SD card MOSI (DI)
//// 52 --> SD card CLK (SCK)
//// --> SD card CS
//
//// Musical note frequencies
//#define c4    261.63
//#define db4   277.18
//#define d4    293.66
//#define eb4   311.13
//#define e4    329.63
//#define f4    349.23
//#define gb4   369.99
//#define g4    392.00
//#define ab4   415.30
//#define a4    440.00
//#define bb4   466.16
//#define b4    493.88
//#define c5    523.25
//
//// Input pins
//const int input1 = 3;
//const int input2 = 5;
//// LED pins
//const int LED1 = 3;
//const int LED2 = 5;
//// LED intensities
//int intensity1;
//int intensity2;
