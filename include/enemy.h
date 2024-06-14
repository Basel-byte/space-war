#pragma once

#include "Collisional.h"
#include "Model.h"

#define ENEMY_COLLISION_RADIUS 3.2

class Enemy: public CollisionalSphere {
public:
    Model model;
    Enemy();
    void draw();
    void collide() override;
    void collideWith(Collisional* other, CollisionType type) override;
};