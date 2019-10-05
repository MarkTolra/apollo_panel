/*
Apollo inspired "control panel" master board code. The slave handles the LCD

Created: 5/10/19
*/

#include <Arduino.h>
#include <Wire.h>

const int battPin = A0;

uint32_t battMonitor();

void setup() {
  Serial.begin(9600);
  Serial.println("Start up");
}

void loop() {
  Serial.println(battMonitor());
  delay(1000);
}

uint32_t battMonitor()
{
  // reads and returns the voltage for battery monitoring'''

  int sensorValue = analogRead(battPin);
  float voltage = sensorValue * (5.0 /1023.0) * 2;  // convert the value to a true value
  // Serial.println(voltage);

  return voltage;
}