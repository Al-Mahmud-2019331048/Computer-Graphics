#include <GL/glut.h>
#include <iostream>
#include <vector>

using namespace std;

// Clipping window boundaries
float xmin = -50, xmax = 50, ymin = -50, ymax = 50;

// Points coordinates
vector<pair<float, float>> points = {
    {10, 10},  // Inside the clipping window
    {60, 60},  // Outside the clipping window
    {-30, 40}, // Inside the clipping window
    {-60, -60},// Outside the clipping window
};

// Function to check if the point is inside the clipping window
bool isInsideClippingWindow(float x, float y) {
    return (x >= xmin && x <= xmax && y >= ymin && y <= ymax);
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Draw Clipping Window (Rectangle)
    glColor3f(0.0, 0.0, 1.0); // Blue color
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    // Iterate over all points and check if they are inside or outside the clipping window
    for (auto &point : points) {
        if (isInsideClippingWindow(point.first, point.second))
            glColor3f(0.0, 1.0, 0.0); // Green if inside
        else
            glColor3f(1.0, 0.0, 0.0); // Red if outside

        // Draw Point
        glPointSize(6);
        glBegin(GL_POINTS);
        glVertex2f(point.first, point.second);
        glEnd();
    }

    glutSwapBuffers();
}

// Keyboard input to change point position
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': for (auto &point : points) point.second += 5; break; // Move up
        case 's': for (auto &point : points) point.second -= 5; break; // Move down
        case 'a': for (auto &point : points) point.first -= 5; break; // Move left
        case 'd': for (auto &point : points) point.first += 5; break; // Move right
        case 'q': exit(0); // Quit program
    }

    // Clip the points to stay within the boundaries of the clipping window
    for (auto &point : points) {
        if (point.first < xmin) point.first = xmin;
        if (point.first > xmax) point.first = xmax;
        if (point.second < ymin) point.second = ymin;
        if (point.second > ymax) point.second = ymax;
    }

    glutPostRedisplay();
}

// Initialization
void init() {
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Multiple Point Clipping using OpenGL");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
