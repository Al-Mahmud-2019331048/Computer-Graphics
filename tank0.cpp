#include <GL/glut.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define PI 3.14159265

float tankX = 0;              // Tank position
float tankAngle = 90;         // Tank direction (90 degrees = facing up)
float bulletX, bulletY;       // Bullet position
bool bulletFired = false;     // Is the bullet active?
float bulletDirX, bulletDirY; // Bullet direction
float targetX = 20;           // Target position (moves left-right)
bool gameOver = false;        // Is the game over?

// Function to draw a rectangle (used for tank and target)
void drawRectangle(float x, float y, float width, float height) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

// Function to draw a small filled circle (used for bullet)
void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); // Center of the circle
    for (int i = 0; i <= num_segments; i++) {
        float angle = 2.0f * PI * i / num_segments;
        float x = r * cos(angle);
        float y = r * sin(angle);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// Function to draw a rotated tank
void drawTank() {
    glPushMatrix();
    glTranslatef(tankX, -35, 0);
    glRotatef(tankAngle - 90, 0, 0, 1); // Rotate around center
    glTranslatef(-tankX, 35, 0);

    glColor3f(0, 1, 0);
    drawRectangle(tankX - 10, -40, 20, 10); // Tank base
    drawRectangle(tankX - 2, -30, 4, 10);   // Tank turret

    glPopMatrix();
}

// Display function
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    if (gameOver) {
        glColor3f(1, 0, 0);
        glRasterPos2f(-10, 0);
        const char *msg = "GAME OVER!";
        while (*msg)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *msg++);
        glFlush();
        return;
    }

    drawTank();

    // Draw the bullet (small yellow circle)
    if (bulletFired) {
        glColor3f(1, 1, 0); // Yellow bullet
        drawCircle(bulletX, bulletY, 2, 10); // Radius = 2, 10 segments
    }

    // Draw the target
    glColor3f(1, 0, 0); // Red target
    drawRectangle(targetX, 20, 10, 10);

    glFlush();
}

// Timer function for animations
void update(int value) {
    if (!gameOver) {
        // Move bullet in its direction
        if (bulletFired) {
            bulletX += bulletDirX * 2;
            bulletY += bulletDirY * 2;

            // Reset bullet if it goes off-screen
            if (bulletX < -50 || bulletX > 50 || bulletY > 50 || bulletY < -50) {
                bulletFired = false;
            }
        }

        // Move target left and right
        targetX += 0.2;
        if (targetX > 30 || targetX < -30)
            targetX = -30;

        // Check for collision (if bullet hits target)
        if (bulletFired &&
            bulletX + 2 > targetX && bulletX < targetX + 10 &&
            bulletY + 2 > 20 && bulletY < 30) {
            gameOver = true;
        }

        glutPostRedisplay();
        glutTimerFunc(16, update, 0);
    }
}

// Special function to rotate tank and fire bullet
void specialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) {
        tankAngle += 5; // Rotate left
    }
    if (key == GLUT_KEY_RIGHT) {
        tankAngle -= 5; // Rotate right
    }
    if (key == GLUT_KEY_UP) {
        if (!bulletFired) {
            bulletFired = true;
            // Start bullet at the tip of the turret
            bulletX = tankX + cos(tankAngle * PI / 180) * 10;
            bulletY = -35 + sin(tankAngle * PI / 180) * 10;
            // Set bullet movement direction
            bulletDirX = cos(tankAngle * PI / 180);
            bulletDirY = sin(tankAngle * PI / 180);
        }
    }
    glutPostRedisplay();
}

// Initialize OpenGL
void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glOrtho(-50, 50, -50, 50, -1, 1);
}

// Main function
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rotating Tank Game");
    init();

    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys); // Handle arrow keys
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
