/*Display the data packet from master on serial monitor and transfer last byte of it to master*/
#include <Wire.h>    //declare I2C library function
int x;    //variable x determine whether led on master is on or off//
//initializing
void setup()
{
  Wire.begin(4);    //join I2Cbus as slave with identified address
  Wire.onReceive(receiveEvent);    //register a function to be called when slave receive a transmission from master//
  Wire.onRequest(requestEvent);    //register a function when master request data from this slave device//
  Serial.begin(9600);    //set serial baud rate
 }
//mian program 
void loop()
{
  delay(100);
}
//when slave receive string from master, trigger this event.
void receiveEvent(int howMany)
{
while( Wire.available()>1)    // execute repeatedly until last byte left in the data packet from master//
  {
    char c = Wire.read();    // receive data from master and assign it to char c
    Serial.print(c);    // display char c on serial monitor
  }
//receive last byte of data packet from master
  x = Wire.read();    // receive last data from master and assign it to int x
  Serial.println(x);    // display int x on serial monitor
}
//trigger this event when master request data from slave,
 void requestEvent()
{
  //transfer last byte of data packet receiving from master to master
  Wire.write(x);
}
