// Sustainability city and communities - Code for Data sciens
// Code Developed by Meritus R & D Team - 27-05-2024
// Copyright © 2024 Meritus R & D Team. All rights reserved.
// This program is the intellectual property of Meritus AI, and may not be distributed or reproduced without explicit authorization from the copyright holder.
const int pirSensorPin = 36;
const int gasSensorPin = 35;
const int vibrationSensorPin = 34;
const int flame_PIN = 27;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  pinMode(pirSensorPin, INPUT);
  pinMode(gasSensorPin, INPUT);
  pinMode(vibrationSensorPin, INPUT);
  pinMode(flame_PIN, INPUT);
  Serial.println("PIR sensor test");
  Serial.println("gas sensor test");
  Serial.println("Vibration sensor test");
  Serial.println("flame sensor test");
}
void loop() {
  int pirState = analogRead(pirSensorPin);
  int mappedValue = map(pirState, 0, 4095, 0, 100);  // Map the analog reading to a 0 range
  Serial.print("PIR (C): ");
  Serial.print(mappedValue);

  int gasSensorValue = analogRead(gasSensorPin);
  float gasRatio = ((float)(gasSensorValue - 0) / (4095 - 0)) * 100.0;
  Serial.print(" , ");
  Serial.print("gas(ppm): ");
  Serial.print(gasRatio);

  int vibrationValue = analogRead(vibrationSensorPin);
  float vibrationMagnitude = map(vibrationValue, 0, 4095, 0, 10);
  Serial.print(" , Vibration(W/m^2) : ");
  Serial.print(vibrationMagnitude);

  int infrared_value = analogRead(flame_PIN);
  int flame = map(infrared_value, 0, 4095, 0, 100);
  if (flame >= 0 && flame <= 100) {
  Serial.print(" , ");
  Serial.print("flame(no unit): ");
  Serial.println(flame);

  } else {
    // Print a warning message
    Serial.println("Warning: Unexpected analog reading detected!");
  }
}