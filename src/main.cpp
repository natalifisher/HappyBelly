// TTGO manual: http://www.lilygo.cn/prod_view.aspx?Id=1126
// shows which are input only (might be wrong idk): https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
// Check which pins are input only! available online

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

void wifiDemo()
{
  Serial.println("loop starting");
  char breed[] = "medium";
  // wifiLoop(val * 3, val * 5, val * 7, val * 9, breed);
  val++;
  delay(5000);
}

void wifiAll()
{
  long humidity = humidityCheck();
  long resPercent = getPercentWeight(1);
  int fell = fallCheck();
  setAge(random(0, 15));
  setWeight(random(1, 99));
  setBreed(random(0, 3));
  // wifiLoop(humidity, resPercent, getWeight(), getAge(), getBreedString(), getHumidityString(humidity), "Empty reservoir", "food not eaten", "fell over");
  wifiLoop(humidity, resPercent, getWeight(), getAge(), getBreedString(), getHumidityString(humidity), getReservoirString(resPercent), getFellOverString(fell));
}

void wifiAllfinal()
{
  int humidity = humidityCheck();
  long resPercent = printPercentWeight();
  int fell = fallCheck(); // return buzzing state
  // wifiLoop(humidity, resPercent, getWeight(), getAge(), getBreedString(), getHumidityString(humidity), getReservoirString(resPercent), getFellOverString());
}

// sets up feeding values based from data entered via bluetooth  (breed, weight, & age)
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
  int intervalCheck = 10;
  if (getTimeSinceDispenced() >= intervalCheck)
  {
    if (getWeightSinceDispensed() == getWeight(2))
    {
      Serial.println("Monitor Pet Health\nPet has not eaten");
      displayText(0xF800, "Monitor Pet Health\nPet has not eaten");
    }
  }
}

void setup()
{
  // Code to run only once:
  // Setup printing
  Serial.begin(9600);
  // Weight sensor setup
  setupWeightSensors();
  // Lights setup
  // setupLights();

  // Buzzer setup
  setupBuzzer();

  // Photosensor setup
  // setupPhotosensor();
  // Humidity sensor setup
  setupHumiditySensor();
  // ask initial user questions here:
  // Servo Setup
  setUpServo();
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
  // setupWifi();
}

void loop()
{
  // demoRun();
  // wifiLoop(float humidity, int resWeight, int petWeight, int age, char *breed)
  // wifiDemo();
  // float humidity = humidityCheck();
  // int resPercent = printPercentWeight();
  // wifiLoop(humidity, resPercent, WEIGHT, AGE, getBreedString());
  delay(3000);
  // float humidity = humidityCheck();
  // Serial.println(humidity);
  float pw = getPercentWeight(1);
  float tw = getPercentWeight(2);
  Serial.println(pw);
  Serial.println(tw);
  openServo();
  humidityCheck();
  // visiblityLight();
  fallCheck();
  wifiAll(); // sends data to the cloud, updates are then visible on user dashboard (visualization )
  Serial.println("here");
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

/* -------- CS 147--- Group 25 ------------
          OSCAR                   NATALI

      |\      _,,,---,,_           /^ ^\
ZZZzz /,`.-'`'    -.  ;-;;,_      / 0 0 \
     |,4-  ) )-,_. ,\ (  `'-'     /\ V /\
    '---''(_/--'  `-'\_)           / - \
                                   |    \
                                   || (__V
-----------------------------------------*/
