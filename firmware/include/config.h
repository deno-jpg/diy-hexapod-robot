#ifndef CONFIG_H
#define CONFIG_H

#include <Adafruit_PWMServoDriver.h>

const float FEMUR_LENGTH = 90.0;
const float TIBIA_LENGTH = 160.0;

const float DEFAULT_SERVO_ANGLE = 90.0;

const int SERVO_MIN = 100;
const int SERVO_MAX = 600;

struct Leg
{
  int coxaPin;
  int femurPin;
  int tibiaPin; 

  Adafruit_PWMServoDriver& controller;
  
  float curX = 180, curY = 0, curZ = 60; // current end point position on default pose

  Leg(int coxaPin, int femurPin, int tibiaPin, Adafruit_PWMServoDriver& controller) 
  : coxaPin(coxaPin), femurPin(femurPin), tibiaPin(tibiaPin), controller(controller) {}
};

struct Controller {
  Adafruit_PWMServoDriver instance;

  int pin0 = 0;
  int pin1 = 1;
  int pin2 = 2;
  int pin3 = 3;
  int pin4 = 4;
  int pin5 = 5;
  int pin6 = 6;  
  int pin7 = 7;
  int pin8 = 8;
  int pin9 = 9;
  int pin10 = 10;
  int pin11 = 11;
  int pin12 = 12;
  int pin13 = 13;
  int pin14 = 14;
  int pin15 = 15;

  Controller(Adafruit_PWMServoDriver instance) : instance(instance) {}
};

extern Leg legRight1, legRight2, legRight3, legLeft1, legLeft2, legLeft3;
extern Controller controllerRight, controllerLeft;

#endif