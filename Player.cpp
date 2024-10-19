#include "player.h"
#include <math.h>
#include <glut.h>

Player::Player(float startX, float startY, float playerWidth, float playerHeight)
    : x(startX), y(startY), width(playerWidth), height(playerHeight),
    jumping(false), ducking(false), score(0), scoreMultiplier(1.0f),
    hasHigherJump(false),
    jumpHeight(450.0f), jumpSpeed(1.3f) {}

float Player::gravity = 0.9f;
void Player::jump() {
    if (!jumping && isOnGround()) {
        jumping = true;
    }
}

void Player::duck() {
    if (!ducking) {
        ducking = true;
        height /= 2;  // Shrink the player
    }
}

void Player::stopDuck() {
    if (ducking) {
        ducking = false;
        height *= 2;  // Restore the player's original height
    }
}

void Player::update() {
    if (jumping) {
        y += jumpSpeed;  // Move player up
        if (y >= jumpHeight) {
            jumping = false;  // Reached peak of jump, start falling
        }
    }
    if (!isOnGround() && !jumping) {
        y -= gravity;  // Apply gravity to bring the player down after jump
    }
    if (y < 200.0f) {
        y = 200.0f;  // Stick to the ground
    }
}

bool Player::isOnGround() {
    return y == 200.0f;
}

void Player::render() {
    // Shortened player's body (rectangle)
    glColor3f(0.6f, 0.4f, 0.2f); // Body color
    float bodyHeight = height * 0.7f; // Shortened body height
    glBegin(GL_QUADS);
    glVertex2f(x, y); // Bottom left
    glVertex2f(x + width, y); // Bottom right
    glVertex2f(x + width, y + bodyHeight); // Top right
    glVertex2f(x, y + bodyHeight); // Top left
    glEnd();

    // Outline the player's body (using lines)
    glColor3f(0.0f, 0.0f, 0.0f); // Outline color (black)
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y); // Bottom left
    glVertex2f(x + width, y); // Bottom right
    glVertex2f(x + width, y + bodyHeight); // Top right
    glVertex2f(x, y + bodyHeight); // Top left
    glEnd();

    // Draw the head (circle) raised slightly
    float headRadius = width / 4; // Set head size relative to body width
    glColor3f(0.8f, 0.6f, 0.4f); // Head color
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x + width / 2, y + bodyHeight + headRadius / 4); // Center of the circle, raised
    const int numSegments = 20; // Number of segments for the circle
    for (int i = 0; i <= numSegments; ++i) {
        float theta = 2.0f * 3.14159f * float(i) / float(numSegments); // Circle angle
        float dx = headRadius * cos(theta); // X component
        float dy = headRadius * sin(theta); // Y component
        glVertex2f(x + width / 2 + dx, y + bodyHeight + headRadius / 4 + dy); // Vertex of the circle
    }
    glEnd();

    // Outline the head (using lines)
    glColor3f(0.0f, 0.0f, 0.0f); // Outline color (black)
    glBegin(GL_LINE_LOOP);
    glVertex2f(x + width / 2, y + bodyHeight + headRadius / 4); // Center of the circle, raised
    for (int i = 0; i <= numSegments; ++i) {
        float theta = 2.0f * 3.14159f * float(i) / float(numSegments); // Circle angle
        float dx = headRadius * cos(theta); // X component
        float dy = headRadius * sin(theta); // Y component
        glVertex2f(x + width / 2 + dx, y + bodyHeight + headRadius / 4 + dy); // Vertex of the circle
    }
    glEnd();

    // Draw the arms (rectangles) angled to the side
    glColor3f(0.4f, 0.2f, 0.1f); // Arm color
    float armWidth = 15.0f; // Width of the arms
    float armHeight = 30.0f; // Height of the arms

    // Left arm
    glBegin(GL_QUADS);
    glVertex2f(x - armWidth, y + bodyHeight * 0.4); // Bottom left
    glVertex2f(x, y + bodyHeight * 0.4); // Bottom right
    glVertex2f(x, y + bodyHeight * 0.4 + armHeight); // Top right
    glVertex2f(x - armWidth, y + bodyHeight * 0.4 + armHeight); // Top left
    glEnd();

    // Right arm
    glBegin(GL_QUADS);
    glVertex2f(x + width, y + bodyHeight * 0.4); // Bottom left
    glVertex2f(x + width + armWidth, y + bodyHeight * 0.4); // Bottom right
    glVertex2f(x + width + armWidth, y + bodyHeight * 0.4 + armHeight); // Top right
    glVertex2f(x + width, y + bodyHeight * 0.4 + armHeight); // Top left
    glEnd();

    // Draw the legs (using rectangles)
    glColor3f(0.5f, 0.3f, 0.1f); // Leg color
    glBegin(GL_QUADS);
    // Left leg
    glVertex2f(x + width / 4 - 5, y); // Bottom left
    glVertex2f(x + width / 4 + 5, y); // Bottom right
    glVertex2f(x + width / 4 + 5, y - 20); // Top right
    glVertex2f(x + width / 4 - 5, y - 20); // Top left

    // Right leg
    glVertex2f(x + 3 * width / 4 - 5, y); // Bottom left
    glVertex2f(x + 3 * width / 4 + 5, y); // Bottom right
    glVertex2f(x + 3 * width / 4 + 5, y - 20); // Top right
    glVertex2f(x + 3 * width / 4 - 5, y - 20); // Top left
    glEnd();

	// hair IG
	glColor3f(1.0f, 0.84f, 0.0f); // Johnny Bravo hair color xD
    glBegin(GL_POLYGON);
    glVertex2f(x + width / 2 - 28, y + bodyHeight + headRadius / 4); // Left point of the crown
    glVertex2f(x + width / 2 - 20, y + bodyHeight + headRadius / 4 + 20); // Left point of the crown

    glVertex2f(x + width / 2, y + bodyHeight + headRadius / 4 + 30 + 15); // Top point of the crown
    glVertex2f(x + width / 2 + 20, y + bodyHeight + headRadius / 4 + 20); // Right point of the crown
    glEnd();


}






// Score management methods
void Player::increaseScore(int amount) {
    score += amount * scoreMultiplier; // Increase score by amount multiplied by multiplier
}

void Player::applyScoreMultiplier(float multiplier) {
    scoreMultiplier = multiplier; // Set the score multiplier
}

void Player::activateHigherJump() {
    hasHigherJump = true;
    gravity *= .5; // Example effect: double the jump speed
}

void Player::deactivateHigherJump() {
    hasHigherJump = false;
    gravity *= 2; // Restore the original jump speed
}

// Getter methods implementation
float Player::getX() const { return x; }
float Player::getY() const { return y; }
float Player::getWidth() const { return width; }
float Player::getHeight() const { return height; }
