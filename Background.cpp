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
    if (collision == 0) {
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
    if (collision == 0) {
        for (size_t i = 0; i < treeX.size(); ++i) {
            treeX[i] -= speed; // Move tree to the left
            if (treeX[i] < -100) { // Reset tree position
                treeX[i] = 1280 + rand() % 100; // Randomly respawn
            }
        }
    }
    else {
        for (size_t i = 0; i < treeX.size(); ++i) {
            treeX[i] += 350; // Move tree to the left
            if (treeX[i] < -100) { // Reset tree position
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

    // Draw sun rays
    glColor3f(1.0f, 1.0f, 0.0f); // Yellow color for rays
    for (int k = 0; k < 12; ++k) { // Draw 12 rays
        float angle = k * (2.0f * 3.14159f / 12);
        float startX = x + cos(angle) * 30; // Start at sun's edge
        float startY = y + sin(angle) * 30;
        float endX = x + cos(angle) * 50; // End point of ray
        float endY = y + sin(angle) * 50;

        glBegin(GL_LINES);
        glVertex2f(startX, startY);
        glVertex2f(endX, endY);
        glEnd();
    }
}

void Background::drawGroundTexture() {
    glColor3f(0.2f, 0.5f, 0.2f); // A slightly darker green for the texture
    glPointSize(3.0f); // Set the point size

    glBegin(GL_POINTS);
    for (float x = 0; x < 1280; x += 20) { // Adjust the spacing as needed
        for (float y = 0; y < groundHeight; y += 10) { // Adjust the spacing as needed
            glVertex2f(x + rand() % 10 - 5, y + rand() % 10 - 5); // Random offset for a more natural look
        }
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

    drawGroundTexture();

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

    // Outline the ground
    glColor3f(0.0f, 0.0f, 0.0f); // Black color for outline
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(1280.0f, 0.0f);
    glVertex2f(1280.0f, groundHeight);
    glVertex2f(0.0f, groundHeight);
    glEnd();

    
}
