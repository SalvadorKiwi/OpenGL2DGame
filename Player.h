// player.h
#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    // Constructor to initialize player position, size, and state
    Player(float x, float y, float width, float height);
    void jump();
    void duck();
    void stopDuck();
    void update();
    void render();
    bool isOnGround();

    // Getter methods for position and dimensions
    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;

    void increaseScore(int amount); // Increase score method
    void applyScoreMultiplier(float multiplier); // Apply score multiplier
    void activateHigherJump(); // Activate higher jump
    void deactivateHigherJump(); // Deactivate higher jump
    static float gravity;

private:
    float x, y;
    float width, height;
    bool jumping;
    bool ducking;
    float jumpHeight;
    float jumpSpeed;

    int score; // Player's score
    float scoreMultiplier; // Score multiplier for power-ups
    bool hasHigherJump; // Flag for higher jump effect
};

#endif
