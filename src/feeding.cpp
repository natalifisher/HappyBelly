
#include "feeding.h"
// source of feeding information: https://a-z-animals.com/blog/dog-feeding-rules-by-size-age-and-weight/
void getFeedingFreqAmt()
{
    if (BREED == TOY)
    {
        // toy breed
        if (AGE < 1)
        {
            FEEDING_FREQUENCY = 3;
            if (WEIGHT <= 3) // third a cup per day
            {
                FEEDING_AMOUNT = 0.11;
            }
            else // 3/4 cup per day
            {
                FEEDING_AMOUNT = 0.25;
            }
        }
        else if (AGE <= 10) // adult
        {
            FEEDING_FREQUENCY = 2;
            FEEDING_AMOUNT = 0.5;
        }
        else // senior, increase amt a little
        {
            FEEDING_FREQUENCY = 2;
            FEEDING_AMOUNT = 0.6;
        }
    }
    else if (BREED == SMALL)
    {
        // small breed
        if (AGE < 1)
        {
            if (WEIGHT < 10) // third cup per day
            {
                FEEDING_FREQUENCY = 3;
                FEEDING_AMOUNT = 0.11;
            }
            else // cup per day
            {
                FEEDING_FREQUENCY = 3;
                FEEDING_AMOUNT = 0.33;
            }
        }
        else if (AGE <= 10) // 1.5 cups a day, twice a day
        {
            FEEDING_FREQUENCY = 2;
            FEEDING_AMOUNT = 0.75;
        }
        else // increase amt a little bit
        {
            FEEDING_FREQUENCY = 2;
            FEEDING_AMOUNT = 0.85;
        }
    }
    else if (BREED == MEDIUM)
    {
        // medium breeds
        if (AGE < 1)
        {
            if (WEIGHT <= 25) // 1 cup per day
            {
                FEEDING_FREQUENCY = 4;
                FEEDING_AMOUNT = 0.25;
            }
            else // 2 cups per day
            {
                FEEDING_FREQUENCY = 3;
                FEEDING_AMOUNT = 0.66;
            }
        }
        else if (AGE <= 10) // adult
        {
            FEEDING_FREQUENCY = 2;
            FEEDING_AMOUNT = 1.25;
        }
        else // senior, increase amt a little
        {
            FEEDING_FREQUENCY = 2;
            FEEDING_AMOUNT = 1.35;
        }
    }
    else if (BREED == LARGE)
    {
        // large breeds
        if (AGE < 1)
        {
            if (WEIGHT < 20) // 3/4 cup per day
            {
                FEEDING_FREQUENCY = 4;
                FEEDING_AMOUNT = 0.1875;
            }
            else if (WEIGHT < 30) // 1.5 cups per day
            {
                FEEDING_FREQUENCY = 4;
                FEEDING_AMOUNT = 0.375;
            }
            else if (WEIGHT < 40) // 2 cups per day
            {
                FEEDING_FREQUENCY = 4;
                FEEDING_AMOUNT = 0.5;
            }
            else if (WEIGHT < 50) // 2.5 cups per day
            {
                FEEDING_FREQUENCY = 3;
                FEEDING_AMOUNT = 0.83;
            }
            else if (WEIGHT < 70) // 3 cups
            {
                FEEDING_FREQUENCY = 3;
                FEEDING_AMOUNT = 1;
            }
            else
            {
                FEEDING_FREQUENCY = 3;
                FEEDING_AMOUNT = 1.25;
            }
        }
        else if (AGE <= 10) // adult, 4 cups per day
        {
            FEEDING_FREQUENCY = 2;
            FEEDING_AMOUNT = 2;
        }
        else // senior, increase amt a little
        {
            FEEDING_FREQUENCY = 2;
            FEEDING_AMOUNT = 2.2;
        }
    }
}