#pragma once

#include "Collisional.h"
#include "Model.h"

#define MISSILE_DEPTH 1.75f
#define MISSILE_WIDTH 5.15f
#define MISSILE_HEIGHT 2.1f

extern float missileDepth, missileWidth, missileHeight, missileShiftX, missileShiftY, missileShiftZ;

class Missile: public CollisionalBox {
public:
    Model model;
    int speed;
    int lifetime;
    float transX;
    float transZ;
    float rotationY;
    bool isFromPlayer;
    
    Missile(double rotationY);
    Missile(float initialX, float initialZ, float initialrZ, double rotationY);
    void draw();
    void collide() override;
    void collideWith(Collisional* other, CollisionType type) override;
};