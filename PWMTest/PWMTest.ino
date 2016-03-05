int LEDPin = 13;
int LEDPin2 = 12;
int FSRPin = 1;
int FSRPin2 = 0;
int value;
int value2;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(LEDPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(FSRPin);
  analogWrite(LEDPin, value / 4);
  Serial.println(value / 4);
}
