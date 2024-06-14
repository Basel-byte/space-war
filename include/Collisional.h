#pragma once
#include <string>

enum CollisionType {
    PLAYER,
    ENEMY,
    PLANET,
    MISSILE,
    HEALTH_PICKABLE,
    MISSILE_PICKABLE
};

std::string generateRandomString();

class Collisional {
public:
    std::string id = generateRandomString();
    bool isCollided = false;
    
    /// @brief The collision action when the object collides with another object
    virtual void collide() = 0;

    /// @brief The collision action when the object collides with another object
    /// @param other The other object that this object is colliding with
    virtual void collideWith(Collisional* other, CollisionType type) = 0;

    /// @brief Check if the object is colliding with another object
    /// @param other The other object that we are checking for collision
    /// @return true if the object is colliding with the other object, false otherwise
    bool isCollidingWith(Collisional* other);

    float getColCenterY() { return colCenterY; }
    float getColCenterX() { return colCenterX; }
    float getColCenterZ() { return colCenterZ; }

    void setCollisionCenterAsCurrent();
    virtual void drawCollisionMock() = 0;

protected:
float colCenterX, colCenterY, colCenterZ;
};

class CollisionalSphere;
class CollisionalBox;

/// @brief A class representing a sphere
class CollisionalSphere : public Collisional {
public:
    // /// @brief Check if the sphere is colliding with another object
    // /// @param other The other object that we are checking for collision
    // /// @return true if the sphere is colliding with the other object, false otherwise
    // bool isCollidingWith(Collisional* other) override;

    /// @brief Check if the sphere is colliding with another sphere
    /// @param other The other sphere that we are checking for collision
    /// @return true if the sphere is colliding with the other sphere, false otherwise
    bool isCollidingWith(CollisionalSphere* other);

    /// @brief Check if the sphere is colliding with a box
    /// @param other The box that we are checking for collision
    /// @return true if the sphere is colliding with the box, false otherwise
    bool isCollidingWith(CollisionalBox* other);

    float getColRadius() { return colRadius; }

    void drawCollisionMock() override;

protected:
    float colRadius;
};

/// @brief A class representing a box
class CollisionalBox : public Collisional {
public:
    // /// @brief Check if the box is colliding with another object
    // /// @param other The other object that we are checking for collision
    // /// @return true if the box is colliding with the other object, false otherwise
    // bool isCollidingWith(Collisional* other) override;

    CollisionalBox(double colWidth, double colHeight, double colDepth, double colRotationY);

    /// @brief Check if the box is colliding with a sphere
    /// @param other The sphere that we are checking for collision
    /// @return true if the box is colliding with the sphere, false otherwise
    bool isCollidingWith(CollisionalSphere* other);

    /// @brief Check if the box is colliding with another box
    /// @param other The other box that we are checking for collision
    /// @return true if the box is colliding with the other box, false otherwise
    bool isCollidingWith(CollisionalBox* other);

    float getColWidth() { return colWidth; }
    float getColHeight() { return colHeight; }
    float getColDepth() { return colDepth; }
    float getColRotationY() { return colRotationY; }

    void drawCollisionMock() override;

protected:
    float colWidth, colHeight, colDepth, colRotationY;
};

void rotateY(double vertex[3], double theta);
void rotateY(float vertex[3], double theta);

// Function to multiply a point by a matrix (4x4 matrix)
void multiplyMatrixVec(const float* matrix, const float* vec, float* result);

void transformPoints(float points[][3], const float* matrix, float transformedPoints[][3]);