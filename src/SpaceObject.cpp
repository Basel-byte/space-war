#include <cstdlib>
#include <cmath>
#include <iostream>

#include <GL/glew.h>

#include <SOIL/SOIL.h>
#include "SpaceObject.h"
#include <SOIL/SOIL.h>
GLuint moonTexture;

// SpaceObject default constructor.
SpaceObject::SpaceObject()
{
    name = "";
    centerX = 0.0;
    centerY = 0.0;
    centerZ = 0.0;
    radius = 0.0;
    angle = 0.0;
}

// SpaceObject constructor.
SpaceObject::SpaceObject(std::string planetId, float x, float y, float z, float r, float a, string fileName)
{
    name = planetId;
    centerX = x;
    centerY = y;
    centerZ = z;
    currentX = x;
    currentY = y;
    currentZ = z;
    radius = r;
    angle = a;
    textureID = SOIL_load_OGL_texture(fileName.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (textureID == 0)
        printf("SOIL loading error: '%s'\n", SOIL_last_result());
    this->textureID = textureID;
    if (name == "earth")
    {
        moonTexture = SOIL_load_OGL_texture("src/textures/moon.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    }
}

void SpaceObject::drawSubRoutine()
{
    GLfloat sunDiffuse[] = {(GLfloat)115 / 256, (GLfloat)115 / 256, (GLfloat)155 / 256,
                            1.0};
    GLfloat sunAmbient[] = {(GLfloat)85 / 256, (GLfloat)85 / 256, (GLfloat)85 / 256,
                            1.0};
    GLfloat sunSpecular[] = {(GLfloat)5, (GLfloat)5, (GLfloat)5, 1.0};
    GLfloat sunShininess[] = {(GLfloat)5, (GLfloat)5, (GLfloat)5, 1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, sunAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, sunDiffuse);
    glMaterialfv(GL_FRONT, GL_SHININESS, sunShininess);

    // glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslatef(centerX, centerY, centerZ);
    glRotatef(0.0, 0.0, 1.0, 0.0);

    glBindTexture(GL_TEXTURE_2D, textureID);
    // set color of texture to be main color
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Yellow color
    glColor3f(1.0, 1.0, 0.0);

    // Enable texturing
    glEnable(GL_TEXTURE_2D);
    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Map the texture onto the sphere
    GLUquadric *quad = gluNewQuadric();
    gluQuadricTexture(quad, 1);
    gluSphere(quad, radius, 200, 200);
    // Disable texturing
    glDisable(GL_TEXTURE_2D);
}

GLfloat ringColor3[3] = {(GLfloat)130 / 256, (GLfloat)80 / 256, (GLfloat)50 / 256};
void SpaceObject::draw()
{
    if (radius > 0.0)
    {
        GLfloat sunShininess[] = {1.5, 1.5, 1.5, 1};

        glPushMatrix();

        drawSubRoutine();
        GLUquadric *quad;
        float lightAmb[] = {0.0, 0.0, 0.0, 1.0};
        float lightDifAndSpec0[] = {0.94, 0.72, 0.02, 1.0};
        float lightPos0[] = {1.0, 1.0, 1.0, 1}; // Demo: last value p define whether it is direction or positional
        float globAmb[] = {.9, .9, .9, 1.0};

        if (name == "sun")
        {
            // Draw light source spheres (or arrow) after disabling lighting.
            glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec0);
            glMaterialfv(GL_FRONT, GL_SHININESS, sunShininess);

            glBindTexture(GL_TEXTURE_2D, textureID);
            // set color of texture to be main color
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // Yellow color
            glColor3f(1.0, 1.0, 0.0);

            // Enable texturing
            glEnable(GL_TEXTURE_2D);
            // Bind the texture
            glBindTexture(GL_TEXTURE_2D, textureID);

            // Map the texture onto the sphere
            quad = gluNewQuadric();
            gluQuadricTexture(quad, 1);
            gluSphere(quad, radius, 200, 200);
            // Disable texturing
            glDisable(GL_TEXTURE_2D);
            glEnable(GL_LIGHTING);
        }
        if (name == "earth")
        {

            glRotatef(10 * 0.0, 0.0, 1.0, 0.2);
            glTranslatef(7, 0, 0);
            glBindTexture(GL_TEXTURE_2D, moonTexture);
            // set color of texture to be main color
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // Yellow color
            glColor3f(1.0, 1.0, 0.0);

            // Enable texturing
            glEnable(GL_TEXTURE_2D);
            // Bind the texture
            glBindTexture(GL_TEXTURE_2D, moonTexture);

            // Map the texture onto the sphere
            quad = gluNewQuadric();
            gluQuadricTexture(quad, 1);
            gluSphere(quad, .3 * radius, 200, 200);
            // Disable texturing
            glDisable(GL_TEXTURE_2D);
        }
        if (name == "saturn")
        {
            // rotate the ring around saturn
            glRotatef(115, 1.0, 0.0, 0.0);
            glMaterialfv(GL_FRONT, GL_AMBIENT, ringColor3);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, ringColor3);
            glutSolidTorus(2, 16, 75, 75);
        }
        glPopMatrix();
    }
}

void SpaceObject::setAngle(float a)
{
    SpaceObject::angle = a;
}

void SpaceObject::setCurrentX(float x)
{
    SpaceObject::currentX = x;
}

void SpaceObject::setCurrentY(float y)
{
    SpaceObject::currentY = y;
}

void SpaceObject::setCurrentZ(float z)
{
    SpaceObject::currentZ = z;
}

float SpaceObject::getCurrentX() const
{
    return currentX;
}

float SpaceObject::getCurrentY() const
{
    return currentY;
}

float SpaceObject::getCurrentZ() const
{
    return currentZ;
}
