// #include <GL/freeglut.h>
// #include <iostream>
// #define numberOfPlanets 9 // Number of rows of asteroids.
// enum planet
// {
//     SUN = 0,
//     EARTH = 3,
//     SATURN = 6,
// };

// // Globals.
// static float xAngle = 0.0, yAngle = 0.0, zAngle = 0.0; // Angles to rotate scene.
// static int isAnimate = 0;                              // Animated?

// static float m = 0.9; // Global ambient white light intensity.
// static float t = 0.0; // Quadratic attenuation factor.
// // Light property vectors.
// float lightAmb[] = {0.0, 0.0, 0.0, 1.0};
// float lightDifAndSpec0[] = {0.94, 0.72, 0.02, 1.0};
// float lightPos0[] = {1.0, 1.0, 1.0, 1}; // Demo: last value p define whether it is direction or positional
// float globAmb[] = {m, m, m, 1.0};

// static void *font = GLUT_BITMAP_8_BY_13; // Font selection.
// static float spaceCraftAngle = 0.0f;     // Angle of the spacecraft.
// static float xVal = 0.0f, zVal = 250.0f; // Co-ordinates of the spacecraft.
// static float latAngle = 0.0;             // Latitudinal spaceCraftAngle.
// static float longAngle = 0.0;            // Longitudinal spaceCraftAngle.
// static int isCollision = 0;              // Is there collision between the spacecraft and an asteroid?
// static unsigned int spacecraft;          // Display lists base index.
// static float earthRadius = 4.2;
// static unsigned int rColor[numberOfPlanets] = {242, 115, 191, 33, 191, 217, 242, 38, 53},
//                     gColor[numberOfPlanets] = {208, 115, 112, 91, 75, 175, 224, 133, 82},
//                     bColor[numberOfPlanets] = {34, 115, 42, 125, 59, 139, 201, 191, 242};

// static unsigned int rAmbient[numberOfPlanets] = {242, 85, 131, 3, 161, 157, 132, 18, 23},
//                     gAmbient[numberOfPlanets] = {208, 85, 82, 61, 45, 115, 112, 113, 52},
//                     bAmbient[numberOfPlanets] = {34, 85, 12, 95, 29, 89, 101, 141, 172};

// static unsigned int rSpecular[numberOfPlanets] = {242, 5, 91, 3, 121, 117, 92, 0, 0},
//                     gSpecular[numberOfPlanets] = {208, 5, 42, 21, 5, 75, 72, 73, 12},
//                     bSpecular[numberOfPlanets] = {34, 5, 2, 55, 0, 49, 61, 101, 132};

// static unsigned int rDiffuse[numberOfPlanets] = {242, 115, 191, 33, 191, 217, 242, 38, 53},
//                     gDiffuse[numberOfPlanets] = {208, 115, 112, 91, 75, 175, 224, 133, 82},
//                     bDiffuse[numberOfPlanets] = {34, 115, 42, 125, 59, 139, 201, 191, 242};

// static float rShininess[numberOfPlanets] = {0, 1.5, 2.5, 3.5, 7, 150, 15, 50, 70},
//              gShininess[numberOfPlanets] = {0, 1.5, 2.5, 3.5, 7, 150, 15, 50, 70},
//              bShininess[numberOfPlanets] = {0, 1.5, 2.5, 2.5, 7, 150, 15, 10, 15};

// GLfloat moonColor[3] = {(GLfloat)90 / 256, (GLfloat)90 / 256, (GLfloat)90 / 256};
// GLfloat ringColor1[3] = {(GLfloat)166 / 256, (GLfloat)98 / 256, (GLfloat)73 / 256};
// GLfloat ringColor2[3] = {(GLfloat)150 / 256, (GLfloat)70 / 256, (GLfloat)73 / 256};
// GLfloat ringColor3[3] = {(GLfloat)130 / 256, (GLfloat)80 / 256, (GLfloat)50 / 256};
// std::string planetNames[9] = {"sun", "mercury", "venus", "earth", "mars", "jupiter", "saturn", "uranus", "neptune"};

// // Radius of the asteroids.
// static float planetsRadius[numberOfPlanets] = {8 * earthRadius, 0.5f * earthRadius, 0.949f * earthRadius, earthRadius,
//                                                0.532f * earthRadius, 4 * earthRadius, 3 * earthRadius,
//                                                1.5f * earthRadius, 1.4f * earthRadius};
// static float planetsAngle[numberOfPlanets] = {0, 4, 1.5, 1, 0.7,
//                                               0.3, 0.2, 0.08, 0.05};
// static float planetsPositions[numberOfPlanets] = {0, -40, -50, -65, -75, -100, -140, -170, -190};
