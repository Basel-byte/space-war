#include "EnemyManager.h"

#include <cstdlib>
#include <ctime>
#include <cmath>



EnemyManager::EnemyManager()
{
    std::srand(std::time(nullptr));
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::init(int numOfEnemies)
{
    float enemiesPositions[] = {-90, -120, -140, -180, -250, -300, -360, -410};
    for (int i = 0; i < numOfEnemies; i++)
    {
        Model enemyModel1;
        enemyModel1.load("../Models/flying-saucer/Low_poly_UFO.obj");

        int randomIndex;
        int arrayLength = sizeof(enemiesPositions) / sizeof( enemiesPositions[0]);
        randomIndex = std::rand() % arrayLength;

        enemyModel1.tx = enemiesPositions[randomIndex];

        // Generate a random angle between 0 and 360 degrees
        float randomAngle = static_cast<float>(std::rand() % 360);
        enemyModel1.ry = randomAngle;
        enemyModels.push_back(enemyModel1);
    }
}

void EnemyManager::draw()
{

    for (int i = 0; i < enemyModels.size(); ++i)
    {

        glPushMatrix();
        glRotatef(enemyModels[i].ry, 0.0, 1.0, 0.0); 
        glTranslatef(enemyModels[i].tx , 0.0f, 0.0f);
        glTranslatef(0.0f, -3.0f, 0.0f);
        glScalef(0.1f, 0.1f, 0.1f);
        enemyModels[i].draw();
        glTranslatef(0.0, 1.0, 0.0);
        // draw health bar
        glPopMatrix();
    }
}
