#include <GL/glut.h>

// Variables to track health
float healthPercentage = 1.0f; // Health starts at 100%
float decayRate = 0.01f;       // Health decays at 1% per second
float healthBarWidth = 0.3f;
float healthLeft = -0.95f;
float healthRight = healthLeft + healthBarWidth;
float healthTop = 0.7f;
float healthBottom = 0.4f;
int reRenderTime = 10; // 10 milliseconds

// Function to increase (+ve percentage) or decrease (-ve percentage) the health bar
void changeHealth(float percentage)
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
void changeHealth(int time)
{
    // Update health
    float changePercentage = -decayRate * time / 1000.0;
    changeHealth(changePercentage);

    // Call updateHealth again after 10 milliseconds
    glutTimerFunc(time, changeHealth, time);
}

// Function to render the health bar
void renderHealthBar()
{
    float currentHealthBarWidth = healthPercentage * healthBarWidth;
    float currentHealthRight = healthLeft + currentHealthBarWidth;

    glViewport(0, 0, 800, 600);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    // Set up modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw the background rectangle
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.7529f, 0.7961f); // Pink color for the background
    glVertex2f(healthLeft, healthTop);
    glVertex2f(healthRight, healthTop);
    glVertex2f(healthRight, healthBottom);
    glVertex2f(healthLeft, healthBottom);
    glEnd();

    // Draw the health rectangle
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f); // Red color for the health bar
    glVertex2f(healthLeft, healthTop);
    glVertex2f(currentHealthRight, healthTop);
    glVertex2f(currentHealthRight, healthBottom);
    glVertex2f(healthLeft, healthBottom);
    glEnd();

    glutSwapBuffers();
}