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
// #include "feeding.h"
#include "servo_sensor.h"
#include "display.h"
#include "bluetooth_connection.h"
#include "wificonnect.h"
#define START_TIME millis()

long randnum;
// for user questionnaire -----------------
boolean questionnaire_is_complete = false;
void runQuestionnaire();

// timers
int timer = millis() + GENERAL_FREQUENCY;
int timer_fallcheck = millis() + FALL_FREQUENCY;
int timer_dispense = millis() + 75000;
int val = 1;

void runQuestionnaire()
{
  for (int i = 1; i <= 3; i++)
  {
    askQuestion(i);
    while (getResponse(i) == '\0')
    {
      // Wait until a response is received for the current question
    }

    showResponse(i, getResponse(i));
    delay(5000);
  }
}

void oneTimeQuestionaire()
{
  // one time questionnaire -------------
  if (questionnaire_is_complete == false)
  {
    runQuestionnaire();
    questionnaire_is_complete = true;
    showComplete();
    timer_dispense = millis() + 75000;
  } // ----------------------------------
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
  long humidity = random(75, 99);
  long resPercent = random(0, 99);
  int fell = random(0, 2);
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

void setup()
{
  // Code to run only once:
  // Setup printing
  Serial.begin(9600);
  // Weight sensor setup
  // setupWeightSensors();
  // Lights setup
  // setupLights();

  // Buzzer setup
  // setupBuzzer();

  // Photosensor setup
  // setupPhotosensor();
  // Humidity sensor setup
  // setupHumiditySensor();
  // ask initial user questions here:
  // Servo Setup
  // setUpServo();
  // setupGyro();

  // questionnaire setup
  setupBluetooth();
  setupDisplay();
  delay(3000); // keep this
  oneTimeQuestionaire();

  // wifi setup
  // note: the questionnaire MUST be done before connecting to Wifi/cloud
  // also must disconnect from the bluetooth connection before the setup starts
  // otherwise the data might not send to the cloud for some reason
  setupWifi();
}

void loop()
{
  // demoRun();
  // wifiLoop(float humidity, int resWeight, int petWeight, int age, char *breed)
  // wifiDemo();
  // float humidity = humidityCheck();
  // int resPercent = printPercentWeight();
  // wifiLoop(humidity, resPercent, WEIGHT, AGE, getBreedString());
  delay(5000);
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
