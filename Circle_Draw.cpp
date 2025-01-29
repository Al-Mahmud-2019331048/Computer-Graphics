#ifdef _WIN32
#include <windows.h>  // Only for Windows
#endif

#include <GL/glut.h>   // OpenGL Library for Rendering
#include <cmath>
#include <iostream>

using namespace std;

int centerX = 0, centerY = 0; // Center of the circle
int radius = 100; // Radius of the circle

// Function to plot symmetrical points
void plotPoint(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// 1️⃣ Cartesian Equation Method: (x-h)^2 + (y-k)^2 = r^2
void drawCircle_Cartesian(int h, int k, int r) {
    int x, y;
    for (x = -r; x <= r; x++) {
        y = round(sqrt(r * r - x * x));
        plotPoint(h + x, k + y);
        plotPoint(h + x, k - y);
    }
}

// 2️⃣ Polar Coordinates Method: x = r * cos(θ), y = r * sin(θ)
void drawCircle_Polar(int h, int k, int r) {
    float theta;
    for (theta = 0; theta <= 2 * M_PI; theta += 0.01) {
        int x = round(r * cos(theta));
        int y = round(r * sin(theta));
        plotPoint(h + x, k + y);
    }
}

// 3️⃣ Bresenham's Circle Algorithm
void drawCircle_Bresenham(int h, int k, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;

    while (x <= y) {
        plotPoint(h + x, k + y);
        plotPoint(h - x, k + y);
        plotPoint(h + x, k - y);
        plotPoint(h - x, k - y);
        plotPoint(h + y, k + x);
        plotPoint(h - y, k + x);
        plotPoint(h + y, k - x);
        plotPoint(h - y, k - x);

        if (d < 0)
            d += 4 * x + 6;
        else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

// 4️⃣ Midpoint Circle Algorithm
void drawCircle_Midpoint(int h, int k, int r) {
    int x = 0, y = r;
    int d = 1 - r;

    while (x <= y) {
        plotPoint(h + x, k + y);
        plotPoint(h - x, k + y);
        plotPoint(h + x, k - y);
        plotPoint(h - x, k - y);
        plotPoint(h + y, k + x);
        plotPoint(h - y, k + x);
        plotPoint(h + y, k - x);
        plotPoint(h - y, k - x);

        if (d < 0)
            d += 2 * x + 3;
        else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

// Display Function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    // Drawing all four circles
//    glColor3f(1.0, 0.0, 0.0); // Red
//    drawCircle_Cartesian(centerX, centerY, radius);

    glColor3f(0.0, 1.0, 0.0); // Green
    drawCircle_Polar(centerX, centerY, radius);
//
//    glColor3f(0.0, 0.0, 1.0); // Blue
//    drawCircle_Bresenham(centerX, centerY, radius);
//
//    glColor3f(1.0, 1.0, 0.0); // Yellow
//    drawCircle_Midpoint(centerX, centerY, radius);

    glFlush();
}

// Initialize OpenGL
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 200, -200, 200);
}

// Main Function
int main(int argc, char **argv) {
    cout << "Enter center (h, k): ";
    cin >> centerX >> centerY;
    cout << "Enter radius: ";
    cin >> radius;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Circle Drawing Algorithms");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
