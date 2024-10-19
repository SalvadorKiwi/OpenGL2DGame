#ifndef OBSTACLE_H
#define OBSTACLE_H

class Obstacle {
public:
    // Constructor to initialize obstacle position and size
    Obstacle(float x, float y, float width, float height);

    // Function to render the obstacle
    void render();

    // Move the obstacle from right to left based on speed
    void move(float speed);

    // Check if the player has collided with the obstacle
    bool checkCollision(float playerX, float playerY, float playerWidth, float playerHeight);

    // Getters and setters for position
    float getX() const;
    float getY() const;
    void setX(float newX);
    void setY(float newY);

private:
    float x, y;         // Position
    float width, height; // Size
    bool active;         // Whether the obstacle is active or has passed
};

#endif
