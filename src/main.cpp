// TTGO manual: http://www.lilygo.cn/prod_view.aspx?Id=1126
// shows which are input only (might be wrong idk): https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
// Check which pins are input only! available online

#include <Arduino.h>
#include "gyro_sensor.h"
#include "weight_sensor.h"
#include "humidity_sensor.h"
#include "light_sensor.h"
#include "lights.h"
#include "constants.h"
#define START_TIME millis()

int timer = millis() + GENERAL_FREQUENCY;
int timer_fallcheck = millis() + FALL_FREQUENCY;
void setup()
{
  // Code to run only once:
  // Setup printing
  Serial.begin(9600);
  // Weight sensor setup
  // setupWeightSensors();
  // Lights setup
  // setupLights();
  // Photosensor setup
  // setupPhotosensor();
  // Humidity sensor setup
  setupHumiditySensor();
  // Gyroscope sensor setup
  setupGyro();
  // ask initial user questions here:
}

void loop()
{
  // Put your main code here, to run repeatedly:
  if ((millis() > timer))
  {
    // visiblityLight()
    humidityCheck();
    // printWeights();
    // fallCheck();
    timer = millis() + GENERAL_FREQUENCY;
  }
  if ((millis() > timer_fallcheck))
  {
    fallCheck();
    timer_fallcheck = millis() + FALL_FREQUENCY;
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
