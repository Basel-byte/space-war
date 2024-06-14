#include "HealthBar.h"


HealthBar::HealthBar() {
    healthPercentage = 1.0f; // Health starts at 100%
    decayRate = 0.01f;       // Health decays at 1% per second
    healthBarWidth = 0.25f;
    healthLeft = 0.5f - healthBarWidth * 0.5f;
    healthRight = healthLeft + healthBarWidth;
    healthTop = 0.97f;
    healthBottom = 0.95f;
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
    healthBottom = healthTop - 10;
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
        ///////////////////// game over ////////////////////
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
}

void HealthBar::renderHealthBar()
{
    float currentHealthBarWidth = healthPercentage * healthBarWidth;
    float currentHealthRight = healthLeft + currentHealthBarWidth;

    // Save the current OpenGL state
    glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT);

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    glColor3f(1.0f, 0.7529f, 0.7961f); // Pink color for the background

    auto drawRectangle = [&](float right, float pos_z) -> void
    {
        glBegin(GL_QUADS);
        glVertex3f(healthLeft, healthTop, pos_z);
        glVertex3f(right, healthTop, pos_z);
        glVertex3f(right, healthBottom, pos_z);
        glVertex3f(healthLeft, healthBottom, pos_z);
        glEnd();
    };

    // Draw the background rectangle
    drawRectangle(healthRight, pos_z);

    if (healthPercentage > 0.5)
        glColor3f(0.0f, 1.0f, 0.0f); // Green color for the health bar
    else
        glColor3f(1.0f, 0.0f, 0.0f); // Red color for the health bar

    drawRectangle(currentHealthRight, pos_z + 0.1);
    drawRectangle(currentHealthRight, pos_z - 0.1);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    // Restore the previous OpenGL state
    glPopAttrib();
}
