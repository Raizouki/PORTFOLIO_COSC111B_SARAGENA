// Pin definitions
#define THERMISTOR_PIN A0
#define PHOTORESISTOR_PIN A2
#define LED_PIN 12

// Threshold values
const int TEMP_THRESHOLD = 50; // 50 Celsius
const int BRIGHTNESS_THRESHOLD = 220; // Light intensity

// Function to read temperature from thermistor
float readTemperature() {
  int sensorValue = analogRead(THERMISTOR_PIN);
  // Convert analog reading to voltage
  float voltage = sensorValue * (5.0 / 1024.0);
  // Assuming a 10k thermistor, Steinhart-Hart equation or similar conversion here
  float temperatureC = (voltage - 0.5) * 100.0; // Simple conversion example
  return temperatureC;
}

// Function to read brightness from photoresistor
int readBrightness() {
  int brightness = analogRead(PHOTORESISTOR_PIN);
  return brightness;
}

void setup() {
  pinMode(LED_PIN, OUTPUT); // Set the LED pin as output
  Serial.begin(9600);       // Initialize serial for debugging
}

void loop() {
  float temperature = readTemperature();
  int brightness = readBrightness();
  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
  
  Serial.print("Brightness: ");
  Serial.println(brightness);

  // If both thresholds are met, blink the LED
  if (temperature >= TEMP_THRESHOLD && brightness >= BRIGHTNESS_THRESHOLD) {
    for (int i = 0; i < 5; i++) { // Fast blinking for alert
      digitalWrite(LED_PIN, HIGH);
      delay(100);
      digitalWrite(LED_PIN, LOW);
      delay(100);
    }
  }
  delay(1000); // Pause before next reading
}
