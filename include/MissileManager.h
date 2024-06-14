#ifndef MISSILEMANAGAER_H
#define MISSILEMANAGER_H

#include <vector>
#include <iostream>
#include "Model.h"
#include "EffectManager.h"
#include "missile.h"

using namespace std;

// struct Missile{
//     // Model missileModel{0.05};
//     Model missileModel;
//     int speed;
//     int lifetime;
//     float transX;
//     float transZ;
//     bool isFromPlayer;
// };

class MissileManager{
private:
    int countOfEnemyMisslles = 0;

public:
    vector<Missile> missiles;
    void addMissile(float initialX, float initialZ, float angle, EffectManager* effectManager);
    void addMissile(float initialX, float initialZ, float destX, float destZ, EffectManager* effectManager);
    void updateMissles();
    void drawMissles();
    bool isAvailable();
};

#endif //MISSILEMANAGER_H