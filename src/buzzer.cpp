#include "buzzer.h"

// Configure buzzer pin as output.
void setupBuzzer()
{
    pinMode(BUZZER_PIN, OUTPUT);
}
void activateBuzzer()
{
    tone(BUZZER_PIN, 1000);
}
void disableBuzzer()
{
    noTone(BUZZER_PIN);
}