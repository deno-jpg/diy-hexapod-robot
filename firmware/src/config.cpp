#include "config.h"

// Left and Right decided by robot direction - USB port is forwards, button is backwards
Controller controllerRight = {Adafruit_PWMServoDriver(0x40)};
Controller controllerLeft = {Adafruit_PWMServoDriver(0x41)};

Leg legRight1 = {controllerRight.pin12, controllerRight.pin13, controllerRight.pin14, controllerRight.instance};
Leg legRight2 = {controllerRight.pin4, controllerRight.pin5, controllerRight.pin6, controllerRight.instance};
Leg legRight3 = {controllerRight.pin0, controllerRight.pin1, controllerRight.pin2, controllerRight.instance};

Leg legLeft1 = {controllerLeft.pin1, controllerLeft.pin2, controllerLeft.pin3, controllerLeft.instance};
Leg legLeft2 = {controllerLeft.pin7, controllerLeft.pin6, controllerLeft.pin5, controllerLeft.instance}; 
Leg legLeft3 = {controllerLeft.pin15, controllerLeft.pin14, controllerLeft.pin13, controllerLeft.instance};