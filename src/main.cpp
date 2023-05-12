#include <Arduino.h>
#include "weight_sensor.h"
#include "DHT20.h" // for humidity sensor
DHT20 DHT;         // humidity sensor
// TTGO manual: http://www.lilygo.cn/prod_view.aspx?Id=1126
// shows which are input only (might be wrong idk): https://randomnerdtutorials.com/esp32-pinout-reference-gpios/

// Check which pins are input only! available online
#define RED_PIN 32
#define YELLOW_PIN 33
#define GREEN_PIN 25
#define BLUE_PIN 25
#define PHTOTOSENSOR_PIN 36
#define PHOTOSENSOR_THRESHOLD 1.5
#define HUMIDITY_MEDIUM_THRESHOLD 50
#define HUMIDITY_HIGH_THRESHOLD 70
#define START_TIME millis()
int timer = millis() + 2000;
// check photosensor reading; if below light threshold, turn on visibility light
void blinkLight(int pin, int freq)
{
  digitalWrite(pin, HIGH);
  delay(freq);
  digitalWrite(pin, LOW);
  delay(freq);
}
void visiblityLight()
{
  // get photosensor reading
  int photosensor_reading = analogRead(PHTOTOSENSOR_PIN);
  if (photosensor_reading > PHOTOSENSOR_THRESHOLD)
  {
    // turn on blue light for visibility
    digitalWrite(BLUE_PIN, HIGH);
  }
  else
  {
    // turn off blue light for visibility
    digitalWrite(BLUE_PIN, LOW);
  }
}

// check the humidity situation in the reservoir
void humidityCheck()
{
  // Get humidity reading
  float cur_humidity = DHT.getHumidity();
  // Print to terminal
  Serial.print("Humidity (%): ");
  // Compare with humidity thresholds
  if (cur_humidity > HUMIDITY_MEDIUM_THRESHOLD)
  {
    // Alert user of medium humidity issue
    // Suggest opening cap for venting, etc
    // These should be changed to be on TTGO menu/ & display
    Serial.println("The humidity in the reservoir is moderate");
    Serial.println("Opening the reservoir cap might help with ventilation");
  }
  if (cur_humidity > HUMIDITY_HIGH_THRESHOLD)
  {
    // Alert user of high humidity issue
    // Suggest replacing food
    // These should be changed to be on TTGO menu/ & display
    Serial.println("The humidity in the reservoir is high!");
    Serial.println("You may want to replace the food with a newer batch");
    blinkLight(YELLOW_PIN, 200); // yellow blinks every 200ms
  }
  else
  {
    Serial.println("The humidity in the reservoir is low");
    Serial.println("This helps prolong food shelf life");
  }
}

void setup()
{
  // Code to run only once:
  // Setup printing
  Serial.begin(9600);
  // Weight sensor setup
  setupWeightSensors();
  // Setup LEDs
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  // Setup humidity sensor
  DHT.begin(); //  ESP32 default pins are 21, 22
}

void loop()
{
  // Put your main code here, to run repeatedly:
  if ((millis() > timer))
    // visiblityLight()
    // humidityCheck()
    timer = millis() + 2000;
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
