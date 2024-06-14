#include "Collisional.h"
#include "sound_service.h"
class CollisionManager
{
private:
    /* data */
    SoundService soundService;

public:
    CollisionManager(SoundService soundService);
    void checkCollisions();
    void collide(Collisional *a, Collisional *b, CollisionType typeA, CollisionType typeB);
    void collidePlayer(Collisional *other, CollisionType type);
    void collideEnemy(Collisional *enemy, Collisional *other, CollisionType type);
    void collideMissile(Collisional *missile, Collisional *other, CollisionType type);
};