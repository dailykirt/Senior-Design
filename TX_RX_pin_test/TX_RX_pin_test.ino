
//this program tests if pins 0,1 which are used for serial can be used on the UNO to signal the mega 

const int pin_1 = 1;
const int pin_2 = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_1, OUTPUT);
  pinMode(pin_2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pin_1,HIGH);
  digitalWrite(pin_2,HIGH);
  delay(1000);
  digitalWrite(pin_1,LOW);
  digitalWrite(pin_2,HIGH);
  delay(1000);

}
