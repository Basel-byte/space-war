
#ifndef SPACEOBJECT_H
#define SPACEOBJECT_H

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut_std.h>
#include <SOIL/SOIL.h>
#include "Collisional.h"
#define numberOfPlanets 9 // Number of rows of asteroids.
using namespace std;

// SpaceObject class.
class SpaceObject: public CollisionalSphere
{
public:
    SpaceObject();

    SpaceObject(std::string name, float x, float y, float z, float r, float a, string fileName);

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

    void collideWith(Collisional* other) override;

    void collide() override;

    // void drawCollisionMock();

private:
    std::string name;
    float centerX, centerY, centerZ, currentX, currentY, currentZ, radius, angle;
    GLuint textureID;
};
#endif // COSMICSPHERE_H
