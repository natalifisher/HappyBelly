// TTGO manual: http://www.lilygo.cn/prod_view.aspx?Id=1126
// shows which are input only (might be wrong idk): https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
// Check which pins are input only! available online

#include <Arduino.h>
#include "SparkFunLSM6DSO.h" // for gyroscope
#include "weight_sensor.h"
#include "humidity_sensor.h"
#include "light_sensor.h"
#include "lights.h"
#include "constants.h"
#define START_TIME millis()

int timer = millis() + 2000;

void fallCheck()
{
}

void setup()
{
  // Code to run only once:
  // Setup printing
  Serial.begin(9600);
  // Weight sensor setup
  setupWeightSensors();
  // Lights setup
  setupLights();
  // Photosensor setup
  setupPhotosensor();
  // Humidity sensor setup
  setupHumiditySensor();
  // ask initial user questions here:
}

void loop()
{
  // Put your main code here, to run repeatedly:
  if ((millis() > timer))
  {
    // visiblityLight()
    // humidityCheck()
    printWeights();
    timer = millis() + 2000;
  }
}

/* --- TESTS FOR WEIGHT SENSORS ---
test getWeight() ------------------
Serial.println(getWeight(1));
Serial.println(getWeight(2));
delay(1000);

test printWeights() ---------------
printWeights();
-------------------------------- */

/* -------- CS 147--- Group 25 ------------
          OSCAR                   NATALI

      |\      _,,,---,,_           /^ ^\
ZZZzz /,`.-'`'    -.  ;-;;,_      / 0 0 \
     |,4-  ) )-,_. ,\ (  `'-'     /\ V /\
    '---''(_/--'  `-'\_)           / - \
                                   |    \
                                   || (__V
-----------------------------------------*/
