//#include <cmath>
//#include <string>
//#include <glut.h>
//
//// Player properties
//float playerX = 50.0f;
//float playerY = 50.0f;
//float playerVelocityY = 0.0f;  // Player's vertical velocity
//float gravity = -0.2f;         // Gravity pulling the player down
//bool isJumping = false;
//bool isDucking = false;
//
//// Game properties
//const int initialLives = 5;
//int lives = initialLives;
//int timeLeft = 60;  // Game time in seconds
//bool isGameActive = true;
//
//// Speed control
//float xSpeed = 0.5f;  // Slow down the speed of x-axis movement
//
//// Collectible properties (multiple collectibles)
//const int numCollectibles = 5;
//float collectibleX[numCollectibles] = { 200.0f, 250.0f, 300.0f, 350.0f, 400.0f };
//float collectibleY[numCollectibles] = { 100.0f, 120.0f, 140.0f, 160.0f, 180.0f };
//bool isCollectibleVisible[numCollectibles] = { true, true, true, true, true };
//float collectibleAngle = 0.0f;  // Rotation angle for collectible animation
//
//// Scoring system
//int score = 0;
//
//// Draw Score, Time, and Lives on Screen
//void DrawScore() {
//    std::string scoreText = "Score: " + std::to_string(score);
//    std::string timeText = "Time: " + std::to_string(timeLeft);
//    std::string livesText = "Lives: ";
//    for (int i = 0; i < lives; i++) {
//        livesText += "<3 ";  // Using heart symbol for lives
//    }
//
//    glRasterPos2f(10.0f, 370.0f);  // Position the score at the top-left corner
//    for (char c : scoreText) {
//        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
//    }
//
//    glRasterPos2f(10.0f, 350.0f);  // Position the time below score
//    for (char c : timeText) {
//        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
//    }
//
//    glRasterPos2f(10.0f, 330.0f);  // Position lives below time
//    for (char c : livesText) {
//        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
//    }
//}
//
//// Player Drawing - Kiwi Bird with Leg Animation
//float playerLegAngle = 0.0f;  // For simulating running animation
//void DrawPlayer() {
//    // Body of kiwi bird
//    glColor3f(1.0f, 0.5f, 0.0f);  // Orange color for kiwi bird
//    glBegin(GL_POLYGON);
//    for (int i = 0; i < 360; i++) {
//        float theta = i * (3.1415926f / 180.0f);
//        glVertex2f(playerX + 15.0f * cos(theta), playerY + 15.0f * sin(theta));  // Circle for body
//    }
//    glEnd();
//
//    // Beak (triangle)
//    glBegin(GL_TRIANGLES);
//    glColor3f(1.0f, 1.0f, 0.0f);  // Yellow for the beak
//    glVertex2f(playerX + 15.0f, playerY + 5.0f);  // Tip
//    glVertex2f(playerX + 25.0f, playerY + 0.0f);  // Left
//    glVertex2f(playerX + 15.0f, playerY - 5.0f);  // Right
//    glEnd();
//
//    // Legs (simple animated movement)
//    glPushMatrix();
//    glTranslatef(playerX, playerY - 15.0f, 0.0f);  // Move to where legs should be
//    glRotatef(playerLegAngle, 0.0f, 0.0f, 1.0f);   // Rotate legs to simulate running
//
//    // Left leg
//    glBegin(GL_LINES);
//    glColor3f(0.5f, 0.35f, 0.05f);  // Brown for legs
//    glVertex2f(0.0f, 0.0f);        // Top of leg
//    glVertex2f(-5.0f, -10.0f);     // Bottom of leg
//    glEnd();
//
//    // Right leg
//    glBegin(GL_LINES);
//    glVertex2f(0.0f, 0.0f);
//    glVertex2f(5.0f, -10.0f);
//    glEnd();
//    glPopMatrix();
//}
//
//// Animate leg movement for running
//void AnimateLegs() {
//    playerLegAngle += 5.0f;  // Rotate legs back and forth
//    if (playerLegAngle >= 30.0f || playerLegAngle <= -30.0f) {
//        playerLegAngle = -playerLegAngle;  // Switch direction when limit reached
//    }
//}
//
//// Collectible - Kiwi slices (multiple)
//void DrawCollectibles() {
//    for (int i = 0; i < numCollectibles; i++) {
//        if (isCollectibleVisible[i]) {
//            glPushMatrix();
//            glTranslatef(collectibleX[i], collectibleY[i], 0.0f);
//            glRotatef(collectibleAngle, 0.0f, 0.0f, 1.0f);  // Rotate collectible
//            glBegin(GL_POLYGON);
//            glColor3f(0.0f, 1.0f, 0.0f);  // Green color for kiwi slice
//            for (int j = 0; j < 360; j++) {
//                float theta = j * (3.1415926f / 180.0f);
//                glVertex2f(10.0f * cos(theta), 10.0f * sin(theta));  // Circle for slice
//            }
//            glEnd();
//            glPopMatrix();
//        }
//    }
//}
//
//// Check collision between player and collectibles
//void CheckCollisions() {
//    for (int i = 0; i < numCollectibles; i++) {
//        float distance = sqrt(pow(playerX - collectibleX[i], 2) + pow(playerY - collectibleY[i], 2));
//        if (distance < 25.0f && isCollectibleVisible[i]) {  // 25 is the radius sum of both objects
//            isCollectibleVisible[i] = false;  // Hide collectible if touched
//            score += 10;  // Increase score by 10
//        }
//    }
//}
//
//// Obstacles properties
//const int numObstacles = 3;
//float obstacleX[numObstacles] = { 600.0f, 700.0f, 800.0f };
//float obstacleY[numObstacles] = { 50.0f, 60.0f, 70.0f };  // Varying heights
//bool isObstacleVisible[numObstacles] = { true, true, true };
//
//// Draw Obstacles
//void DrawObstacles() {
//    for (int i = 0; i < numObstacles; i++) {
//        if (isObstacleVisible[i]) {
//            glBegin(GL_QUADS);
//            glColor3f(0.7f, 0.0f, 0.0f);  // Red color for obstacles
//            glVertex2f(obstacleX[i], obstacleY[i]);
//            glVertex2f(obstacleX[i] + 20.0f, obstacleY[i]);
//            glVertex2f(obstacleX[i] + 20.0f, obstacleY[i] + 30.0f);  // Height of obstacle
//            glVertex2f(obstacleX[i], obstacleY[i] + 30.0f);
//            glEnd();
//        }
//    }
//}
//
//// Check collision between player and obstacles
//void CheckObstacleCollisions() {
//    for (int i = 0; i < numObstacles; i++) {
//        if (isObstacleVisible[i]) {
//            if (playerX + 15.0f > obstacleX[i] && playerX < obstacleX[i] + 20.0f &&
//                playerY < obstacleY[i] + 30.0f) {
//                lives--;  // Decrease lives
//                if (lives <= 0) {
//                    isGameActive = false;  // End game if lives are zero
//                }
//            }
//        }
//    }
//}
//
//// Update game state
//void UpdateGame() {
//    // Update player position based on gravity and jumping
//    if (isJumping) {
//        playerVelocityY += gravity;  // Apply gravity
//        playerY += playerVelocityY;   // Update player position
//
//        // Check if the player is on the ground
//        if (playerY <= 50.0f) {  // Assuming 50.0f is the ground level
//            playerY = 50.0f;
//            isJumping = false;
//            playerVelocityY = 0.0f;  // Reset vertical velocity
//        }
//    }
//
//    // Move obstacles
//    for (int i = 0; i < numObstacles; i++) {
//        if (isObstacleVisible[i]) {
//            obstacleX[i] -= xSpeed;  // Move obstacles left at slower speed
//            if (obstacleX[i] < -20.0f) {  // Reset obstacle if it goes off screen
//                obstacleX[i] = 600.0f + rand() % 200;  // Randomize new position
//                obstacleY[i] = 50.0f + rand() % 50;  // Vary height
//            }
//        }
//    }
//
//    // Move collectibles
//    for (int i = 0; i < numCollectibles; i++) {
//        if (isCollectibleVisible[i]) {
//            collectibleX[i] -= xSpeed;  // Move collectibles left at slower speed
//            if (collectibleX[i] < -20.0f) {  // Reset collectible if it goes off screen
//                collectibleX[i] = 600.0f + rand() % 200;  // Randomize new position
//                collectibleY[i] = 100.0f + rand() % 100;  // Vary height
//            }
//        }
//    }
//
//    // Check collisions
//    CheckCollisions();
//    CheckObstacleCollisions();
//
//    // Animate collectibles (rotate them)
//    collectibleAngle += 2.0f;
//    if (collectibleAngle > 360.0f) {
//        collectibleAngle -= 360.0f;
//    }
//}
//
//// Timer function to decrease time left
//void Timer(int value) {
//    if (isGameActive) {
//        timeLeft--;
//        if (timeLeft <= 0) {
//            isGameActive = false;  // End game when time runs out
//        }
//        glutTimerFunc(1000, Timer, 0);  // Call Timer every second
//    }
//}
//
//// Keyboard input for jumping and ducking
//void Keyboard(unsigned char key, int x, int y) {
//    if (key == 'w') {  // 'w' for jumping
//        if (!isJumping && !isDucking) {
//            playerVelocityY = 10.0f;  // Initial jump velocity
//            isJumping = true;
//        }
//    }
//    if (key == 's') {  // 's' for ducking
//        if (!isJumping) {
//            isDucking = true;
//            playerY -= 10.0f;  // Shrink player for ducking
//        }
//    }
//}
//
//// Keyboard release for ducking
//void KeyUp(unsigned char key, int x, int y) {
//    if (key == 's') {  // Stop ducking
//        isDucking = false;
//        playerY += 10.0f;  // Return to normal height
//    }
//}
//
//// Draw game boundaries
//void DrawBoundaries() {
//    // Upper boundary (composed of 4 quads)
//    glBegin(GL_QUADS);
//    glColor3f(0.0f, 0.0f, 1.0f);  // Blue for boundaries
//    for (int i = 0; i < 4; i++) {
//        glVertex2f(i * 200.0f, 590.0f);  // Upper boundary, just below window top
//        glVertex2f(i * 200.0f + 200.0f, 590.0f);
//        glVertex2f(i * 200.0f + 200.0f, 600.0f);
//        glVertex2f(i * 200.0f, 600.0f);
//    }
//    glEnd();
//
//    // Lower boundary (same)
//    glBegin(GL_QUADS);
//    glColor3f(0.0f, 0.0f, 1.0f);  // Blue for boundaries
//    for (int i = 0; i < 4; i++) {
//        glVertex2f(i * 200.0f, 0.0f);  // Lower boundary
//        glVertex2f(i * 200.0f + 200.0f, 0.0f);
//        glVertex2f(i * 200.0f + 200.0f, 10.0f);
//        glVertex2f(i * 200.0f, 10.0f);
//    }
//    glEnd();
//}
//
//// Display function
//void Display() {
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    if (isGameActive) {
//        DrawBoundaries();  // Draw the boundaries
//        DrawPlayer();      // Draw the kiwi bird
//        DrawCollectibles();
//        DrawObstacles();
//        DrawScore();
//        AnimateLegs();  // Animate player legs
//        UpdateGame();   // Update game state
//    }
//    else {
//        // Display game over screen
//        glColor3f(1.0f, 0.0f, 0.0f);  // Red for game over text
//        glRasterPos2f(300.0f, 200.0f);
//        std::string gameOverText = "Game Over!";
//        for (char c : gameOverText) {
//            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
//        }
//        // Display final score
//        std::string scoreText = "Final Score: " + std::to_string(score);
//        glRasterPos2f(300.0f, 180.0f);
//        for (char c : scoreText) {
//            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
//        }
//    }
//
//    glutSwapBuffers();
//}
//
//// Main function
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("Kiwi Runner");
//
//    glClearColor(0.5f, 0.7f, 1.0f, 1.0f);  // Sky blue background
//    glOrtho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
//
//    glutDisplayFunc(Display);
//    glutKeyboardFunc(Keyboard);
//    glutKeyboardUpFunc(KeyUp);  // Detect key release for ducking
//    glutTimerFunc(1000, Timer, 0);  // Start timer
//    glutIdleFunc(Display);  // Keep updating
//
//    glutMainLoop();
//    return 0;
//}
