#ifndef KINEMATICS_H
#define KINEMATICS_H
#include "config.h"


void solveIK(Leg leg, float x, float y, float z);
void solveIK(Leg& leg, float x, float y, float z, bool updateCurrent);
float solveCoxa(float x, float y, float z);
float solveFemur(float x, float y, float z);
float solveTibia(float x, float y, float z);

void setServoAngle(Adafruit_PWMServoDriver& controller, int servo, float angle);
float toDegrees(float radian);
float angleToPwm(float angle);

float dotProduct(float x1, float y1, float x2, float y2);

void updateTripodGait(float velocityX, float velocityY);
void initializeGait();

#endif