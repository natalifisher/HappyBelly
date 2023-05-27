#include <Arduino.h>
#include "display.h"

const int NUM_STRINGS = 3;
const int MAX_STRING_LENGTH = 50;

char questions[NUM_STRINGS][MAX_STRING_LENGTH] = {
    "Cat or Dog",
    "Weight?\n\n light medium heavy",
    "Breed?\n\n small medium big"};

TFT_eSPI tft;

void setupDisplay()
{
    tft.begin();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
}

void askQuestion(int q_num)
{
    q_num--;
    tft.setTextSize(2.5);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_RED);
    tft.setCursor(20, 20);
    tft.println("ABOUT PET:");
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(20, 45);
    tft.println(questions[q_num]);
    tft.setCursor(60, 90);
    tft.setTextColor(TFT_GREENYELLOW);
    if (q_num == 0)
    {
        tft.println("(A) or (B)");
    }
    else
    {
        tft.setCursor(20, 110);
        tft.println("(A) or (B) or (C)");
    }
}

void showResponse(int r_num, char response)
{
    tft.fillScreen(TFT_GREEN);
    tft.setTextSize(2.5);
    tft.setCursor(20, 20);
    tft.setTextColor(TFT_BLACK);
    tft.println("ENTERED:");
    tft.setTextSize(4);
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(90, 70);

    switch (response)
    {
    case 'A':
        if (r_num == 1)
        {
            tft.println("CAT");
        }
        else if (r_num == 2)
        {
            tft.setCursor(50, 70);
            tft.println("LIGHT");
        }
        else if (r_num == 3)
        {
            tft.setCursor(50, 70);
            tft.println("SMALL");
        }

        break;
    case 'B':
        if (r_num == 1)
        {
            tft.setCursor(90, 70);
            tft.println("DOG");
        }
        else
        {
            tft.setCursor(40, 70);
            tft.println("MEDIUM");
        }
        break;
    case 'C':
        if (r_num == 2)
        {
            tft.setCursor(50, 70);
            tft.println("HEAVY");
        }
        else
        {
            tft.setCursor(90, 70);
            tft.println("BIG");
        }
        break;

    default:
        tft.setCursor(40, 70);
        tft.println("INVALID");
        break;
    }
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

void displayMessage(int color, char *message, int ypos)
{
    // ypos starts at 20
    tft.setTextSize(2);
    tft.setTextColor(color);
    tft.setCursor(ypos, 20);
    tft.println(message);
}

// void showComplete()
// {

//     tft.setTextColor(TFT_BLACK);
//     tft.setTextSize(4);

//     for (size_t i = 0; i < 10; i++)
//     {
//         tft.setTextColor(TFT_BLACK);
//         tft.fillScreen(TFT_WHITE);
//         tft.setCursor(20, 50);
//         tft.println("COMPLETE!");
//         delay(500);

//         tft.setTextColor(TFT_WHITE);
//         tft.fillScreen(TFT_BLACK);
//         tft.setCursor(20, 50);
//         tft.println("COMPLETE!");
//         delay(500);
//     }
// }
