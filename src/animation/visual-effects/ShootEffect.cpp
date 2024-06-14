#include "ShootEffect.h"
#include <cmath>
#include <GL/glew.h>
#include <GL/freeglut.h>

ShootEffect :: ShootEffect(float x_src, float y_src, float z_src, float x_dest, float y_dest, float z_dest){
    // Calculate the direction vector from source to destination
    float dx = x_dest - x_src;
    float dy = y_dest - y_src;
    float dz = z_dest - z_src;

    // Normalize the direction vector
    float length = sqrt(dx * dx + dy * dy + dz * dz);
    dx /= length; dy /= length; dz /= length;

    for (int i = 0; i < MAX_PARTICLES; ++i){
        Particle p;
        p.x = x_src; p.y = y_src; p.z = z_src; // Particle initial position
        float speed = static_cast<float>(rand()) / RAND_MAX * 0.01f; // particle random speed

        float theta = static_cast<float>(rand()) / RAND_MAX * 2.0f * 3.14159265359f; // Random angle in [0, 2pi]
        float phi = (static_cast<float>(rand()) / RAND_MAX * (CONE_ANGLE * 3.14159265359f / 180.0f)) - (CONE_ANGLE * 3.14159265359f / 360.0f); // Random angle in [-CONE_ANGLE/2, CONE_ANGLE/2]

        float vx = cos(theta) * sin(phi);
        float vy = sin(theta) * sin(phi);
        float vz = cos(phi);

        // Rotate the vector (vx, vy, vz) to align with the direction vector (dx, dy, dz)
        float dot = vx * dx + vy * dy + vz * dz;
        float crossX = vy * dz - vz * dy;
        float crossY = vz * dx - vx * dz;
        float crossZ = vx * dy - vy * dx;

        p.vx = speed * (vx * dx + crossX * 1.0f + dot * (1.0f - cos(phi)));
        p.vy = speed * (vy * dy + crossY * 1.0f + dot * (1.0f - cos(phi)));
        p.vz = speed * (vz * dz + crossZ * 1.0f + dot * (1.0f - cos(phi)));

        p.r = static_cast<float>(rand()) / RAND_MAX;
        p.lifetime = INITIAL_LIFETIME;

        particles.push_back(p);
    }
}

void ShootEffect :: updateFireballs(){
    for (auto it = particles.begin(); it != particles.end();) {
        it->x += it->vx;
        it->y += it->vy;
        it->z += it->vz;

        it->lifetime -= 0.02f;

        if (it->lifetime <= 0.0f) it = particles.erase(it);
        else ++it;
    }
}

void ShootEffect :: renderFireballs(){
    glEnable(GL_POINT_SMOOTH);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    for (const auto& p : particles) {
        // glColor4f(p.r, 0, 0, 1);
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();
}

bool ShootEffect :: isAlive(){return !particles.empty();}
