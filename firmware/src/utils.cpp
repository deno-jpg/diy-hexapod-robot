#include "utils.h"

void resetJoints(Leg leg)
{
  setServoAngle(leg.controller, leg.coxaPin, DEFAULT_SERVO_ANGLE);
  setServoAngle(leg.controller, leg.femurPin, DEFAULT_SERVO_ANGLE);
  setServoAngle(leg.controller, leg.tibiaPin, DEFAULT_SERVO_ANGLE);
}

void resetLegs()
{
  resetJoints(legRight1);
  resetJoints(legRight2);
  resetJoints(legRight3);
  resetJoints(legLeft1);
  resetJoints(legLeft2);
  resetJoints(legLeft3);
}