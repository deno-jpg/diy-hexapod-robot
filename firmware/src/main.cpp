#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Dabble.h>
#include "config.h"
#include "kinematics.h"
#include "utils.h"
#include "gait.h"

void setup()
{
  Serial.begin(9600);

  Dabble.begin(9600, 3, 2);

  controllerRight.instance.begin();
  controllerRight.instance.setPWMFreq(50);
  controllerLeft.instance.begin();
  controllerLeft.instance.setPWMFreq(50);
  delay(1000);

  resetLegs();
  delay(1000);

  initializeGait();
  delay(1000);
}

void loop()
{
  Dabble.processInput();

    float velocityX = GamePad.getXaxisData();
    float velocityY = GamePad.getYaxisData();

    updateTripodGait(velocityX, velocityY);


  delay(20);
}