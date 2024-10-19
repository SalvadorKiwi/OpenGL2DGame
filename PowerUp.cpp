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
            float orbitRadius = kiwiRadius * 3.0f;
            float seedOrbitRadius = kiwiRadius * 0.8f;

            // Define numSegments for smooth circles
            int numSegments = 100;  // Adjust the number for smoother or more jagged circles

            if (type == SCORE_MULTIPLIER) {
                // Central point for rotation
                float angle = glutGet(GLUT_ELAPSED_TIME) * 0.05f;  // Slow rotation speed

                // Brown border around the kiwi (outer circle)
                glColor3f(0.55f, 0.27f, 0.07f);  // Brown color
                glBegin(GL_LINE_LOOP);
                for (int i = 0; i <= numSegments; i++) {
                    float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
                    float dx = (kiwiRadius + 2.0f) * cos(theta);  // Slightly larger radius for border
                    float dy = (kiwiRadius + 2.0f) * sin(theta);
                    glVertex2f(x + width / 2 + dx, y + height / 2 + dy);
                }
                glEnd();

                // Draw the kiwi itself (green inner circle)
                glColor3f(0.0f, 1.0f, 0.0f);  // Green kiwi
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(x + width / 2, y + height / 2);
                for (int i = 0; i <= numSegments; i++) {
                    float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
                    float dx = kiwiRadius * cos(theta);
                    float dy = kiwiRadius * sin(theta);
                    glVertex2f(x + width / 2 + dx, y + height / 2 + dy);
                }
                glEnd();

                // White center of the kiwi
                glColor3f(1.0f, 1.0f, 1.0f);  // White center
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(x + width / 2, y + height / 2);
                for (int i = 0; i <= numSegments; i++) {
                    float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
                    float dx = centerRadius * cos(theta);
                    float dy = centerRadius * sin(theta);
                    glVertex2f(x + width / 2 + dx, y + height / 2 + dy);
                }
                glEnd();

                // Seeds (use points)
                float seedOrbitRadius = kiwiRadius * 0.8f;
                glColor3f(0.0f, 0.0f, 0.0f);  // Black seeds
                glPointSize(5.0f);  // Set point size for seeds
                glBegin(GL_POINTS);
                for (int i = 0; i < 6; i++) {
                    float seedAngle = (i * 60.0f) * (3.1415926f / 180.0f);
                    float seedX = seedOrbitRadius * cos(seedAngle);
                    float seedY = seedOrbitRadius * sin(seedAngle);
                    glVertex2f(x + width / 2 + seedX, y + height / 2 + seedY);  // Draw seed as a point
                }
                glEnd();

                // Repeat the same steps for the second kiwi with reverse rotation
                glPushMatrix();
                glTranslatef(x + width / 2, y + height / 2, 0.0f);
                glRotatef(-angle, 0.0f, 0.0f, 1.0f);

                // Draw the brown border around the second kiwi
                glColor3f(0.55f, 0.27f, 0.07f);  // Brown color
                glBegin(GL_LINE_LOOP);
                for (int i = 0; i <= numSegments; i++) {
                    float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
                    float dx = (kiwiRadius + 2.0f) * cos(theta);  // Slightly larger radius for border
                    float dy = (kiwiRadius + 2.0f) * sin(theta);
                    glVertex2f(orbitRadius + dx, dy);
                }
                glEnd();

                // Draw the second kiwi (green inner circle)
                glColor3f(0.0f, 1.0f, 0.0f);
                glBegin(GL_TRIANGLE_FAN);
                for (int i = 0; i <= numSegments; i++) {
                    float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
                    float dx = kiwiRadius * cos(theta);
                    float dy = kiwiRadius * sin(theta);
                    glVertex2f(orbitRadius + dx, dy);
                }
                glEnd();

                // Seeds (as points for second kiwi)
                glColor3f(0.0f, 0.0f, 0.0f);
                glPointSize(5.0f);
                glBegin(GL_POINTS);
                for (int i = 0; i < 6; i++) {
                    float seedAngle = (i * 60.0f) * (3.1415926f / 180.0f);
                    float seedX = seedOrbitRadius * cos(seedAngle);
                    float seedY = seedOrbitRadius * sin(seedAngle);
                    glVertex2f(orbitRadius + seedX, seedY);  // Draw seed as a point
                }
                glEnd();

                glPopMatrix();
            }

            // Jump boost power-up logic (same logic for kiwi, seeds, and border as above)
            if (type == JUMP_BOOST) {
                // Wing flapping logic
                float flapAngle = 20.0f * sin(glutGet(GLUT_ELAPSED_TIME) * 0.01f);  // Wing flap angle

                // Draw wings
                glPushMatrix();
                glTranslatef(x + width / 2, y + height / 2, 0.0f);

                // Left wing
                glPushMatrix();
                glRotatef(flapAngle, 0.0f, 0.0f, 1.0f);  // Flap rotation for left wing
                glColor3f(0.9f, 0.9f, 0.9f);  // Light grey wings
                glBegin(GL_TRIANGLES);
                glVertex2f(-kiwiRadius, 0.0f);           // Kiwi center
                glVertex2f(-kiwiRadius - 20.0f, 10.0f);  // Left wing top
                glVertex2f(-kiwiRadius - 20.0f, -10.0f); // Left wing bottom
                glEnd();
                glPopMatrix();

                // Right wing
                glPushMatrix();
                glRotatef(-flapAngle, 0.0f, 0.0f, 1.0f);  // Flap rotation for right wing
                glColor3f(0.9f, 0.9f, 0.9f);  // Light grey wings
                glBegin(GL_TRIANGLES);
                glVertex2f(kiwiRadius, 0.0f);            // Kiwi center
                glVertex2f(kiwiRadius + 20.0f, 10.0f);   // Right wing top
                glVertex2f(kiwiRadius + 20.0f, -10.0f);  // Right wing bottom
                glEnd();
                glPopMatrix();

                glPopMatrix(); // End of wing drawing

                // Draw the kiwi itself (golden for jump boost)
                glColor3f(1.0f, 0.84f, 0.0f);  // Golden kiwi
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(x + width / 2, y + height / 2);
                for (int i = 0; i <= numSegments; i++) {
                    float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
                    float dx = kiwiRadius * cos(theta);
                    float dy = kiwiRadius * sin(theta);
                    glVertex2f(x + width / 2 + dx, y + height / 2 + dy);
                }
                glEnd();

                // White center of the kiwi
                glColor3f(1.0f, 1.0f, 1.0f);  // White center
                glBegin(GL_TRIANGLE_FAN);
                glVertex2f(x + width / 2, y + height / 2);
                for (int i = 0; i <= numSegments; i++) {
                    float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
                    float dx = centerRadius * cos(theta);
                    float dy = centerRadius * sin(theta);
                    glVertex2f(x + width / 2 + dx, y + height / 2 + dy);
                }
                glEnd();

                // Seeds (as points)
                glColor3f(0.0f, 0.0f, 0.0f);  // Black seeds
                glPointSize(5.0f);  // Set point size for seeds
                glBegin(GL_POINTS);
                for (int i = 0; i < 6; i++) {
                    float seedAngle = (i * 60.0f) * (3.1415926f / 180.0f);
                    float seedX = seedOrbitRadius * cos(seedAngle);
                    float seedY = seedOrbitRadius * sin(seedAngle);
                    glVertex2f(x + width / 2 + seedX, y + height / 2 + seedY);  // Draw seed as a point
                }
                glEnd();
            }
    }
}


