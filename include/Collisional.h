#pragma once

class Collisional {
public:
    /// @brief The collision action when the object collides with another object
    virtual void collide() = 0;

    /// @brief The collision action when the object collides with another object
    /// @param other The other object that this object is colliding with
    virtual void collideWith(Collisional* other) = 0;

    /// @brief Check if the object is colliding with another object
    /// @param other The other object that we are checking for collision
    /// @return true if the object is colliding with the other object, false otherwise
    bool isCollidingWith(Collisional* other);

    double getColCenterX() { return colCenterX; }
    double getColCenterY() { return colCenterY; }
    double getColCenterZ() { return colCenterZ; }

    void setCollisionCenterAsCurrent();
    virtual void drawCollisionMock() = 0;

protected:
double colCenterX, colCenterY, colCenterZ;
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

    double getColRadius() { return colRadius; }

    void drawCollisionMock() override;

protected:
    double colRadius;
};

/// @brief A class representing a box
class CollisionalBox : public Collisional {
public:
    // /// @brief Check if the box is colliding with another object
    // /// @param other The other object that we are checking for collision
    // /// @return true if the box is colliding with the other object, false otherwise
    // bool isCollidingWith(Collisional* other) override;

    /// @brief Check if the box is colliding with a sphere
    /// @param other The sphere that we are checking for collision
    /// @return true if the box is colliding with the sphere, false otherwise
    bool isCollidingWith(CollisionalSphere* other);

    /// @brief Check if the box is colliding with another box
    /// @param other The other box that we are checking for collision
    /// @return true if the box is colliding with the other box, false otherwise
    bool isCollidingWith(CollisionalBox* other);

    double getColWidth() { return colWidth; }
    double getColHeight() { return colHeight; }
    double getColDepth() { return colDepth; }

    void drawCollisionMock() override;

protected:
    double colWidth, colHeight, colDepth;
};