#ifndef POWERUP_H
#define POWERUP_H

#include "collectible.h"

class PowerUp : public Collectible {
public:
    // PowerUp type enumeration
    enum PowerUpType { SCORE_MULTIPLIER, JUMP_BOOST };

    // Constructor to initialize PowerUp with type
    PowerUp(float x, float y, float width, float height, PowerUpType type);

    // Override applyEffect to implement PowerUp effects
    void applyEffect(int& score, float& jumpHeight, int& scoreMultiplier);

	void removeEffect(int& score, float& jumpHeight, int& scoreMultiplier);

    // Function to render the PowerUp (different from Collectible)
    void render() override;

private:
    PowerUpType type;  // Type of power-up (score multiplier or jump boost)
};

#endif
