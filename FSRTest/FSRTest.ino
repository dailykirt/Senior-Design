const int THRESHOLD = 400;
const int FSR = A0;
const int RED = 5;
const int GREEN = 6;
const int BLUE = 7;

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int intensity = analogRead(FSR);
  Serial.print("Intensity: ");
  Serial.println(intensity);

  if (intensity > THRESHOLD) {
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, HIGH);
  }
  else {
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
  }
}
