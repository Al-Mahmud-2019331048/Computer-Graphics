#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define GRID_SIZE 20
#define GRID_COUNT 20

// Directions
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

// Snake properties
int snakeX[100] = {10}, snakeY[100] = {10};
int snakeLength = 5;
int direction = RIGHT;
bool gameOver = false;

// Food position
int foodX, foodY;

// Function to generate new food at a random position
void generateFood() {
    foodX = rand() % GRID_COUNT;
    foodY = rand() % GRID_COUNT;
}

// Function to draw a square (used for snake and food)
void drawSquare(int x, int y) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + 1, y);
    glVertex2f(x + 1, y + 1);
    glVertex2f(x, y + 1);
    glEnd();
}

// Function to draw the border
void drawBorder() {
    glColor3f(1, 1, 0);  // Yellow color for the border
    glLineWidth(5);       // Set line width for border
    glBegin(GL_LINE_LOOP);
    glVertex2f(0, 0);
    glVertex2f(GRID_COUNT, 0);
    glVertex2f(GRID_COUNT, GRID_COUNT);
    glVertex2f(0, GRID_COUNT);
    glEnd();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (gameOver) {
        glColor3f(1, 0, 0);
        glRasterPos2f(GRID_SIZE / 2 - 2, GRID_SIZE / 2);
        const char *msg = "GAME OVER!";
        while (*msg)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *msg++);
        glFlush();
        return;
    }

    // Draw the border
    drawBorder();

    // Draw food
    glColor3f(1, 0, 0);
    drawSquare(foodX, foodY);

    // Draw snake
    glColor3f(0, 1, 0);
    for (int i = 0; i < snakeLength; i++)
        drawSquare(snakeX[i], snakeY[i]);

    glFlush();
}

// Timer function for movement
void update(int value) {
    if (gameOver)
        return;

    // Move the snake body
    for (int i = snakeLength - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    // Move the snake head
    if (direction == UP)
        snakeY[0]++;
    else if (direction == DOWN)
        snakeY[0]--;
    else if (direction == LEFT)
        snakeX[0]--;
    else if (direction == RIGHT)
        snakeX[0]++;

    // Check for collisions with walls (outside the border)
    if (snakeX[0] < 0 || snakeX[0] >= GRID_COUNT || snakeY[0] < 0 || snakeY[0] >= GRID_COUNT)
        gameOver = true;

    // Check for collisions with itself
    for (int i = 1; i < snakeLength; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
            gameOver = true;
    }

    // Check if food is eaten
    if (snakeX[0] == foodX && snakeY[0] == foodY) {
        snakeLength++;
        generateFood();
    }

    glutPostRedisplay();
    glutTimerFunc(150, update, 0);
}

// Keyboard function to control the snake
void keyboard(int key, int x, int y) {
    if (key == GLUT_KEY_UP && direction != DOWN)
        direction = UP;
    else if (key == GLUT_KEY_DOWN && direction != UP)
        direction = DOWN;
    else if (key == GLUT_KEY_LEFT && direction != RIGHT)
        direction = LEFT;
    else if (key == GLUT_KEY_RIGHT && direction != LEFT)
        direction = RIGHT;
}

// Initialize OpenGL
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glOrtho(0, GRID_COUNT, 0, GRID_COUNT, -1, 1);
    generateFood();
}

// Main function
int main(int argc, char **argv) {
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(900, 900);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Snake Game");
    init();
    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);
    glutTimerFunc(150, update, 0);
    glutMainLoop();
    return 0;
}
