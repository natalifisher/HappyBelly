#include <Arduino.h>
// TTGO manual: http://www.lilygo.cn/prod_view.aspx?Id=1126
// shows which are input only (might be wrong idk): https://randomnerdtutorials.com/esp32-pinout-reference-gpios/

// Check which pins are input only! available online
#define RED_PIN 32
#define YELLOW_PIN 33
#define GREEN_PIN 25
#define BLUE_PIN 25
#define PHTOTOSENSOR_PIN 36
#define PHOTOSENSOR_THRESHOLD 1.5
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

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}