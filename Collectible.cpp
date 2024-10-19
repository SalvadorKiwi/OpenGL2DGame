#include "collectible.h"
#include <glut.h>

Collectible::Collectible(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height), collected(false) {}


int Collectible::flag = 0;

void Collectible::render() {
    if (!collected) {
        glColor3f(1.0f, 0.85f, 0.0f);  // Yellow color for the collectible
        glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
        glEnd();
    }
}

bool Collectible::checkCollision(float playerX, float playerY, float playerWidth, float playerHeight) {
    if (!collected && playerX < x + width && playerX + playerWidth > x &&
        playerY < y + height && playerY + playerHeight > y) {
        collected = true;
        return true;
    }
    return false;
}

void Collectible::applyEffect(int& score) {
    // Adds 25 to the score
    if (flag == 0) {
        score += 25;
	}
	else {
		score += 50;
	}
}

// Getters and setters for x and y
float Collectible::getX() const { return x; }
float Collectible::getY() const { return y; }
void Collectible::setX(float newX) { x = newX; }
void Collectible::setY(float newY) { y = newY; }
