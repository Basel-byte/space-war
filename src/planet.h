//
// Created by Amr Magdy on 5/8/2023.
//

#ifndef COSMICSPHERE_H
#define COSMICSPHERE_H

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut_std.h>
#include <SOIL/SOIL.h>
using namespace std;

// SpaceObject class.
class SpaceObject
{
public:
    SpaceObject();

    SpaceObject(std::string planetId, float x, float y, float z, float r, float a, unsigned int colorR,
                unsigned int colorG, unsigned int colorB, GLuint textureID);

    float getCenterX() { return centerX; }

    float getCenterY() { return centerY; }

    float getCenterZ() { return centerZ; }

    float getRadius() { return radius; }

    float getAngle() { return angle; }

    void draw();

    void drawSubRoutine();

    void setAngle(float angle);

    void setCurrentX(float x);

    void setCurrentY(float y);

    void setCurrentZ(float z);

    float getCurrentX() const;

    float getCurrentY() const;

    float getCurrentZ() const;

private:
    std::string id;
    float centerX, centerY, centerZ, currentX, currentY, currentZ, radius, angle;
    unsigned char color[3];
    GLuint textureID;
};
#endif // COSMICSPHERE_H
