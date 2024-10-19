#include "player.h"
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
    glColor3f(0.6f, 0.4f, 0.2f);  // Brown color for the kiwi
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
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
