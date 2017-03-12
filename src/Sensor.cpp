#include <Arduino.h>
#include "Sensor.h"

Sensor::Sensor(int triggerPin, int echoPin) {
  this->triggerPin = triggerPin;
  this->echoPin = echoPin;

  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

int Sensor::getDistance() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  int lecture_echo = pulseIn(echoPin, HIGH, 20000);

  return lecture_echo / 58;
}
