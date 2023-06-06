
/* --------- CS 147--- Group 25 ---------------|
|---------------HAPPY BELLY -------------------|
|          OSCAR                   NATALI      |
|                                              |
|      |\      _,,,---,,_           /^ ^\      |
|ZZZzz /,`.-'`'    -.  ;-;;,_      / 0 0 \     |
|     |,4-  ) )-,_. ,\ (  `'-'     /\ V /\     |
|    '---''(_/--'  `-'\_)           / - \      |
|                                   |    \     |
|                                   || (__V    |
|----------------------------------------------*/

// TTGO manual: http://www.lilygo.cn/prod_view.aspx?Id=1126
// shows which are input only: https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
// Check which pins are input only

#include <Arduino.h>
#include "gyro_sensor.h"
#include "weight_sensor.h"
#include "buzzer.h"
#include "humidity_sensor.h"
#include "light_sensor.h"
#include "lights.h"
#include "feeding.h"
#include "constants.h"
#include "feeding.h"
#include "servo_sensor.h"
#include "display.h"
#include "bluetooth_connection.h"
#include "wificonnect.h"

#define START_TIME millis()

boolean dispense = false;

// used to access TTGO screen responses
std::map<String, String> responses;

// needed to print Breed ------------------
const char *breedString = getBreedString();

// for user questionnaire -----------------
boolean questionnaire_is_complete = false;

// timers ---------------------------------
int timer = millis() + GENERAL_FREQUENCY;
int timer_fallcheck = millis() + FALL_FREQUENCY;
int timer_dispense = millis() + 75000;
int val = 1;
long randnum;
int dispenseInterval = -1;
unsigned long startTime = millis();
unsigned long currentTime;
unsigned long elapsedTime;
int recentlyOpened = 0;

// functions ------------------------------
void runQuestionnaire()
{
  for (int i = 1; i <= 3; i++)
  {
    askQuestion(i);
    while (getResponse(i) == '\0')
    {
      // Waits until a response is received for the current question
    }
    getResponses(responses);
    switch (i)
    {
    case 1:
      if (responses.find("Breed?") != responses.end())
      {
        Serial.print("Breed entered is: ");
        Serial.println(responses["Breed?"]);
        showResponse(i, responses["Breed?"]); // displays to TTGO
      }
      break;
    case 2:
      if (responses.find("Weight of Pet?") != responses.end())
      {
        Serial.print("Weight entered is: ");
        Serial.println(responses["Weight of Pet?"]);
        showResponse(i, responses["Weight of Pet?"]);
      }
      break;
    case 3:
      if (responses.find("Age of Pet?") != responses.end())
      {
        Serial.print("Age entered is: ");
        Serial.println(responses["Age of Pet?"]);
        showResponse(i, responses["Age of Pet?"]);
      }
      break;
    default:
      break;
    }
  }
}

void oneTimeQuestionaire()
{
  if (questionnaire_is_complete == false)
  {
    runQuestionnaire();
    questionnaire_is_complete = true;
    showComplete();
    timer_dispense = millis() + 75000; // not sure if needed?
  }
}
void servoRun()
{
  if (dispenseInterval == -1)
  {
    // dispense first time, etc
    openServo();
    recentlyOpened = 1;
    delay(3000);
    closeServo();
    dispenseInterval = 1;
  }
  // dispenseInterval = (86400000 / getFeedingFrequency());
  // if (dispenseInterval >= elapsedTime)
  // {
  //   dispenseInterval = dispenseInterval + dispenseInterval;
  //   openServo();
  //   recentlyOpened = 1;
  //   delay(getFeedingAmount());
  //   closeServo();
  // }
}

void demoRun()
{
  if ((millis() > timer))
  {
    // visiblityLight()
    humidityCheck();
    printWeights();
    // openServo();
    // fallCheck();
    timer = millis() + GENERAL_FREQUENCY;
  }
  if ((millis() > timer_fallcheck))
  {
    fallCheck();
    timer_fallcheck = millis() + FALL_FREQUENCY;
  }
  if ((millis() > timer_dispense))
  {
    openServo();
    timer_dispense = millis() + 75000;
    closeServo();
  }
}

// sends collected data to cloud (AWS)
void wifiAll()
{
  long humidity = humidityCheck();
  long resPercent = getPercentWeight(1);
  int fell = fallCheck();
  wifiLoop(humidity, resPercent, getWeight(), getAge(), getBreedString(), getHumidityString(humidity), getReservoirString(resPercent), getFellOverString(fell));
}

// sets up feeding values based from data entered via bluetooth (breed, weight, & age)
void setupFeeding()
{
  // iterates through each question and response stored
  for (const auto &entry : responses)
  {
    const String &key = entry.first;
    const String &value = entry.second;

    if (key == "Breed?")
    {
      switch (value[0])
      {
      case 'T':
      case 't':
        setBreed(0);
        break;
      case 'S':
      case 's':
        setBreed(1);
        break;
      case 'M':
      case 'm':
        setBreed(2);
        break;
      case 'L':
      case 'l':
        setBreed(3);
        break;
      default:
        break;
      }
      // Serial.println(getBreedString());
    }
    else if (key == "Weight of Pet?")
    {
      int weight = value.toInt();
      setWeight(weight);
      // Serial.println(getWeight());
    }
    else if (key == "Age of Pet?")
    {
      int age = value.toInt();
      setAge(age);
      // Serial.println(getAge());
    }
  }
}

// helps alert the user if their pet is not eating
void checkDispensedFoodEaten()
{
  int intervalCheck = 20; // in seconds
  if (recentlyOpened == 1)
  {
    if (getTimeSinceDispenced() >= intervalCheck)
    {
      if (getWeightSinceDispensed() - getWeight(2) < 5)
      {
        Serial.println("Monitor Pet Health\nPet has not eaten");
        displayText(0xF800, "Pet didn't eat all food");
        delay(5000);
      }
      recentlyOpened = 0;
    }
  }
}

void setup()
{
  // Setup printing
  Serial.begin(9600);
  // Weight sensor setup
  setupWeightSensors();
  // Lights setup
  setupLights();
  // Buzzer setup
  setupBuzzer();
  // Photosensor setup
  setupPhotosensor();
  // Humidity sensor setup
  setupHumiditySensor();
  // ask initial user questions here:
  // Servo Setup
  setUpServo();
  // Gyro and accelerometer setup
  setupGyro();
  // questionnaire setup
  setupBluetooth();
  setupDisplay();
  delay(3000); // keep this
  oneTimeQuestionaire();
  setupFeeding();

  // wifi setup
  // note: the questionnaire MUST be done before connecting to Wifi/cloud
  // also must disconnect from the bluetooth connection before the setup starts
  // otherwise the data might not send to the cloud for some reason
  setupWifi();
}

void loop()
{
  delay(3000);
  currentTime = millis();                // current time
  elapsedTime = currentTime - startTime; // elapsed time
  servoRun();
  checkDispensedFoodEaten();
  float pw = getPercentWeight(1);
  float tw = getPercentWeight(2);
  Serial.println(pw);
  Serial.println(tw);
  humidityCheck();
  visiblityLight();
  fallCheck();

  wifiAll(); // sends data to the cloud, updates are then visible on user dashboard (visualization )
}

/* ---  TEST FOR SERVO ---
setUpServo();
openServo();
closeServo();

*/

/* --- TESTS FOR WEIGHT SENSORS ---
test getWeight() ------------------
Serial.println(getWeight(1));
Serial.println(getWeight(2));
delay(1000);

test printWeights() ---------------
printWeights();
-------------------------------- */