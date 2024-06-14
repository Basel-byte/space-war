#include "SpaceObject.h"

class Sun: public SpaceObject
{
public:
    Sun();
    Sun(std::string name, float x, float y, float z, float r, float a, string fileName);
    void drawSubRoutine() override;
};

class Saturn: public SpaceObject
{
public:
    Saturn();
    Saturn(std::string name, float x, float y, float z, float r, float a, string fileName);
    void drawSubRoutine() override;
};