#include "weight_sensor.h"
#include <Arduino.h>
#include "HX711.h"
#include "soc/rtc.h"

/* ---- WEIGHT SENSOR PIN GUIDE -----------
DT/DOUT: - 21 || 27 || 33 (digital input pins)
SCK: ----- 22 || 26 || 32 (digital output pins)
VCC: ----- 3.3V
GND: ----- GND
----------------------------------------- */

HX711 scale_one;
HX711 scale_two;

void setupWeightSensors()
{
  // scale ONE setup
  scale_one.begin(33, 26); // format: (DT/DOUT, SCK)
  scale_one.set_scale(427.00);
  scale_one.tare();
  // // scale TWO setup
  // scale_two.begin(21, 22); // format: (DT/DOUT, SCK)
  // scale_two.set_scale(459.00);
  // scale_two.tare();
}

int getWeight(int scale_num)
{
  if (scale_num == 1)
  {
    return int(scale_one.get_units());
  }
  else if (scale_num == 2)
  {
    return int(scale_two.get_units());
  }
  return 0;
}

void printWeights()
{
  Serial.println("Scale 1: " + String(scale_one.get_units(), 5) + "\t||\t"); // +
                                                                             //  "Scale 2: " + String(scale_two.get_units(), 0));
  scale_one.power_down();
  // scale_two.power_down();
  delay(1000);
  scale_one.power_up();
  // scale_two.power_up();
}
