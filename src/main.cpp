#include <Arduino.h>
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

// check photosensor reading; if below light threshold, turn on visibility light
void visiblityLight()
{
  // get photosensor reading
  int photosensor_reading = analogRead(PHTOTOSENSOR_PIN);
  if (photosensor_reading > PHOTOSENSOR_THRESHOLD)
  {
    // turn on blue light for visibility
    digitalWrite(BLUE_PIN, HIGH);
  };
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
  Serial.print(9600);
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
  // visiblityLight()

  delay(999);
}