
#include "feeding.h"

int FEEDING_FREQUENCY; // how many times per day
float FEEDING_AMOUNT;  // in cups, per meal
int AGE;               // note it can only take integer values
int WEIGHT;            // in lbs
enum BREEDS            // breeds
{
    TOY,
    SMALL,
    MEDIUM,
    LARGE
};
const float FLOW_RATE = 0.02;
unsigned long feedingTime = 0;

BREEDS BREED; // selected breed
// source of feeding information: https://a-z-animals.com/blog/dog-feeding-rules-by-size-age-and-weight/

// source of feeding information: https://a-z-animals.com/blog/dog-feeding-rules-by-size-age-and-weight/
// void setUpFeedingAmt(char *(*getResponseFunc)())
// {
// }

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

const char *getBreedString()
{
    if (BREED == TOY)
    {
        return "TOY";
    }
    else if (BREED == SMALL)
    {
        return "SMALL";
    }
    else if (BREED == MEDIUM)
    {
        return "MEDIUM";
    }
    else if (BREED == LARGE)
    {
        return "LARGE";
    }
    else
    {
        return "NA";
    }
}

int getAge()
{
    return AGE;
}
int getWeight()
{
    return WEIGHT;
}

void setAge(int newAge)
{
    AGE = newAge;
}

void setWeight(int newWeight)
{
    WEIGHT = newWeight;
}

void setBreed(int newBreed)
{
    if (int(TOY) == newBreed)
    {
        BREED = TOY;
    }
    if (int(SMALL) == newBreed)
    {
        BREED = SMALL;
    }
    if (int(MEDIUM) == newBreed)
    {
        BREED = MEDIUM;
    }
    if (int(LARGE) == newBreed)
    {
        BREED = LARGE;
    }
}
int getFeedingFrequency()
{
    return FEEDING_FREQUENCY;
}
float getFeedingAmount()
{
    return (FEEDING_AMOUNT / FLOW_RATE);
}