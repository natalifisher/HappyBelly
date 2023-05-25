#include <Arduino.h>
#include <Servo.h>
#include "servo_sensor.h"

/* ---- SERVO SENSOR PIN GUIDE -----------
RED: POWER 5V
BLACK: GROUND
WHITE: PIN 27(PREFERED), 0-19(PREFER NOT USE 6-8,11,16)
----------------------------------------- */

Servo myservo; 
//  int open = 0;
//  int close = 90;
int pos = 0;

void setUpServo() {
  myservo.attach(27); // servo pin #
  myservo.write(0);
  closeServo();
  delay(1000);

}

void openServo() {
    while( pos >= 0) {
      pos -= 1;
      myservo.write(pos);
      delay(10);
    }
}

void closeServo() {
while( pos <= 90) {
      pos += 1;
      myservo.write(pos);
      delay(10);
    }
}