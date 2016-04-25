byte commandByte;
byte noteByte;
byte velocityByte;

const int LED = 6;

void setup(){
  Serial.begin(31250);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  delay(2000);
}

void checkMIDI(){
  do{
    if (Serial.available()){
      commandByte = Serial.read();//read first byte
      noteByte = Serial.read();//read next byte
      velocityByte = Serial.read();//read final byte
      if (velocityByte > 64) {
        digitalWrite(LED, HIGH);
      }
      else {
        digitalWrite(LED, LOW);
      }
    }
  }
  while (Serial.available() > 2);//when at least three bytes available
}
    

void loop(){
  checkMIDI();
}
