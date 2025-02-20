#include <GL/glut.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define PI 3.14159265

// Tank parameters
float tankX = 0;              // Tank horizontal position
float tankAngle = 90;         // Tank angle in degrees (90 means facing up)
// We assume the pivot point for the tank is at (tankX, -35)

// Bullet parameters
float bulletX, bulletY;       // Bullet position
bool bulletFired = false;     // Is the bullet active?
float bulletDirX, bulletDirY; // Bullet movement direction
float bulletSpeed = 2.0;      // Bullet movement speed
const float bulletRadius = 2.0;  // Radius for drawing and collision

// Target parameters
float targetX = 20;           // Target horizontal position (moves left-right)
bool gameOver = false;        // Is the game over?

// Window boundaries (as defined by glOrtho)
const float leftBound = -50;
const float rightBound = 50;
const float bottomBound = -50;
const float topBound = 50;

// Function to draw a rectangle (for tank and target)
void drawRectangle(float x, float y, float width, float height) {
    glBegin(GL_QUADS);
      glVertex2f(x, y);
      glVertex2f(x + width, y);
      glVertex2f(x + width, y + height);
      glVertex2f(x, y + height);
    glEnd();
}

// Function to draw a small filled circle (for bullet)
void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
      glVertex2f(cx, cy); // Center
      for (int i = 0; i <= num_segments; i++) {
          float angle = 2.0f * PI * i / num_segments;
          glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
      }
    glEnd();
}

// Function to draw the tank with rotation
void drawTank() {
    glPushMatrix();
      // Translate so that the pivot is at (tankX, -35)
      glTranslatef(tankX, -35, 0);
      // Rotate the tank: when tankAngle is 90, no rotation is applied.
      glRotatef(tankAngle - 90, 0, 0, 1);
      // Translate back so drawing is relative to the original coordinate system
      glTranslatef(-tankX, 35, 0);

      glColor3f(0, 1, 0);
      // Draw tank base (for example, a rectangle centered at tankX)
      drawRectangle(tankX - 10, -40, 20, 10);
      // Draw tank turret (positioned so its tip is at a fixed offset when tankAngle is 90)
      drawRectangle(tankX - 2, -30, 4, 10);
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

    // Draw bullet (yellow circle)
    if (bulletFired) {
        glColor3f(1, 1, 0);
        drawCircle(bulletX, bulletY, bulletRadius, 10);
    }

    // Draw target (red rectangle)
    glColor3f(1, 0, 0);
    drawRectangle(targetX, 20, 10, 10);

    glFlush();
}

// Timer function for animations
void update(int value) {
    if (!gameOver) {
        // Move bullet if active
        if (bulletFired) {
            bulletX += bulletDirX * bulletSpeed;
            bulletY += bulletDirY * bulletSpeed;

            // Bounce off left and right walls
            if (bulletX - bulletRadius < leftBound) {
                bulletX = leftBound + bulletRadius;
                bulletDirX = -bulletDirX;
            }
            else if (bulletX + bulletRadius > rightBound) {
                bulletX = rightBound - bulletRadius;
                bulletDirX = -bulletDirX;
            }
            // Bounce off bottom and top walls
            if (bulletY - bulletRadius < bottomBound) {
                bulletY = bottomBound + bulletRadius;
                bulletDirY = -bulletDirY;
            }
            else if (bulletY + bulletRadius > topBound) {
                bulletY = topBound - bulletRadius;
                bulletDirY = -bulletDirY;
            }
        }

        // Move target left and right
        targetX += 0.2;
        if (targetX > 30 || targetX < -30)
            targetX = -30;

        // Check for collision (simple AABB check)
        if (bulletFired &&
            bulletX + bulletRadius > targetX && bulletX - bulletRadius < targetX + 10 &&
            bulletY + bulletRadius > 20 && bulletY - bulletRadius < 30) {
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
            // Compute bullet starting position at turret tip.
            // For default orientation (tankAngle == 90), turret tip is at (tankX, -20).
            // The pivot is at (tankX, -35) so offset is (0,15).
            float offset = 15; // Distance from pivot to turret tip
            // Calculate bullet start position using tankAngle in degrees.
            bulletX = tankX + cos(tankAngle * PI / 180) * offset;
            bulletY = -35 + sin(tankAngle * PI / 180) * offset;
            // Set bullet movement direction (same as the tank's facing direction)
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
