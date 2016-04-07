void setup() {
  pinMode(13, OUTPUT);

  Serial.begin(115200);

  while(!Serial) {
  }
}

void loop() {
  if (Serial.available() > 0) {
    bool LED = Serial.read();
    digitalWrite(13, LED);
  }
}
