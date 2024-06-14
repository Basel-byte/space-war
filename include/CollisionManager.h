#include "Collisional.h"

class CollisionManager
{
public:
    CollisionManager();
    void checkCollisions();
    void collide(Collisional* a, Collisional* b, CollisionType typeA, CollisionType typeB);
    void collidePlayer(Collisional* other, CollisionType type);
    void collideEnemy(Collisional* enemy, Collisional* other, CollisionType type);
    void collideMissile(Collisional* missile, Collisional* other, CollisionType type);
};