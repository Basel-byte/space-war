#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/freeglut.h>

struct Material {
    float *ambient;
    float *diffuse;
    float *specular;
    GLuint texture;

    Material(float *ambient, float *diffuse, float *specular) :
        ambient(ambient),
        diffuse(diffuse),
        specular(specular),
        texture(0)
    {}
};
#endif
