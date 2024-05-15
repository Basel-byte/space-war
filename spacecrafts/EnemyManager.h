#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <vector>
#include <cstdlib>
#include <ctime>

#include "../model-loader/Model.h"  

class EnemyManager {
public:
    EnemyManager(); 
    ~EnemyManager();  

    void init(int numOfEnemies);  
    void draw();  

public:
    float maxMove = 300.0f; 
    float speed = 1.0f;      
    bool forward = true;  
    int moveCounter = 0;  

    std::vector<Model> enemyModels;  
    std::vector<float> shuttlePositions;
};

#endif
