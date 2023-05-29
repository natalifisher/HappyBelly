
// this code was initially based on the following tutorial:
// https://how2electronics.com/connecting-esp32-to-amazon-aws-iot-core-using-mqtt/

#include "secrets.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include "humidity_sensor.h"
// #include "DHT20.h"
// #define DHTTYPE DHT20 // DHT 11

#define AWS_IOT_PUBLISH_TOPIC "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"

// float humidity;
// float temperature;

// DHT20 DHT; // Initialize DHT

void connectAWS();

void wifiLoop(float humidity, int resWeight, int petWeight, int age, const char *breed, const char *humidityWarning, const char *reservoirWarning, const char *fallOverWarning);

void messageHandler(char *topic, byte *payload, unsigned int length);

void setupWifi();

void wifiLoop(float humidity, int resWeight, int petWeight, int age, const char *breed, const char *humidityWarning, const char *reservoirWarning, const char *fallOverWarning);