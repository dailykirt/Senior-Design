volatile int state = LOW;

void setup() {
  // Start the serial
  Serial.begin(9600);

  // LED output
  pinMode(13, OUTPUT);
  // Push button input
  pinMode(2, INPUT);

  // Set the pull-up on the push button
  digitalWrite(2, HIGH);

  // Attach the interrupt
  attachInterrupt(digitalPinToInterrupt(2), blink, CHANGE);
}

void loop() {
  // Write the state to the LED
  digitalWrite(13, state);

  // If the LED is off
  if ((state == 0)) {
    Serial.println("The LED is OFF.");
  // If the LED is on
  } else {
    Serial.println("The LED is ON.");
  }
}

void blink() {
  state = !state;
}

//------------------------------------------------------------------------------------------

//long start = 0;
//volatile long lastButtonPush = 0;
//
//void setup() {
//  // Start the serial
//  Serial.begin(9600);
//
//  // LED output
//  pinMode(13, OUTPUT);
//  // Push button input
//  pinMode(2, INPUT);
//
//  // Set the pull-up on the push button
//  digitalWrite(2, HIGH);
//
//  // Seed the random number generator
//  randomSeed(millis());
//
//  // Wait between 1 to 3 seconds
//  delay(random(1000, 3000));
//
//  // Turn on the LED
//  digitalWrite(13, HIGH);
//
//  // Attach the interrupt
//  attachInterrupt(digitalPinToInterrupt(2), react, FALLING);
//
//  // Get the start time
//  start = millis();
//}
//
//void loop() {
//}
//
//void react() {
//  long time = millis();
//
//  if (time - lastButtonPush > 500) {
//    Serial.print("Your reaction time: ");
//    Serial.print(time - start);
//    Serial.println(" ms");
//  }
//
//  lastButtonPush = time;
//}

//------------------------------------------------------------------------------------------

// Interrupt - pin 2
// LED output - pin 13

//// LED connected to digital pin 13
//int LEDPin = 13;
//// Interrupt pin connect to digital pin 2
//int interruptPin = 2;
//// Initial state of LED is on
//volatile int state = 1;
//
//void setup() {
//  // put your setup code here, to run once:
//  // Sets the LED pin as an output pin
//  pinMode(LEDPin, OUTPUT);
//  pinMode(interruptPin, INPUT);
//  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
//  digitalWrite(LEDPin, state);
//}
//
//void blink() {
//  if (state == 1) {
//    state = 0;
//  } else {
//    state = 1;
//  }
//}
