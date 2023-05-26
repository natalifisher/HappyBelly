#include <Arduino.h>
#include "bluetooth_connection.h"

char responses[10] = {'\0'};
int counter = 0;

void MyCallbacks::onWrite(BLECharacteristic *pCharacteristic)
{
  std::string value = pCharacteristic->getValue();
  if (value.length() > 0)
  {
    responses[counter] = value[0];
    Serial.println("*********");
    Serial.println("Response #" + String(counter + 1));
    Serial.println(responses[counter]);
    Serial.println("*********");
    counter++;
  }
}

void setupBluetooth()
{
  Serial.begin(9600);
  BLEDevice::init("Happy Belly");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE);
  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->setValue("Hello World");
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->start();
}

char getResponse(int num)
{
  return responses[num - 1];
}
