#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

class Collectible {
public:
    // Constructor to initialize collectible position and size
    Collectible(float x, float y, float width, float height);

    // Function to render the collectible
    virtual void render();

    void updatePosition();

    // Check if the player has collided with the collectible
    bool checkCollision(float playerX, float playerY, float playerWidth, float playerHeight);

    // Virtual function to apply the effect (overridden by PowerUp)
    virtual void applyEffect(int& score);

    float getWidth() const { return width; }
    float getHeight() const { return height; }

    // Getters and setters for position
    float getX() const;
    float getY() const;
    void setX(float newX);
    void setY(float newY);
    static int flag;
protected:
    float x, y;         // Position
    float width, height; // Size
    bool collected;      // Whether the collectible has been collected
};

#endif
