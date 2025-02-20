#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>

// Triangle position and speed
float x_pos = 0.0f, y_pos = 0.0f;
float x_speed = 0.2f, y_speed = 0.2f;

// Triangle color
float r = 1.0f, g = 1.0f, b = 1.0f;

// Window size
const float windowSize = 50.0f;

// Function to generate random colors
void changeColor() {
    r = (float)rand() / RAND_MAX;
    g = (float)rand() / RAND_MAX;
    b = (float)rand() / RAND_MAX;
}

// Function to draw the triangle
void drawTriangle() {
    glBegin(GL_TRIANGLES);
    glColor3f(r, g, b); // Set color
    glVertex2f(x_pos, y_pos + 5.0f);   // Top vertex
    glVertex2f(x_pos - 5.0f, y_pos - 5.0f); // Bottom left vertex
    glVertex2f(x_pos + 5.0f, y_pos - 5.0f); // Bottom right vertex
    glEnd();
}

// Function to update the triangle's position
void update(int value) {
    // Move the triangle
    x_pos += x_speed;
    y_pos += y_speed;

    // Check for collision with window boundaries
    if (x_pos + 5.0f >= windowSize || x_pos - 5.0f <= -windowSize) {
        x_speed = -x_speed; // Reverse direction
        changeColor();      // Change color
    }
    if (y_pos + 5.0f >= windowSize || y_pos - 5.0f <= -windowSize) {
        y_speed = -y_speed; // Reverse direction
        changeColor();      // Change color
    }

    glutPostRedisplay(); // Redraw the scene
    glutTimerFunc(10, update, 0); // Call update every 10 ms
}

// Function to display the triangle
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawTriangle();
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
    glutCreateWindow("Bouncing Triangle");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(10, update, 0); // Start the update loop

    glutMainLoop();
    return 0;
}
