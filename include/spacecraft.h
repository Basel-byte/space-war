#pragma once

#include "Collisional.h"
#include "Model.h"

#define SPACECRAFT_COLLISION_RADIUS 0.5

class Spacecraft: public CollisionalSphere {
public:
    Model model;
    Spacecraft();
    void draw();
    // void drawCollisionMock();
    // bool checkCollision(Collisional another);
    void collide() override;
    void collideWith(Collisional* other, CollisionType type) override;
};