#ifndef COLLISIONEFFECT_H
#define COLLISIONEFFECT_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>

#include "VisualEffect.h"
#include <vector>

using namespace std;


struct Fireball {
    float x, y, z;
    float vx, vy, vz;
    float scale;
    float life;
};

class CollisionEffect : public VisualEffect{
private:
    int NUM_FIREBALLS = 20;
    float EXPLOSION_SPEED = 0.15f;
    float FIREBALL_LIFETIME = 5.0f;
    float FIREBALL_SCALE = 0.2f;
    
    vector<Fireball> fireballs;
    GLuint fireTexture;
    GLuint smokeTexture;

public:
    CollisionEffect(float loc_x, float loc_y, float loc_z);
    void updateFireballs() override;
    void renderFireballs() override;
    bool isAlive() override;
};

#endif // COLLISIONEFFECT_H