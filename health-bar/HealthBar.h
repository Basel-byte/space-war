#ifndef HealthBar_H
#define HealthBar_H

#include <GL/freeglut.h>
#include <GL/glext.h>

class HealthBar {
private:
    // Variables to track health
    float healthPercentage;
    float decayRate;
    float healthBarWidth;
    float healthLeft;
    float healthRight;
    float healthTop;
    float healthBottom;
    float pos_z;
public:
    int reRenderTime;
    HealthBar();
    HealthBar(float x, float y, float z, float w, float h);
    HealthBar(float x, float y, float z, float w, float h, float decayRate, int reRenderTime);
    void changeHealth(float percentage);
    void changeHealth(int time);
    void renderHealthBar();
};


#endif
