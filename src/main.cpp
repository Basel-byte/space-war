#define _USE_MATH_DEFINES

#include <cmath>
#include "SpaceObject.h"
#include "planets.h"
#include "menu.h"
// 37 5 87.5

#include "spaceDrawer.h"
#include "animation.h"
#include "CollisionManager.h"
#include "constants.h"
#include "missile.h"
#include "PlayerHealthBar.h"

CollisionManager collisionManager = CollisionManager(soundService);
SpaceObject *planets[numberOfPlanets];

void display()
{
    if (!isStarted)
    {
        glViewport(0, 0, width, height);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();
        // Set up the camera for the menu
        gluLookAt(0, 0, 244.0f,   // Camera position
                  0.0, 0.0, 0.0,  // Look-at position
                  0.0, 1.0, 0.0); // Up vector

        glPushMatrix();
        glTranslatef(-200, -180, 0);
        Menu::drawMenu(selected);
        glPopMatrix();
        glutSwapBuffers();
    }
    else
    {
        if(playerHealthBar.getHealthPercentage() <= 1e-3){
            isStarted = false;
            selected = 2;
            glutPostRedisplay();
            return;
        }
        drawSpace();
        collisionManager.checkCollisions();
    }
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 13:
        cout << "enter" << endl;
        break;
    case 27:
        exit(0);
        break;
    // case 'p':
    //     soundService.playSound("collision");
    //     break;
    // case 'o':
    //     soundService.playSound("explosion");
    //     break;
    // case 'i':
    //     soundService.playSound("shoot");
    //     break;
    case ' ':
        isStarted = !isStarted;
        playerHealthBar.changeHealth(100.0f);
        switch (selected)
        {
        case 0:
            exit(0);
            break;
        case 1:
            startBarDecay();
            break;
        case 2:
            // survivalMode;
            break;
        default:
            break;
        }
        glutPostRedisplay();

        break;
    case 'v':
        toggleViewMode();
        glutPostRedisplay();
        break;
    case 'f': // For shooting Enemies
        if (isStarted)
            addMissile();
        break;
    case '[':
        // if (missileDepth > 0.1f)
        missileShiftX -= 0.1f;
        cout << "missileShiftX: " << missileShiftX << endl;
        break;
    case ']':
        missileShiftX += 0.1f;
        cout << "missileShiftX: " << missileShiftX << endl;
        break;
    case 'p':
        // if (missileWidth > 0.1f)
        missileShiftY -= 0.1f;
        cout << "missileShiftY: " << missileShiftY << endl;
        break;
    case 'o':
        missileShiftY += 0.1f;
        cout << "missileShiftY: " << missileShiftY << endl;
        break;
    case 'i':
        // if (missileHeight > 0.1f)
        missileShiftZ -= 0.1f;
        cout << "missileShiftZ: " << missileShiftZ << endl;
        break;
    case 'u':
        missileShiftZ += 0.1f;
        cout << "missileShiftZ: " << missileShiftZ << endl;
        break;
    default:
        break;
    }
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
    float tempXVal = xVal, tempZVal = zVal, tempAngle = spaceCraftAngle;

    // Compute next position.
    if (key == GLUT_KEY_LEFT)
        tempAngle = spaceCraftAngle + 5.0f;
    if (key == GLUT_KEY_RIGHT)
        tempAngle = spaceCraftAngle - 5.0f;
    if (key == GLUT_KEY_UP)

    {
        if (!isStarted)
        {
            selected = (selected + 1) % 3;
            cout << "selected: " << selected << endl;
        }
        else
        {
            tempXVal = xVal - (float)sin(spaceCraftAngle * M_PI / 180.0);
            tempZVal = zVal - (float)cos(spaceCraftAngle * M_PI / 180.0);
        }
    }
    if (key == GLUT_KEY_DOWN)
    {
        if (!isStarted)
        {
            selected = (selected - 1) % 3;
            if (selected < 0)
                selected = 2;
            cout << "selected: " << selected << endl;
        }
        else
        {
            tempXVal = xVal + (float)sin(spaceCraftAngle * M_PI / 180.0);
            tempZVal = zVal + (float)cos(spaceCraftAngle * M_PI / 180.0);
        }
    }

    // Angle correction.
    if (tempAngle > 360.0)
        tempAngle -= 360.0;
    if (tempAngle < 0.0)
        tempAngle += 360.0;

    // Move spacecraft to next position only if there will not be collision with an asteroid.

    xVal = tempXVal;
    zVal = tempZVal;
    spaceCraftAngle = tempAngle;

    glutPostRedisplay();
}

// OpenGL reshape function
void reshape(int w, int h)
{
    width = w;
    height = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, ((double)w) / ((double)h), 0.1, 9000.0);
    glMatrixMode(GL_MODELVIEW);
}

const char *loadTexture(std::string planetName)
{
    string filename = "src/textures/" + planetName + ".jpg";
    return filename.c_str();
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    /*
     * Initializing spacecraft & enemies
     */
    initAnimation(width, height);
    glutTimerFunc(50, timer, 0);

    // Load skybox textures
    loadSkyboxTextures();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    spacecraft = glGenLists(1);
    glNewList(spacecraft, GL_COMPILE);
    glPushMatrix();
    glRotatef(180.0, 0.0, 1.0, 0.0); // To make the spacecraft point down the $z$-axis initially.
    glColor3f(1.0, 1.0, 1.0);
    glutWireCone(5.0, 10.0, 10, 10);
    glPopMatrix();
    glEndList();

    planets[0] = new Sun(planetNames[0], planetsPositions[0], 0.0, 0.0, planetsRadius[0], 0.0, loadTexture(planetNames[0]));
    planets[1] = new Saturn(planetNames[1], planetsPositions[1], 0.0, 0.0, planetsRadius[1], 0.0, loadTexture(planetNames[1]));

    for (size_t i = 2; i < numberOfPlanets; i++)
    {
        const char *texture = loadTexture(planetNames[i]);

        planets[i] = new SpaceObject(planetNames[i], planetsPositions[i], 0.0, 0.0, planetsRadius[i], 0.0, texture);
    }
    soundService.initSoundService();
}

int prevMouseX = 0;
int prevMouseY = 0;

void mouseMotion(int x, int y)
{
    // Check if there has been actual mouse movement
    if (x != prevMouseX || y != prevMouseY)
    {
        // Calculate the change in mouse position
        int deltaX = x - screenwidth / 2;
        int deltaY = y - screenheight / 2;

        // Calculate the angle between the mouse position and the center of the screen
        float angle = atan2(deltaY, deltaX) * 180.0f / M_PI;

        // Adjust the angle to be in the range [0, 360]
        if (angle < 0.0f)
            angle += 360.0f;

        // Update the spacecraft angle
        spaceCraftAngle = angle;

        // Update the previous mouse position
        prevMouseX = x;
        prevMouseY = y;

        // Redraw the scene
        glutPostRedisplay();
    }
}

// Main function
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("Space War");
    glEnable(GL_DEPTH_TEST);
    init(); // Initialize OpenGL settings
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);

    // Set motion and passive motion callbacks
    // glutMotionFunc(mouseMotion);
    glutPassiveMotionFunc(mouseMotion);

    glutMainLoop();

    return 0;
}