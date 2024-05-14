# include <math.h>

#include "Collisional.h"

bool Sphere::isCollidingWith(Collisional* other) {
    if (Sphere* sphere = dynamic_cast<Sphere*>(other)) {
        return isCollidingWith(sphere);
    } else if (Box* box = dynamic_cast<Box*>(other)) {
        return isCollidingWith(box);
    } else {
        return false;
    }
}

bool Sphere::isCollidingWith(Sphere* other) {
    // Check if the distance between the two spheres is less than the sum of their radii
    float dx = centerX - other->centerX;
    float dy = centerY - other->centerY;
    float dz = centerZ - other->centerZ;
    float distance = sqrt(dx * dx + dy * dy + dz * dz);
    return distance < radius + other->radius;
}

bool Sphere::isCollidingWith(Box* other) {
    // Check if the sphere is inside the box
    float dx = centerX - other->centerX - other->width / 2;
    float dy = centerY - other->centerY - other->height / 2;
    float dz = centerZ - other->centerZ - other->depth / 2;
    float distance = sqrt(dx * dx + dy * dy + dz * dz);
    return distance < radius;
}

bool Box::isCollidingWith(Collisional* other) {
    if (Sphere* sphere = dynamic_cast<Sphere*>(other)) {
        return isCollidingWith(sphere);
    } else if (Box* box = dynamic_cast<Box*>(other)) {
        return isCollidingWith(box);
    } else {
        return false;
    }
}

bool Box::isCollidingWith(Sphere* other) {
    // Check if the sphere is inside the box
    float dx = other->centerX - centerX - width / 2;
    float dy = other->centerY - centerY - height / 2;
    float dz = other->centerZ - centerZ - depth / 2;
    float distance = sqrt(dx * dx + dy * dy + dz * dz);
    return distance < other->radius;
}

bool Box::isCollidingWith(Box* other) {
    // Check if the boxes are overlapping
    float dx = centerX - other->centerX;
    float dy = centerY - other->centerY;
    float dz = centerZ - other->centerZ;
    float distanceX = fabs(dx) - (width + other->width) / 2;
    float distanceY = fabs(dy) - (height + other->height) / 2;
    float distanceZ = fabs(dz) - (depth + other->depth) / 2;
    return distanceX <= 0 && distanceY <= 0 && distanceZ <= 0;
}