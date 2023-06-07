#include <Arduino.h>
#include "constants.h"
#include "lights.h"
#include "DHT20.h"
#include "display.h"

void setupHumiditySensor();
float humidityCheck();
const char *getHumidityString(int cur_humidity);