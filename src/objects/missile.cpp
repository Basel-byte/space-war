#include "missile.h"

float missileDepth = MISSILE_DEPTH;
float missileWidth = MISSILE_WIDTH;
float missileHeight = MISSILE_HEIGHT;
float missileShiftX = 0.0f, missileShiftY = 0.0f, missileShiftZ = 0.0f;

Missile::Missile(double rotationY) : CollisionalBox(missileWidth, missileHeight, missileDepth, rotationY){
    model.load("Models/missile/missile.obj");
}

Missile::Missile(float initialX, float initialZ, float initialrZ, double rotationY) : CollisionalBox(missileWidth, missileHeight, missileDepth, rotationY){
    model.load("Models/missile/missile.obj");
    model.tx = initialX;
    model.tz = initialZ;
    model.ry = initialrZ;
}

void Missile::draw() {
    model.draw();
    setCollisionCenterAsCurrent();
    colDepth = missileDepth;
    colWidth = missileWidth;
    colHeight = missileHeight;
    colCenterX += missileShiftX;
    colCenterY += missileShiftY;
    colCenterZ += missileShiftZ;
}

void Missile::collide() {
    std::cout << "Missile collided" << std::endl;
}

void Missile::collideWith(Collisional* another, CollisionType type){
    std::cout << "Missile collided with something" << std::endl;
}