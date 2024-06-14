#ifndef MISSILEMANAGAER_H
#define MISSILEMANAGER_H

#include <vector>
#include <iostream>
#include "Model.h"
#include "EffectManager.h"
#include "missile.h"
#include "sound_service.h"
using namespace std;

class MissileManager
{
private:
    int countOfEnemyMisslles = 0;
    SoundService soundService;

public:
    MissileManager(SoundService soundService);
    vector<Missile> missiles;
    void addMissile(float initialX, float initialZ, float angle, EffectManager *effectManager);
    void addMissile(float initialX, float initialZ, float destX, float destZ, EffectManager *effectManager);
    void updateMissles();
    void drawMissles();
    bool isAvailable();
};

#endif // MISSILEMANAGER_H