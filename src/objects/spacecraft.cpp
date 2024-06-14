#include "spacecraft.h"

Spacecraft::Spacecraft() {
    model.load("Models/shuttle/shuttle.obj");
    colRadius = SPACECRAFT_COLLISION_RADIUS;
}

void Spacecraft::draw() {
    model.draw();
    setCollisionCenterAsCurrent();
}

void Spacecraft::collide() {
    std::cout << "Spacecraft collided" << std::endl;
}

void Spacecraft::collideWith(Collisional* another, CollisionType type) {
    std::cout << "Spacecraft collided with something" << std::endl;
}