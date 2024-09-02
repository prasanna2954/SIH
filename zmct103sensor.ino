#define SENSOR_PIN A0  // Analog input pin

void setup() {
  Serial.begin(115200);  // Start serial communication at 115200 baud rate
}

void loop() {
  int sensorValue = analogRead(SENSOR_PIN);  // Read the analog value
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);  // Print the value to Serial Monitor
  delay(1000);  // Wait for a second
}
