#include "MissileManager.h"

#include <cmath>

const int initialSpeed = 1;
const int fullLife = 100;
const int acceleration = 1; // was 2
const int missileClock = 1;

void MissileManager :: addMissile(float initialX, float initialZ, float angle, EffectManager* effectManager){
    Model model;
    model.load("Models/missile/missile.obj");
    
    model.tx = initialX;
    model.tz = initialZ;
    model.ry = angle;

    Missile missile = Missile(angle);

    // Remember: add the simple model here;
    missile.model = model;

    missile.lifetime = fullLife;
    missile.speed = initialSpeed; // this will be incremented to get the current position.
    missile.isFromPlayer = true;
    missile.rotationY = angle;
    missiles.push_back(missile);

    effectManager->addShootingEffect(initialX - 3 * sin((M_PI / 180.0) * angle), 0,
                                    initialZ - 3 * cos((M_PI / 180.0) * angle),
                                    initialX - 2 * sin((M_PI / 180.0) * angle), 0,
                                    initialZ - 2 * cos((M_PI / 180.0) * angle));
    //  effectManager->addCollisionEffect(initialX - 3 * sin((M_PI / 180.0) * angle), 0,
    //                                 initialZ - 3 * cos((M_PI / 180.0) * angle));
}

void MissileManager :: addMissile(float initialX, float initialZ, float destX, float destZ, EffectManager* effectManager){
    Model model;
    model.load("Models/missile/missile.obj");
    
    model.tx = initialX;
    model.tz = initialZ;

    float angle = atan(((float)(destX - initialX)) / ((float)(destZ - initialZ))) * 180 / M_PI;
    model.ry = destZ - initialZ >= 0? 180 + angle : angle;
    Missile missile = Missile(angle);


    //Remember: add the simple model here;
    missile.model = model;

    missile.lifetime = fullLife;
    missile.speed = initialSpeed; // this will be incremented to get the current position.
    missile.transX = destX - initialX;
    missile.transZ = destZ - initialZ;
    missile.rotationY = model.ry;
    float magnitude = sqrt(missile.transX * missile.transX + missile.transZ * missile.transZ);
    missile.transX /= magnitude;
    missile.transZ /= magnitude;
    missile.isFromPlayer = false;
    missiles.push_back(missile);
    countOfEnemyMisslles++;

    effectManager->addShootingEffect(initialX, 0, initialZ, destX, 0, destZ);
}

void MissileManager :: updateMissles(){
    for (auto it = missiles.begin(); it != missiles.end();){
        it->speed += acceleration;
        it->lifetime -= missileClock;
        // bool isCollided = it->model.checkCollision() /// uncomment this
        // bool isCollided = false;
        if(it->isCollided || it->lifetime == 0) {
            cout << "Deleting missile" << endl;
            if(it->isFromPlayer == false) countOfEnemyMisslles--;
            it = missiles.erase(it);
        }
        else it = ++it;
    }
    // cout << "Size: "<< missiles.size() << endl;
}

void MissileManager :: drawMissles() {
    for(auto& missile : missiles){
        glPushMatrix();
        if(missile.isFromPlayer){
            // missile.obj
            glTranslatef(missile.model.tx - missile.speed * sin(missile.model.ry * M_PI / 180.0), 
                        0, missile.model.tz - missile.speed * cos(missile.model.ry * M_PI / 180.0));
            glRotatef(missile.model.ry, 0, 1, 0);
            missile.draw();
        }
        else{
            glTranslatef(missile.model.tx + missile.speed * missile.transX, 0, 
                         missile.model.tz + missile.speed * missile.transZ);
            glRotatef(missile.model.ry, 0, 1, 0);
            missile.draw();
        }
        // missile.model.setCollisionCenterAsCurrent();
        glPopMatrix();
        missile.drawCollisionMock();

        // rocket.obj
        // glTranslatef(x, 0, z);
        // glRotatef(-90, 1, 0, 0);
        // glRotatef(a, 0, 0, 1);
        // glScalef(0.02f, 0.02f, 0.02f);
        // glTranslatef(1 * sin(a), 100, 1 * cos(a));
    }
}

bool MissileManager :: isAvailable() { return countOfEnemyMisslles < 1;}