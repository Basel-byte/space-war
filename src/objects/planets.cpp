#include "planets.h"

GLfloat ringColor3[3] = {(GLfloat)130 / 256, (GLfloat)80 / 256, (GLfloat)50 / 256};

Sun::Sun() : SpaceObject() {
    name = "Sun";
}

Sun::Sun(std::string name, float x, float y, float z, float r, float a, string fileName) : SpaceObject(name, x, y, z, r, a, fileName) {}

void Sun::drawSubRoutine() {
    GLfloat lightDifAndSpec0[] = {0.94, 0.72, 0.02, 1.0};
    GLfloat lightPos0[] = {1.0, 1.0, 1.0, 1}; // Demo: last value p define whether it is direction or positional
    GLfloat sunShininess[] = {1.5, 1.5, 1.5, 1};

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
    GLUquadric *quad = gluNewQuadric();
    gluQuadricTexture(quad, 1);
    gluSphere(quad, radius, 200, 200);
    // Disable texturing
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

Saturn::Saturn() : SpaceObject() {
    name = "Saturn";
}

Saturn::Saturn(std::string name, float x, float y, float z, float r, float a, string fileName) : SpaceObject(name, x, y, z, r, a, fileName) {}

void Saturn::drawSubRoutine() {
    // rotate the ring around saturn
    glRotatef(115, 1.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ringColor3);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ringColor3);
    glutSolidTorus(2, 16, 75, 75);
}