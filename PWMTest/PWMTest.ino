int LEDPin = 3;
int FSRPin = 1;
int value;

void setup() {
  // put your setup code here, to run once:
  pinMode(LEDPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(FSRPin);
  analogWrite(LEDPin, value / 4);
}
