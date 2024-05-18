#ifndef ANIMATION_H
#define ANIMATION_H

#include <GL/glut.h>
#include <vector>
#include "EnemyManager.h"
#include "../model-loader/Model.h"

extern Model spacecraftobj;
extern EnemyManager enemyManager;
extern MissileManager missileManager;

extern float planetRotations[];
extern float craftAngle;
extern float screenwidth;
extern float screenheight;

enum viewMode {
    firstPersonView,
    thirdPersonView
};
extern viewMode mode;

void timer(int value);
void spacecraftThirdPersonView();
void spacecraftFirstPersonView();
void drawSmallPortSpaceCraft(float spaceCraftAngle, float xVal, float zVal);
void initAnimation(float width, float height);
void toggleViewMode();
#endif 
