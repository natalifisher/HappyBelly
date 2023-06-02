#include "lights.h"

void setupLights()
{
    // Setup LEDs
    pinMode(RED_PIN, OUTPUT);
    pinMode(YELLOW_PIN, OUTPUT);
    // pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
}
void blinkLight(int pin, int freq)
{
    digitalWrite(pin, HIGH);
    delay(freq);
    digitalWrite(pin, LOW);
    delay(freq);
}