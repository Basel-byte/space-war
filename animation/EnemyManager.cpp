#include "EnemyManager.h"

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>



EnemyManager::EnemyManager()
{
    std::srand(std::time(nullptr));
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::init(int numOfEnemies)
{
    // float enemiesPositions[] = {-90, -120, -140, -180, -250, -300, -360, -410};
    float enemiesPositions[] = {-90, -120, -140, -180};
    for (int i = 0; i < numOfEnemies; i++)
    {
        Model enemyModel1(0.5);
        enemyModel1.load("Models/flying-saucer/Low_poly_UFO.obj");

        int randomIndex;
        int arrayLength = sizeof(enemiesPositions) / sizeof( enemiesPositions[0]);
        randomIndex = std::rand() % arrayLength;

        // enemyModel1.tx = enemiesPositions[randomIndex];
        enemyModel1.tx = enemiesPositions[randomIndex];

        // Generate a random angle between 0 and 360 degrees
        float randomAngle = static_cast<float>(std::rand() % 360);
        cout << "Random: " << randomAngle << endl;
        enemyModel1.ry = randomAngle;
        enemyModels.push_back(enemyModel1);
    }
}

void EnemyManager::draw(){

    for (int i = 0; i < enemyModels.size(); ++i)
    {

        glPushMatrix();
        glRotatef(enemyModels[i].ry, 0.0, 1.0, 0.0); 
        glTranslatef(enemyModels[i].tx , 0.0f, 0.0f);
        glTranslatef(0.0f, -3.0f, 0.0f);
        glScalef(0.1f, 0.1f, 0.1f);
        enemyModels[i].draw();
        enemyModels[i].setCollisionCenterAsCurrent();
        glPopMatrix();
        enemyModels[i].drawCollisionMock();
    }
}

void EnemyManager :: shootPlayer(MissileManager* missileManager, int playerPosX, int playerPosZ, EffectManager* effectManager){
    /*randomly choose an enemy every timer tick to shoot our player*/
    if(!missileManager->isAvailable()) return;
    int x = 0, z = 0;
    for(int i = 0; i < enemyModels.size(); i++){
        float enemyh = fabs(enemyModels[i].tx);
        float enemyAngle = getAngle(enemyModels[i].ry);
        float x = enemyh * cos(enemyAngle * M_PI / 180.0);
        float z = enemyh * sin(enemyAngle * M_PI / 180.0);
        int quad = getQuad(enemyModels[i].ry + 270);
        if(quad == 3 || quad == 4) x = -x;
        if(quad == 2 || quad == 3) z = -z;
        if(fabs(x - playerPosX) + fabs(z - playerPosZ) < 50)
            missileManager->addMissile(x, z, playerPosX, playerPosZ, effectManager);
    }
}

float EnemyManager :: getAngle(float angle){
    while(angle > 90){
        if(angle >= 180) angle -= 180;
        else angle = 180 - angle;
    }
    return angle;
}

int EnemyManager :: getQuad(float angle){
    angle = (angle > 360)? angle - 360 : angle;
    if(angle <= 90) return 1;
    if(angle <= 180) return 2;
    if(angle <= 270) return 3;
    return 4;
}
