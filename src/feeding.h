
#include "constants.h"

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
BREEDS BREED; // selected breed
// source of feeding information: https://a-z-animals.com/blog/dog-feeding-rules-by-size-age-and-weight/
void getFeedingFreqAmt();