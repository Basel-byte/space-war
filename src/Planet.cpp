#include <cstdlib>
#include <cmath>
#include <iostream>

#include <GL/glew.h>

#include <SOIL/SOIL.h>
#include "Planet.h"
GLuint moonTexture;

// SpaceObject default constructor.
SpaceObject::SpaceObject()
{
    id = "";
    centerX = 0.0;
    centerY = 0.0;
    centerZ = 0.0;
    radius = 0.0;
    angle = 0.0;
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
}

// SpaceObject constructor.
SpaceObject::SpaceObject(std::string planetId, float x, float y, float z, float r, float a, unsigned int colorR,
                         unsigned int colorG, unsigned int colorB, GLuint textureID)
{
    id = planetId;
    centerX = x;
    centerY = y;
    centerZ = z;
    currentX = x;
    currentY = y;
    currentZ = z;
    radius = r;
    angle = a;
    color[0] = colorR;
    color[1] = colorG;
    color[2] = colorB;
    this->textureID = textureID;
    if (id == "earth")
    {
        moonTexture = SOIL_load_OGL_texture("src\\textures\\moon.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    }
}
const int NumberOfPlanets = 9;
static float rShininess[NumberOfPlanets] = {0, 1.5, 2.5, 3.5, 7, 150, 15, 50, 70},
             gShininess[NumberOfPlanets] = {0, 1.5, 2.5, 3.5, 7, 150, 15, 50, 70},
             bShininess[NumberOfPlanets] = {0, 1.5, 2.5, 2.5, 7, 150, 15, 10, 15};
static unsigned int rAmbient[NumberOfPlanets] = {242, 85, 131, 3, 161, 157, 132, 18, 23},
                    gAmbient[NumberOfPlanets] = {208, 85, 82, 61, 45, 115, 112, 113, 52},
                    bAmbient[NumberOfPlanets] = {34, 85, 12, 95, 29, 89, 101, 141, 172};

static unsigned int rSpecular[NumberOfPlanets] = {242, 5, 91, 3, 121, 117, 92, 0, 0},
                    gSpecular[NumberOfPlanets] = {208, 5, 42, 21, 5, 75, 72, 73, 12},
                    bSpecular[NumberOfPlanets] = {34, 5, 2, 55, 0, 49, 61, 101, 132};

static unsigned int rDiffuse[NumberOfPlanets] = {242, 115, 191, 33, 191, 217, 242, 38, 53},
                    gDiffuse[NumberOfPlanets] = {208, 115, 112, 91, 75, 175, 224, 133, 82},
                    bDiffuse[NumberOfPlanets] = {34, 115, 42, 125, 59, 139, 201, 191, 242};
void SpaceObject::drawSubRoutine()
{
    GLfloat sunDiffuse[] = {(GLfloat)115 / 256, (GLfloat)115 / 256, (GLfloat)155 / 256,
                            1.0};
    GLfloat sunAmbient[] = {(GLfloat)85 / 256, (GLfloat)85 / 256, (GLfloat)85 / 256,
                            1.0};
    GLfloat sunSpecular[] = {(GLfloat)5, (GLfloat)5, (GLfloat)5, 1.0};
    GLfloat sunShininess[] = {(GLfloat)5, (GLfloat)5, (GLfloat)5, 1.0};

    glColor3ubv(color);

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

GLfloat moonColor[3] = {(GLfloat)90 / 256, (GLfloat)90 / 256, (GLfloat)90 / 256};
GLfloat ringColor1[3] = {(GLfloat)166 / 256, (GLfloat)98 / 256, (GLfloat)73 / 256};
GLfloat ringColor2[3] = {(GLfloat)150 / 256, (GLfloat)70 / 256, (GLfloat)73 / 256};
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

        if (id == "sun")
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
        if (id == "earth")
        {
            // rotate the moon around earth
            glMaterialfv(GL_FRONT, GL_AMBIENT, moonColor);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, moonColor);
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
        if (id == "saturn")
        {
            // rotate the ring around saturn
            glRotatef(115, 1.0, 0.0, 0.0);
            glMaterialfv(GL_FRONT, GL_AMBIENT, ringColor3);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, ringColor3);
            glutSolidTorus(2, 16, 75, 75);
        }
        glPopMatrix();

        // setCurrentX(centerX * (float)cos(angle * M_PI / 180));
        // setCurrentY(centerY);
        // setCurrentZ(-1 * centerX * (float)sin(angle * M_PI / 180));
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
