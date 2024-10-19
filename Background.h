#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <vector>

class Background {
public:
    // Constructor
    Background(float groundHeight);

    // Function to render the background
    void render();

    // Function to update the positions of clouds and trees
    void update();

    static float speed;
	static int collision;
private:

    float groundHeight;                 // Height of the ground
    std::vector<float> cloudX;         // Store cloud positions
    std::vector<float> treeX;          // Store tree positions

    void updateClouds();                // Update cloud positions
    void updateTrees();                 // Update tree positions
    void drawTree(float x, float y);   // Draw individual trees
    void drawCloud(float x, float y);   // Draw individual clouds
    void drawSun(float x, float y);     // Draw the sun
    void drawGroundTexture();
};

#endif // BACKGROUND_H
