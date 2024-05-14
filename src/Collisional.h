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
    virtual bool isCollidingWith(Collisional* other) = 0;
};

/// @brief A class representing a sphere
class Sphere : public Collisional {
public:
    float radius;
    float centerX, centerY, centerZ;

    /// @brief The collision action when the sphere collides with another object
    virtual void collide() override;
    
    /// @brief The collision action when the sphere collides with another object
    /// @param other The other object that the sphere is colliding with
    virtual void collideWith(Collisional* other) override;

    /// @brief Check if the sphere is colliding with another object
    /// @param other The other object that we are checking for collision
    /// @return true if the sphere is colliding with the other object, false otherwise
    bool isCollidingWith(Collisional* other) override;

    /// @brief Check if the sphere is colliding with another sphere
    /// @param other The other sphere that we are checking for collision
    /// @return true if the sphere is colliding with the other sphere, false otherwise
    bool isCollidingWith(Sphere* other);

    /// @brief Check if the sphere is colliding with a box
    /// @param other The box that we are checking for collision
    /// @return true if the sphere is colliding with the box, false otherwise
    bool isCollidingWith(Box* other);
};

/// @brief A class representing a box
class Box : public Collisional {
public:
    float centerX, centerY, centerZ;
    float width, height, depth;

    /// @brief The collision action when the box collides with another object
    virtual void collide() override;
    
    /// @brief The collision action when the box collides with another object
    /// @param other The other object that the box is colliding with
    virtual void collideWith(Collisional* other) override;

    /// @brief Check if the box is colliding with another object
    /// @param other The other object that we are checking for collision
    /// @return true if the box is colliding with the other object, false otherwise
    bool isCollidingWith(Collisional* other) override;

    /// @brief Check if the box is colliding with a sphere
    /// @param other The sphere that we are checking for collision
    /// @return true if the box is colliding with the sphere, false otherwise
    bool isCollidingWith(Sphere* other);

    /// @brief Check if the box is colliding with another box
    /// @param other The other box that we are checking for collision
    /// @return true if the box is colliding with the other box, false otherwise
    bool isCollidingWith(Box* other);
};