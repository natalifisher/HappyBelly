
#include "light_sensor.h"

void setupPhotosensor()
{
    pinMode(PHOTOSENSOR_PIN, INPUT); // needed?
}
// check photosensor reading; if below light threshold, turn on visibility light
void visiblityLight()
{
    // get photosensor reading
    float photosensor_reading = analogRead(PHOTOSENSOR_PIN);
    photosensor_reading = photosensor_reading * 3.3 / 4095.0;
    Serial.println(photosensor_reading);
    if (photosensor_reading < PHOTOSENSOR_THRESHOLD)
    {
        Serial.println("light");
        // turn on blue light for visibility
        digitalWrite(BLUE_PIN, HIGH); // connect several blue LEDs here
    }
    else
    {
        // turn off blue light for visibility
        digitalWrite(BLUE_PIN, LOW);
    }
}