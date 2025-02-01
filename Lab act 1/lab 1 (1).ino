void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {

    String isOpen = Serial.readStringUntil('\n');

    if (isOpen == "open") {
      digitalWrite(12, HIGH);
    }
    if (isOpen == "close") {
      digitalWrite(12, LOW);
    }
  }
}
