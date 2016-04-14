//this program attempts to connect two arduinos over SPI while letting this arduino control port expanders over I2C
//https://www.arduino.cc/en/Reference/SPI
//http://www.gammon.com.au/spi
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_MCP23017.h"

char buf [100];
volatile byte pos;
volatile boolean process_it;

Adafruit_MCP23017 MCP0;
Adafruit_MCP23017 MCP1;
Adafruit_MCP23017 MCP2;
Adafruit_MCP23017 MCP3;
Adafruit_MCP23017 MCP4;
Adafruit_MCP23017 MCP5;
Adafruit_MCP23017 MCP6;
Adafruit_MCP23017 MCP7;

uint16_t value = 0x0000;
bool bitValue = false;

// SPI interrupt routine
ISR (SPI_STC_vect)
{
byte c = SPDR;  // grab byte from SPI Data Register
  
  // add to buffer if room
  if (pos < sizeof buf)
    {
    buf [pos++] = c;
    
    // example: newline means time to process buffer
    if (c == '\n')
      process_it = true;
      
    }  // end of room available
}  // end of interrupt routine SPI_STC_vect

void setup() {
  //This gets port I/o expanders working over I2C
  MCP0.begin(0);
  MCP1.begin(1);
  MCP2.begin(2);
  MCP3.begin(3);
  MCP4.begin(4);
  MCP5.begin(5);
  MCP6.begin(6);
  MCP7.begin(7);

  Serial.begin(9600);
  
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

  //the following is to get SPI communications between two arduinos working 
  // turn on SPI in slave mode
  SPCR |= bit (SPE);

  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);
  
  // get ready for an interrupt 
  pos = 0;   // buffer empty
  process_it = false;

  // now turn on interrupts
  SPI.attachInterrupt();
}

void loop() {
  if (value == 0x0000) {
    value = 0xFFFF;
  }
  else {
    value = 0x0000;
  }

  MCP0.writeGPIOAB(value);
  MCP1.writeGPIOAB(value);
  MCP2.writeGPIOAB(value);
  MCP3.writeGPIOAB(value);
  MCP4.writeGPIOAB(value);
  MCP5.writeGPIOAB(value);
  MCP6.writeGPIOAB(value);
  MCP7.writeGPIOAB(value);
  
// main loop - wait for flag set in interrupt routine
  if (process_it)
    {
    buf [pos] = 0;  
    Serial.println (buf);
    pos = 0;
    process_it = false;
  }  // end of flag set
  
  delay(100);
}
/*
void setup (void)
{
  Serial.begin (9600);   // debugging
  
  // turn on SPI in slave mode
  SPCR |= bit (SPE);

  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);
  
  // get ready for an interrupt 
  pos = 0;   // buffer empty
  process_it = false;

  // now turn on interrupts
  SPI.attachInterrupt();

}  // end of setup


// SPI interrupt routine
ISR (SPI_STC_vect)
{
byte c = SPDR;  // grab byte from SPI Data Register
  
  // add to buffer if room
  if (pos < sizeof buf)
    {
    buf [pos++] = c;
    
    // example: newline means time to process buffer
    if (c == '\n')
      process_it = true;
      
    }  // end of room available
}  // end of interrupt routine SPI_STC_vect

// main loop - wait for flag set in interrupt routine
void loop (void)
{
  if (process_it)
    {
    buf [pos] = 0;  
    Serial.println (buf);
    pos = 0;
    process_it = false;
    }  // end of flag set
    
}  // end of loop
*/


