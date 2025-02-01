const int ledPin = 13;
const int sensorPin = A0; 
const int threshold = 220;
int sensorValue = 0;
bool stopBlinking = false;
unsigned long previousMillis = 0; 
const long interval = 100; 

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(sensorPin);
 
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    if (input.equalsIgnoreCase("stop")) {
      stopBlinking = true; 
    }
  }

  if (sensorValue > threshold && !stopBlinking) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis; 
      if (digitalRead(ledPin) == LOW) {
        digitalWrite(ledPin, HIGH);
      } else {
        digitalWrite(ledPin, LOW);
      }
    }
  } else {
    noBlink(); 
  }
}

void noBlink() {
  digitalWrite(ledPin, LOW); 
}
