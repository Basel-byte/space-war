#ifndef SHOOTEFFECT_H
#define SHOOTEFFECT_H

#include <vector>
#include <iostream>
#include "VisualEffect.h"

using namespace std;

struct Particle {
    float x, y, z; // Position
    float vx, vy, vz; // Velocity
    float r; // Color
    float lifetime; // Lifetime
};

class ShootEffect : public VisualEffect{
private:
    vector<Particle> particles;
    int MAX_PARTICLES = 50;
    float INITIAL_LIFETIME = 3.0f;
    float CONE_ANGLE = 100.0f;

public:
    ShootEffect(float x_src, float y_src, float z_src, float x_dest, float y_dest, float z_dest);
    void updateFireballs() override;
    void renderFireballs() override;
    bool isAlive() override;
};

#endif // SHOOTEFFECT_H