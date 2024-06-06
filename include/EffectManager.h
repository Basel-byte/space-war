#ifndef EFFECTMANAGER_H
#define EFFECTMANAGER_H

#include <iostream>
#include <vector>

#include "VisualEffect.h"
using namespace std;

class EffectManager{
private:
    vector<VisualEffect*> effects;

public:
    void addShootingEffect(float src_x, float src_y, float src_z, float dest_x, float dest_y, float dest_z);
    void addCollisionEffect(float at_x, float at_y, float at_z);
    void updateAndDrawEffects();
    int getEffectCount();
};
#endif // EFFECTMANAGER_H