
// this code was initially based on the following tutorial:
// https://how2electronics.com/connecting-esp32-to-amazon-aws-iot-core-using-mqtt/

#include "wificonnect.h"

WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);

void connectAWS()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.setServer(AWS_IOT_ENDPOINT, 8883);

  // // Create a message handler
  // client.setCallback(messageHandler);

  Serial.println("Connecting to AWS IOT");

  while (!client.connect(THINGNAME))
  {
    Serial.print(".");
    delay(100);
  }

  if (!client.connected())
  {
    Serial.println("AWS IoT Timeout!");
    return;
  }

  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

  Serial.println("AWS IoT Connected!");
}

void publishMessage(float humidity, int resWeight, int petWeight, int age, const char *breed, const char *humidityWarning, const char *reservoirWarning, const char *fallOverWarning)
{
  StaticJsonDocument<200> doc;
  doc["humidity"] = humidity;
  doc["resWeight"] = resWeight;
  doc["petWeight"] = petWeight;
  doc["age"] = age;
  doc["breed"] = breed;
  doc["humidityWarning"] = humidityWarning;
  doc["reservoirWarning"] = reservoirWarning;
  // doc["foodEatenWarning"] = foodEatenWarning; //not enough memory?
  doc["fallOverWarning"] = fallOverWarning;

  // doc["temperature"] = temperature;
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client

  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

void messageHandler(char *topic, byte *payload, unsigned int length)
{
  Serial.print("incoming: ");
  Serial.println(topic);

  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char *message = doc["message"];
  Serial.println(message);
}

void setupWifi()
{
  connectAWS();
}

void wifiLoop(float humidity, int resWeight, int petWeight, int age, const char *breed, const char *humidityWarning, const char *reservoirWarning, const char *fallOverWarning)
{
  //  humidity, resWeight, petWeight, age, breed
  // Serial.println("hi");
  // DHT.read();
  // humidity = DHT.getHumidity();
  // temperature = DHT.getTemperature();

  // if (isnan(humidity) || isnan(temperature)) // Check if any reads failed and exit early (to try again).
  // {
  //   Serial.println(F("Failed to read from DHT sensor!"));
  //   return;
  // }

  // Serial.print(F("Humidity: "));
  // Serial.print(humidity);
  // Serial.print(F("%  Temperature: "));
  // Serial.print(temperature);
  // Serial.println(F("°C "));

  publishMessage(humidity, resWeight, petWeight, age, breed, humidityWarning, reservoirWarning, fallOverWarning);
  client.loop();
  // delay(1000);
}