#ifndef ANIMATION_H
#define ANIMATION_H

#include <GL/glut.h>
#include <vector>
#include "EnemyManager.h"
#include "../model-loader/Model.h"

extern Model spacecraftobj;
extern EnemyManager enemyManager;
extern float planetRotations[];
extern float craftAngle;
extern float screenwidth;
extern float screenheight;

void timer(int value);
void spacecraftFirstPersonView();
void drawSmallPortSpaceCraft(float spaceCraftAngle, float xVal, float zVal);
void initAnimation(float width, float height);
#endif 
