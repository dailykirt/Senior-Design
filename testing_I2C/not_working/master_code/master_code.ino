 /* Character string “light is” and byte x which is 0 or 1 is sent from master device to slave device repeatingly. When slave device receive the data, slave is requested data by master, byte x is transfered to master and assigned to variable c. Master program judge whether c is 1 or 0, master light up a led when c is 1, or it is off.*/

#include <Wire.h>    //declare I2C library function
#define LED 13
byte x = 0;    //variable x determine whether led on master is on or off
//initializing
void setup()
{
  Wire.begin();    // join the I2C bus as master
  pinMode(LED,OUTPUT);    // initialize the digital pin 13 as output 
}
//main program
 void loop()
{
  Wire.beginTransmission(4);    //begin a transmission to slave device 4
  Wire.write("light is ");    // send character string “light is ”
  Wire.write(x);    // send one byte data to slave
  Wire.endTransmission();    // end a transmission to slave
  x++; //variable x plus one
  if(x==2)    //if variable x value is 2, assign 0 to variable x
  x=0;
  delay(1000);    //delay one second
  Wire.requestFrom(4, 1);    //request one byte from slave 4
  while(Wire.available()>0)    // when data is received from slave to master
  {
    byte c = Wire.read();    //receive one byte from slave and assign to variable c
//if c is 1, light up led
if(c==1)
    {digitalWrite(LED,LOW);}
    else
     {digitalWrite(LED,HIGH);}
  }
  delay(1000);
}
