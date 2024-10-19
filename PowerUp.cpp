    #include "powerup.h"
    #include <collectible.h>
    #include <math.h>
    #include <glut.h>
    #include <Player.h>

    PowerUp::PowerUp(float x, float y, float width, float height, PowerUpType type)
        : Collectible(x, y, width, height), type(type) {}

    void PowerUp::applyEffect(int& score, float& jumpHeight, int& scoreMultiplier) {
        if (type == SCORE_MULTIPLIER) {
			Collectible::flag = 1;
            scoreMultiplier = 2;  // Temporarily doubles the score
        }
        else if (type == JUMP_BOOST) {
            Player::gravity *= 0.5f;  // Temporarily increases the jump height
        }
    }

    void PowerUp::removeEffect(int& score, float& jumpHeight, int& scoreMultiplier) {
        if (type == SCORE_MULTIPLIER) {
            Collectible::flag = 0;
            scoreMultiplier = 1;  // Reset the score multiplier
        }
        else
        {
            if (type == JUMP_BOOST)
            {
                Player::gravity *= 2.0f;
            }
        }
    }


    void PowerUp::render() {
        if (!collected) {
            float kiwiRadius = width / 3;
            float seedRadius = 2.0f;
            float centerRadius = kiwiRadius / 2;

            if (type == SCORE_MULTIPLIER) {
                // Central point for rotation
                float angle = glutGet(GLUT_ELAPSED_TIME) * 0.05f;  // Slow rotation speed

                // Draw the central rotating point (white dot)
                glColor3f(1.0f, 1.0f, 1.0f);  // White color for the central dot
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(x + width / 2, y + height / 2);  // Center point for the dot
                float dotRadius = 5.0f;  // Radius for the dot
                int numSegments = 100;  // Number of segments for smoothness
                for (int i = 0; i <= numSegments; i++) {
                    float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
                    float dx = dotRadius * cos(theta);
                    float dy = dotRadius * sin(theta);
                    glVertex2f(x + width / 2 + dx, y + height / 2 + dy);
                }
                glEnd();

                // Orbiting green kiwi 1
                glPushMatrix();  // Save current state
                glTranslatef(x + width / 2, y + height / 2, 0.0f);  // Move to center
                glRotatef(angle, 0.0f, 0.0f, 1.0f);  // Rotate around the Z-axis
                float orbitRadius = 30.0f;  // Orbit radius for kiwi

                // Draw kiwi 1
                glColor3f(0.0f, 1.0f, 0.0f);  // Green kiwi
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(orbitRadius, 0.0f);  // Kiwi center
                for (int i = 0; i <= numSegments; i++) {
                    float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
                    float dx = kiwiRadius * cos(theta);  // X coordinate
                    float dy = kiwiRadius * sin(theta);  // Y coordinate
                    glVertex2f(orbitRadius + dx, dy);  // Offset by orbitRadius
                }
                glEnd();

                // Draw seeds around kiwi 1 (rotating)
                float seedOrbitRadius = kiwiRadius * 0.8f;  // Radius for seed orbit
                for (int i = 0; i < 6; i++) {
                    float seedAngle = (i * 60.0f) * (3.1415926f / 180.0f);  // Seed angles
                    float seedX = seedOrbitRadius * cos(seedAngle);
                    float seedY = seedOrbitRadius * sin(seedAngle);

                    glColor3f(0.0f, 0.0f, 0.0f);  // Black color for seeds
                    glBegin(GL_TRIANGLE_FAN);
                    glVertex2f(orbitRadius + seedX, seedY);  // Seed position
                    for (int j = 0; j <= numSegments; j++) {
                        float theta = 2.0f * 3.1415926f * float(j) / float(numSegments);
                        float dx = seedRadius * cos(theta);
                        float dy = seedRadius * sin(theta);
                        glVertex2f(orbitRadius + seedX + dx, seedY + dy);  // Draw seed
                    }
                    glEnd();
                }
                glPopMatrix();  // Restore state

                // Orbiting green kiwi 2 (opposite direction)
                glPushMatrix();  // Save current state
                glTranslatef(x + width / 2, y + height / 2, 0.0f);  // Move to center
                glRotatef(-angle, 0.0f, 0.0f, 1.0f);  // Rotate opposite

                // Draw kiwi 2
                glColor3f(0.0f, 1.0f, 0.0f);  // Green kiwi
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(orbitRadius, 0.0f);  // Kiwi center
                for (int i = 0; i <= numSegments; i++) {
                    float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
                    float dx = kiwiRadius * cos(theta);  // X coordinate
                    float dy = kiwiRadius * sin(theta);  // Y coordinate
                    glVertex2f(orbitRadius + dx, dy);  // Offset by orbitRadius
                }
                glEnd();

                // Draw seeds around kiwi 2 (rotating in opposite direction)
                for (int i = 0; i < 6; i++) {
                    float seedAngle = (i * 60.0f) * (3.1415926f / 180.0f);
                    float seedX = seedOrbitRadius * cos(seedAngle);
                    float seedY = seedOrbitRadius * sin(seedAngle);

                    glColor3f(0.0f, 0.0f, 0.0f);  // Black color for seeds
                    glBegin(GL_TRIANGLE_FAN);
                    glVertex2f(orbitRadius + seedX, seedY);
                    for (int j = 0; j <= numSegments; j++) {
                        float theta = 2.0f * 3.1415926f * float(j) / float(numSegments);
                        float dx = seedRadius * cos(theta);
                        float dy = seedRadius * sin(theta);
                        glVertex2f(orbitRadius + seedX + dx, seedY + dy);
                    }
                    glEnd();
                }
                glPopMatrix();  // Restore state
            }

            else if (type == JUMP_BOOST) {
                // Draw the golden kiwi fruit (as before)
                float kiwiRadius = width / 3;  // Smaller radius for the kiwi
                glColor3f(1.0f, 0.84f, 0.0f);  // Golden color for kiwi
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(x + width / 2, y + height / 2);  // Center point for the circle

                int numSegments = 100;  // Number of segments to make the circle smooth
                for (int i = 0; i <= numSegments; i++) {
                    float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
                    float dx = kiwiRadius * cos(theta);
                    float dy = kiwiRadius * sin(theta);
                    glVertex2f(x + width / 2 + dx, y + height / 2 + dy);
                }
                glEnd();

                // Draw the white center of the kiwi
                //float centerRadius = kiwiRadius / 2;  // Smaller radius for the center
                glColor3f(1.0f, 1.0f, 1.0f);  // White color for the center
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(x + width / 2, y + height / 2);  // Center point for the inner circle

                for (int i = 0; i <= numSegments; i++) {
                    float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
                    float dx = centerRadius * cos(theta);
                    float dy = centerRadius * sin(theta);
                    glVertex2f(x + width / 2 + dx, y + height / 2 + dy);
                }
                glEnd();

                // Draw the seeds
                glColor3f(0.0f, 0.0f, 0.0f);  // Black color for the seeds
               // float seedRadius = 2.0f;  // Radius of the seeds
                for (int i = 0; i < 6; i++) {
                    float angle = (i * 60.0f) * (3.1415926f / 180.0f);
                    float seedX = (centerRadius * 0.7) * cos(angle);
                    float seedY = (centerRadius * 0.7) * sin(angle);

                    glBegin(GL_TRIANGLE_FAN);
                    glVertex2f(x + width / 2 + seedX, y + height / 2 + seedY);
                    for (int j = 0; j <= numSegments; j++) {
                        float theta = 2.0f * 3.1415926f * float(j) / float(numSegments);
                        float dx = seedRadius * cos(theta);
                        float dy = seedRadius * sin(theta);
                        glVertex2f(x + width / 2 + seedX + dx, y + height / 2 + seedY + dy);
                    }
                    glEnd();
                }

                // Draw the wings with a flapping effect
                float wingHeight = 30.0f;  // Height of the wings
                float wingWidth = 20.0f;   // Width of the wings
                float wingYPosition = y + height / 2 + (sin(glutGet(GLUT_ELAPSED_TIME) * 0.005) * 10);  // Flapping effect

                // Left wing
                glColor3f(1.0f, 1.0f, 1.0f);  // White color for the wings
                glBegin(GL_TRIANGLES);
                glVertex2f(x + width / 2 - wingWidth - 5.0f, wingYPosition);  // Left tip
                glVertex2f(x + width / 2 - wingWidth - 15.0f, wingYPosition - wingHeight); // Bottom left
                glVertex2f(x + width / 2 - wingWidth - 5.0f, wingYPosition - wingHeight); // Bottom right
                glEnd();

                // Right wing with up-and-down rotation
                glBegin(GL_TRIANGLES);
                glVertex2f(x + width / 2 + wingWidth + 5.0f, wingYPosition);  // Right tip
                glVertex2f(x + width / 2 + wingWidth + 15.0f, wingYPosition - wingHeight); // Bottom left
                glVertex2f(x + width / 2 + wingWidth + 5.0f, wingYPosition - wingHeight); // Bottom right
                glEnd();
            }
        }
    }
