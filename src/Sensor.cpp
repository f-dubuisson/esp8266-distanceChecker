#include <Arduino.h>
#include "Sensor.h"

Sensor::Sensor(int triggerPin, int echoPin) {
  this->triggerPin = triggerPin;
  this->echoPin = echoPin;

  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
}

float Sensor::getDistance() {
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  long lecture_echo = pulseIn(echoPin, HIGH);
  
  return ((double)lecture_echo) / 58;
}
