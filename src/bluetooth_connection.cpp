#include <Arduino.h>
#include "bluetooth_connection.h"
#include <map>

boolean check_health = false;
std::map<String, String> petInfo;
char answers[10] = {'\0'};
int question_num = 1;

// this will run when user send data via bluetooth
void MyCallbacks::onWrite(BLECharacteristic *pCharacteristic)
{
  std::string value = pCharacteristic->getValue();
  const char *valueStr = value.c_str();

  switch (question_num)
  {
  case 1:
    petInfo["Breed?"] = valueStr;
    answers[question_num - 1] = 'c';
    break;
  case 2:
    petInfo["Weight of Pet?"] = valueStr;
    answers[question_num - 1] = 'c';
    break;
  case 3:
    petInfo["Age of Pet?"] = valueStr;
    answers[question_num - 1] = 'c';
    break;
  }
  question_num++;

  if (question_num > 3)
  {
    if (value[0] == 'O' || value[0] == 'o')
    {
      openServo();
    }
    else if (value[0] == 'C' || value[0] == 'c')
    {
      closeServo();
    }
    else if (value[0] == 'W' || value[0] == 'w')
    {
      printPercentWeight();
    }
    // else if (value[0] == 'H' || value[0] == 'h') // health
    // {
    //   checkDispensedFoodEaten();
    // }
  }
}

void getResponses(std::map<String, String> &responses)
{
  responses = petInfo;
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
  return answers[num - 1];
}
