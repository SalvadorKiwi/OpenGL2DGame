#include "obstacle.h"
#include <stdlib.h>
#include <glut.h>

Obstacle::Obstacle(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height), active(true) {}

void Obstacle::render() {
    if (active) {
        // Randomly choose a primitive type for rendering
        if (rand() % 2 == 0) {  // 50% chance to draw a quad
            glColor3f(1.0f, 0.0f, 0.0f);  // Red color for obstacles
            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + width, y);
            glVertex2f(x + width, y + height);
            glVertex2f(x, y + height);
            glEnd();
        }
        else {  // Otherwise, draw a triangle
            glColor3f(0.0f, 0.0f, 1.0f);  // Blue color for triangles
            glBegin(GL_TRIANGLES);
            glVertex2f(x, y);
            glVertex2f(x + width / 2, y + height);
            glVertex2f(x + width, y);
            glEnd();
        }
    }
}


void Obstacle::move(float speed) {
    if (active) {
        x -= speed;  // Move the obstacle to the left
    }

    // Deactivate the obstacle if it moves off-screen
    if (x + width < 0) {
        active = false;
    }
}

bool Obstacle::checkCollision(float playerX, float playerY, float playerWidth, float playerHeight) {
    // Check for collision between the player and the obstacle
    if (active && playerX < x + width && playerX + playerWidth > x &&
        playerY < y + height && playerY + playerHeight > y) {
        return true;  // Collision detected
    }
    return false;
}

// Getters and setters for x and y
float Obstacle::getX() const { return x; }
float Obstacle::getY() const { return y; }
void Obstacle::setX(float newX) { x = newX; }
void Obstacle::setY(float newY) { y = newY; }
