#include <Arduino.h>
#include "kinematics.h"

void solveIK(Leg leg, float x, float y, float z)
{
  setServoAngle(leg.controller, leg.coxaPin, solveCoxa(x, y, z));
  setServoAngle(leg.controller, leg.femurPin, solveFemur(x, y, z));
  setServoAngle(leg.controller, leg.tibiaPin, solveTibia(x, y, z));
}

void solveIK(Leg& leg, float x, float y, float z, bool updateCurrent)
{
  setServoAngle(leg.controller, leg.coxaPin, solveCoxa(x, y, z));
  setServoAngle(leg.controller, leg.femurPin, solveFemur(x, y, z));
  setServoAngle(leg.controller, leg.tibiaPin, solveTibia(x, y, z));
  
  if (updateCurrent) {
    leg.curX = x;
    leg.curY = y;
    leg.curZ = z;
  }
}

float solveCoxa(float x, float y, float z)
{
  // solving on xy plane
  float angle = toDegrees(dotProduct(1, 0, x, y));
  if (y < 0)
    angle = -angle;

  /*Serial.println("--- Coxa ---");
  Serial.print("Calculated angle: ");
  Serial.println(angle);
  Serial.print("Servo default: ");
  Serial.println(DEFAULT_SERVO_ANGLE);
  Serial.println("[Adding angle from default]");
  Serial.print("Setting to: ");
  Serial.println(angle + DEFAULT_SERVO_ANGLE);
  Serial.println("-------------");*/

  return angle + DEFAULT_SERVO_ANGLE;
}

float solveFemur(float x, float y, float z)
{
  // solving for xz plane
  float d = sqrt(x * x + z * z);
  float L1 = FEMUR_LENGTH;
  float L2 = TIBIA_LENGTH;

  float angle = acos((d * d + L1 * L1 - L2 * L2) / (2 * L1 * d));
  angle = toDegrees(angle);

  float theta = atan2(z, x);
  angle += toDegrees(theta);

  /*Serial.println("--- Femur ---");
  Serial.print("Atan2: ");
  Serial.println(toDegrees(theta));
  Serial.print("Internal angle: ");
  Serial.println(angle - theta);
  Serial.print("Adding theta to internal angle: ");
  Serial.println(angle);*/

  if (angle < 0)
  {
    angle = 0;
    Serial.println("WARNING! Femur angle clampped to 0");
  }
  else if (angle > 90)
  {
    angle = 90;
    Serial.println("WARNING! Femur angle clampped to 90");
  }

  Serial.println("-------------");

  return angle;
}

float solveTibia(float x, float y, float z)
{
  // solving for xz plane
  float d = sqrt(x * x + z * z);
  float L1 = FEMUR_LENGTH;
  float L2 = TIBIA_LENGTH;

  float angle = acos((L2 * L2 + L1 * L1 - d * d) / (2 * L2 * L1));
  angle = toDegrees(angle);

  /*Serial.println("--- Tibia ---");
  Serial.print("Calculated angle: ");
  Serial.println(angle);*/

  if (angle < 20)
  {
    Serial.println("WARNING! Tibia angle clampped to 20");
  }

  Serial.println("-------------");

  return angle;
}

void setServoAngle(Adafruit_PWMServoDriver& controller, int servo, float angle)
{
  controller.setPWM(servo, 0, angleToPwm(angle));
}

float angleToPwm(float angle)
{
  return SERVO_MIN + ((SERVO_MAX - SERVO_MIN) * angle / 180.0);
}

float toDegrees(float radian)
{
  return radian * (180.0 / M_PI);
}

// Returns dot product of 2 vectors in radians
float dotProduct(float x1, float y1, float x2, float y2)
{
  float xy = x1 * x2 + y1 * y2;
  float len1 = sqrt(x1 * x1 + y1 * y1);
  float len2 = sqrt(x2 * x2 + y2 * y2);

  if (len1 == 0 || len2 == 0)
    return 0;
  return acos(xy / (len1 * len2));
}