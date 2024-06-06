#ifndef MODEL_H
#define MODEL_H

#include <math.h>
#include <time.h>

#include <GL/freeglut.h>
#include <GL/glext.h>

#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#include "Face.h"
#include "Material.h"
#include "Collisional.h"

#define WIDTH 600
#define HEIGHT 600

#define INTERVAL 2

class Model: public CollisionalSphere {
private:
    std::string prefix;
    std::vector<Material> materials;
    std::map<std::string, int> map_material;

    std::vector<float *> vertices;
    std::vector<float *> texcoords;
    std::vector<float *> normals;
    std::vector<Face> faces;

    GLuint list;

    static int count_char(std::string &str, char ch);
    static bool has_double_slash(std::string &str);
    void load_material(const char *filename);
    void add_face_3v(std::string &line);
    void add_face_3vt(std::string &line);
    void add_face_3vn(std::string &line);
    void add_face_3vtn(std::string &line);
    void add_face_4v(std::string &line);
    void add_face_4vt(std::string &line);
    void add_face_4vn(std::string &line);
    void add_face_4vtn(std::string &line);

public:
    Model(double collisionRadius);
    float pos_x, pos_y, pos_z;
    float tx, ty, tz;
    float rx, ry, rz;

    void load(const char *filename);
    void draw();
    void drawCollisionMock();
    bool checkCollision(Model another);
    void collide() override;
    void collideWith(Collisional* another) override;
    // ~Model();
};


#endif
