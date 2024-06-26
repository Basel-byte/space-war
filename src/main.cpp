#include <cmath>
#include "SpaceObject.h"
#include "menu.h"
// 37 5 87.5
#include "spaceDrawer.h"
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
        drawSpace();
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
    case ' ':
        isStarted = !isStarted;
        glutPostRedisplay();

        break;

    case 'x':
        xAngle += 5.0;
        if (xAngle > 360.0)
            xAngle -= 360.0;
        glutPostRedisplay();
        break;
    case 'X':
        xAngle -= 5.0;
        if (xAngle < 0.0)
            xAngle += 360.0;
        glutPostRedisplay();
        break;
    case 'y':
        yAngle += 5.0;
        if (yAngle > 360.0)
            yAngle -= 360.0;
        glutPostRedisplay();
        break;
    case 'Y':
        yAngle -= 5.0;
        if (yAngle < 0.0)
            yAngle += 360.0;
        glutPostRedisplay();
        break;
    case 'z':
        zAngle += 5.0;
        if (zAngle > 360.0)
            zAngle -= 360.0;
        glutPostRedisplay();
        break;
    case 'Z':
        zAngle -= 5.0;
        if (zAngle < 0.0)
            zAngle += 360.0;
        glutPostRedisplay();
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

void init()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

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
    for (size_t i = 0; i < 9; i++)
    {
        string filename = "src/textures/" + planetNames[i] + ".jpg";

        const char *filename_cstr = filename.c_str();

        planets[i] = new SpaceObject(planetNames[i], planetsPositions[i], 0.0, 0.0, planetsRadius[i],
                                     0.0, filename_cstr);
    }
}

// Main function
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(960, 580);
    glutCreateWindow("Sphere");
    init(); // Initialize OpenGL settings

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);
    glutMainLoop();
    return 0;
}