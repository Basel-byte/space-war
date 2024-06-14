#pragma once

#include <cmath>

#include <SOIL/SOIL.h>
#include "SpaceObject.h"
#include "Model.h"
#include "animation.h"
#include "EffectManager.h"
#include "constants.h"

extern int width, height;
extern int selected;
// Globals.
extern float xAngle, yAngle, zAngle; // Angles to rotate scene.

extern float spaceCraftAngle;     // Angle of the spacecraft.
extern float xVal, zVal; // Co-ordinates of the spacecraft.
extern float earthRadius;

extern std::string planetNames[numberOfPlanets];
extern unsigned int spacecraft; // Display lists base index.

// Radius of the asteroids.
extern float planetsRadius[numberOfPlanets];

extern float planetsPositions[numberOfPlanets];
extern bool isStarted;
extern GLuint skyboxTextureID; // Texture IDs for each face of the skybox
extern EffectManager effectManager;

void addMissile();

void loadSkyboxTextures();

void drawSkybox();

// Set up camera for third-person view
void setCamera();

void drawSpace();