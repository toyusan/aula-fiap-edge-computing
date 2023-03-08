// Project 1 - LED Flasher
int ledPin = 10;
int ledPin2 = 13;
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  digitalWrite(ledPin2, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  digitalWrite(ledPin2, LOW);
  delay(1000);
}
