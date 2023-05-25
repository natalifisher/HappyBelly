
#include "light_sensor.h"

void setupPhotosensor()
{
    pinMode(PHOTOSENSOR_PIN, INPUT); // needed?
}
// check photosensor reading; if below light threshold, turn on visibility light
void visiblityLight()
{
    // get photosensor reading
    int photosensor_reading = analogRead(PHOTOSENSOR_PIN);
    if (photosensor_reading > PHOTOSENSOR_THRESHOLD)
    {
        // turn on blue light for visibility
        digitalWrite(BLUE_PIN, HIGH); // connect several blue LEDs here
    }
    else
    {
        // turn off blue light for visibility
        digitalWrite(BLUE_PIN, LOW);
    }
}