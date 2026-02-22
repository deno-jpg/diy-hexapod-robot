#ifndef GAIT_H
#define GAIT_H
#include "config.h"

void initializeGait();
void updateTripodGait(float velocityX, float velocityY);
void moveLegInGait(Leg& leg, float velocityX, float velocityY, float phaseOffset);

#endif