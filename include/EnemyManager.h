#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "MissileManager.h"
#include "EffectManager.h"
#include "enemy.h"

using namespace std;

class EnemyManager {
public:
    EnemyManager(); 
    ~EnemyManager();  

    void init(int numOfEnemies);
    void draw();
    float getAngle(float angle);
    int getQuad(float angle);

public:
    float maxMove = 300.0f; 
    float speed = 1.0f;      
    bool forward = true;  
    int moveCounter = 0;  

    std::vector<Enemy> enemys;  
    std::vector<float> shuttlePositions;
    void shootPlayer(MissileManager* missileManager, int playerPosX, int playerPosZ, EffectManager* effectManager);
};

#endif
