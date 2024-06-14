#include "CollisionManager.h"
#include "constants.h"
#include "animation.h"
#include "spaceDrawer.h"

CollisionManager::CollisionManager(SoundService soundService)
{
    this->soundService = soundService;
}

void CollisionManager::checkCollisions()
{
    // make a list of all collisionals
    vector<CollisionalSphere *> collisionalSpheres;
    vector<CollisionType> collisionalTypes;
    vector<std::string> collisionalSphereNames;

    // add spacecraft to the list
    collisionalSpheres.push_back(&spacecraftobj);
    collisionalSphereNames.push_back("spacecraft");
    collisionalTypes.push_back(CollisionType::PLAYER);

    // add planets to the list
    for (auto planet : planets)
    {
        collisionalSpheres.push_back(planet);
        collisionalSphereNames.push_back(planet->getName());
        collisionalTypes.push_back(CollisionType::PLANET);
    }

    for (size_t i = 0; i < enemyManager.enemys.size(); ++i)
    {
        collisionalSpheres.push_back(&enemyManager.enemys[i]);
        collisionalSphereNames.push_back("enemy");
        collisionalTypes.push_back(CollisionType::ENEMY);
    }

    // iterate through all the collisionals and check for collisions
    for (int i = 0; i < collisionalSpheres.size(); i++)
    {
        auto collisional = collisionalSpheres[i];
        // cout << i << " " << collisional->id << " " << collisional << endl;
        for (int j = i + 1; j < collisionalSpheres.size(); j++)
        {
            // skip both enemies
            if (collisionalTypes[i] == CollisionType::ENEMY && collisionalTypes[j] == CollisionType::ENEMY)
            {
                continue;
            }
            auto anotherCollisional = collisionalSpheres[j];
            if (collisional->isCollidingWith(anotherCollisional))
            {
                cout << "Collision detected between " << collisionalSphereNames[i] << " and " << collisionalSphereNames[j] << endl;
                collide(collisional, anotherCollisional, collisionalTypes[i], collisionalTypes[j]);
                soundService.playSound("collision");
            }
        }
    }

    for (int i = 0; i < missileManager.missiles.size(); i++)
    {
        auto missile = &(missileManager.missiles[i]);
        // cout << "missile " << i << " " << missile->id << " " << missile << endl;
        for (int j = 0; j < collisionalSpheres.size(); j++)
        {
            // skip missile and enemy
            if (collisionalTypes[j] == CollisionType::ENEMY)
            {
                continue;
            }
            auto other = collisionalSpheres[j];
            // cout << "Checking collision between missile and " << collisionalSphereNames[j] << endl;
            if ((*missile).isCollidingWith(other))
            {
                cout << "Collision detected between missile and " << collisionalSphereNames[j] << endl;
                // cout << "Missile info: " <<  "x:" << missile.getColCenterX() << " y:" << missile.getColCenterY() << " z:" << missile.getColCenterZ() << endl;
                // cout << collisionalSphereNames[i] << " info: " <<  "x:" << other->getColCenterX() << " y:" << other->getColCenterY() << " z:" << other->getColCenterZ() << endl;
                collide(missile, other, CollisionType::MISSILE, collisionalTypes[j]);
            }
        }

        for (int j = i + 1; j < missileManager.missiles.size(); j++)
        {
            auto anotherMissile = &(missileManager.missiles[j]);
            // cout << "Checking collision between missiles" << endl;
            if ((*missile).isCollidingWith(anotherMissile))
            {
                cout << "Collision detected between missiles" << endl;
                // cout << "Missile 1 info: " <<  "x:" << missile.getColCenterX() << " y:" << missile.getColCenterY() << " z:" << missile.getColCenterZ() << endl;
                // cout << "Missile 2 info: " <<  "x:" << anotherMissile.getColCenterX() << " y:" << anotherMissile.getColCenterY() << " z:" << anotherMissile.getColCenterZ() << endl;
                collide(missile, anotherMissile, CollisionType::MISSILE, CollisionType::MISSILE);
            }
        }
    }
}

void CollisionManager::collide(Collisional *a, Collisional *b, CollisionType typeA, CollisionType typeB)
{
    if (typeA == CollisionType::PLAYER)
    {
        collidePlayer(b, typeB);
    }
    else if (typeA == CollisionType::ENEMY)
    {
        collideEnemy(a, b, typeB);
    }
    else if (typeA == CollisionType::MISSILE)
    {
        collideMissile(a, b, typeB);
    }

    if (typeB == CollisionType::PLAYER)
    {
        collidePlayer(a, typeA);
    }
    else if (typeB == CollisionType::ENEMY)
    {
        collideEnemy(b, a, typeA);
    }
    else if (typeB == CollisionType::MISSILE)
    {
        collideMissile(b, a, typeA);
    }

    a->isCollided = true;
    b->isCollided = true;
}

void CollisionManager::collidePlayer(Collisional *other, CollisionType type)
{
    if (type == CollisionType::PLANET)
    {
        // decrease health by 100;
        xVal -= 10.0;
    }
    else if (type == CollisionType::ENEMY)
    {
        // decrease health by 100;
    }
    else if (type == CollisionType::MISSILE)
    {
        // decrease health by 100;
    }
}

void CollisionManager::collideEnemy(Collisional *enemy, Collisional *other, CollisionType type)
{
    cout << "Adding collision effect" << endl;
    effectManager.addCollisionEffect(enemy->getColCenterX(), enemy->getColCenterY(), enemy->getColCenterZ());
    soundService.playSound("explosion");
}

void CollisionManager::collideMissile(Collisional *missile, Collisional *other, CollisionType type)
{
    cout << "Adding collision effect" << endl;
    effectManager.addCollisionEffect(missile->getColCenterX(), missile->getColCenterY(), missile->getColCenterZ());
}
