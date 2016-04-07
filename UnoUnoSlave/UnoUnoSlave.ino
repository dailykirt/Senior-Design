#include <Wire.h>
#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 MCP0;
Adafruit_MCP23017 MCP1;
Adafruit_MCP23017 MCP2;
Adafruit_MCP23017 MCP3;
Adafruit_MCP23017 MCP4;
Adafruit_MCP23017 MCP5;
Adafruit_MCP23017 MCP6;
Adafruit_MCP23017 MCP7;
//Adafruit_MCP23017 MCP[8] = {MCP0, MCP1, MCP2, MCP3, MCP4, MCP5, MCP6, MCP7};

void setup() {
  MCP0.begin(0);
  MCP1.begin(1);
  MCP2.begin(2);
  MCP3.begin(3);
  MCP4.begin(4);
  MCP5.begin(5);
  MCP6.begin(6);
  MCP7.begin(7);

  Serial.begin(115200);

  for (int i = 0; i < 16; i++) {
    MCP0.pinMode(i, OUTPUT);
    MCP1.pinMode(i, OUTPUT);
    MCP2.pinMode(i, OUTPUT);
    MCP3.pinMode(i, OUTPUT);
    MCP4.pinMode(i, OUTPUT);
    MCP5.pinMode(i, OUTPUT);
    MCP6.pinMode(i, OUTPUT);
    MCP7.pinMode(i, OUTPUT);
  }
}

void loop() {
  if (Serial.available() > 0) {
    char number = Serial.read();

    switch (number) {
      case 0:
        MCP0.writeGPIOAB(0x0000);
        MCP1.writeGPIOAB(0xFFFF);
        MCP2.writeGPIOAB(0xFFFF);
        MCP3.writeGPIOAB(0xFFFF);
        MCP4.writeGPIOAB(0xFFFF);
        MCP5.writeGPIOAB(0xFFFF);
        MCP6.writeGPIOAB(0xFFFF);
        MCP7.writeGPIOAB(0xFFFF);
        break;
      case 1:
        MCP0.writeGPIOAB(0xFFFF);
        MCP1.writeGPIOAB(0x0000);
        MCP2.writeGPIOAB(0xFFFF);
        MCP3.writeGPIOAB(0xFFFF);
        MCP4.writeGPIOAB(0xFFFF);
        MCP5.writeGPIOAB(0xFFFF);
        MCP6.writeGPIOAB(0xFFFF);
        MCP7.writeGPIOAB(0xFFFF);
        break;
      case 2:
        MCP0.writeGPIOAB(0xFFFF);
        MCP1.writeGPIOAB(0xFFFF);
        MCP2.writeGPIOAB(0x0000);
        MCP3.writeGPIOAB(0xFFFF);
        MCP4.writeGPIOAB(0xFFFF);
        MCP5.writeGPIOAB(0xFFFF);
        MCP6.writeGPIOAB(0xFFFF);
        MCP7.writeGPIOAB(0xFFFF);
        break;
      case 3:
        MCP0.writeGPIOAB(0xFFFF);
        MCP1.writeGPIOAB(0xFFFF);
        MCP2.writeGPIOAB(0xFFFF);
        MCP3.writeGPIOAB(0x0000);
        MCP4.writeGPIOAB(0xFFFF);
        MCP5.writeGPIOAB(0xFFFF);
        MCP6.writeGPIOAB(0xFFFF);
        MCP7.writeGPIOAB(0xFFFF);
        break;
      case 4:
        MCP0.writeGPIOAB(0xFFFF);
        MCP1.writeGPIOAB(0xFFFF);
        MCP2.writeGPIOAB(0xFFFF);
        MCP3.writeGPIOAB(0xFFFF);
        MCP4.writeGPIOAB(0x0000);
        MCP5.writeGPIOAB(0xFFFF);
        MCP6.writeGPIOAB(0xFFFF);
        MCP7.writeGPIOAB(0xFFFF);
        break;
      case 5:
        MCP0.writeGPIOAB(0xFFFF);
        MCP1.writeGPIOAB(0xFFFF);
        MCP2.writeGPIOAB(0xFFFF);
        MCP3.writeGPIOAB(0xFFFF);
        MCP4.writeGPIOAB(0xFFFF);
        MCP5.writeGPIOAB(0x0000);
        MCP6.writeGPIOAB(0xFFFF);
        MCP7.writeGPIOAB(0xFFFF);
        break;
      case 6:
        MCP0.writeGPIOAB(0xFFFF);
        MCP1.writeGPIOAB(0xFFFF);
        MCP2.writeGPIOAB(0xFFFF);
        MCP3.writeGPIOAB(0xFFFF);
        MCP4.writeGPIOAB(0xFFFF);
        MCP5.writeGPIOAB(0xFFFF);
        MCP6.writeGPIOAB(0x0000);
        MCP7.writeGPIOAB(0xFFFF);
        break;
      case 7:
        MCP0.writeGPIOAB(0xFFFF);
        MCP1.writeGPIOAB(0xFFFF);
        MCP2.writeGPIOAB(0xFFFF);
        MCP3.writeGPIOAB(0xFFFF);
        MCP4.writeGPIOAB(0xFFFF);
        MCP5.writeGPIOAB(0xFFFF);
        MCP6.writeGPIOAB(0xFFFF);
        MCP7.writeGPIOAB(0x0000);
        break;
      default:
        break;
    }
  }
}

//// Paint example specifically for the TFTLCD breakout board.
//// If using the Arduino shield, use the tftpaint_shield.pde sketch instead!
//// DOES NOT CURRENTLY WORK ON ARDUINO LEONARDO
//
//#include <Adafruit_GFX.h>    // Core graphics library
//#include <Adafruit_TFTLCD.h> // Hardware-specific library
//#include <TouchScreen.h>
//
//#if defined(__SAM3X8E__)
//    #undef __FlashStringHelper::F(string_literal)
//    #define F(string_literal) string_literal
//#endif
//
//// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
//// For the Arduino Uno, Duemilanove, Diecimila, etc.:
////   D0 connects to digital pin 8  (Notice these are
////   D1 connects to digital pin 9   NOT in order!)
////   D2 connects to digital pin 2
////   D3 connects to digital pin 3
////   D4 connects to digital pin 4
////   D5 connects to digital pin 5
////   D6 connects to digital pin 6
////   D7 connects to digital pin 7
//
//// For the Arduino Mega, use digital pins 22 through 29
//// (on the 2-row header at the end of the board).
////   D0 connects to digital pin 22
////   D1 connects to digital pin 23
////   D2 connects to digital pin 24
////   D3 connects to digital pin 25
////   D4 connects to digital pin 26
////   D5 connects to digital pin 27
////   D6 connects to digital pin 28
////   D7 connects to digital pin 29
//
//// For the Arduino Due, use digital pins 33 through 40
//// (on the 2-row header at the end of the board).
////   D0 connects to digital pin 33
////   D1 connects to digital pin 34
////   D2 connects to digital pin 35
////   D3 connects to digital pin 36
////   D4 connects to digital pin 37
////   D5 connects to digital pin 38
////   D6 connects to digital pin 39
////   D7 connects to digital pin 40
//
//#define YP A3  // must be an analog pin, use "An" notation!
//#define XM A2  // must be an analog pin, use "An" notation!
//#define YM 9   // can be a digital pin
//#define XP 8   // can be a digital pin
//
//#define TS_MINX 150
//#define TS_MINY 120
//#define TS_MAXX 920
//#define TS_MAXY 940
//
//// For better pressure precision, we need to know the resistance
//// between X+ and X- Use any multimeter to read it
//// For the one we're using, its 300 ohms across the X plate
//TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
//
//#define LCD_CS A3
//#define LCD_CD A2
//#define LCD_WR A1
//#define LCD_RD A0
//// optional
//#define LCD_RESET A4
//
//// Assign human-readable names to some common 16-bit color values:
//#define BLACK   0x0000
//#define BLUE    0x001F
//#define RED     0xF800
//#define GREEN   0x07E0
//#define CYAN    0x07FF
//#define MAGENTA 0xF81F
//#define YELLOW  0xFFE0
//#define WHITE   0xFFFF
//
//
//Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
//
//#define BOXSIZE 40
//#define PENRADIUS 3
//int oldcolor, currentcolor;
//
//void setup(void) {
//  tft.reset();
//  uint16_t identifier = tft.readID();
//  identifier = 0x8357;
//  tft.begin(identifier);
//  tft.fillScreen(BLACK); 
//  pinMode(13, OUTPUT);
//  Serial.begin(115200);
//}
//
//#define MINPRESSURE 10
//#define MAXPRESSURE 1000
//
//void loop() {
//  if (Serial.available() > 0) {
//    char number = Serial.read();
//
//    switch (number) {
//      case 0:
//        number = '0';
//        break;
//      case 1:
//        number = '1';
//        break;
//      case 2:
//        number = '2';
//        break;
//      case 3:
//        number = '3';
//        break;
//      case 4:
//        number = '4';
//        break;
//      case 5:
//        number = '5';
//        break;
//      case 6:
//        number = '6';
//        break;
//      case 7:
//        number = '7';
//        break;
//      default:
//        break;
//    }
//  
//    tft.drawChar(0, 0, number, RED, BLACK, 2);
//  }
//}
