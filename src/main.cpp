#include <cmath>
#include "planet.h"
GLfloat Xangle = 0.0f, Yangle = 0.0f, Zangle = 0.0f;
// 37 5 87.5
GLfloat cameraX = -37.5f, cameraY = 5.0f, cameraZ = 87.5f; // Initial camera position
GLfloat cameraSpeed = 0.5f;                                // Speed of camera movement
static int width = 960, height = 580;
#define numberOfPlanets 9 // Number of rows of asteroids.
enum planet
{
    SUN = 0,
    EARTH = 3,
    SATURN = 6,
};

// Globals.
static float xAngle = 0.0, yAngle = 0.0, zAngle = 0.0; // Angles to rotate scene.
static int isAnimate = 0;                              // Animated?

static float m = 0.9; // Global ambient white light intensity.
static float t = 0.0; // Quadratic attenuation factor.
// Light property vectors.

static void *font = GLUT_BITMAP_8_BY_13; // Font selection.
static float spaceCraftAngle = 0.0f;     // Angle of the spacecraft.
static float xVal = 0.0f, zVal = 250.0f; // Co-ordinates of the spacecraft.
static float latAngle = 0.0;             // Latitudinal spaceCraftAngle.
static float longAngle = 0.0;            // Longitudinal spaceCraftAngle.
static int isCollision = 0;              // Is there collision between the spacecraft and an asteroid?
static unsigned int spacecraft;          // Display lists base index.
static float earthRadius = 4.2;
static unsigned int rColor[numberOfPlanets] = {242, 115, 191, 33, 191, 217, 242, 38, 53},
                    gColor[numberOfPlanets] = {208, 115, 112, 91, 75, 175, 224, 133, 82},
                    bColor[numberOfPlanets] = {34, 115, 42, 125, 59, 139, 201, 191, 242};

std::string planetNames[9] = {"sun", "mercury", "venus", "earth", "mars", "jupiter", "saturn", "uranus", "neptune"};

// Radius of the asteroids.
static float planetsRadius[numberOfPlanets] = {8 * earthRadius, 0.5f * earthRadius, 0.949f * earthRadius, earthRadius,
                                               0.532f * earthRadius, 4 * earthRadius, 3 * earthRadius,
                                               1.5f * earthRadius, 1.4f * earthRadius};
static float planetsAngle[numberOfPlanets] = {0, 4, 1.5, 1, 0.7,
                                              0.3, 0.2, 0.08, 0.05};
static float planetsPositions[numberOfPlanets] = {0, -40, -50, -65, -75, -100, -140, -170, -190};
bool isStarted = false;
static SpaceObject *planets[9];
GLuint skyboxTextureID[6]; // Texture IDs for each face of the skybox

void loadSkyboxTextures()
{
    const char *skyboxFileNames[6] = {
        "src\\textures\\space2.jpg", // Positive X face
        "src\\textures\\space2.jpg",
        "src\\textures\\space2.jpg",
        "src\\textures\\space2.jpg",
        "src\\textures\\space2.jpg",
        "src\\textures\\space2.jpg"};

    for (int i = 0; i < 6; ++i)
    {
        skyboxTextureID[i] = SOIL_load_OGL_texture(skyboxFileNames[i], SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
        if (skyboxTextureID[i] == 0)
        {
            printf("Error loading skybox texture: %s\n", SOIL_last_result());
        }
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
        glBindTexture(GL_TEXTURE_2D, skyboxTextureID[i]);
        glBegin(GL_QUADS);
        // Define vertices and texture coordinates for each face
        // Adjust these coordinates as necessary to fit your skybox layout
        // Repeat texture coordinates if needed
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
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, t);

    // Draw a vertical line on the left of the viewport to separate the two viewports
    glColor3f(1.0, 1.0, 1.0);
    GLfloat sun_diffuse[] = {(GLfloat)155 / 256, (GLfloat)155 / 256, (GLfloat)155 / 256, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, sun_diffuse);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_diffuse);
    drawSkybox();
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(2.5, -4.9, -5.0);
    glVertex3f(2.5, -1.5, -5.0);
    glVertex3f(7.9, -1.5, -5.0);
    glVertex3f(7.9, -4.9, -5.0);
    glEnd();
    glLineWidth(1.0);

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
    // Draw light source spheres (or arrow) after disabling lighting.
    glDisable(GL_LIGHTING);
    // Draw all the asteroids in arrayAsteroids.

    for (int i = 0; i < numberOfPlanets; i++)
        (*planets[i]).draw();
    // End Large viewport.

    glEnable(GL_SCISSOR_TEST);
    glScissor(2 * width / 3 - 10, 10, width / 3, height / 3);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    // Begin Small viewport.
    glViewport(2 * width / 3 - 10, 10, width / 3, height / 3);
    glLoadIdentity();
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, t);
    drawSkybox();
    // Draw light source spheres (or arrow) after disabling lighting.
    glDisable(GL_LIGHTING);

    // Fixed camera.
    gluLookAt(0.0, 200.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);

    // Draw all the asteroids in arrayAsteroids.
    for (int i = 0; i < numberOfPlanets; i++)
        (*planets[i]).draw();

    // Draw spacecraft.
    glPushMatrix();
    glTranslatef(xVal, 0.0, zVal);
    glRotatef(spaceCraftAngle, 0.0, 1.0, 0.0);
    glCallList(spacecraft);
    glPopMatrix();
    // End Small viewport.

    glutSwapBuffers();
}

void drawString(float x, float y, float z, const char *string)
{
    glRasterPos3f(x, y, z);
    while (*string)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string); // Larger font size (GLUT_BITMAP_HELVETICA_18)
        string++;
    }
}
int selected = 0;
void drawRectangle(float x, float y, float z, float width, float height)
{
    glBegin(GL_QUADS);
    glVertex3f(x, y, z);
    glVertex3f(x + width, y, z);
    glVertex3f(x + width, y + height, z);
    glVertex3f(x, y + height, z);
    glEnd();
}
float rectWidth;
void drawMenu()
{
    rectWidth = 300.0f;            // Width of menu rectangles
    float rectHeight = 70.0f;      // Height of menu rectangles
    float verticalSpacing = 50.0f; // Spacing between rectangles

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

void display()
{
    if (!isStarted)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        // Set up the camera for the menu
        gluLookAt(0, 0, 244.0f,   // Camera position
                  0.0, 0.0, 0.0,  // Look-at position
                  0.0, 1.0, 0.0); // Up vector

        glPushMatrix();
        glTranslatef(-200, -180, 0);
        drawMenu();
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

    isCollision = 0;
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
        // glActiveTexture(GL_TEXTURE0);
        GLuint textureID = SOIL_load_OGL_texture(filename_cstr, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
        if (textureID == 0)
            printf("SOIL loading error: '%s'\n", SOIL_last_result());

        planets[i] = new SpaceObject(planetNames[i], planetsPositions[i], 0.0, 0.0, planetsRadius[i],
                                     0.0, rColor[i] % 256, gColor[i] % 256, bColor[i] % 256, textureID);
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