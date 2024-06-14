#ifndef FACE_H
#define FACE_H

struct Face
{
    int edge;
    int *vertices;
    int *texcoords;
    int normal;

    Face(int edge, int *vertices, int *texcoords, int normal = -1) :
        edge(edge),
        vertices(vertices),
        texcoords(texcoords),
        normal(normal)
    {}
};

#endif
