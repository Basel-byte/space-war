#ifndef MISSILEMANAGAER_H
#define MISSILEMANAGER_H

#include <vector>
#include <iostream>
#include "../model-loader/Model.h"
#include "EffectManager.h"

using namespace std;

struct Missile{
    Model missileModel;
    int speed;
    int lifetime;
    float transX;
    float transZ;
    bool isFromPlayer;
};

class MissileManager{
private:
    vector<Missile> missiles;
    int countOfEnemyMisslles = 0;

public:

    void addMissile(float initialX, float initialZ, float angle, EffectManager* effectManager);
    void addMissile(float initialX, float initialZ, float destX, float destZ, EffectManager* effectManager);
    void updateMissles();
    void drawMissles();
    bool isAvailable();

};

#endif //MISSILEMANAGER_H