#ifndef PLAYER_HEALTH_BAR
#define PLAYER_HEALTH_BAR

#include "HealthBar.h"

HealthBar playerHealthBar;

void startBarDecay(int time)
{
    playerHealthBar.changeHealth(time);
    glutTimerFunc(time, startBarDecay, time);
}

void startBarDecay() {
    glutTimerFunc(playerHealthBar.reRenderTime, startBarDecay, playerHealthBar.reRenderTime);
}

#endif