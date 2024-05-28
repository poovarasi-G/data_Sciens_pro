// Sustainability city and communities - Code for Data sciens
// Code Developed by Meritus R & D Team - 27-05-2024
// Copyright © 2024 Meritus R & D Team. All rights reserved.
// This program is the intellectual property of Meritus AI, and may not be distributed or reproduced without explicit authorization from the copyright holder
#include <Wire.h>
#include "MAX30105.h"
MAX30105 particleSensor;

const int ldrSensorPin = 36;
const int gasSensorPin = 35;
const int soundSensorPin = 34;
#define sensorPin1 2
#define sensorPin2 23

const float dist = 0.3;
bool sensor1State = false;
bool sensor2State = false;
unsigned long interval = 0;
unsigned long startTime = 0;
double speed = 0;
const int timeout = 3000;

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing...");

  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  // Initialize sensor
  if (particleSensor.begin(Wire, I2C_SPEED_FAST) == false) {  //Use default I2C port, 400kHz speed
    Serial.println("MAX30102 was not found. Please check wiring/power. ");
    while (1)
      ;
  }
  //The LEDs are very low power and won't affect the temp reading much but
  //you may want to turn off the LEDs to avoid any local heating
  particleSensor.setup(0);            //Configure sensor. Turn off LEDs
  particleSensor.enableDIETEMPRDY();  //Enable the temp ready interrupt. This is required.
}

void loop() {

  int ldrSensorValue = analogRead(ldrSensorPin);
  Serial.print("ldrValue(lx) : ");
  Serial.print(ldrSensorValue);
  Serial.print(", ");

  int gasSensorValue = analogRead(gasSensorPin);
  Serial.print("gasValue(ppm): ");
  Serial.print(gasSensorValue);
  Serial.print(", ");

  int soundSensorValue = analogRead(soundSensorPin);
  Serial.print("soundValue(db) : ");
  Serial.print(soundSensorValue);
  Serial.print(", ");

  float temperatureF = particleSensor.readTemperatureF();
  Serial.print(" temperature(^F) : ");
  Serial.print(temperatureF, 4);

  sensor1State = digitalRead(sensorPin1);
  sensor2State = digitalRead(sensorPin2);
  startTime = 0;

  if (sensor1State == 0) {
    startTime = millis();
    while (digitalRead(sensorPin2)) {
      // Serial.print(sensor2State);
      if (millis() - startTime > timeout) {
        Serial.println(", Timeout");
        return;
      }
      delay(3);
    }

    interval = millis() - startTime;
    if (interval > 3) {
      speed = ((dist) / (interval / 1000.0)) * (18 / 5.0);
      Serial.print(", Speed in kmph = ");
      Serial.println(speed);
      // if (speed > 1) {
      //   digitalWrite(buzzerPin, HIGH);
    }
  }
  Serial.println();
}