#ifndef ANIMATION_H
#define ANIMATION_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>
#include "EnemyManager.h"
#include "Model.h"

extern SoundService soundService;
extern EnemyManager enemyManager;
extern MissileManager missileManager;

extern float planetRotations[];
extern float craftAngle;
extern float screenwidth;
extern float screenheight;

enum viewMode
{
    firstPersonView,
    thirdPersonView,
    topView
};

extern viewMode mode;

void timer(int value);
void spacecraftThirdPersonView();
void spacecraftFirstPersonView();
void spacecraftTopView();
void drawSmallPortSpaceCraft(float spaceCraftAngle, float xVal, float zVal);
void initAnimation(float width, float height);
void toggleViewMode();
#endif
