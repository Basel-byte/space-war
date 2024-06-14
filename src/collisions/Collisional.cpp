#include <math.h>
#include <random>
#include <string>
#include <algorithm>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Collisional.h"
#include "constants.h"

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
    return other->isCollidingWith(this);
}

void CollisionalSphere::drawCollisionMock() {
    if(!showCollisionMockups) return;
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

CollisionalBox::CollisionalBox(double width, double height, double depth, double ry) {
    colWidth = width;
    colHeight = height;
    colDepth = depth;
    colRotationY = ry;
}



bool CollisionalBox::isCollidingWith(CollisionalSphere* other) {
    // rotate the vertices of the current box
    float halfWidth = colWidth / 2.0f;
    float halfHeight = colHeight / 2.0f;
    float halfDepth = colDepth / 2.0f;

    float vertices[8][3] = {
        {-halfWidth, -halfHeight, -halfDepth},
        {halfWidth, -halfHeight, -halfDepth},
        {halfWidth, halfHeight, -halfDepth},
        {-halfWidth, halfHeight, -halfDepth},
        {-halfWidth, -halfHeight, halfDepth},
        {halfWidth, -halfHeight, halfDepth},
        {halfWidth, halfHeight, halfDepth},
        {-halfWidth, halfHeight, halfDepth}
    };

    for (int i = 0; i < 8; i++) {
        rotateY(vertices[i], colRotationY);
    }

    // Calculate min and max values for each axis
    float minX = vertices[0][0], minY = vertices[0][1], minZ = vertices[0][2];
    float maxX = vertices[0][0], maxY = vertices[0][1], maxZ = vertices[0][2];
    for (int i = 0; i < 8; i++) {
        if (vertices[i][0] < minX) minX = vertices[i][0];
        if (vertices[i][0] > maxX) maxX = vertices[i][0];
        if (vertices[i][1] < minY) minY = vertices[i][1];
        if (vertices[i][1] > maxY) maxY = vertices[i][1];
        if (vertices[i][2] < minZ) minZ = vertices[i][2];
        if (vertices[i][2] > maxZ) maxZ = vertices[i][2];
    }

    minX += colCenterX;
    maxX += colCenterX;
    minY += colCenterY;
    maxY += colCenterY;
    minZ += colCenterZ;
    maxZ += colCenterZ;

    float x = max(minX, min(maxX, other->getColCenterX()));
    float y = max(minY, min(maxY, other->getColCenterY()));
    float z = max(minZ, min(maxZ, other->getColCenterZ()));

    float distance = sqrt((x - other->getColCenterX()) * (x - other->getColCenterX()) +
                         (y - other->getColCenterY()) * (y - other->getColCenterY()) +
                         (z - other->getColCenterZ()) * (z - other->getColCenterZ()));

    return distance < other->getColRadius();
}

bool CollisionalBox::isCollidingWith(CollisionalBox* other) {
    // rotate the vertices of the current box
    float halfWidth = colWidth / 2.0f;
    float halfHeight = colHeight / 2.0f;
    float halfDepth = colDepth / 2.0f;

    float vertices[8][3] = {
        {-halfWidth, -halfHeight, -halfDepth},
        {halfWidth, -halfHeight, -halfDepth},
        {halfWidth, halfHeight, -halfDepth},
        {-halfWidth, halfHeight, -halfDepth},
        {-halfWidth, -halfHeight, halfDepth},
        {halfWidth, -halfHeight, halfDepth},
        {halfWidth, halfHeight, halfDepth},
        {-halfWidth, halfHeight, halfDepth}
    };

    for (int i = 0; i < 8; i++) {
        rotateY(vertices[i], colRotationY);
    }

    // rotate the vertices of the other box
    halfWidth = other->getColWidth() / 2.0f;
    halfHeight = other->getColHeight() / 2.0f;
    halfDepth = other->getColDepth() / 2.0f;
    float otherVertices[8][3] = {
        {-halfWidth, -halfHeight, -halfDepth},
        {halfWidth, -halfHeight, -halfDepth},
        {halfWidth, halfHeight, -halfDepth},
        {-halfWidth, halfHeight, -halfDepth},
        {-halfWidth, -halfHeight, halfDepth},
        {halfWidth, -halfHeight, halfDepth},
        {halfWidth, halfHeight, halfDepth},
        {-halfWidth, halfHeight, halfDepth}
    };

    for (int i = 0; i < 8; i++) {
        rotateY(otherVertices[i], other->getColRotationY());
    }

    // Calculate min and max values for each axis
    float minX = vertices[0][0], minY = vertices[0][1], minZ = vertices[0][2];
    float maxX = vertices[0][0], maxY = vertices[0][1], maxZ = vertices[0][2];
    for (int i = 0; i < 8; i++) {
        if (vertices[i][0] < minX) minX = vertices[i][0];
        if (vertices[i][0] > maxX) maxX = vertices[i][0];
        if (vertices[i][1] < minY) minY = vertices[i][1];
        if (vertices[i][1] > maxY) maxY = vertices[i][1];
        if (vertices[i][2] < minZ) minZ = vertices[i][2];
        if (vertices[i][2] > maxZ) maxZ = vertices[i][2];
    }

    float otherMinX = otherVertices[0][0], otherMinY = otherVertices[0][1], otherMinZ = otherVertices[0][2];
    float otherMaxX = otherVertices[0][0], otherMaxY = otherVertices[0][1], otherMaxZ = otherVertices[0][2];
    for (int i = 0; i < 8; i++) {
        if (otherVertices[i][0] < otherMinX) otherMinX = otherVertices[i][0];
        if (otherVertices[i][0] > otherMaxX) otherMaxX = otherVertices[i][0];
        if (otherVertices[i][1] < otherMinY) otherMinY = otherVertices[i][1];
        if (otherVertices[i][1] > otherMaxY) otherMaxY = otherVertices[i][1];
        if (otherVertices[i][2] < otherMinZ) otherMinZ = otherVertices[i][2];
        if (otherVertices[i][2] > otherMaxZ) otherMaxZ = otherVertices[i][2];
    }

    // Check if the boxes are overlapping
    return (minX + colCenterX <= otherMaxX + other->getColCenterX() &&
            maxX + colCenterX >= otherMinX + other->getColCenterX() &&
            minY + colCenterY <= otherMaxY + other->getColCenterY() &&
            maxY + colCenterY >= otherMinY + other->getColCenterY() &&
            minZ + colCenterZ <= otherMaxZ + other->getColCenterZ() &&
            maxZ + colCenterZ >= otherMinZ + other->getColCenterZ());
}

void CollisionalBox::drawCollisionMock() {
    if(!showCollisionMockups) return;
    // Calculate the half dimensions
    float halfWidth = colWidth / 2.0f;
    float halfHeight = colHeight / 2.0f;
    float halfDepth = colDepth / 2.0f;

    // Define the 8 vertices of the cuboid relative to the origin
    float vertices[8][3] = {
        {-halfWidth, -halfHeight, -halfDepth},
        {halfWidth, -halfHeight, -halfDepth},
        {halfWidth, halfHeight, -halfDepth},
        {-halfWidth, halfHeight, -halfDepth},
        {-halfWidth, -halfHeight, halfDepth},
        {halfWidth, -halfHeight, halfDepth},
        {halfWidth, halfHeight, halfDepth},
        {-halfWidth, halfHeight, halfDepth}
    };

    // Save the current matrix
    glPushMatrix();

    glLoadIdentity();

    // Translate to the center point
    glTranslatef(colCenterX, colCenterY, colCenterZ);
    glRotatef(colRotationY, 0.0, 1.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    
    // Set the line width
    glLineWidth(2.0f); // You can adjust the value to make the lines thicker or thinner

    // Draw the cuboid as a wireframe
    glBegin(GL_LINES);
    
    // Front face
    glVertex3fv(vertices[0]); glVertex3fv(vertices[1]);
    glVertex3fv(vertices[1]); glVertex3fv(vertices[2]);
    glVertex3fv(vertices[2]); glVertex3fv(vertices[3]);
    glVertex3fv(vertices[3]); glVertex3fv(vertices[0]);

    // Back face
    glVertex3fv(vertices[4]); glVertex3fv(vertices[5]);
    glVertex3fv(vertices[5]); glVertex3fv(vertices[6]);
    glVertex3fv(vertices[6]); glVertex3fv(vertices[7]);
    glVertex3fv(vertices[7]); glVertex3fv(vertices[4]);

    // Connect front and back faces
    glVertex3fv(vertices[0]); glVertex3fv(vertices[4]);
    glVertex3fv(vertices[1]); glVertex3fv(vertices[5]);
    glVertex3fv(vertices[2]); glVertex3fv(vertices[6]);
    glVertex3fv(vertices[3]); glVertex3fv(vertices[7]);

    glEnd();

    // Restore the original matrix
    glPopMatrix();
}

void rotateY(double vertex[3], double theta) {
    double x = vertex[0];
    double z = vertex[2];
    vertex[0] = x * cos(theta) + z * sin(theta);
    vertex[2] = -x * sin(theta) + z * cos(theta);
    // y-coordinate remains the same
}

void rotateY(float vertex[3], double theta) {
    float x = vertex[0];
    float z = vertex[2];
    vertex[0] = x * cos(theta) + z * sin(theta);
    vertex[2] = -x * sin(theta) + z * cos(theta);
    // y-coordinate remains the same
}

std::string generateRandomString() {
    auto randchar = []() -> char {
        const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(20, 0);
    std::generate_n(str.begin(), 20, randchar);
    return str;
}