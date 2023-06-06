#include <Arduino.h>
#include <Servo.h>
#include "servo_sensor.h"

/* ---- SERVO SENSOR PIN GUIDE -----------
RED: POWER 5V
BLACK: GROUND
WHITE: PIN 27(PREFERED), 0-19(PREFER NOT USE 6-8,11,16)
----------------------------------------- */
// used to calculate how long since food was dispenced
// for warning owner if pet hasnt been eating food

unsigned long last_dispensed_time = 0;

Servo myservo;
//  int open = 0;
//  int close = 90;
int pos = 0;

void setUpServo()
{
  myservo.attach(13); // servo pin #
  myservo.write(0);
  closeServo();
  delay(1000);
}

void openServo()
{
  Serial.println("opening servo...");
  displayText(0x0000,"DISPENSING.."); // displays on ttGo screen

  // keeps track of how long food has been out for
  last_dispensed_time = millis();
  setDispensedBaseWeight();

  while (pos >= 0)
  {
    pos -= 1;
    myservo.write(pos);
    delay(10);
  }
}

void closeServo()
{
  Serial.println("closing servo...");
  displayText(0xF800 ,"CLOSING.....");
  while (pos <= 90)
  {
    pos += 1;
    myservo.write(pos);
    delay(10);
  }
  displayText(0x07E0 ,"-- CLOSED --"); 
}

void dispense() {
  openServo();
  closeServo();
}
// returns seconds food has been on plate for
int getTimeSinceDispenced() {
  unsigned long elapsedTime = millis() - last_dispensed_time;
  unsigned long elapsedSeconds = elapsedTime / 1000;
  return elapsedSeconds;
}