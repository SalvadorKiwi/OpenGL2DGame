//#include <cmath> 
//#include <math.h>
//#include <time.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <random>
//#include <string>          
//#include <windows.h>     // For Windows API and PlaySound
//#include <mmsystem.h>    // For PlaySound (winmm.lib needed)
//#include <glut.h>
//
//#ifndef M_PI
//#define M_PI 3.14159265358979323846
//#endif
//
//
//// Global variables for heart properties
//double hpX = -0.9;    // Starting X position for the hearts (top-left)
//double hpY = 0.9;    // Y position for the hearts (top-left)
//double hpHeartSize = 0.003; // Size for the hearts
//double hpspacing = 0.1;;   // Space between hearts
//
//double playerScale = 0.2;  // Scale factor for player size
//double playerPosX = -0.6;   // Player X position
//double playerPosY = -0.7;   // Player Y position
//bool isJumping = false;
//bool isDucking = false;
//bool wasDucking = false; // Tracks the previous state of ducking
//
//
//
//void playBackGroundMusic() {
//    PlaySoundA("C:/Users/Ahmed Hany/Desktop/GameSound/background.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
//}
//
//void playSound(const char* filePath) {
//    PlaySoundA(filePath, NULL, SND_FILENAME | SND_ASYNC);
//}
//
//
//
//
//
//float generateRandomNumber(float min, float max) {
//    static std::random_device rd; // Seed generator
//    static std::mt19937 gen(rd()); // Mersenne Twister engine
//    std::uniform_real_distribution<float> dis(min, max);
//    return dis(gen);
//}
//
//
//// Global variables for the cactus
//double cactusBodyX = generateRandomNumber(1.0, 6.0);//X position for the cactus body
//double cactusBodyY = -0.7; // Y position for the cactus body
//double cactusBodyWidth = 0.08; // Width of the cactus body
//double cactusBodyHeight = 0.15; // Height of the cactus body //0.2
//bool cactusVisible = false; // Track if the cactus is visible
//
//// Properties for the arms
//double armWidth = 0.05; // Width of the arms
//double armHeight = 0.1; // Height of the arms
//double leftArmX = cactusBodyX - armWidth; // X position for the left arm
//double leftArmY = cactusBodyY + 0.1; // Y position for the left arm
//double rightArmX = cactusBodyX + cactusBodyWidth; // X position for the right arm
//double rightArmY = cactusBodyY + 0.1; // Y position for the right arm
//
////props for the first collectible
//double coinX = 3.0;
//double coinY = generateRandomNumber(-0.6, 0.0);
//double coinRadius = 0.05f; // Radius of the coin
//bool coinVisible = true;
//
////props for the life gain collectible
//double heartX = 15.0;
//double heartY = generateRandomNumber(-0.6, 0.0);
//double heartSize = 0.004f;
//double heartRadius = 0.05f; // Radius of the coin
//bool heartVisible = true;
//
//// Airplane Global Variables
//float airplaneX = 2.5;         // Start off-screen on the left
//float airplaneY = generateRandomNumber(-0.6, 0.0);      // Center Y position
//float airplaneWidth = 0.1f;     // Width of the airplane body
//float airplaneHeight = 0.1f;   // Height of the airplane body
//bool airplaneVisible = true;     // Visibility of the airplane
//
//
//float shieldPosX = 20.0;
//float shieldPosY = generateRandomNumber(-0.6, 0.0);
//float shieldRadius = 0.05f; // Base radius of the shield
//float shieldAnimationTime = 0.0f; // Time variable for animation
//float shieldTransparency = 0.3f; // Adjust transparency (0.0 to 1.0)
//bool shieldVisible = true;
//bool isShielded = false;
//float shieldActiveTime = 0.0f; // Time for which the shield has been active
//const float shieldDuration = 10.0; // Duration for shield activation in seconds
//
//float sunX = 0.7f;
//float sunY = 0.59;
//float sunRadius = 0.1f;
//
//
//int sunDirection = -1;
//
//
//double shoeX = 12.0;
//double shoeY = generateRandomNumber(-0.6, 0.0);
//double shoeRadius = 0.05;
//float shoeAnimationTime = 0.0f; // Time variable for animation
//bool jumpBoostVisible = true;
//bool jumpBoost = false;
//float jumpBoostActiveTime = 0.0f; // Time for which the shield has been active
//const float JumpBoostDuration = 10.0; // Duration for shield activation in seconds
//
//
//float gravity = jumpBoost ? -0.0025f : -0.004f;   // Increase gravity for a faster fall
//float jumpSpeed = jumpBoost ? 0.08 : 0.065f;   // Increase jump speed for a quicker jump
//float playerSpeedY = 0.0f;
//float duckHeight = -0.7f;
//
//double GameSpeed = 0.01f;
//
//
//
//int growth = -1;
//
//
//
//
//
//
//
//
//int currentLives = 5;
//
//bool shouldClearScreen = false;
//
//int minutes = 1;
//int seconds = 10;
//
//int currentScore = 0; // Variable to hold the current score
//
//bool lose = false;
//bool win = false;
//
//
//void keyboard(unsigned char key, int x, int y) {
//    if (key == 'w' && !isJumping) {
//        playSound("C:/Users/Ahmed Hany/Desktop/GameSound/jump.wav");
//
//        isJumping = true;
//        playerSpeedY = jumpSpeed;
//    }
//    if (key == 's') {
//        isDucking = true;
//    }
//}
//
//void keyboardUp(unsigned char key, int x, int y) {
//    if (key == 's') {
//        isDucking = false;
//    }
//}
//
//
//
//
//
//void displayGameOver(int score) {
//    playSound("C:/Users/Ahmed Hany/Desktop/GameSound/gameLose.wav");
//
//    glColor3f(1.0f, 0.0f, 0.0f); // Red color for "Game Over"
//
//    // Set the raster position for the "Game Over" text
//    glRasterPos2f(-0.1f, 0.0f); // Center it horizontally
//
//    // Render the "Game Over" message
//    const char* gameOverText = "You Lose";
//    for (const char* c = gameOverText; *c != '\0'; c++) {
//        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
//    }
//
//    // Set the raster position for the score text
//    glRasterPos2f(-0.1f, -0.2f); // Position below the "Game Over" message
//
//    // Render the score
//
//    std::string scoreText = "Score: " + std::to_string(score);
//    for (const char* c = scoreText.c_str(); *c != '\0'; c++) {
//        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
//    }
//}
//
//void YouWin(int score) {
//
//    glColor3f(1.0f, 0.0f, 0.0f); // Red color for "Game Over"
//
//    // Set the raster position for the "Game Over" text
//    glRasterPos2f(-0.1f, 0.0f); // Center it horizontally
//
//    // Render the "Game Over" message
//    const char* gameOverText = "You Win";
//    for (const char* c = gameOverText; *c != '\0'; c++) {
//        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
//    }
//
//    // Set the raster position for the score text
//    glRasterPos2f(-0.1f, -0.2f); // Position below the "Game Over" message
//
//    // Render the score
//    std::string scoreText = "Score: " + std::to_string(score);
//    for (const char* c = scoreText.c_str(); *c != '\0'; c++) {
//        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
//    }
//}
//// Function to draw a filled circle (head)
//void drawCircle(float x, float y, float radius) {
//    glBegin(GL_TRIANGLE_FAN);
//    glVertex2f(x, y); // Center of the circle
//    for (float angle = 0; angle <= 2 * M_PI; angle += 0.1) {
//        glVertex2f(x + radius * cos(angle), y + radius * sin(angle));
//    }
//    glVertex2f(x + radius * cos(0), y + radius * sin(0));
//
//    glEnd();
//}
//void drawSun() {
//    // Set the color to yellow
//    glColor3f(1.0f, 1.0f, 0.0f);
//
//    // Draw the sun as a circle
//    glBegin(GL_TRIANGLE_FAN);
//    glVertex2f(sunX, sunY); // Center of the circle
//    for (float angle = 0; angle <= 2 * M_PI; angle += 0.1) {
//        glVertex2f(sunX + sunRadius * cos(angle), sunY + sunRadius * sin(angle));
//    }
//    glVertex2f(sunX + sunRadius * cos(0), sunY + sunRadius * sin(0));
//
//    glEnd();
//
//    // Draw the sun rays
//    int numRays = 12; // Number of rays around the sun
//    float rayLength = 0.1f; // Length of each ray
//
//    for (int i = 0; i < numRays; ++i) {
//        float angle = i * (2.0f * M_PI / numRays);
//        float xStart = sunX + sunRadius * cos(angle);
//        float yStart = sunY + sunRadius * sin(angle);
//        float xEnd = sunX + (sunRadius + rayLength) * cos(angle);
//        float yEnd = sunY + (sunRadius + rayLength) * sin(angle);
//
//        glBegin(GL_LINES);
//        glVertex2f(xStart, yStart);
//        glVertex2f(xEnd, yEnd);
//        glEnd();
//    }
//}
//
//void changeSunPosition(int value) {
//    // Move the sun left or right based on the current direction
//    sunX += sunDirection * 0.001f;
//
//    // If the sun reaches -0.3, change direction to move right
//    if (sunX <= -0.3f) {
//        sunDirection = 1; // Change direction to right
//    }
//    // If the sun reaches 0.3, change direction to move left
//    else if (sunX >= 0.75f) {
//        sunDirection = -1; // Change direction to left
//    }
//
//    glutPostRedisplay(); // Request display update
//    glutTimerFunc(10, changeSunPosition, value); // Call this function again after 10 ms
//}
//
//void drawRectangle(float x, float y, float width, float height) {
//    glBegin(GL_QUADS);
//    glVertex2f(x, y);
//    glVertex2f(x + width, y);
//    glVertex2f(x + width, y + height);
//    glVertex2f(x, y + height);
//    glEnd();
//}
//// Function to draw a line (arms and legs)
//void drawLine(float x1, float y1, float x2, float y2) {
//    glBegin(GL_LINES);
//    glVertex2f(x1, y1);
//    glVertex2f(x2, y2);
//    glEnd();
//}
//// Function to draw a filled triangle (feet)
//void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
//    glBegin(GL_TRIANGLES);
//    glVertex2f(x1, y1);
//    glVertex2f(x2, y2);
//    glVertex2f(x3, y3);
//    glEnd();
//}
//
//
//
//void generatePlayerBody() {
//    // Update the player's state before drawing
//
//    // Head
//    if (jumpBoost) {
//        glColor4f(0.5f, 0.0f, 0.5f, 0.5f); // Lean purple color with transparency (50% opacity)
//    }
//    else {
//        glColor3f(0.5f, 0.3f, 0.2f); // Dark brown color for head
//    }
//
//    // Adjust head position based on ducking state
//    if (isDucking) {
//        drawCircle(playerPosX, playerPosY + 0.3f * playerScale, 0.1f * playerScale);
//    }
//    else {
//        drawCircle(playerPosX, playerPosY + 0.8f * playerScale, 0.1f * playerScale);
//    }
//
//    // Body
//    if (jumpBoost) {
//        glColor4f(0.5f, 0.0f, 0.5f, 0.5f); // Lean purple color with transparency (50% opacity)
//    }
//    else {
//        glColor3f(0.5f, 0.3f, 0.2f); // Dark brown color for body
//    }
//
//    // Adjust body position based on ducking state
//    if (isDucking) {
//        drawRectangle(playerPosX - 0.05f * playerScale, playerPosY + 0.1f * playerScale, 0.1f * playerScale, 0.2f * playerScale);
//    }
//    else {
//        drawRectangle(playerPosX - 0.05f * playerScale, playerPosY + 0.4f * playerScale, 0.1f * playerScale, 0.4f * playerScale);
//    }
//
//    // Arms
//    if (jumpBoost) {
//        glColor4f(0.5f, 0.0f, 0.5f, 0.5f); // Lean purple color with transparency (50% opacity)
//    }
//    else {
//        glColor3f(0.5f, 0.3f, 0.2f); // Dark brown color for arms
//    }
//
//    // Adjust arm position based on ducking state
//    if (isDucking) {
//        drawLine(playerPosX - 0.15f * playerScale, playerPosY + 0.2f * playerScale, playerPosX + 0.05f * playerScale, playerPosY + 0.2f * playerScale); // Left arm
//        drawLine(playerPosX + 0.05f * playerScale, playerPosY + 0.2f * playerScale, playerPosX + 0.15f * playerScale, playerPosY + 0.2f * playerScale); // Right arm
//    }
//    else {
//        drawLine(playerPosX - 0.15f * playerScale, playerPosY + 0.6f * playerScale, playerPosX + 0.05f * playerScale, playerPosY + 0.6f * playerScale); // Left arm
//        drawLine(playerPosX + 0.05f * playerScale, playerPosY + 0.6f * playerScale, playerPosX + 0.15f * playerScale, playerPosY + 0.6f * playerScale); // Right arm
//    }
//
//    // Legs
//    if (jumpBoost) {
//        glColor4f(0.5f, 0.0f, 0.5f, 0.5f); // Lean purple color with transparency (50% opacity)
//    }
//    else {
//        glColor3f(0.5f, 0.3f, 0.2f); // Dark brown color for legs
//    }
//
//    // Adjust leg length based on ducking state
//    if (isDucking) {
//        drawLine(playerPosX - 0.05f * playerScale, playerPosY + 0.1f * playerScale, playerPosX - 0.1f * playerScale, playerPosY);
//        drawLine(playerPosX + 0.05f * playerScale, playerPosY + 0.1f * playerScale, playerPosX + 0.1f * playerScale, playerPosY);
//    }
//    else {
//        drawLine(playerPosX - 0.05f * playerScale, playerPosY + 0.4f * playerScale, playerPosX - 0.1f * playerScale, playerPosY);
//        drawLine(playerPosX + 0.05f * playerScale, playerPosY + 0.4f * playerScale, playerPosX + 0.1f * playerScale, playerPosY);
//    }
//
//    // Feet (triangles)
//    if (jumpBoost) {
//        glColor4f(0.5f, 0.0f, 0.5f, 0.5f); // Lean purple color with transparency (50% opacity)
//    }
//    else {
//        glColor3f(0.5f, 0.3f, 0.2f); // Dark brown color for feet
//    }
//
//    drawTriangle(playerPosX - 0.1f * playerScale, playerPosY, playerPosX - 0.15f * playerScale, playerPosY - 0.05f * playerScale, playerPosX - 0.05f * playerScale, playerPosY - 0.05f * playerScale); // Left foot
//    drawTriangle(playerPosX + 0.1f * playerScale, playerPosY, playerPosX + 0.15f * playerScale, playerPosY - 0.05f * playerScale, playerPosX + 0.05f * playerScale, playerPosY - 0.05f * playerScale); // Right foot
//}
//
//
//
//
//void drawHeart(double x, double y, double size) {
//    // Draw the filled heart
//    glBegin(GL_TRIANGLE_FAN);
//
//    glColor3f(1.0f, 0.0f, 0.0f); // Red color for the heart
//
//    glVertex2f(x, y); // Center of the heart
//
//    for (float angle = 0; angle <= 2 * M_PI; angle += 0.01) {
//        float px = x + size * (16 * pow(sin(angle), 3)); // Heart shape equation x
//        float py = y + size * (13 * cos(angle) - 5 * cos(2 * angle) - 2 * cos(3 * angle) - cos(4 * angle)); // Heart shape equation y
//        glVertex2f(px, py);
//    }
//    glEnd();
//
//}
//void drawHeartBorder(double x, double y, double size) {
//    // Draw the border
//    glBegin(GL_LINE_LOOP); // Use LINE_LOOP for the border
//    glColor3f(0.0f, 0.0f, 0.0f); // Black color for the border
//
//    for (float angle = 0; angle <= 2 * M_PI; angle += 0.01) {
//        float px = x + size * (16 * pow(sin(angle), 3)); // Heart shape equation x
//        float py = y + size * (13 * cos(angle) - 5 * cos(2 * angle) - 2 * cos(3 * angle) - cos(4 * angle)); // Heart shape equation y
//        glVertex2f(px, py);
//    }
//    glEnd();
//}
//
//void upperBoundry(float x1, float y1, float x2, float y2) {
//    glColor3f(0.0f, 0.5f, 0.8f); // Set the color of the rectangle to dark blue
//
//    glBegin(GL_QUADS);
//    // Bottom-left corner
//    glVertex2f(x1, y1);
//
//    // Bottom-right corner
//    glVertex2f(x2, y1);
//
//    // Top-right corner
//    glVertex2f(x2, y2);
//
//    // Top-left corner
//    glVertex2f(x1, y2);
//    glEnd();
//}
//
//
//void drawFloor(double x1, double y1, double x2, double y2) {
//    glBegin(GL_LINES); // Start drawing lines
//    glColor3f(0.0f, 0.0f, 0.0f); // Set the color to black
//
//    // Specify the endpoints of the line
//    glVertex2f(x1, y1); // First endpoint
//    glVertex2f(x2, y2); // Second endpoint
//
//    glEnd(); // Finish drawing lines
//}
//void GreyBackgroundUnderFloor(double x1, double y1, double x2, double y2) {
//    glBegin(GL_QUADS); // Start drawing a rectangle
//    glColor3f(0.8f, 0.8f, 0.8f); // Grey color
//
//    // Specify the corners of the rectangle (background)
//    glVertex2f(x1, x1); // Bottom-left corner
//    glVertex2f(x2, x1);  // Bottom-right corner
//    glVertex2f(x2, y2);   // Top-right corner
//    glVertex2f(x1, y2);  // Top-left corner
//
//    glEnd();
//}
//void drawFloorAndBackground(double x1, double y1, double x2, double y2) {
//    GreyBackgroundUnderFloor(x1, y1, x2, y2); // Draw the background
//    drawFloor(x1, y1, x2, y2); // Draw the line for the floor
//}
//
//
//void displayScore(double x, double y) {
//    std::string scoreText = "Score: " + std::to_string(currentScore);
//
//    // Set position for score text
//    glRasterPos2f(x, y);
//
//    // Render the score text (assuming you have a function to render text)
//    for (char c : scoreText) {
//        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
//    }
//}
//void updateScore(int value) {
//
//    if (lose) {
//        playSound("C:/Users/Ahmed Hany/Desktop/GameSound/gameLose.wav");
//
//        displayGameOver(currentScore);       // Display "Game Over" message
//        glFlush();               // Ensure everything is displayed
//        return;
//    }
//
//    if (win) {
//        playSound("C:/Users/Ahmed Hany/Desktop/GameSound/gameWin.wav");
//        YouWin(currentScore);       // Display "Game Over" message
//        glFlush();               // Ensure everything is displayed
//        return;                  // Stop further rendering if the game is over
//    }
//
//    if (seconds == 0 && minutes == 0) {
//        return;
//    }
//
//    currentScore += value; // Increment the score by the specified value
//
//    glutPostRedisplay(); // Request a redraw to update the display
//    glutTimerFunc(100, updateScore, value); // Call this function again after 100 ms
//}
//void displayTime(double x, double y) {
//    // Set the color for the text
//    glColor3f(0.0f, 0.0f, 0.0f); // Black color for the timer text
//
//
//    // Set the raster position for the text
//    glRasterPos2f(x, y);
//
//    // Format the time as "MM:SS"
//    char timeString[6];
//    sprintf_s(timeString, sizeof(timeString), "%02d:%02d", minutes, seconds);
//
//    // Render each character of the string
//    for (char* c = timeString; *c != '\0'; c++) {
//        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
//    }
//}
//void updateTimer(int value) {
//    // Decrease the time (assuming you are managing minutes and seconds)
//    if (seconds > 0) {
//        seconds--;
//    }
//    else if (minutes > 0) {
//        minutes--;
//        seconds = 59; // Reset seconds to 59 when minutes decrease
//    }
//
//    // Update the cactus position
//
//    // Check if time is up
//    if (minutes == 0 && seconds == 0) {
//        win = true; // Set flag to clear the screen
//    }
//
//    // Request display update
//    glutPostRedisplay(); // Request display update
//    glutTimerFunc(1000, updateTimer, value); // Call this function again after 1000 ms
//}
//
//
//
//void drawCactus() {
//    if (!cactusVisible) return; // Do not draw cactus if it's not visible
//
//    // Draw the body of the cactus (rectangle)
//    glColor3f(0.2f, 0.8f, 0.2f); // Set color for the cactus (green)
//    drawRectangle(cactusBodyX, cactusBodyY, cactusBodyWidth, cactusBodyHeight); // Draw the cactus body
//
//    // Draw the left arm of the cactus (rectangle)
//    drawRectangle(leftArmX, leftArmY, armWidth, armHeight); // Draw the left arm
//
//    // Draw the right arm of the cactus (rectangle)
//    drawRectangle(rightArmX, rightArmY, armWidth, armHeight); // Draw the right arm
//}
//void resetCactus() {
//    cactusVisible = false; // Make cactus visible again
//
//    // Reset cactus position
//    cactusBodyX = generateRandomNumber(1.0, 5.0);; // Set to the initial X position
//
//    // Ensure cactus does not overlap with airplane, coin, or heart
//    if (fabs(airplaneX - cactusBodyX) < 0.5) {
//        cactusBodyX += (cactusBodyX < airplaneX) ? 0.6 : -0.6;
//    }
//    if (fabs(coinX - cactusBodyX) < 0.5) {
//        cactusBodyX += (cactusBodyX < coinX) ? 0.6 : -0.6;
//    }
//    if (fabs(heartX - cactusBodyX) < 0.5) {
//        cactusBodyX += (cactusBodyX < heartX) ? 0.6 : -0.6;
//    }
//    if (fabs(shieldPosX - cactusBodyX) < 0.5) {
//        cactusBodyX += (cactusBodyX < shieldPosX) ? 0.6 : -0.6;
//    }
//    if (fabs(shoeX - cactusBodyX) < 0.5) {
//        cactusBodyX += (cactusBodyX < shoeX) ? 0.6 : -0.6;
//    }
//}
//void ChangeCactusPosition(int value) {
//    // Move cactus towards player
//    cactusBodyX -= GameSpeed; // Move right towards player
//
//    // Update arm positions relative to the cactus body
//    leftArmX = cactusBodyX - armWidth; // X position for the left arm
//    rightArmX = cactusBodyX + cactusBodyWidth; // X position for the right arm
//
//    glutPostRedisplay(); // Request display update
//    glutTimerFunc(10, ChangeCactusPosition, value); // Call this function again after 100 ms
//}
//bool checkCollisionCactus() {
//    // Check if the cactus is visible
//    if (!cactusVisible) return false;
//
//    // Calculate player and cactus boundaries
//    double playerLeft = playerPosX - (0.1 * playerScale);
//    double playerRight = playerPosX + (0.1 * playerScale);
//    double playerBottom = playerPosY; // player's feet
//    double playerTop = playerPosY + (0.8 * playerScale); // head height
//
//    double cactusLeft = cactusBodyX;
//    double cactusRight = cactusBodyX + cactusBodyWidth;
//    double cactusBottom = cactusBodyY;
//    double cactusTop = cactusBodyY + cactusBodyHeight;
//
//    // Check for collision
//    return (playerRight > cactusLeft && playerLeft < cactusRight &&
//        playerTop > cactusBottom && playerBottom < cactusTop);
//}
//
//
//
//
//
//void drawCoin() {
//    if (!coinVisible) return; // Do not draw coin if it's not visible
//
//    coinRadius = 0.05;
//
//    // Set the base color for the coin without the glow effect
//    glColor3f(1.0f, 0.84f, 0.0f); // Standard gold color for the coin
//
//    // Draw the main circle for the coin at (coinX, coinY) with a smaller radius
//    drawCircle(coinX, coinY, coinRadius);
//
//    // Set the color for the shine lines on the coin
//    glColor3f(1.0f, 1.0f, 1.0f); // Bright white for the shine
//
//    // Draw a smaller rectangle as a detail on the coin at (coinX, coinY)
//    glColor3f(0.9f, 0.7f, 0.0f); // Darker gold color for the detail
//    drawRectangle(coinX - 0.025f, coinY - 0.005f, 0.05f, 0.01f);
//
//    // Draw the triangle on top of the rectangle
//    glColor3f(1.0f, 1.0f, 1.0f); // Color for the triangle (adjust as needed)
//    float triangleX1 = coinX - 0.025f; // Left vertex of the triangle
//    float triangleX2 = coinX + 0.025f; // Right vertex of the triangle
//    float triangleY = coinY + 0.02f; // Move the peak of the triangle higher (adjust as needed)
//
//    // Draw the triangle on top of the rectangle
//    drawTriangle(triangleX1, coinY + 0.009f, triangleX2, coinY + 0.009f, coinX, triangleY);
//}
//
//
//
//void resetCoin() {
//    coinVisible = true; // Make coin visible again
//
//
//    // Reset coin position
//    coinX = 3.0; // Set back to the initial X position
//    coinRadius = 0.05;
//    coinY = generateRandomNumber(-0.6, 0.0); // Set back to the initial Y position
//
//    // Ensure coin does not overlap with other objects
//    if (fabs(airplaneX - coinX) < 0.5) {
//        coinX += (coinX < airplaneX) ? 0.6 : -0.6;
//    }
//    if (fabs(cactusBodyX - coinX) < 0.5) {
//        coinX += (coinX < cactusBodyX) ? 0.6 : -0.6;
//    }
//    if (fabs(heartX - coinX) < 0.5) {
//        coinX += (coinX < heartX) ? 0.6 : -0.6;
//    }
//    if (fabs(shoeX - coinX) < 0.5) {
//        coinX += (coinX < shoeX) ? 0.6 : -0.6;
//    }
//    if (fabs(shieldPosX - coinX) < 0.5) {
//        coinX += (coinX < shieldPosX) ? 0.6 : -0.6;
//    }
//}
//void changeCoinPosition(int value) {
//    // Move coin towards the player
//
//
//    coinX -= GameSpeed; // Move left towards player
//
//
//    if (coinVisible) {
//        coinRadius += growth * 0.0003; // Adjust the radius based on growth 
//
//        // Check radius limits and change growth 
//        if (coinRadius >= 0.07f) { // Max radius
//            growth = -1; // Start shrinking
//        }
//        else if (coinRadius <= 0.05f) { // Min radius
//            growth = 1; // Start growing
//        }
//    }
//
//
//    glutPostRedisplay(); // Request display update
//    glutTimerFunc(10, changeCoinPosition, value); // Call this function again after 100 ms
//}
//bool checkCollisionCoin() {
//    if (!coinVisible) return false;
//
//    // Calculate player boundaries
//    double playerLeft = playerPosX - (0.1 * playerScale);
//    double playerRight = playerPosX + (0.1 * playerScale);
//    double playerBottom = playerPosY; // Player's feet
//    double playerTop;
//
//    // Adjust the player's top boundary based on whether the player is ducking or not
//    if (isDucking) {
//        playerTop = playerPosY + (0.4 * playerScale); // Reduced height for ducking
//    }
//    else {
//        playerTop = playerPosY + (0.8 * playerScale); // Normal height
//    }
//    // Calculate coin boundaries using the coinRadius
//    double coinLeft = coinX - coinRadius;
//    double coinRight = coinX + coinRadius;
//    double coinBottom = coinY - coinRadius;
//    double coinTop = coinY + coinRadius;
//
//    // Check if the player and coin boundaries overlap
//    return (playerRight > coinLeft && playerLeft < coinRight &&
//        playerTop > coinBottom && playerBottom < coinTop);
//}
//
//
//void drawHeartCollectible() {
//    if (!heartVisible) return; // Don't draw if the heart is not visible
//
//    drawHeart(heartX, heartY, heartSize); // Draw the heart at the specified position and size
//}
//void resetHeart() {
//    heartVisible = true; // Make heart visible again
//
//    // Reset heart position
//    heartX = 15.0; // Set back to the initial X position
//    heartY = generateRandomNumber(-0.6, 0.0); // Set back to the initial Y position
//
//    // Ensure the heart does not overlap with other objects
//    if (fabs(airplaneX - heartX) < 0.5) {
//        heartX += (heartX < airplaneX) ? 0.6 : -0.6;
//    }
//    if (fabs(cactusBodyX - heartX) < 0.5) {
//        heartX += (heartX < cactusBodyX) ? 0.6 : -0.6;
//    }
//    if (fabs(coinX - heartX) < 0.5) {
//        heartX += (heartX < coinX) ? 0.6 : -0.6;
//    }
//    if (fabs(shieldPosX - heartX) < 0.5) {
//        heartX += (heartX < shieldPosX) ? 0.6 : -0.6;
//    }
//    if (fabs(shoeX - heartX) < 0.5) {
//        heartX += (heartX < shoeX) ? 0.6 : -0.6;
//    }
//}
//void changeHeartPosition(int value) {
//    // Move coin towards the player
//    heartX -= GameSpeed; // Move left towards player
//
//
//    glutPostRedisplay(); // Request display update
//    glutTimerFunc(10, changeHeartPosition, value); // Call this function again after 100 ms
//}
//bool checkCollisionHeart() {
//    if (!heartVisible) return false;
//
//    // Calculate player boundaries
//    double playerLeft = playerPosX - (0.1 * playerScale);
//    double playerRight = playerPosX + (0.1 * playerScale);
//    double playerBottom = playerPosY; // Player's feet
//    double playerTop;
//
//    // Adjust the player's top boundary based on whether the player is ducking or not
//    if (isDucking) {
//        playerTop = playerPosY + (0.4 * playerScale); // Reduced height for ducking
//    }
//    else {
//        playerTop = playerPosY + (0.8 * playerScale); // Normal height
//    }
//    // Calculate coin boundaries using the coinRadius
//    double heartLeft = heartX - heartRadius;
//    double heartRight = heartX + heartRadius;
//    double heartBottom = heartY - heartRadius;
//    double heartTop = heartY + heartRadius;
//
//    // Check if the player and coin boundaries overlap
//    return (playerRight > heartLeft && playerLeft < heartRight &&
//        playerTop > heartBottom && playerBottom < heartTop);
//}
//
//
//
//
//void drawAirplane() {
//    if (!airplaneVisible) {
//        return;
//    }
//
//    // Draw the body (a triangle)
//    glColor3f(0.0f, 0.0f, 1.0f); // Blue color for the airplane body
//    glBegin(GL_TRIANGLES);
//    glVertex2f(airplaneX, airplaneY);               // Tip of the airplane (pointing left)
//    glVertex2f(airplaneX + 0.1f, airplaneY - 0.05f); // Bottom-right
//    glVertex2f(airplaneX + 0.1f, airplaneY + 0.05f); // Bottom-left
//    glEnd();
//
//    // Draw a rectangle inside the triangle (airplane body)
//    glColor3f(0.0f, 0.5f, 1.0f); // Lighter blue for the rectangle
//    float rectX = airplaneX; // X position for the rectangle
//    float rectY = airplaneY - 0.02f; // Y position for the rectangle
//    float rectWidth = 0.01f; // Width of the rectangle
//    float rectHeight = 0.04f; // Height of the rectangle
//
//    glBegin(GL_QUADS);
//    glVertex2f(rectX, rectY);                // Bottom-left corner
//    glVertex2f(rectX + rectWidth, rectY);   // Bottom-right corner
//    glVertex2f(rectX + rectWidth, rectY + rectHeight); // Top-right corner
//    glVertex2f(rectX, rectY + rectHeight);   // Top-left corner
//    glEnd();
//
//    // Draw the wings (two triangles)
//    glColor3f(1.0f, 0.0f, 0.0f); // Red color for the wings
//    glBegin(GL_TRIANGLES);
//    glVertex2f(airplaneX + 0.1f, airplaneY);         // Base of the wing
//    glVertex2f(airplaneX + 0.2f, airplaneY + 0.05f); // Wing tip
//    glVertex2f(airplaneX + 0.2f, airplaneY - 0.05f); // Wing tip
//    glEnd();
//}
//
//void resetAirplane() {
//    airplaneVisible = true; // Make the airplane visible again
//
//    // Reset airplane position
//    airplaneX = 2.5; // Set back to the initial X position
//    airplaneY = generateRandomNumber(-0.6, 0.0); // Set back to the initial Y position
//
//    // Ensure the airplane does not overlap with other objects
//    if (fabs(cactusBodyX - airplaneX) < 0.5) {
//        airplaneX += (airplaneX < cactusBodyX) ? 0.6 : -0.6;
//    }
//    if (fabs(coinX - airplaneX) < 0.5) {
//        airplaneX += (airplaneX < coinX) ? 0.6 : -0.6;
//    }
//    if (fabs(heartX - airplaneX) < 0.5) {
//        airplaneX += (airplaneX < heartX) ? 0.6 : -0.6;
//    }
//    if (fabs(shoeX - airplaneX) < 0.5) {
//        airplaneX += (airplaneX < shoeX) ? 0.6 : -0.6;
//    }
//    if (fabs(shieldPosX - airplaneX) < 0.5) {
//        airplaneX += (airplaneX < shieldPosX) ? 0.6 : -0.6;
//    }
//}
//void ChangeAirplanePosition(int value) {
//    // Move cactus towards player
//    airplaneX -= GameSpeed; // Move right towards player
//
//    glutPostRedisplay(); // Request display update
//    glutTimerFunc(10, ChangeAirplanePosition, value); // Call this function again after 100 ms
//}
//bool checkCollisionAirplane() {
//    if (!airplaneVisible) return false;
//
//    // Calculate player boundaries
//    double playerLeft = playerPosX - (0.1 * playerScale);
//    double playerRight = playerPosX + (0.1 * playerScale);
//    double playerBottom = playerPosY;
//    double playerTop;
//
//    // Adjust the player's top boundary based on whether the player is ducking or not
//    if (isDucking) {
//        playerTop = playerPosY + (0.4 * playerScale); // Reduced height for ducking
//    }
//    else {
//        playerTop = playerPosY + (0.8 * playerScale); // Normal height
//    }
//    // Calculate airplane boundaries
//    double airplaneLeft = airplaneX;
//    double airplaneRight = airplaneX + airplaneWidth + (0.1); // Adjusted to widen the right boundary
//    double airplaneBottom = airplaneY - (airplaneHeight / 2); // Centering the airplane vertically
//    double airplaneTop = airplaneY + (airplaneHeight / 2);
//
//    // Check for collision with touching condition
//    return (playerRight >= airplaneLeft && playerLeft <= airplaneRight &&
//        playerTop >= airplaneBottom && playerBottom <= airplaneTop);
//}
//
//
//
//
//void drawShieldBubble() {
//    shieldRadius = 0.05;
//    if (!shieldVisible) {
//        return;
//    }
//    int segments = 100; // Number of segments for the circle to make it smooth
//
//    // Calculate the animated radius using a sine wave
//    float animatedRadius = shieldRadius + 0.02f * sin(shieldAnimationTime * 2.0f);
//
//    // Draw the filled circle (bubble)
//    glColor4f(0.0f, 0.5f, 1.0f, shieldTransparency); // Light blue color with transparency
//    glBegin(GL_TRIANGLE_FAN);
//    glVertex2f(shieldPosX, shieldPosY); // Center of the circle
//
//    for (int i = 0; i <= segments; i++) {
//        float angle = 2.0f * M_PI * i / segments;
//        float x = shieldPosX + animatedRadius * cos(angle);
//        float y = shieldPosY + animatedRadius * sin(angle);
//        glVertex2f(x, y);
//    }
//    glEnd();
//
//    // Draw the black border
//    glColor3f(0.0f, 0.0f, 0.0f); // Black color for the border
//    glBegin(GL_LINE_LOOP);
//    for (int i = 0; i <= segments; i++) {
//        float angle = 2.0f * M_PI * i / segments;
//        float x = shieldPosX + animatedRadius * cos(angle);
//        float y = shieldPosY + animatedRadius * sin(angle);
//        glVertex2f(x, y);
//    }
//    glEnd();
//
//    // Draw two additional lines for emphasis
//    glBegin(GL_LINES);
//    glVertex2f(shieldPosX - animatedRadius * 0.5f, shieldPosY); // Left side
//    glVertex2f(shieldPosX + animatedRadius * 0.5f, shieldPosY); // Right side
//
//    glVertex2f(shieldPosX, shieldPosY - animatedRadius * 0.5f); // Bottom side
//    glVertex2f(shieldPosX, shieldPosY + animatedRadius * 0.5f); // Top side
//    glEnd();
//}
//void updateShieldStatus(float deltaTime) {
//    if (isShielded) {
//        shieldActiveTime += deltaTime; // Increment shield active time
//
//        // Check if shield duration has exceeded
//        if (shieldActiveTime >= shieldDuration) {
//            isShielded = false; // Deactivate shield
//            shieldVisible = true; // Optionally make the shield visible again for future collection
//            shieldActiveTime = 0.0f; // Reset active time
//        }
//    }
//}
//void resetShield() {
//    shieldVisible = true; // Make coin visible again
//
//    // Reset coin position
//    shieldPosX = 20.0; // Set back to the initial X position
//    shieldRadius = 0.05;
//
//    shieldPosY = generateRandomNumber(-0.6, 0.0); // Set back to the initial Y position
//
//    // Ensure coin does not overlap with other objects
//    if (fabs(airplaneX - shieldPosX) < 0.5) {
//        shieldPosX += (shieldPosX < airplaneX) ? 0.6 : -0.6;
//    }
//    if (fabs(cactusBodyX - shieldPosX) < 0.5) {
//        shieldPosX += (shieldPosX < cactusBodyX) ? 0.6 : -0.6;
//    }
//    if (fabs(heartX - shieldPosX) < 0.5) {
//        shieldPosX += (shieldPosX < heartX) ? 0.6 : -0.6;
//    }
//    if (fabs(coinX - shieldPosX) < 0.5) {
//        shieldPosX += (shieldPosX < coinX) ? 0.6 : -0.6;
//    }
//    if (fabs(shoeX - shieldPosX) < 0.5) {
//        shieldPosX += (shieldPosX < shoeX) ? 0.6 : -0.6;
//    }
//}
//void ChangeShieldPosition(int value) {
//    // Move cactus towards player
//    shieldPosX -= GameSpeed; // Move right towards player
//
//    shieldRadius += growth * 0.0003; // Adjust the radius based on growth direction
//
//    // Check radius limits and change growth direction
//    if (shieldRadius >= 0.06f) { // Max radius
//        growth = -1; // Start shrinking
//    }
//    else if (shieldRadius <= 0.05f) { // Min radius
//        growth = 1; // Start growing
//    }
//
//
//    glutPostRedisplay(); // Request display update
//    glutTimerFunc(10, ChangeShieldPosition, value); // Call this function again after 100 ms
//}
//bool checkCollisionShield() {
//    if (!shieldVisible) return false;
//
//    // Calculate player boundaries
//    double playerLeft = playerPosX - (0.1 * playerScale);
//    double playerRight = playerPosX + (0.1 * playerScale);
//    double playerBottom = playerPosY; // Player's feet
//    double playerTop;
//
//    // Adjust the player's top boundary based on whether the player is ducking or not
//    if (isDucking) {
//        playerTop = playerPosY + (0.4 * playerScale); // Reduced height for ducking
//    }
//    else {
//        playerTop = playerPosY + (0.8 * playerScale); // Normal height
//    }
//    // Calculate coin boundaries using the coinRadius
//    double shieldLeft = shieldPosX - shieldRadius;
//    double shieldRight = shieldPosX + shieldRadius;
//    double shieldBottom = shieldPosY - shieldRadius;
//    double shieldTop = shieldPosY + shieldRadius;
//
//    // Check if the player and coin boundaries overlap
//    return (playerRight > shieldLeft && playerLeft < shieldRight &&
//        playerTop > shieldBottom && playerBottom < shieldTop);
//}
//void drawPlayerShield() {
//    if (!isShielded) return; // Do not draw the shield if it's not visible
//
//    int segments = 100; // Number of segments for the circle to make it smooth
//
//    // Calculate the animated radius using a sine wave
//    float animatedRadius = 0.1 + (0.2 * sin(shieldAnimationTime * 2.0f));
//
//    // Set the color and transparency of the shield
//    glColor4f(0.0f, 0.5f, 1.0f, shieldTransparency); // Light blue color with transparency
//    glBegin(GL_TRIANGLE_FAN);
//    glVertex2f(playerPosX, playerPosY); // Center of the shield at player's position
//
//    for (int i = 0; i <= segments; i++) {
//        float angle = 2.0f * M_PI * i / segments;
//        float x = playerPosX + animatedRadius * cos(angle); // Calculate x position
//        float y;
//        if (isDucking) {
//            y = playerPosY + animatedRadius * sin(angle) + 0.03; // Calculate y position
//
//        }
//        else {
//            y = playerPosY + animatedRadius * sin(angle) + 0.1; // Calculate y position
//
//        }
//        glVertex2f(x, y);
//    }
//    glEnd();
//}
//
//
//
//void updateJumpBoostStatus(float deltaTime) {
//    if (jumpBoost) {
//        jumpBoostActiveTime += deltaTime; // Increment shield active time
//
//        // Check if shield duration has exceeded
//        if (jumpBoostActiveTime >= JumpBoostDuration) {
//            jumpBoost = false; // Deactivate shield
//            jumpSpeed = jumpBoost ? 0.08 : 0.065f;
//            gravity = jumpBoost ? -0.0025f : -0.004f;   // Increase gravity for a faster fall
//            jumpBoostVisible = true; // Optionally make the shield visible again for future collection
//            jumpBoostActiveTime = 0.0f; // Reset active time
//        }
//    }
//}
//
//
//void drawShoe() {
//    shoeRadius = 0.05f; // Set the base radius for the shoe
//    if (!jumpBoostVisible) {
//        return; // Exit if the shoe is not visible
//    }
//    int segments = 100; // Number of segments for the circle to make it smooth
//
//    // Calculate the animated radius using a sine wave
//    float animatedRadius = shoeRadius + 0.02f * sin(shoeAnimationTime * 2.0f);
//
//    // Draw the filled circle (bubble)
//    glColor4f(0.5f, 0.0f, 0.5f, 0.5f); // Lean purple color with transparency (50% opacity)
//    glBegin(GL_TRIANGLE_FAN);
//    glVertex2f(shoeX, shoeY); // Center of the circle
//
//    for (int i = 0; i <= segments; i++) {
//        float angle = 2.0f * M_PI * i / segments;
//        float x = shoeX + animatedRadius * cos(angle);
//        float y = shoeY + animatedRadius * sin(angle);
//        glVertex2f(x, y);
//    }
//    glEnd();
//
//    // Draw the black border
//    glColor3f(0.0f, 0.0f, 0.0f); // Black color for the border
//    glBegin(GL_LINE_LOOP);
//    for (int i = 0; i <= segments; i++) {
//        float angle = 2.0f * M_PI * i / segments;
//        float x = shoeX + animatedRadius * cos(angle); // Corrected from shoeY
//        float y = shoeY + animatedRadius * sin(angle); // Corrected from shoeY
//        glVertex2f(x, y);
//    }
//    glEnd();
//
//    // Draw two lines to emphasize the shoe shape (forming |_ )
//    glBegin(GL_LINES);
//    glVertex2f(shoeX, shoeY - animatedRadius * 0.5f); // Bottom of the vertical line
//    glVertex2f(shoeX, shoeY + animatedRadius * 0.5f); // Top of the vertical line
//
//    glVertex2f(shoeX - animatedRadius * 0.5f, shoeY - animatedRadius * 0.5f); // Left bottom point
//    glVertex2f(shoeX, shoeY - animatedRadius * 0.5f); // Right bottom point
//    glEnd();
//}
//void resetShoe() {
//    jumpBoostVisible = true; // Make coin visible again
//
//    // Reset coin position
//    shoeX = 12.0; // Set back to the initial X position
//    shoeRadius = 0.05;
//
//    shoeY = generateRandomNumber(-0.6, 0.0);
//
//    // Ensure coin does not overlap with other objects
//    if (fabs(airplaneX - shoeX) < 0.5) {
//        shoeX += (shoeX < airplaneX) ? 0.6 : -0.6;
//    }
//    if (fabs(cactusBodyX - shoeX) < 0.5) {
//        shoeX += (shoeX < cactusBodyX) ? 0.6 : -0.6;
//    }
//    if (fabs(heartX - shoeX) < 0.5) {
//        shoeX += (shoeX < heartX) ? 0.6 : -0.6;
//    }
//    if (fabs(coinX - shoeX) < 0.5) {
//        shoeX += (shoeX < coinX) ? 0.6 : -0.6;
//    }
//    if (fabs(shieldPosX - shoeX) < 0.5) {
//        shoeX += (shoeX < shieldPosX) ? 0.6 : -0.6;
//    }
//}
//void ChangeShoePosition(int value) {
//    // Move cactus towards player
//    shoeX -= GameSpeed; // Move right towards player
//
//    shoeRadius += growth * 0.0003; // Adjust the radius based on growth direction
//
//    // Check radius limits and change growth direction
//    if (shoeRadius >= 0.07f) { // Max radius
//        growth = -1; // Start shrinking
//    }
//    else if (shoeRadius <= 0.05f) { // Min radius
//        growth = 1; // Start growing
//    }
//
//
//    glutPostRedisplay(); // Request display update
//    glutTimerFunc(10, ChangeShoePosition, value); // Call this function again after 100 ms
//}
//bool checkCollisionShoe() {
//    if (!jumpBoostVisible) return false;
//
//    // Calculate player boundaries
//    double playerLeft = playerPosX - (0.1 * playerScale);
//    double playerRight = playerPosX + (0.1 * playerScale);
//    double playerBottom = playerPosY; // Player's feet
//    double playerTop;
//
//    // Adjust the player's top boundary based on whether the player is ducking or not
//    if (isDucking) {
//        playerTop = playerPosY + (0.4 * playerScale); // Reduced height for ducking
//    }
//    else {
//        playerTop = playerPosY + (0.8 * playerScale); // Normal height
//    }
//    // Calculate coin boundaries using the coinRadius
//    double shoeLeft = shoeX - shoeRadius;
//    double shoeRight = shoeX + shoeRadius;
//    double shoeBottom = shoeY - shoeRadius;
//    double shoeTop = shoeY + shoeRadius;
//
//    // Check if the player and coin boundaries overlap
//    return (playerRight > shoeLeft && playerLeft < shoeRight &&
//        playerTop > shoeBottom && playerBottom < shoeTop);
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//void updateGameLogic(int value) {
//
//
//
//    if (airplaneX <= -1.2) {
//        resetAirplane();
//    }
//    if (heartX <= -1.1) {
//        resetHeart();
//    }
//    if (cactusBodyX <= -1.1) {
//        resetCactus();
//    }
//    if (coinX <= -1.1) {
//        resetCoin();
//    }
//    if (shieldPosX <= -1.1) {
//        resetShield();
//    }
//    if (shoeX <= -1.1) {
//        resetShoe();
//    }
//    if (isShielded) {
//        updateShieldStatus(0.02);
//    }
//    if (jumpBoost) {
//        updateJumpBoostStatus(0.02);
//
//    }
//
//
//    if (isJumping) {
//        playerPosY += playerSpeedY;
//        playerSpeedY += gravity;
//        if (playerPosY <= -0.7f) {
//            playerPosY = -0.7f;
//            isJumping = false;
//        }
//    }
//    else {
//
//        playerPosY = -0.7;
//
//    }
//
//    if (!lose) { // Only update if the game is not over
//        // Check for collision with the cactus
//        if (cactusVisible && checkCollisionCactus()) {
//
//            if (!isShielded) {
//                currentLives--; // Decrement lives
//                cactusBodyX += 0.7;
//
//            }
//            else {
//                cactusVisible = false;
//                isShielded = false;
//            }
//
//            if (currentLives <= 0) {
//                lose = true; // Set the game over flag
//                displayGameOver(currentScore); // Display "Game Over" message
//                glFlush(); // Ensure everything is displayed
//            }
//        }
//
//        if (airplaneVisible && checkCollisionAirplane()) {
//
//            playSound("C:/Users/Ahmed Hany/Desktop/GameSound/collide.wav");
//
//            if (!isShielded) {
//                currentLives--; // Decrement lives
//                airplaneX += 1.0;
//                coinX += 1.0;
//                shoeX += 1.0;
//                heartX += 1.0;
//                shieldPosX += 1.0;
//            }
//            else {
//                isShielded = false;
//                airplaneVisible = false;
//            }
//
//            if (currentLives <= 0) {
//                lose = true; // Set the game over flag
//                displayGameOver(currentScore); // Display "Game Over" message
//                glFlush(); // Ensure everything is displayed
//            }
//        }
//        if (shieldVisible && checkCollisionShield()) {
//            playSound("C:/Users/Ahmed Hany/Desktop/GameSound/powerUp.wav");
//            shieldVisible = false; // Hide the shield after collision
//            isShielded = true; // Activate shielded state
//            shieldActiveTime = 0.0f; // Reset the active time for the shield
//            resetShield(); // Reset shield position
//        }
//
//        if (coinVisible && checkCollisionCoin()) {
//            playSound("C:/Users/Ahmed Hany/Desktop/GameSound/collectible.wav");
//            coinVisible = false;
//            currentScore += 100;
//            resetCoin(); // Reset cactus position and visibility after collision
//        }
//
//        if (heartVisible && checkCollisionHeart()) {
//            playSound("C:/Users/Ahmed Hany/Desktop/GameSound/collectible.wav");
//            heartVisible = false;
//            currentLives += (currentLives < 5) ? 1 : 0;
//            resetHeart();
//        }
//        if (jumpBoostVisible && checkCollisionShoe()) {
//            playSound("C:/Users/Ahmed Hany/Desktop/GameSound/powerUp.wav");
//            jumpBoostVisible = false;
//            jumpBoost = true;
//            gravity = jumpBoost ? -0.0025f : -0.004f;   // Increase gravity for a faster fall
//            jumpSpeed = jumpBoost ? 0.08 : 0.065f;
//            jumpBoostActiveTime = 0.0;
//            resetShoe();
//        }
//
//
//        // Call for redisplay
//
//        glutPostRedisplay(); // Refresh the screen
//    }
//    else {
//        return;
//
//    }
//
//    glutTimerFunc(10, updateGameLogic, value); // Call this function again after 100 ms
//}
//
//
//void increaseGameSpeed(int value) {
//    if (GameSpeed <= 0.04) {
//        GameSpeed += 0.0005; // Decrease GameSpeed by 0.1 (or any desired value)
//    }
//
//
//    // Ensure GameSpeed doesn't go below a minimum value
//
//
//    // Restart the timer for the next 10-second interval
//    glutTimerFunc(10000, increaseGameSpeed, 0);
//}
//
//
//
//
//
//
//
//
//
//void clearScreen() {
//    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set clear color to black
//
//}
//
//
//
//
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
//
//    if (lose) {
//        displayGameOver(currentScore);       // Display "Game Over" message
//        glFlush();               // Ensure everything is displayed
//        return;
//    }
//
//    if (win) {
//        YouWin(currentScore);       // Display "Game Over" message
//        glFlush();               // Ensure everything is displayed
//        return;                  // Stop further rendering if the game is over
//    }
//    upperBoundry(-1.0f, 0.8, 1.0f, 1.0f); // Draws a rectangle from (-1.0, -0.5) to (1.0, 0.5)
//
//    // Continue rendering if the game is still running
//    for (int i = 0; i < 5; i++) {
//        drawHeartBorder(hpX + i * hpspacing, hpY, hpHeartSize);
//    }
//
//    for (int i = 0; i < currentLives; i++) {
//        drawHeart(hpX + i * hpspacing, hpY, hpHeartSize);
//    }
//
//
//
//
//
//    drawTriangle(-0.5, -0.9, -0.3, -0.9, -0.4, -0.8);
//
//    drawCoin();
//    drawCactus();
//    drawHeartCollectible();
//    drawAirplane();
//    drawShieldBubble();
//    drawPlayerShield();
//    drawFloorAndBackground(-1.0, -0.7, 1.0, -0.7);
//
//    drawSun();
//    drawShoe();
//
//    generatePlayerBody();
//    displayTime(0.9, 0.9);
//    displayScore(0.7f, 0.9f);
//
//    glFlush(); // Ensure everything is displayed
//}
//
//void reshape(int width, int height) {
//    glViewport(0, 0, width, height);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Set the coordinate system
//    glMatrixMode(GL_MODELVIEW);
//}
//
//void setup(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Single buffer and RGB mode
//    glutInitWindowSize(1900, 800);                 // Initial window size
//    glutCreateWindow("Game");                     // Create the window with a title
//
//
//
//    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);  // Set the background color to light sky blue
//
//    glutDisplayFunc(display);          // Register display callback function
//    glutReshapeFunc(reshape);          // Register reshape callback function
//
//    // Initialize the timer with 1 second interval
//    glutTimerFunc(1000, updateTimer, 0);
//
//    // Initialize the score update mechanism (e.g., every 100 ms update the score by 1)
//    glutTimerFunc(10, updateScore, 1);
//
//    glutTimerFunc(10, changeSunPosition, 0); // Call decreaseGameSpeed every 30 seconds
//
//
//    glutTimerFunc(10, ChangeCactusPosition, 0); // Start cactus movement timer
//
//    glutTimerFunc(10, ChangeAirplanePosition, 0); // Start cactus movement timer
//
//
//    glutTimerFunc(10, changeCoinPosition, 0); // Start coin movement timer
//
//    glutTimerFunc(10, changeHeartPosition, 0); // Start coin movement timer
//
//    glutTimerFunc(10, ChangeShieldPosition, 0); // Start coin movement timer   
//
//    glutTimerFunc(10, ChangeShoePosition, 0);
//
//    glutTimerFunc(10000, increaseGameSpeed, 0); // Call decreaseGameSpeed every 30 seconds
//
//
//
//
//
//    glutKeyboardFunc(keyboard);
//    glutKeyboardUpFunc(keyboardUp);
//
//
//
//
//
//    glutTimerFunc(10, updateGameLogic, 0); // Start game logic updates
//
//
//    glutMainLoop();  // Start the GLUT event loop
//}
//
//int main(int argc, char** argv) {
//    playBackGroundMusic();
//
//    setup(argc, argv); // Call the setup function 
//
//    // Initialize timers
//
//    //glutMainLoop(); // Enter the GLUT event processing loop
//    return 0;
//}