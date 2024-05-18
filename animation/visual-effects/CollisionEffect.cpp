#include "CollisionEffect.h"
#include <algorithm>
#include <iostream>

CollisionEffect :: CollisionEffect(float x, float y, float z) {
    fireTexture = SOIL_load_OGL_texture("animation/visual-effects/assets/flame.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    smokeTexture = SOIL_load_OGL_texture("animation/visual-effects/assets/smoke.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    for (int i = 0; i < NUM_FIREBALLS; ++i) {
        Fireball fb;
        fb.x = x; fb.y = y; fb.z = z;  // Start at the explosion center
        fb.vx = ((float)rand() / RAND_MAX - 0.5f) * EXPLOSION_SPEED;
        fb.vy = ((float)rand() / RAND_MAX - 0.5f) * EXPLOSION_SPEED;
        fb.vz = ((float)rand() / RAND_MAX - 0.5f) * EXPLOSION_SPEED;
        fb.scale = FIREBALL_SCALE;
        fb.life = FIREBALL_LIFETIME;
        fireballs.push_back(fb);
    }
}

void CollisionEffect::updateFireballs() {
    float deltaTime = 0.05f;
    for (auto& fb : fireballs) {
        fb.x += fb.vx * deltaTime;
        fb.y += fb.vy * deltaTime;
        fb.z += fb.vz * deltaTime;
        fb.scale += deltaTime * 0.03f;  // Gradually increase size
        fb.life -= deltaTime;
    }
    fireballs.erase(std::remove_if(fireballs.begin(), fireballs.end(), [](const Fireball& fb) {
        return fb.life <= 0.0f;
    }), fireballs.end());
}

void CollisionEffect::renderFireballs() {
    for (const auto& fb : fireballs) {
        if (fb.life <= 1.0f) {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBindTexture(GL_TEXTURE_2D, smokeTexture);
            glColor4f(1.0f, 1.0f, 1.0f, 0.7f);  // Make smoke semi-transparent
        } else {
            glBindTexture(GL_TEXTURE_2D, fireTexture);
            glColor3f(1.0f, 1.0f, 1.0f);
        }

        glEnable(GL_TEXTURE_2D);

        glPushMatrix();
        glTranslatef(fb.x, fb.y, fb.z);
        GLUquadric* quad = gluNewQuadric();
        gluQuadricTexture(quad, GL_TRUE);
        gluSphere(quad, fb.scale, 30, 30);
        gluDeleteQuadric(quad);
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);

        if (fb.life <= 1.0f) glDisable(GL_BLEND);
    }
}

bool CollisionEffect::isAlive() {return !fireballs.empty();}