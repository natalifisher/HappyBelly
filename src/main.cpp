#include <Arduino.h>
#include "weight_sensor.h"

void setup() {
  Serial.begin(9600);
  setupWeightSensors();
}

void loop() {


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



