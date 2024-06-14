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
        Enemy enemy;

        int randomIndex;
        int arrayLength = sizeof(enemiesPositions) / sizeof( enemiesPositions[0]);
        randomIndex = std::rand() % arrayLength;

        // enemyModel1.tx = enemiesPositions[randomIndex];
        enemy.model.tx = enemiesPositions[randomIndex];

        // Generate a random angle between 0 and 360 degrees
        float randomAngle = static_cast<float>(std::rand() % 360);
        cout << "Random: " << randomAngle << endl;
        enemy.model.ry = randomAngle;
        enemys.push_back(enemy);
    }
}

void EnemyManager::draw(){

    for (int i = 0; i < enemys.size(); ++i)
    {

        glPushMatrix();
        glRotatef(enemys[i].model.ry, 0.0, 1.0, 0.0); 
        glTranslatef(enemys[i].model.tx , 0.0f, 0.0f);
        glTranslatef(0.0f, -3.0f, 0.0f);
        glScalef(0.1f, 0.1f, 0.1f);
        enemys[i].draw();
        glPopMatrix();
        enemys[i].drawCollisionMock();
    }
}

void EnemyManager :: shootPlayer(MissileManager* missileManager, int playerPosX, int playerPosZ, EffectManager* effectManager){
    /*randomly choose an enemy every timer tick to shoot our player*/
    if(!missileManager->isAvailable()) return;
    int x = 0, z = 0;
    for(int i = 0; i < enemys.size(); i++){
        float enemyh = fabs(enemys[i].model.tx);
        float enemyAngle = getAngle(enemys[i].model.ry);
        float x = enemyh * cos(enemyAngle * M_PI / 180.0);
        float z = enemyh * sin(enemyAngle * M_PI / 180.0);
        int quad = getQuad(enemys[i].model.ry + 270);
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

void EnemyManager :: deleteEnemy(Enemy* enemy){
    for(auto it = enemys.begin(); it != enemys.end();){
        if(&(*it) == enemy){
            it = enemys.erase(it);
            break;
        }
        else it = ++it;
    }
}