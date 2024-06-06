#include "animation.h"

#define numberOfPlanets 9

Model spacecraftobj = Model(0.06);
EnemyManager enemyManager;
MissileManager missileManager;

float planetRotations[numberOfPlanets] = {0};
static float rotationSpeed[numberOfPlanets] = {0, 4, 1.5, 1, 0.7,
                                               0.3, 0.2, 0.08, 0.05};

float screenwidth =0, screenheight = 0;
viewMode mode = firstPersonView;


void timer(int value)
{
    for (int i = 0; i < numberOfPlanets; i++)
    {
        planetRotations[i] += rotationSpeed[i];
        if (planetRotations[i] >= 360.0f)
        {
            planetRotations[i] -= 360.0f;
        }
    }
    for (int i = 0; i < enemyManager.enemyModels.size(); ++i)
    {
        if (enemyManager.moveCounter >= enemyManager.maxMove)
        {
            enemyManager.forward = false;
        }
        if (enemyManager.moveCounter <= 0)
        {
            enemyManager.forward = true;
        }
        if (enemyManager.forward)
        {
            enemyManager.enemyModels[i].ry += 0.1;
            enemyManager.moveCounter++;
        }
        else
        {
            enemyManager.enemyModels[i].ry -= 0.1;
            enemyManager.moveCounter--;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(50, timer, 0);
}
void spacecraftThirdPersonView(){
    glPushMatrix();
    glLoadIdentity();
    glScalef(0.001f, 0.001f, 0.001f);
    glTranslatef(0.0f, 0.0f, -250.0f);
    glTranslatef(0.0f, 0.0f, 20.0f);
    glTranslatef(0.0f, -45.0f, 0.0f);
    glTranslatef(0.0f, -45.0f, 0.0f);
    glRotatef(270, 0.0, 1.0, 0.0);
    spacecraftobj.draw();
    spacecraftobj.setCollisionCenterAsCurrent();
    glPopMatrix();
    spacecraftobj.drawCollisionMock();
}

void spacecraftFirstPersonView()
{
    glPushMatrix();
    glLoadIdentity();
    glScalef(0.006f, 0.006f, 0.006f);

    glTranslatef(0.0f, 0.0f, 20.0f);
    glTranslatef(0.0f, -45.0f, 0.0f);
    glRotatef(270, 0.0, 1.0, 0.0);
    spacecraftobj.draw();
    spacecraftobj.setCollisionCenterAsCurrent();
    glPopMatrix();
    spacecraftobj.drawCollisionMock();
}

void drawSmallPortSpaceCraft(float spaceCraftAngle, float xVal, float zVal)
{
    // Draw spacecraft.
    glPushMatrix();
    //  glRotatef( 90, 0.0, 1.0, 0.0);
    glTranslatef(xVal, 0.0, zVal);
    glScalef(0.1f, 0.1f, 0.1f);
    // glRotatef(90, 1.0, 0.0, 0.0);
    glRotatef(90, 0.0, 0.0, 1.0);
    // glCallList(spacecraft);
    glRotatef(spaceCraftAngle, 0.0, 1.0, 0.0);
    spacecraftobj.draw();
    // spacecraftobj.draw();
    glPopMatrix();
}

void initAnimation(float width, float height){
    screenwidth = width;
    screenheight = height;

    spacecraftobj.load("Models/shuttle/shuttle.obj");
    enemyManager.init(10);
}


void toggleViewMode() {
    mode = (mode == thirdPersonView) ? firstPersonView : thirdPersonView;
}
