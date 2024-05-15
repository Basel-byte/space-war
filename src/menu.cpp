#include "menu.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

void Menu::drawString(float x, float y, float z, const char *string)
{
    glRasterPos3f(x, y, z);
    while (*string)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string); // Larger font size (GLUT_BITMAP_HELVETICA_18)
        string++;
    }
}

void Menu::drawRectangle(float x, float y, float z, float width, float height)
{
    glBegin(GL_QUADS);
    glVertex3f(x, y, z);
    glVertex3f(x + width, y, z);
    glVertex3f(x + width, y + height, z);
    glVertex3f(x, y + height, z);
    glEnd();
}

void Menu::drawMenu(int selected)
{
    float rectWidth;
    rectWidth = 300.0f;
    float rectHeight = 70.0f;
    float verticalSpacing = 50.0f;

    // Set clear color to blue (RGB: 0, 0, 1)
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    // Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Disable lighting temporarily
    glDisable(GL_LIGHTING);

    // Draw a background rectangle for the menu
    glColor3f(1.0f, 1.0f, 1.0f);                      // White color for the background
    drawRectangle(50.0f, 50.0f, 0.0, rectWidth, 300); // Background for menu
    if (selected == 0)
    {
        glColor3f(1.0f, 0.0f, 0.0f); // White color for the background

        drawRectangle(50.0f, 50.0f, .01f, rectWidth, 100); // Background for menu
                                                           // Draw text for menu options
                                                           // Black color for text
        glColor3f(1.0f, 1.0f, 1.0f);
        drawString(165.0f, 100.0f, 6.0f, "Option 1"); // Adjusted text position
    }
    else if (selected == 1)
    {
        glColor3f(1.0f, 0.0f, 0.0f); // White color for the background

        drawRectangle(50.0f, 150.0f, .01f, rectWidth, 100); // Background for menu
                                                            // Draw text for menu options
                                                            // Black color for text
        glColor3f(1.0f, 1.0f, 1.0f);
        drawString(165.0f, 200.0f, 6.0f, "Option 2"); // Adjusted text position
    }
    else if (selected == 2)
    {
        glColor3f(1.0f, 0.0f, 0.0f); // White color for the background

        drawRectangle(50.0f, 250.0f, .01f, rectWidth, 100); // Background for menu
                                                            // Draw text for menu options
                                                            // Black color for text
        glColor3f(1.0f, 1.0f, 1.0f);
        drawString(165.0f, 300.0f, 6.0f, "Option 3"); // Adjusted text position
    }
    glColor3f(0.0f, 0.0f, 0.0f);
    drawString(165.0f, 100.0f, 6.0f, "Option 1"); // Adjusted text position
    glColor3f(0.0f, 0.0f, 0.0f);
    drawString(165.0f, 200.0f, 6.0f, "Option 2"); // Adjusted text position
    glColor3f(0.0f, 0.0f, 0.0f);
    drawString(165.0f, 300.0f, 6.0f, "Option 3"); // Adjusted text position

    // Draw lines between the text
    glColor3f(1.0f, 1.0f, 0.0f); // Black color for lines
    glLineWidth(2.0);            // Set line width to 2
    glBegin(GL_LINES);
    glVertex3f(50.0f, 150.0f, 5.0f);  // Start of first line
    glVertex3f(350.0f, 150.0f, 5.0f); // End of first line
    glVertex3f(50.0f, 250.0f, 5.0f);  // Start of second line
    glVertex3f(350.0f, 250.0f, 5.0f); // End of second line
    glEnd();

    // Re-enable lighting
    glEnable(GL_LIGHTING);
}
