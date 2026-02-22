#include "gait.h"
#include "kinematics.h"

float gaitPhase = 0.0;
const float GAIT_SPEED = 0.02; 
const float STEP_HEIGHT = 100.0;
const float STEP_LENGTH = 150.0;
const float DEFAULT_X = 180.0;
const float DEFAULT_Y = 0.0;
const float DEFAULT_Z = 0.0;

void initializeGait()
{
  // Set all legs to default standing position
  solveIK(legRight1, DEFAULT_X, DEFAULT_Y, DEFAULT_Z, true);
  solveIK(legRight2, DEFAULT_X, DEFAULT_Y, DEFAULT_Z, true);
  solveIK(legRight3, DEFAULT_X, DEFAULT_Y, DEFAULT_Z, true);
  solveIK(legLeft1, DEFAULT_X, DEFAULT_Y, DEFAULT_Z, true);
  solveIK(legLeft2, DEFAULT_X, DEFAULT_Y, DEFAULT_Z, true);
  solveIK(legLeft3, DEFAULT_X, DEFAULT_Y, DEFAULT_Z, true);
  
  gaitPhase = 0.0;
}

void moveLegInGait(Leg& leg, float velocityX, float velocityY, float phaseOffset)
{
  // Calculate the phase for this leg
  float legPhase = fmod(gaitPhase + phaseOffset, 1.0);
  
  float targetX, targetY, targetZ;
  
  // Tripod gait: first half of cycle = swing phase, second half = stance phase
  if (legPhase < 0.5) {
    // Swing phase - leg is in the air moving forward
    float swingProgress = legPhase * 2.0; // 0.0 to 1.0
    
    // Move from back to front during swing
    targetX = DEFAULT_X - (STEP_LENGTH * velocityX * (0.5 - swingProgress));
    targetY = DEFAULT_Y - (STEP_LENGTH * velocityY * (0.5 - swingProgress));
    
    // Lift leg during swing (parabolic arc)
    float lift = STEP_HEIGHT * sin(swingProgress * M_PI);
    targetZ = DEFAULT_Z - lift;
    
  } else {
    // Stance phase - leg is on ground pushing backward
    float stanceProgress = (legPhase - 0.5) * 2.0; // 0.0 to 1.0
    
    // Move from front to back during stance
    targetX = DEFAULT_X + (STEP_LENGTH * velocityX * (0.5 - stanceProgress));
    targetY = DEFAULT_Y + (STEP_LENGTH * velocityY * (0.5 - stanceProgress));
    targetZ = DEFAULT_Z; // Leg on ground
  }
  
  // Constrain positions to safe ranges
  targetX = constrain(targetX, 100.0f, 250.0f);
  targetY = constrain(targetY, -80.0f, 80.0f);
  targetZ = constrain(targetZ, 20.0f, 100.0f);
  
  solveIK(leg, targetX, targetY, targetZ, true);
}

void updateTripodGait(float velocityX, float velocityY)
{
  // Calculate speed based on velocity magnitude
  float speed = sqrt(velocityX * velocityX + velocityY * velocityY);
  
  // If speed is very low, just stand still
  if (speed < 0.1) {
    // Optional: gradually return to neutral stance
    return;
  }
  
  // Normalize velocities to -1.0 to 1.0 range
  float normVelX = constrain(velocityX / 7.0f, -1.0f, 1.0f);
  float normVelY = constrain(velocityY / 7.0f, -1.0f, 1.0f);
  
  // Update gait phase based on speed
  gaitPhase += GAIT_SPEED * speed;
  if (gaitPhase >= 1.0) {
    gaitPhase -= 1.0;
  }
  
  // Tripod A: Right front (R1), Left middle (L2), Right back (R3)
  // Move with phase offset 0.0
  moveLegInGait(legRight1, normVelX, normVelY, 0.0);
  moveLegInGait(legLeft2, normVelX, normVelY, 0.0);
  moveLegInGait(legRight3, normVelX, normVelY, 0.0);
  
  // Tripod B: Left front (L1), Right middle (R2), Left back (L3)
  // Move with phase offset 0.5 (opposite phase)
  moveLegInGait(legLeft1, normVelX, normVelY, 0.5);
  moveLegInGait(legRight2, normVelX, normVelY, 0.5);
  moveLegInGait(legLeft3, normVelX, normVelY, 0.5);
}
