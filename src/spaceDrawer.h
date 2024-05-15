#include <cmath>

#include <SOIL/SOIL.h>
#include "SpaceObject.h"

// #include "../spacecrafts/EnemyManager.h"
#include "../model-loader/Model.h"
#include "../animation/animation.h"

#define numberOfPlanets 9
static int width = 960, height = 580;
int selected = 0;
// Globals.
static float xAngle = 0.0, yAngle = 0.0, zAngle = 0.0; // Angles to rotate scene.

static float spaceCraftAngle = 0.0f;     // Angle of the spacecraft.
static float xVal = 0.0f, zVal = 250.0f; // Co-ordinates of the spacecraft.
static float earthRadius = 4.2;

std::string planetNames[9] = {"sun", "mercury", "venus", "earth", "mars", "jupiter", "saturn", "uranus", "neptune"};
static unsigned int spacecraft; // Display lists base index.

// Radius of the asteroids.
static float planetsRadius[numberOfPlanets] = {8 * earthRadius, 0.5f * earthRadius, 0.949f * earthRadius, earthRadius,
                                               0.532f * earthRadius, 4 * earthRadius, 3 * earthRadius,
                                               1.5f * earthRadius, 1.4f * earthRadius};

static float planetsPositions[numberOfPlanets] = {0, -40, -50, -65, -75, -100, -140, -170, -190};
bool isStarted = false;
static SpaceObject *planets[9];
GLuint skyboxTextureID; // Texture IDs for each face of the skybox

void loadSkyboxTextures()
{
    const char *skyboxFileNames =
        "textures/space2.jpg";

    skyboxTextureID = SOIL_load_OGL_texture(skyboxFileNames, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (skyboxTextureID == 0)
    {
        printf("Error loading skybox texture: %s\n", SOIL_last_result());
    }
}
void drawSkybox()
{

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Disable lighting for the skybox
    glDisable(GL_LIGHTING);

    // Draw the skybox
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(xVal, 0.0, zVal);
    glRotatef(spaceCraftAngle, 0.0, 1.0, 0.0);

    // Enable texturing for the skybox
    glEnable(GL_TEXTURE_2D);

    // Draw the skybox faces
    for (int i = 0; i < 6; ++i)
    {
        glBindTexture(GL_TEXTURE_2D, skyboxTextureID);
        glBegin(GL_QUADS);

        switch (i)
        {
        case 0: // Positive X face
            glTexCoord2f(0, 0);
            glVertex3f(500.0f, -500.0f, -500.0f);
            glTexCoord2f(1, 0);
            glVertex3f(500.0f, -500.0f, 500.0f);
            glTexCoord2f(1, 1);
            glVertex3f(500.0f, 500.0f, 500.0f);
            glTexCoord2f(0, 1);
            glVertex3f(500.0f, 500.0f, -500.0f);
            break;
        case 1: // Negative X face
            glTexCoord2f(0, 0);
            glVertex3f(-500.0f, -500.0f, 500.0f);
            glTexCoord2f(1, 0);
            glVertex3f(-500.0f, -500.0f, -500.0f);
            glTexCoord2f(1, 1);
            glVertex3f(-500.0f, 500.0f, -500.0f);
            glTexCoord2f(0, 1);
            glVertex3f(-500.0f, 500.0f, 500.0f);
            break;
        case 2: // Positive Y face
            glTexCoord2f(0, 0);
            glVertex3f(-500.0f, 500.0f, -500.0f);
            glTexCoord2f(1, 0);
            glVertex3f(500.0f, 500.0f, -500.0f);
            glTexCoord2f(1, 1);
            glVertex3f(500.0f, 500.0f, 500.0f);
            glTexCoord2f(0, 1);
            glVertex3f(-500.0f, 500.0f, 500.0f);
            break;
        case 3: // Negative Y face
            glTexCoord2f(0, 0);
            glVertex3f(-500.0f, -500.0f, 500.0f);
            glTexCoord2f(1, 0);
            glVertex3f(500.0f, -500.0f, 500.0f);
            glTexCoord2f(1, 1);
            glVertex3f(500.0f, -500.0f, -500.0f);
            glTexCoord2f(0, 1);
            glVertex3f(-500.0f, -500.0f, -500.0f);
            break;
        case 4: // Positive Z face
            glTexCoord2f(0, 0);
            glVertex3f(-500.0f, -500.0f, 500.0f);
            glTexCoord2f(1, 0);
            glVertex3f(500.0f, -500.0f, 500.0f);
            glTexCoord2f(1, 1);
            glVertex3f(500.0f, 500.0f, 500.0f);
            glTexCoord2f(0, 1);
            glVertex3f(-500.0f, 500.0f, 500.0f);
            break;
        case 5: // Negative Z face
            glTexCoord2f(0, 0);
            glVertex3f(500.0f, -500.0f, -500.0f);
            glTexCoord2f(1, 0);
            glVertex3f(-500.0f, -500.0f, -500.0f);
            glTexCoord2f(1, 1);
            glVertex3f(-500.0f, 500.0f, -500.0f);
            glTexCoord2f(0, 1);
            glVertex3f(500.0f, 500.0f, -500.0f);
            break;
        }
        glEnd();
    }

    // Restore previous state
    glPopMatrix();
    glEnable(GL_LIGHTING);
    cout << "draw skybox" << endl;
}
void drawSpace()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Set up the modelview matrix
    glLoadIdentity();

    // Draw the skybox

    float globAmb[] = {.9, .9, .9, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);   // Enable local viewpoint

    // Turn lights on.
    glEnable(GL_LIGHT0);

    // Begin Large viewport.
    glViewport(0, 0, width, height);

    glLoadIdentity();
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);

    // Draw a vertical line on the left of the viewport to separate the two viewports
    glColor3f(1.0, 1.0, 1.0);
    GLfloat sun_diffuse[] = {(GLfloat)155 / 256, (GLfloat)155 / 256, (GLfloat)155 / 256, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, sun_diffuse);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_diffuse);
    drawSkybox();

    // Locate the camera at the tip of the cone and pointing in the direction of the cone.
    gluLookAt(xVal - 10 * sin((M_PI / 180.0) * spaceCraftAngle),
              0.0,
              zVal - 10 * cos((M_PI / 180.0) * spaceCraftAngle),
              xVal - 11 * sin((M_PI / 180.0) * spaceCraftAngle),
              0.0,
              zVal - 11 * cos((M_PI / 180.0) * spaceCraftAngle),
              0.0,
              1.0,
              0.0);

    /*
     * Animation
     */
    spacecraftFirstPersonView();

    // Draw light source spheres (or arrow) after disabling lighting.
    glDisable(GL_LIGHTING);
    // Draw all the asteroids in arrayAsteroids.

    for (int i = 0; i < numberOfPlanets; i++)
    {
        glPushMatrix();
        glRotatef(planetRotations[i], 0.0, 1.0, 0.0); // Rotate around the y-axis
        // Translate to the position of the planet and draw it
        (*planets[i]).draw();

        glPopMatrix();
    }

    glPushMatrix();
    enemyManager.draw();
    glPopMatrix();

    // End Large viewport.

    glEnable(GL_SCISSOR_TEST);
    glScissor(2 * width / 3 - 10, 10, width / 3, height / 3);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    // Begin Small viewport.
    glViewport(2 * width / 3 - 10, 10, width / 3, height / 3);
    glLoadIdentity();
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);
    drawSkybox();
    // Draw light source spheres (or arrow) after disabling lighting.
    glDisable(GL_LIGHTING);

    // Fixed camera.
    gluLookAt(0.0, 200.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);

    // Draw all the asteroids in arrayAsteroids.
    for (int i = 0; i < numberOfPlanets; i++)
    {
        glPushMatrix();
        glRotatef(planetRotations[i], 0.0, 1.0, 0.0); // Rotate around the y-axis
        (*planets[i]).draw();
        glPopMatrix();
    }

    drawSmallPortSpaceCraft(spaceCraftAngle,  xVal,  zVal);

    glPushMatrix();
    enemyManager.draw();
    glPopMatrix();


    // End Small viewport.

    glutSwapBuffers();
}
