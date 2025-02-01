int ledPin1 = 8;
int ledPin2 = 9;
int ledPin3 = 10;
int ledPin4 = 11;
int ledPin5 = 12;

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
}

void loop() {
  int fadeValue = 0;
  int fadeAmount = 255;

  // Turn on all LEDs one by one by fading
  fadeLED(ledPin5, fadeValue, fadeAmount, true);
  fadeLED(ledPin4, fadeValue, fadeAmount, true);
  fadeLED(ledPin3, fadeValue, fadeAmount, true);
  fadeLED(ledPin2, fadeValue, fadeAmount, true);
  fadeLED(ledPin1, fadeValue, fadeAmount, true);

  // Turn off all LEDs one by one by fading
  fadeLED(ledPin5, fadeValue, fadeAmount, false);
  fadeLED(ledPin4, fadeValue, fadeAmount, false);
  fadeLED(ledPin3, fadeValue, fadeAmount, false);
  fadeLED(ledPin2, fadeValue, fadeAmount, false);
  fadeLED(ledPin1, fadeValue, fadeAmount, false);
}

void fadeLED(int ledPin, int fadeValue, int fadeAmount, bool fadeIn) {
  if (fadeIn) {
    // Fade in
    while (fadeValue <= 255) {
      analogWrite(ledPin, fadeValue);
      fadeValue += fadeAmount;
      delay(1000);
    }
  } else {
    // Reset fadeValue for fading out
    fadeValue = 255;
    // Fade out
    while (fadeValue >= 0) {
      analogWrite(ledPin, fadeValue);
      fadeValue -= fadeAmount;
      delay(1000);
    }
  }
}
