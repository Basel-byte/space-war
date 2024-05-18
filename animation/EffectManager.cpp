#include "EffectManager.h"
#include "visual-effects/ShootEffect.h"
#include "visual-effects/CollisionEffect.h"
#include "visual-effects/VisualEffect.h"

void EffectManager::addShootingEffect(float src_x, float src_y, float src_z, float dest_x, float dest_y, float dest_z) {
    effects.push_back(new ShootEffect(src_x, src_y, src_z, dest_x, dest_y, dest_z));
}

void EffectManager::addCollisionEffect(float at_x, float at_y, float at_z) {
    effects.push_back(new CollisionEffect(at_x, at_y, at_z));
}

void EffectManager::updateAndDrawEffects() {
    for (auto it = effects.begin(); it != effects.end();) {
        (*it)->updateFireballs();  
        (*it)->renderFireballs();  
        if (!((*it)->isAlive())) {
            delete *it;
            it = effects.erase(it);
        } 
        else ++it;
    }
}

int EffectManager :: getEffectCount(){
    return effects.size();
}