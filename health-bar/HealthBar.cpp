#include "HealthBar.h"


HealthBar::HealthBar() {
    healthPercentage = 1.0f; // Health starts at 100%
    decayRate = 0.01f;       // Health decays at 1% per second
    healthBarWidth = 0.3f;
    healthLeft = -0.95f;
    healthRight = healthLeft + healthBarWidth;
    healthTop = 0.95f;
    healthBottom = 0.915f;
    reRenderTime = 10; // 10 milliseconds
    pos_z = 0;
}
HealthBar::HealthBar(float x, float y, float z, float w, float h) {
    healthPercentage = 1.0f; 
    decayRate = 0.01f;      
    healthBarWidth = w;
    healthLeft = x;
    healthRight = healthLeft + healthBarWidth;
    healthTop = y;
    healthBottom = healthTop - 0.3;
    pos_z = z;
}

HealthBar::HealthBar(float x, float y, float z, float w, float h, float decayRate, int reRenderTime) {
    HealthBar(x, y, z, w, h);
    this->decayRate = decayRate;
    this->reRenderTime = reRenderTime;
}

// Function to increase (+ve percentage) or decrease (-ve percentage) the health bar
void HealthBar::changeHealth(float percentage)
{
    // Update health
    healthPercentage += percentage;
    if (healthPercentage > 1.0f)
    {
        healthPercentage = 1.0f;
    }
    else if (healthPercentage <= 0.0f)
    {
        ///////////////////// game over //////////////
        healthPercentage = 0.0f;
    }
    // Redisplay the scene
    glutPostRedisplay();
}

// Function to update health over time
void HealthBar::changeHealth(int time)
{
    // Update health
    float changePercentage = -decayRate * time / 1000.0;
    changeHealth(changePercentage);

    // Call updateHealth again after 10 milliseconds
    // glutTimerFunc(time, changeHealth, time);
}

// Function to render the health bar
void HealthBar::renderHealthBar()
{
    float currentHealthBarWidth = healthPercentage * healthBarWidth;
    float currentHealthRight = healthLeft + currentHealthBarWidth;

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // glClearColor(1.0, 1.0, 1.0, 1.0);

    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    // Set up modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw the background rectangle
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.7529f, 0.7961f); // Pink color for the background
    glVertex3f(healthLeft, healthTop, pos_z);
    glVertex3f(healthRight, healthTop, pos_z);
    glVertex3f(healthRight, healthBottom, pos_z);
    glVertex3f(healthLeft, healthBottom, pos_z);
    glEnd();

    // Draw the health rectangle
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f); // Red color for the health bar
    glVertex3f(healthLeft, healthTop, pos_z + 0.1);
    glVertex3f(currentHealthRight, healthTop, pos_z + 0.1);
    glVertex3f(currentHealthRight, healthBottom, pos_z + 0.1);
    glVertex3f(healthLeft, healthBottom, pos_z);
    glEnd();

    glutSwapBuffers();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}