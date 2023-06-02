#include <Arduino.h>
#include "display.h"
#include "map"

const int NUM_STRINGS = 3;
const int MAX_STRING_LENGTH = 50;

TFT_eSPI tft;

char questions[NUM_STRINGS][MAX_STRING_LENGTH] = {
    "Breed of Pet?",
    "Weight of Pet?",
    "Age of Pet?"};

void setupDisplay()
{
    tft.begin();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    // boot animation
    tft.setTextSize(3.5);
    tft.setTextDatum(MC_DATUM);
    tft.setTextColor(TFT_WHITE);

    int textX = tft.width() / 2;
    int textY = tft.height() / 2;
    const char *text = "HAPPY BELLY";

    uint16_t colors[] = {TFT_RED, TFT_ORANGE, TFT_YELLOW, TFT_GREEN, TFT_BLUE,
                         TFT_PURPLE, TFT_RED, TFT_MAGENTA, TFT_BLACK, TFT_RED};

    int numColors = sizeof(colors) / sizeof(colors[0]);

    for (int i = 0; i < numColors; i++)
    {
        tft.fillScreen(colors[i]);
        tft.drawString(text, textX, textY);

        // Delay before changing color
        delay(600);
    }
}

void askQuestion(int q_num)
{
    q_num--;
    tft.setTextSize(2.5);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_RED);
    tft.setCursor(20, 10);
    tft.println("ABOUT PET:");
    
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(20, 30);
    tft.println(questions[q_num]);

    if (q_num == 0)
    {
        tft.setTextColor(TFT_ORANGE);
        tft.setCursor(50, 60);
        tft.setTextSize(2);
        tft.println("TOY || SMALL");
        tft.setCursor(40, 80);
        tft.println("MEDIUM || LARGE");
        tft.setCursor(35, 110);
    }
    else {
        tft.setCursor(35, 80);
    }

    tft.setTextColor(TFT_GREENYELLOW);
    tft.println("ENTER via phone");
}

void showResponse(int r_num, const String &response)
{
    tft.fillScreen(TFT_GREEN);
    tft.setTextSize(2.5);
    tft.setCursor(20, 20);
    tft.setTextColor(TFT_BLACK);
    tft.println("ENTERED:");

    tft.setTextSize(4);
    tft.setTextColor(TFT_WHITE);

    tft.setCursor(75, 70);
    tft.println(response);

    // used to shows response for 5 seconds before moving on
    delay(5000);
}

void showComplete()
{
    tft.setTextColor(TFT_BLACK);
    tft.setTextSize(4);

    for (size_t i = 0; i < 5; i++)
    {
        // Fade to white background
        for (int brightness = 0; brightness <= 255; brightness += 25)
        {
            tft.fillScreen(tft.color565(brightness, brightness, brightness));
            delay(10);
        }

        // Fade to black text color
        for (int brightness = 255; brightness >= 0; brightness -= 25)
        {
            tft.setTextColor(tft.color565(brightness, brightness, brightness));
            tft.setCursor(20, 50);
            tft.println("COMPLETE!");
            delay(10);
        }
        delay(250);

        // Fade to black background
        for (int brightness = 255; brightness >= 0; brightness -= 25)
        {
            tft.fillScreen(tft.color565(brightness, brightness, brightness));
            delay(10);
        }

        // Fade to white text color
        for (int brightness = 0; brightness <= 255; brightness += 25)
        {
            tft.setTextColor(tft.color565(brightness, brightness, brightness));
            tft.setCursor(20, 50);
            tft.println("COMPLETE!");
            delay(10);
        }
        delay(250);
    }
}
void displayText(int color, const String &text)
{
    tft.fillScreen(color);
    tft.setTextSize(3);
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(20, 50);
    tft.println(text);
}

void displayMessage(int color, char *message, int ypos)
{
    // ypos starts at 20
    tft.setTextSize(2);
    tft.setTextColor(color);
    tft.setCursor(ypos, 20);
    tft.println(message);
}

