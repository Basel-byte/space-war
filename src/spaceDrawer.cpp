#include "spaceDrawer.h"
#include "PlayerHealthBar.h"

int selected = 0;
// Globals.
float xAngle = 0.0, yAngle = 0.0, zAngle = 0.0; // Angles to rotate scene.

float spaceCraftAngle = 0.0f;     // Angle of the spacecraft.
float xVal = 0.0f, zVal = 250.0f; // Co-ordinates of the spacecraft.
float earthRadius = 4.2;

std::string planetNames[numberOfPlanets] = {"sun", "saturn", "mercury", "venus", "earth", "moon", "mars", "jupiter", "uranus", "neptune"};
unsigned int spacecraft; // Display lists base index.

// Radius of the asteroids.
float planetsRadius[numberOfPlanets] = {8 * earthRadius, 3 * earthRadius, 0.5f * earthRadius, 0.949f * earthRadius, earthRadius,
                                               0.3f * earthRadius, 0.532f * earthRadius, 4 * earthRadius,
                                               1.5f * earthRadius, 1.4f * earthRadius};

float planetsPositions[numberOfPlanets] = {0, -140, -40, -50, -65, -58, -75, -100, -170, -190};
bool isStarted = false;
GLuint skyboxTextureID; // Texture IDs for each face of the skybox
EffectManager effectManager;


void addMissile(){
    missileManager.addMissile(xVal - 10 * sin((M_PI / 180.0) * spaceCraftAngle), 
                              zVal - 10 * cos((M_PI / 180.0) * spaceCraftAngle),
                              spaceCraftAngle, &effectManager);
}

void loadSkyboxTextures()
{
    const char *skyboxFileNames =
        "src/textures/space2.jpg";

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
    // cout << "draw skybox" << endl;
}

// Set up camera for third-person view
void setCamera()
{
    // Set up modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Calculate camera position relative to the spacecraft
    float cameraDistance = 10.0f; // Distance from the spacecraft
    float cameraHeight = -0.3f;   // Height above the spacecraft (lowered slightly)
    float angleOffset = 15.0f;    // Angle offset from the spacecraft's direction

    // Calculate camera position
    float cameraX = xVal - cameraDistance * sin((M_PI / 180.0) * spaceCraftAngle);
    float cameraY = cameraHeight; // Adjust the height
    float cameraZ = zVal - cameraDistance * cos((M_PI / 180.0) * spaceCraftAngle);

    // Calculate look-at position
    float lookAtX = xVal - 11 * sin((M_PI / 180.0) * spaceCraftAngle);
    float lookAtY = -0.2f; // Look straight ahead
    float lookAtZ = zVal - 11 * cos((M_PI / 180.0) * spaceCraftAngle);

    // Position and orient the camera for third-person view
    gluLookAt(cameraX, cameraY, cameraZ, // Camera position
              lookAtX, lookAtY, lookAtZ, // Look at the specified point
              0.0, 1.0, 0.0);            // Up vector
}

void drawSpace()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Begin Large viewport.
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

    // Set up modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    playerHealthBar.renderHealthBar();

    // Set up the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw the skybox

    float globAmb[] = {.9, .9, .9, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);   // Enable local viewpoint

    // Turn lights on.
    glEnable(GL_LIGHT0);

    enemyManager.shootPlayer(&missileManager, xVal, zVal, &effectManager);
    missileManager.updateMissles(); // updating missiles

    // Begin Large viewport.
    glViewport(0, 0, width, height);

    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, ((double)800) / ((double)600), 0.1, 9000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);

    // Draw a vertical line on the left of the viewport to separate the two viewports
    glColor3f(1.0, 1.0, 1.0);
    GLfloat sun_diffuse[] = {(GLfloat)155 / 256, (GLfloat)155 / 256, (GLfloat)155 / 256, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, sun_diffuse);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_diffuse);
    drawSkybox();

    // Locate the camera at the tip of the cone and pointing in the direction of the cone.
    if (mode == firstPersonView)
    {
        gluLookAt(xVal,
                  0.0,
                  zVal,
                  xVal - 11 * sin((M_PI / 180.0) * spaceCraftAngle),
                  0.0,
                  zVal - 11 * cos((M_PI / 180.0) * spaceCraftAngle),
                  0.0,
                  1.0,
                  0.0);

        glPushMatrix();
        spacecraftFirstPersonView();
        glPopMatrix();
    }
    else if (mode == thirdPersonView)
    {
        /*
         * Animation
         */

        // setCamera();
 
        gluLookAt(xVal,
                  0.0,
                  zVal,
                  xVal - 11 * sin((M_PI / 180.0) * spaceCraftAngle),
                  0.0,
                  zVal - 11 * cos((M_PI / 180.0) * spaceCraftAngle),
                  0.0,
                  1.0,
                  0.0);

        glPushMatrix();
        spacecraftThirdPersonView();
        glPopMatrix();
    } else if (mode == topView)
    {
        gluLookAt(xVal, 150.0, zVal,  // Camera position
                  xVal, 0.0, zVal,  // Look at the spacecraft
                  0.0, 0.0, -1.0);  // Up vector        
        glPushMatrix();
        spacecraftThirdPersonView();
        glPopMatrix();
    }

    // Draw light source spheres (or arrow) after disabling lighting.
    glDisable(GL_LIGHTING);
    // Draw all the asteroids in arrayAsteroids.
    if(mode == thirdPersonView){
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, -0.5f);
        glTranslatef(0.0f, -0.5f, 0.0f);
    }
    for (int i = 0; i < numberOfPlanets; i++)
    {
        glPushMatrix();
        glRotatef(planetRotations[i], 0.0, 1.0, 0.0); // Rotate around the y-axis
        // Translate to the position of the planet and draw it
        (*planets[i]).draw();
        glPopMatrix();
        (*planets[i]).drawCollisionMock();

        
    }
    glPushMatrix();
    missileManager.drawMissles();
    effectManager.updateAndDrawEffects();
    glPopMatrix();

    glPushMatrix();

    glPopMatrix();

    glPushMatrix();
    enemyManager.draw();
    glPopMatrix();

    ///////////////// sample drawing of pickable objects ///////////////////////
    SpaceObject healthKit(" ", 50.0, 0.0, 30.0, 1.0, 0, "textures/solid_red.jpeg");
    healthKit.draw();

    SpaceObject weaponUpgrader(" ", 100.0, 0.0, 30.0, 1.0, 0, "textures/green.png");
    weaponUpgrader.draw();

    if(mode == thirdPersonView ){
        glPopMatrix();
    }

    // End Large viewport.

    glEnable(GL_SCISSOR_TEST);
    glScissor(2 * width / 3 - 10, 10, width / 3, height / 3);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    // // New small viewport for the red rectangle
    // glEnable(GL_SCISSOR_TEST);
    // int rectWidth = width-width/10;
    // int rectHeight = 20;
    // int rectX = (width - rectWidth) / 2; // Center horizontally
    // int rectY = height - rectHeight - 10; // 10 pixels from the top

    // glScissor(rectX, rectY, rectWidth, rectHeight);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // glViewport(rectX, rectY, rectWidth, rectHeight);
    // glLoadIdentity();

    // // Draw the red rectangle
    // glDisable(GL_LIGHTING);
    // glBegin(GL_QUADS);
    // glColor3f(1.0, 0.0, 0.0); // Red color
    // glVertex2f(0.0, 0.0);
    // glVertex2f(1.0, 0.0);
    // glVertex2f(1.0, 1.0);
    // glVertex2f(0.0, 1.0);
    // glEnd();

    // glDisable(GL_SCISSOR_TEST);

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

    drawSmallPortSpaceCraft(spaceCraftAngle, xVal, zVal);

    glPushMatrix();
    missileManager.drawMissles();
    glPopMatrix();

    glPushMatrix();
    enemyManager.draw();
    effectManager.updateAndDrawEffects();
    glPopMatrix();

    // End Small viewport.

    glutSwapBuffers();
}