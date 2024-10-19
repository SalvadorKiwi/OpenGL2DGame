#include "collectible.h"
#include <stdlib.h>
#include <math.h>
#include <glut.h>

Collectible::Collectible(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height), collected(false) {}


int Collectible::flag = 0;


void Collectible::render() {
    if (!collected) {
        // Animation for floating effect (using a sine wave for vertical movement)
        float animationOffset = sin(glutGet(GLUT_ELAPSED_TIME) / 200.0f) * 5.0f;  // Floating effect

        // Kiwi slice properties
        float centerX = x + width / 2.0f;
        float centerY = y + height / 2.0f + animationOffset;
        float radius = width / 2.0f;

        // Outer brown ring of the kiwi (using GL_LINE_LOOP)
        glColor3f(0.6f, 0.3f, 0.0f);  // Brown color for the outer ring
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i <= 30; i++) {
            float theta = 2.0f * 3.1415926f * float(i) / float(30);
            float dx = radius * cosf(theta);
            float dy = radius * sinf(theta);
            glVertex2f(centerX + dx, centerY + dy);
        }
        glEnd();

        // Kiwi body (using GL_TRIANGLE_FAN)
        glColor3f(0.0f, 1.0f, 0.0f);  // Green color for the kiwi flesh
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(centerX, centerY);  // Center of the circle
        for (int i = 0; i <= 30; i++) {
            float theta = 2.0f * 3.1415926f * float(i) / float(30);
            float dx = radius * cosf(theta);
            float dy = radius * sinf(theta);
            glVertex2f(centerX + dx, centerY + dy);
        }
        glEnd();

        // Kiwi seeds (using GL_POINTS)
        glColor3f(0.0f, 0.0f, 0.0f);  // Black color for the seeds
        glBegin(GL_POINTS);
        for (int i = 0; i < 10; i++) {
            float theta = 2.0f * 3.1415926f * float(i) / float(10);
            float seedRadius = radius * 0.6f;  // Seeds placed inside the kiwi
            float dx = seedRadius * cosf(theta);
            float dy = seedRadius * sinf(theta);
            glVertex2f(centerX + dx, centerY + dy);
        }
        glEnd();
    }
}

// Method to animate the collectible's position
void Collectible::updatePosition() {
    // Here, you can include more advanced movement logic, but for now, we keep it simple with just oscillation.
    y += sin(glutGet(GLUT_ELAPSED_TIME) / 200.0f) * 0.5f;  // Slow floating up and down
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
