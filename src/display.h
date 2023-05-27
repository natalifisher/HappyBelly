#ifndef DISPLAY_H
#define DISPLAY_H

#include <TFT_eSPI.h>

void setupDisplay();
void askQuestion(int q_num);
void showResponse(int r_num, char response);
void showComplete();
void displayMessage(int color, char *message, int ypos);

#endif
