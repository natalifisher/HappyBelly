#ifndef WEIGHT_SENSOR_H
#define WEIGHT_SENSOR_H

#include <Arduino.h>
#include "HX711.h"

void setupWeightSensors();
int getWeight(int scale_num);
int getPercentWeight(int scale_num);
void printWeights();
float printPercentWeight();
#endif
