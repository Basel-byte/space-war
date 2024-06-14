#include "Collisional.h"
#include "SpaceObject.h"

class CollisionManager
{
public:
    CollisionManager();
    void checkCollisions();
    void collide(Collisional* a, Collisional* b, CollisionType typeA, CollisionType typeB);
    void collidePlayer(Collisional* other, CollisionType type);
    void collideEnemy(Collisional* enemy, Collisional* other, CollisionType type);
    void collideMissile(Collisional* missile, Collisional* other, CollisionType type);
    void collideHealthPickable(Collisional* pickable, Collisional* other, CollisionType type);
    void collideMissilePickable(Collisional* pickable, Collisional* other, CollisionType type);
};

SpaceObject generateWeaponPickable(float x, float y, float z);
SpaceObject generateHealthPickable(float x, float y, float z);
void addRandomPickable(float x, float y, float z);