#include <stdlib.h>  // For rand() and srand()
#include <stdio.h>
#include "player.h"
#include "background.h"
#include "obstacle.h"
#include "collectible.h"
#include "powerup.h"
#include <glut.h>
#include <math.h>
#include <vector>

enum GameState {
    RUNNING,      // Game is running
    GAME_LOST,    // Player lost all lives
    GAME_ENDED    // Time ran out
};

GameState currentState = RUNNING;  // Track the current game state

// Create a normal collectible and two power-ups
Collectible collectible(300.0f, 50.0f, 50.0f, 50.0f);  // A normal collectible
PowerUp powerUp1(500.0f, 50.0f, 50.0f, 50.0f, PowerUp::SCORE_MULTIPLIER);  // A score multiplier power-up
PowerUp powerUp2(700.0f, 50.0f, 50.0f, 50.0f, PowerUp::JUMP_BOOST);  // A jump boost power-up

float randomPowerUp1SpawnDelay = 15.0f;  // Initial random delay for PowerUp1 (between 15-20 seconds)
float randomPowerUp2SpawnDelay = 20.0f;  // Initial random delay for PowerUp2 (between 20-25 seconds)

float gameDuration = 50.0f;  // Game lasts for 50 seconds
float gameStartTime = 0.0f;  // To track when the game starts
bool gameOver = false;       // To track whether the game is over
bool playerLost = false;     // To track whether the player lost (ran out of lives)



float collectibleSpawnInterval = 5.0f;  // Base spawn interval for collectibles (in seconds)
float powerUpSpawnInterval = 5.0f;      // Base spawn interval for power-ups (in seconds)
float powerUp1ActivationTime = -1;  // Time when score multiplier is activated (-1 means inactive)
float powerUp2ActivationTime = -1;  // Time when jump boost is activated (-1 means inactive)
float obstacleSpawnInterval = 5.0f;     // Base spawn interval for obstacles (in seconds)
int score = 0;
static int scoreMultiplier = 1;
float playerJumpHeight = 130.0f;  // Initial jump height
int lives = 3333;  // Player's lives
float gameTime = 50.0;  // Game duration in seconds
float startTime = 0.0f;  // Store when the game starts
int scoreMultiplierCount = 0;
int jumpBoostCount = 0;
// Create a player object and a background object
Background background(200.0f);  // Ground height  
Player player(50.0f, 200.0f, 100.0f, 100.0f);  // x, y, width, height

std::vector<Obstacle> obstacles;  // Vector to hold multiple obstacles

const float HEALTH_BAR_WIDTH = 200.0f;  // Width of the health bar
const float HEALTH_BAR_HEIGHT = 20.0f;  // Height of the health bar
const float HEALTH_BAR_X = 10.0f;       // X position of the health bar
const float HEALTH_BAR_Y = 660.0f;      // Y position of the health bar



void setOrthographicProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1280.0, 0.0, 720.0);  // Left = 0, Right = 1280, Bottom = 0, Top = 720
    glMatrixMode(GL_MODELVIEW);
}

void displayHealthBar() {
    // Calculate health bar width based on lives
    float currentHealthWidth = (HEALTH_BAR_WIDTH / 3333) * lives;  // Scale based on max lives

    // Draw the health bar background (red)
    glColor3f(1.0f, 0.0f, 0.0f);  // Red color
    glBegin(GL_QUADS);
    glVertex2f(HEALTH_BAR_X, HEALTH_BAR_Y);
    glVertex2f(HEALTH_BAR_X + HEALTH_BAR_WIDTH, HEALTH_BAR_Y);
    glVertex2f(HEALTH_BAR_X + HEALTH_BAR_WIDTH, HEALTH_BAR_Y + HEALTH_BAR_HEIGHT);
    glVertex2f(HEALTH_BAR_X, HEALTH_BAR_Y + HEALTH_BAR_HEIGHT);
    glEnd();

    // Draw the health portion (green)
    glColor3f(0.0f, 1.0f, 0.0f);  // Green color
    glBegin(GL_QUADS);
    glVertex2f(HEALTH_BAR_X, HEALTH_BAR_Y);
    glVertex2f(HEALTH_BAR_X + currentHealthWidth, HEALTH_BAR_Y);
    glVertex2f(HEALTH_BAR_X + currentHealthWidth, HEALTH_BAR_Y + HEALTH_BAR_HEIGHT);
    glVertex2f(HEALTH_BAR_X, HEALTH_BAR_Y + HEALTH_BAR_HEIGHT);
    glEnd();
}

void displayScore() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(10, 690);
    char scoreText[50];
    sprintf(scoreText, "Score: %d", score);
    for (char* c = scoreText; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void displayRemainingTime(float currentTime) {
    float timeLeft = gameDuration - (currentTime - gameStartTime);

    // If timeLeft is negative or zero, the game is over
    if (timeLeft <= 0) {
        timeLeft = 0;
        gameOver = true;
    }

    // Display remaining time
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(600, 690);  // Position for the timer
    char timeText[50];
    sprintf(timeText, "Time Left: %.1f", timeLeft);
    for (char* c = timeText; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}
void displayEndGameScreen() {
    glColor3f(1.0f, 0.0f, 0.0f);  // Red for "Game Lost" or "Game Ended"
    glRasterPos2f(600, 360);  // Center the message

    char endMessage[50];
    if (currentState == GAME_LOST) {
        sprintf(endMessage, "Game Lost! Final Score: %d", score);
    }
    else if (currentState == GAME_ENDED) {
        sprintf(endMessage, "Game Ended! Final Score: %d", score);
    }

    for (char* c = endMessage; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }

    // Display instructions to restart the game
    glColor3f(1.0f, 1.0f, 1.0f);  // White color for instructions
    glRasterPos2f(500, 300);  // Position below the end message
    char restartMessage[] = "Press SPACE to restart the game";
    for (char* c = restartMessage; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void displayEndGameMessage() {
    glColor3f(1.0f, 0.0f, 0.0f);  // Red color for "Game End" or "Game Lose"
    glRasterPos2f(600, 360);  // Centered on the screen

    char endMessage[50];
    if (playerLost) {
        sprintf(endMessage, "Game Lose! Final Score: %d", score);
    }
    else {
        sprintf(endMessage, "Game End! Final Score: %d", score);
    }

    for (char* c = endMessage; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    if (currentState == RUNNING) {
        background.update();
        background.render();
        player.update();
        player.render();

        // Render the collectible and power-ups
        collectible.render();
        powerUp1.render();
        powerUp2.render();

        // Render all obstacles
        for (auto& obstacle : obstacles) {
            obstacle.render();
        }

        // Display health, score, and remaining time
        displayHealthBar();
        displayScore();
        displayRemainingTime(glutGet(GLUT_ELAPSED_TIME) / 1000.0f);

    }
    else {
        // Game is over, display the end game screen
        displayEndGameScreen();
    }

    glutSwapBuffers();
}


void spawnCollectible() {
    float minY = player.getY();
    float maxY = player.getY() + playerJumpHeight;
    float randomY = minY + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxY - minY)));

    collectible = Collectible(1280.0f, randomY, 50.0f, 50.0f);  // Spawn on the right side off-screen
}

void spawnPowerUp1() {
    if (scoreMultiplierCount < 2) {  // Max two power-ups
        float minY = player.getY();
        float maxY = player.getY() + playerJumpHeight;
        float randomY = minY + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxY - minY)));

        powerUp1 = PowerUp(1280.0f, randomY, 50.0f, 50.0f, PowerUp::SCORE_MULTIPLIER);
        scoreMultiplierCount++;
    }
}

void spawnPowerUp2() {
    if (jumpBoostCount < 2) {  // Max two power-ups
        float minY = player.getY();
        float maxY = player.getY() + playerJumpHeight;
        float randomY = minY + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxY - minY)));

        powerUp2 = PowerUp(1280.0f, randomY, 50.0f, 50.0f, PowerUp::JUMP_BOOST);
        jumpBoostCount++;
    }
}


void spawnObstacle() {
    float randomY = 200.0f;  // You can adjust this to randomize the height if needed
    obstacles.emplace_back(1280.0f, randomY, 50.0f, 50.0f);  // Spawn a new obstacle
}

void updateGame() {
    float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;  // Get time in seconds
    if (currentState != RUNNING) {
        return;  // Don't update game if it's not running
    }
    if (gameOver) {
        displayEndGameMessage();
        glutSwapBuffers();
        return;  // Don't update the game anymore
    }
    float timeLeft = gameDuration - (currentTime - gameStartTime);
    if (timeLeft <= 0) {
        gameOver = true;  // End the game when time is up
        return;
    }
    static float lastCSpawnTime = 0;
    static float lastP1SpawnTime = 0;  // Separate spawn time for PowerUp1
    static float lastP2SpawnTime = 0;  // Separate spawn time for PowerUp2
    static float lastOSpawnTime = 0;
 

    // Move collectibles, power-ups, and obstacles towards the player
    collectible.setX(collectible.getX() - Background::speed);
    powerUp1.setX(powerUp1.getX() - Background::speed);
    powerUp2.setX(powerUp2.getX() - Background::speed);


 

    // Move all obstacles
    for (auto& obstacle : obstacles) {
        obstacle.setX(obstacle.getX() - Background::speed);
    }

    for (auto& obstacle : obstacles) {
        if (obstacle.checkCollision(player.getX(), player.getY(), player.getWidth(), player.getHeight())) {
            // Bounce everything to the right (simulate player bouncing back)
			Background::collision = 1;
            for (auto& obs : obstacles) {
                obs.setX(obs.getX() + 350.0f);  // Move obstacles to the right
            }
            collectible.setX(collectible.getX() + 350.0f);
            powerUp1.setX(powerUp1.getX() + 350.0f);
            powerUp2.setX(powerUp2.getX() + 350.0f);

            // If the player hits again without jumping or ducking, they lose a life
            lives--;
            if (lives == 0) {
                currentState = GAME_LOST;
                return;
            }
        }
    }


    // Spawn collectibles based on increasing speed
    if (currentTime - lastCSpawnTime >= collectibleSpawnInterval / Background::speed) {
        spawnCollectible();
        lastCSpawnTime = currentTime;
    }

    // Randomize the next spawn time for PowerUp1 (Score Multiplier)
    if (scoreMultiplierCount < 2 && currentTime - lastP1SpawnTime >= randomPowerUp1SpawnDelay / Background::speed) {
        spawnPowerUp1();
        lastP1SpawnTime = currentTime;
        randomPowerUp1SpawnDelay = 15.0f + static_cast<float>(rand() % 5);  // Random delay between 15 and 20 seconds
    }

    // Randomize the next spawn time for PowerUp2 (Jump Boost)
    if (jumpBoostCount < 2 && currentTime - lastP2SpawnTime >= randomPowerUp2SpawnDelay / Background::speed) {
        spawnPowerUp2();
        lastP2SpawnTime = currentTime;
        randomPowerUp2SpawnDelay = 20.0f + static_cast<float>(rand() % 5);  // Random delay between 20 and 25 seconds
    }

    // Spawn obstacles more frequently as speed increases
    if (currentTime - lastOSpawnTime >= obstacleSpawnInterval / Background::speed) {
        spawnObstacle();
        lastOSpawnTime = currentTime;
    }

    // Check for collisions with collectibles and power-ups
    if (collectible.checkCollision(player.getX(), player.getY(), player.getWidth(), player.getHeight())) {
        collectible.applyEffect(score);  // Add 25 to the score
    }

    // Activate and handle score multiplier
    if (powerUp1.checkCollision(player.getX(), player.getY(), player.getWidth(), player.getHeight())) {
        if (powerUp1ActivationTime == -1) {  // If power-up is not active
            powerUp1.applyEffect(score, Player::gravity, scoreMultiplier);  // Apply score multiplier
            powerUp1ActivationTime = currentTime;  // Record activation time
        }
    }

    // Activate and handle jump boost
    if (powerUp2.checkCollision(player.getX(), player.getY(), player.getWidth(), player.getHeight())) {
        if (powerUp2ActivationTime == -1) {  // If power-up is not active
            powerUp2.applyEffect(score, Player::gravity, scoreMultiplier);  // Apply jump boost
            powerUp2ActivationTime = currentTime;  // Record activation time
        }
    }

    // Check if 7 seconds have passed since power-ups were activated and deactivate
    if (powerUp1ActivationTime != -1 && currentTime - powerUp1ActivationTime >= 7.0f) {
        powerUp1.removeEffect(score, Player::gravity, scoreMultiplier);  // Remove score multiplier
        powerUp1ActivationTime = -1;  // Reset activation time
    }

    if (powerUp2ActivationTime != -1 && currentTime - powerUp2ActivationTime >= 7.0f) {
        powerUp2.removeEffect(score, Player::gravity, scoreMultiplier);  // Remove jump boost
        powerUp2ActivationTime = -1;  // Reset activation time
    }

    // Increase speed over time
    Background::speed += 0.0001f;

    player.update();  // Update player state
    glutPostRedisplay();  // Trigger display update
}

void restartGame() {
    // Reset game state and variables
    score = 0;
    lives = 3;  // Or however many lives you want to give
    Background::speed = 5.0f;  // Reset the game speed
    gameStartTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;  // Restart the timer
    currentState = RUNNING;  // Set state back to running
    obstacles.clear();  // Clear obstacles
    // Reset other game elements like collectibles, power-ups, etc.
}



void keyboard(unsigned char key, int x, int y) {
    if (currentState == RUNNING) {
        if (key == 'w') {  // Jump with 'w'
            player.jump();
        }
        else if (key == 's') {  // Duck with 's'
            player.duck();
        }
    }
    else {
        // Game is over, allow restarting
        if (key == ' ') {
            restartGame();  // Call function to restart the game
        }
    }
}



void keyboardUp(unsigned char key, int x, int y) {
    if (key == 's') {  // Stop ducking when 's' is released
        player.stopDuck();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Kiwi Infinite Runner");

    // Set the background color
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);  // Sky blue

    setOrthographicProjection();

    // Set up the game loop and input callbacks
    glutDisplayFunc(display);
    glutIdleFunc(updateGame);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);

    glutMainLoop();
    return 0;
}