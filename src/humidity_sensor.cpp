#include "humidity_sensor.h"
DHT20 DHT; // humidity sensor
void setupHumiditySensor()
{
    // Setup humidity sensor
    DHT.begin(); //  ESP32 default pins 21 22

    Serial.begin(9600);
    Serial.println(__FILE__);
    Serial.print("DHT20 LIBRARY VERSION: ");
    Serial.println(DHT20_LIB_VERSION);
    Serial.println();

    delay(1000);
}
float humidityCheck()
{
    DHT.read();
    // Get humidity reading
    float cur_humidity = DHT.getHumidity();
    // Print to terminal for testing
    Serial.print("Humidity (%): ");
    Serial.println(cur_humidity);
    // Compare with humidity thresholds
    if (cur_humidity > HUMIDITY_HIGH_THRESHOLD)
    {
        // These print statements were used during testing
        // Alert user of high humidity issue
        // Suggest replacing food
        // Serial.println("The humidity in the reservoir is high!");
        // Serial.println("You may want to replace the food with a newer batch");
        blinkLight(YELLOW_PIN, 100); // yellow blinks every 100ms
    }
    else if (cur_humidity > HUMIDITY_MEDIUM_THRESHOLD)
    {
        // Alert user of medium humidity issue
        // Suggest opening cap for venting, etc
        // Serial.println("The humidity in the reservoir is moderate");
        // Serial.println("Opening the reservoir cap might help with ventilation");
        blinkLight(YELLOW_PIN, 250); // yellow blinks every 300ms
    }
    else // low humidity
    {
        // Serial.println("The humidity in the reservoir is low");
        // Serial.println("This helps prolong food shelf life");
        digitalWrite(YELLOW_PIN, LOW); // turn off yellow LED
    }
    return cur_humidity;
}

const char *getHumidityString(int cur_humidity)
{
    if (cur_humidity > HUMIDITY_HIGH_THRESHOLD)
    {
        // Alert user of high humidity issue
        // Suggest replacing food
        return "HUMIDITY: HIGH! Maybe replace food";
    }
    else if (cur_humidity > HUMIDITY_MEDIUM_THRESHOLD)
    {
        // Alert user of medium humidity issue
        // Suggest opening cap for venting, etc
        return "Humidity: moderate. Improve ventilation";
    }
    else
    {
        return "Humidity: low. Prolongs food life";
    }
}
