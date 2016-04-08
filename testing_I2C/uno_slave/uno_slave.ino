#include <Wire.h>
int x = 0;
void setup() {
  Serial.begin(115200);

  Wire.begin(0);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);    //register a function when master request data from this slave device//
}

void loop() {
}

void receiveEvent(int howMany) {
  byte number = Wire.read();
  Serial.print(number);
}


 void requestEvent()
{
  //transfer last byte of data packet receiving from master to master
  if(x==0){
    char t = 'p';
    x = 1;
    Wire.write(t);
  }else{
    char t = 'q';
    x = 0;
    Wire.write(t);
  }
}
