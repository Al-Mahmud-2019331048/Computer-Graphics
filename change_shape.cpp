#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Object properties
float x_pos = 0.0f, y_pos = 0.0f; // Position
float x_speed = 0.3f, y_speed = 0.2f; // Speed

// Color properties
float r = 1.0f, g = 1.0f, b = 1.0f;

// Window boundary size
const float windowSize = 50.0f;

// Shape flag (0 = Triangle, 1 = Square, 2 = Circle)
int shapeType = 0;

// Function to generate random colors
void changeColor() {
    r = (float)rand() / RAND_MAX;
    g = (float)rand() / RAND_MAX;
    b = (float)rand() / RAND_MAX;
}

// Function to switch shape (Triangle → Square → Circle)
void switchShape() {
    shapeType = (shapeType + 1) % 3; // Cycle between 0, 1, and 2
}

// Function to draw the object
void drawObject() {
    glColor3f(r, g, b); // Set color

    if (shapeType == 0) {  // Draw Triangle
        glBegin(GL_TRIANGLES);
        glVertex2f(x_pos, y_pos + 5.0f);   // Top vertex
        glVertex2f(x_pos - 5.0f, y_pos - 5.0f); // Bottom left vertex
        glVertex2f(x_pos + 5.0f, y_pos - 5.0f); // Bottom right vertex
        glEnd();
    }
    else if (shapeType == 1) {  // Draw Square
        glBegin(GL_QUADS);
        glVertex2f(x_pos - 5.0f, y_pos - 5.0f);
        glVertex2f(x_pos + 5.0f, y_pos - 5.0f);
        glVertex2f(x_pos + 5.0f, y_pos + 5.0f);
        glVertex2f(x_pos - 5.0f, y_pos + 5.0f);
        glEnd();
    }
    else if (shapeType == 2) {  // Draw Circle
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x_pos, y_pos); // Center
        for (int i = 0; i <= 360; i += 10) {
            float angle = i * (3.14159f / 180.0f);  // Convert degrees to radians
            float x = x_pos + 5.0f * cos(angle);
            float y = y_pos + 5.0f * sin(angle);
            glVertex2f(x, y);
        }
        glEnd();
    }
}

// Function to update the object's position
void update(int value) {
    // Move the object
    x_pos += x_speed;
    y_pos += y_speed;

    // Check for collision with window boundaries
    if (x_pos + 5.0f >= windowSize || x_pos - 5.0f <= -windowSize) {
        x_speed = -x_speed; // Reverse direction
        changeColor();      // Change color
        switchShape();      // Change shape
    }
    if (y_pos + 5.0f >= windowSize || y_pos - 5.0f <= -windowSize) {
        y_speed = -y_speed; // Reverse direction
        changeColor();      // Change color
        switchShape();      // Change shape
    }

    glutPostRedisplay(); // Redraw the scene
    glutTimerFunc(10, update, 0); // Call update every 10 ms
}

// Function to display the object
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawObject();
    glutSwapBuffers();
}

// Function to initialize OpenGL settings
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black
    glOrtho(-windowSize, windowSize, -windowSize, windowSize, -1.0f, 1.0f); // Set orthographic projection
    srand(time(0)); // Seed random number generator
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Bouncing Shape");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(10, update, 0); // Start the update loop

    glutMainLoop();
    return 0;
}
