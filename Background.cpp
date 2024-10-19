#include "background.h"
#include <glut.h>
#include <cstdlib>
#include <cmath>

float Background::speed = 1.0f; // Initialize the speed of the background
int Background::collision = 0;

Background::Background(float groundHeight)
    : groundHeight(groundHeight) {
    // Initialize clouds and trees
    for (int i = 0; i < 4; ++i) {
        cloudX.push_back(rand() % 1280);
        treeX.push_back(rand() % 1280);
    }
}

void Background::updateClouds() {

    if (collision == 0)
    {
        for (size_t i = 0; i < cloudX.size(); ++i) {
            cloudX[i] -= speed; // Move cloud to the left
            if (cloudX[i] < -100) { // Reset cloud position
                cloudX[i] = 1280 + rand() % 100; // Randomly respawn
            }
        }
    }
    else {
		
        for (size_t i = 0; i < cloudX.size(); ++i) {
            cloudX[i] += 350; // Move cloud to the left
            if (cloudX[i] < -100) { // Reset cloud position
                cloudX[i] = 1280 + rand() % 100; // Randomly respawn
            }
        }
    }
}

void Background::updateTrees() {

    if (collision == 0)
    {
        for (size_t i = 0; i < treeX.size(); ++i) {
            treeX[i] -= speed; // Move cloud to the left
            if (treeX[i] < -100) { // Reset cloud position
                treeX[i] = 1280 + rand() % 100; // Randomly respawn
            }
        }
    }
    else {

        for (size_t i = 0; i < treeX.size(); ++i) {
            treeX[i] += 350; // Move cloud to the left
            if (treeX[i] < -100) { // Reset cloud position
                treeX[i] = 1280 + rand() % 100; // Randomly respawn
            }
        }
        collision = 0;
    }
}

void Background::update() {
    updateClouds(); // Update the positions of clouds
    updateTrees();  // Update the positions of trees
}

void Background::drawCloud(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f); // White color for clouds
    // Draw a simple cloud using circles (or you can use ellipses)
    for (int i = -20; i <= 20; i += 10) {
        for (int j = -10; j <= 10; j += 10) {
            float distance = sqrt(i * i + j * j);
            if (distance <= 20) { // Only draw within the radius
                glBegin(GL_POLYGON);
                for (int k = 0; k < 20; ++k) {
                    float angle = 2.0f * 3.14159f * k / 20; // Circle approximation
                    glVertex2f(x + i + cos(angle) * 10, y + j + sin(angle) * 10);
                }
                glEnd();
            }
        }
    }
}

void Background::drawTree(float x, float y) {
    // Draw the trunk
    glColor3f(0.5f, 0.25f, 0.1f); // Brown color for the trunk
    glBegin(GL_QUADS);
    glVertex2f(x - 15, y);        // Bottom left
    glVertex2f(x + 15, y);        // Bottom right
    glVertex2f(x + 15, y + 60);   // Top right
    glVertex2f(x - 15, y + 60);   // Top left
    glEnd();

    // Draw the leaves (tree top)
    glColor3f(0.0f, 0.5f, 0.0f); // Green color for leaves
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 60, y + 60);   // Left point of leaves
    glVertex2f(x + 60, y + 60);   // Right point of leaves
    glVertex2f(x, y + 120);        // Top point of leaves
    glEnd();
}

void Background::drawSun(float x, float y) {
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow color for the sun
    glBegin(GL_POLYGON);
    for (int k = 0; k < 20; ++k) {
        float angle = 2.0f * 3.14159f * k / 20; // Circle approximation
        glVertex2f(x + cos(angle) * 30, y + sin(angle) * 30);
    }
    glEnd();
}

void Background::render() {
    // Render the sky
    glColor3f(0.5f, 0.8f, 1.0f);  // Light blue color for the sky
    glBegin(GL_QUADS);
    glVertex2f(0.0f, groundHeight);  // From ground height upwards
    glVertex2f(1280.0f, groundHeight);
    glVertex2f(1280.0f, 720.0f);    // Top of the window
    glVertex2f(0.0f, 720.0f);
    glEnd();

    // Render the ground
    glColor3f(0.3f, 0.7f, 0.3f);  // Green color for the ground
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 0.0f);  // Bottom of the screen
    glVertex2f(1280.0f, 0.0f);
    glVertex2f(1280.0f, groundHeight);  // Up to the ground height
    glVertex2f(0.0f, groundHeight);
    glEnd();

    // Render clouds
    for (const auto& x : cloudX) {
        drawCloud(x, 500); // Example y-coordinate for clouds
    }

    // Render trees
    for (const auto& x : treeX) {
        drawTree(x, groundHeight); // Draw trees at ground height
    }

    // Draw the sun
    drawSun(100, 600); // Position the sun in the sky
}
