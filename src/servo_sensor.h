#ifndef SERVO_SENSOR_H
#define SERVO_SENSOR_H

#include <Arduino.h>
#include <Servo.h>
#include "display.h"
#include "weight_sensor.h"

void setUpServo();
void openServo();
void closeServo();
int getTimeSinceDispenced();

#endif
