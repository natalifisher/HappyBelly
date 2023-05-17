#include "humidity_sensor.h"
DHT20 DHT; // humidity sensor
void setupHumiditySensor()
{
    // Setup humidity sensor
    DHT.begin(); //  ESP32 default pins are 21, 22
}
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
