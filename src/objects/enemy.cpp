#include "enemy.h"

Enemy::Enemy() {
    model.load("Models/flying-saucer/Low_poly_UFO.obj");
    model.pos_x = 0.0f;
    model.pos_y = 0.0f;
    model.pos_z = 0.0f;
    model.tx = 0.0f;
    model.ty = 0.0f;
    model.tz = 0.0f;
    model.rx = 0.0f;
    model.ry = 0.0f;
    model.rz = 0.0f;
    colRadius = ENEMY_COLLISION_RADIUS;
}

void Enemy::draw() {
    model.draw();
    setCollisionCenterAsCurrent();
    colCenterY += 2.0;
}

void Enemy::collide() {
    std::cout << "Enemy collided" << std::endl;
}

void Enemy::collideWith(Collisional* another, CollisionType type) {
    std::cout << "Enemy collided with something" << std::endl;
}