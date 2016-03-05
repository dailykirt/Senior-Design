/*
 The circuit:
 * SD card attached to SPI bus as follows:
 ** DI - MOSI - pin 50 / pin 11
 ** DO - MISO - pin 51 / pin 12
 ** SCK - CLK - pin 52 / pin 13
 ** CS - pin 53 / pin 4 / pin 10
 */
#include <SPI.h>
#include <SD.h>
#include <UTFT.h>

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

File root;
UTFT LCD(CTE32HR, 38, 39, 40, 41);

void setup() {
  // Initialize the LCD
  LCD.InitLCD();
  // Set the font
  LCD.setFont(BigFont);
  // Clear the screen
  LCD.clrScr();
  // Set the color to be red
  LCD.setColor(255, 0, 0);
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega, 14 on the Leonardo) must be left as an output
  // or the SD library functions will not work.

  if (!SD.begin(7)) {
    Serial.println("initialization failed!");
    return;
  }

  SD.remove("SDTest.txt");

  Serial.println("initialization done.");
  root = SD.open("SDTest.txt", FILE_WRITE);

  if (root) {
    Serial.print("Writing to test.txt...");
    root.println("Testing...");
    root.close();
    Serial.println("done");
  } else {
    Serial.println("error opening test.txt");
  }

  root = SD.open("SDTest.txt");

  if (root) {
    Serial.println("SDTest.txt:");

    while (root.available()) {
      Serial.write(root.read());
    }

    root.close();
  } else {
    Serial.println("Error opening SDTest.txt");
  }

  Serial.println("Done. Exiting...");
  LCD.print("Got it?", 0, 0);
}

void loop()
{
  // nothing happens after setup finishes.
}
