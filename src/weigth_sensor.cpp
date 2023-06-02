#include "weight_sensor.h"
#include <Arduino.h>
#include "HX711.h"
#include "soc/rtc.h"
#include "constants.h"
#include "buzzer.h"
#include "lights.h"
/* ---- WEIGHT SENSOR PIN GUIDE -----------
DT/DOUT: - 21 || 27 || 33 (digital input pins)
SCK: ----- 22 || 26 || 32 (digital output pins)
VCC: ----- 3.3V
GND: ----- GND
----------------------------------------- */

HX711 scale_one;
HX711 scale_two;
int buzzingWeight = 0;
void setupWeightSensors()
{
  // scale ONE setup
  scale_one.begin(33, 26); // format: (DT/DOUT, SCK)
  scale_one.set_scale(427.00);
  scale_one.tare();
  // // scale TWO setup
  scale_two.begin(27, 32); // format: (DT/DOUT, SCK)
  scale_two.set_scale(459.00);
  scale_two.tare();
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

float getPercentWeight(int scale_num)
{
  if (scale_num == 1)
  {
    return float(scale_one.get_units() * 100.0 / MAX_WEIGHT);
  }
  else if (scale_num == 2)
  {
    return float(scale_two.get_units() * 100.0 / MAX_WEIGHT);
  }
  return 0;
}

void printWeights()
{
  Serial.println("\n\nScale 1: " + String(scale_one.get_units(), 0) + "\t||\t Scale 2:" + String(scale_two.get_units(), 0) + "\n\n");
  scale_one.power_down();
  scale_two.power_down();
  delay(1000);
  scale_one.power_up();
  scale_two.power_up();
}

float printPercentWeight()
{
  float wt = getPercentWeight(1);
  Serial.println("\n\nReservoir: " + String(wt) + "\n\n");
  scale_one.power_down();
  scale_two.power_down();
  delay(1000);
  scale_one.power_up();
  scale_two.power_up();

  if (wt < 50) // less than half empty
  {
    activateBuzzer();
    buzzingWeight = 1;
    blinkLight(RED_PIN, 500); // red blinks every 500ms
  }
  else if (buzzingWeight == 1)
  {
    disableBuzzer(); // turn off buzzer
    buzzingWeight = 0;
    digitalWrite(RED_PIN, LOW);
  }
  return wt;
}

const char *getReservoirString(float weightPercent)
{
  if (weightPercent < 15)
  {
    return "RESERVOIR is EMPTY";
  }
  else if (weightPercent < 50)
  {
    return "Reservoir less than half full";
  }
  else if (weightPercent < 75)
  {
    return "Reservoir less than 3/4 full";
  }
  else
  {
    return "Reservoir is full";
  }
}