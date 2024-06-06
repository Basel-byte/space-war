#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Collisional.h"

void Collisional::setCollisionCenterAsCurrent() {
    // Get current position of the object from the modelview matrix
    GLfloat modelView[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, modelView);
    colCenterX = modelView[12];
    colCenterY = modelView[13];
    colCenterZ = modelView[14];
}

bool Collisional::isCollidingWith(Collisional* other) {
    if (CollisionalSphere* sphere = dynamic_cast<CollisionalSphere*>(other)) {
        return isCollidingWith(sphere);
    } else if (CollisionalBox* box = dynamic_cast<CollisionalBox*>(other)) {
        return isCollidingWith(box);
    } else {
        return false;
    }
}

bool CollisionalSphere::isCollidingWith(CollisionalSphere* other) {
    // Check if the distance between the two spheres is less than the sum of their radii
    float dx = colCenterX - other->colCenterX;
    float dy = colCenterY - other->colCenterY;
    float dz = colCenterZ - other->colCenterZ;
    float distance = sqrt(dx * dx + dy * dy + dz * dz);
    return distance < colRadius + other->colRadius;
}

bool CollisionalSphere::isCollidingWith(CollisionalBox* other) {
    // Check if the sphere is inside the box
    float dx = colCenterX - other->getColCenterX() - other->getColWidth() / 2;
    float dy = colCenterY - other->getColCenterY() - other->getColHeight() / 2;
    float dz = colCenterZ - other->getColCenterZ() - other->getColDepth() / 2;
    float distance = sqrt(dx * dx + dy * dy + dz * dz);
    return distance < colRadius;
}

void CollisionalSphere::drawCollisionMock() {
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(colCenterX, colCenterY, colCenterZ);
    glColor3f(1.0, 0.0, 0.0);
    glutWireSphere(colRadius, 20, 20);
    glPopMatrix();
    glDisable(GL_BLEND);
}

// bool Box::isCollidingWith(Collisional* other) {
//     if (Sphere* sphere = dynamic_cast<Sphere*>(other)) {
//         return isCollidingWith(sphere);
//     } else if (Box* box = dynamic_cast<Box*>(other)) {
//         return isCollidingWith(box);
//     } else {
//         return false;
//     }
// }

bool CollisionalBox::isCollidingWith(CollisionalSphere* other) {
    // Check if the sphere is inside the box
    float dx = other->getColCenterX() - colCenterX - colWidth / 2;
    float dy = other->getColCenterY() - colCenterY - colHeight / 2;
    float dz = other->getColCenterZ() - colCenterZ - colDepth / 2;
    float distance = sqrt(dx * dx + dy * dy + dz * dz);
    return distance < other->getColRadius();
}

bool CollisionalBox::isCollidingWith(CollisionalBox* other) {
    // Check if the boxes are overlapping
    float dx = colCenterX - other->colCenterX;
    float dy = colCenterY - other->colCenterY;
    float dz = colCenterZ - other->colCenterZ;
    float distanceX = fabs(dx) - (colWidth + other->colWidth) / 2;
    float distanceY = fabs(dy) - (colHeight + other->colHeight) / 2;
    float distanceZ = fabs(dz) - (colDepth + other->colDepth) / 2;
    return distanceX <= 0 && distanceY <= 0 && distanceZ <= 0;
}

void CollisionalBox::drawCollisionMock() {
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(colCenterX, colCenterY, colCenterZ);
    glColor3f(0.0, 1.0, 0.0);
    // draw using vertices
    double halfW = colWidth / 2.0;
    double halfH = colHeight / 2.0;
    double halfD = colDepth / 2.0;
    
    // Define the vertices
    double vertices[8][3] = {
        {-halfW, -halfH, -halfD}, // v0
        {halfW, -halfH, -halfD}, // v1
        {halfW, halfH, -halfD}, // v2
        {-halfW, halfH, -halfD}, // v3
        {-halfW, -halfH, halfD}, // v4
        {halfW, -halfH, halfD}, // v5
        {halfW, halfH, halfD}, // v6
        {-halfW, halfH, halfD}  // v7
    };

    // Define the edges
    GLubyte indices[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Bottom edges
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // Top edges
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // Side edges
    };

    // Draw edges using GL_LINES
    glBegin(GL_LINES);
    for (int i = 0; i < 12; ++i) {
        glVertex3dv(vertices[indices[i][0]]);
        glVertex3dv(vertices[indices[i][1]]);
    }
    glEnd();
    glPopMatrix();
    glDisable(GL_BLEND);
}