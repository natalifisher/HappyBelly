#ifndef BLUETOOTH_CONNECTION_H
#define BLUETOOTH_CONNECTION_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "servo_sensor.h"

#include <map>
#include <String.h>

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

extern std::map<String, String> petInfo;

class MyCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic);
};
char *getResponses(); // returns all, whole array
void setupBluetooth();
char getResponse(int num); // used to check if user completed question #


// retrieves user responses from questionnaire and stores in a 'responses' map
void getResponses(std::map<String, String> &responses);

#endif
