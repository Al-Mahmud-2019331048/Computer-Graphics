#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

// Define the clipping window boundaries
const int x_min = -100, y_min = -100;
const int x_max = 100,  y_max = 100;

// Function to check if a point is inside the clipping window
bool inside(double x, double y) {
    return (x >= x_min && x <= x_max && y >= y_min && y <= y_max);
}

// Midpoint Subdivision Algorithm for Line Clipping
bool MidpointSubdivisionClip(double &x1, double &y1, double &x2, double &y2) {
    if (inside(x1, y1) && inside(x2, y2)) {
        return true; // Both endpoints inside
    }
    if ((x1 < x_min && x2 < x_min) || (x1 > x_max && x2 > x_max) ||
        (y1 < y_min && y2 < y_min) || (y1 > y_max && y2 > y_max)) {
        return false; // Both endpoints outside
    }

    double xm = (x1 + x2) / 2.0;
    double ym = (y1 + y2) / 2.0;

    if (fabs(x1 - x2) < 0.5 && fabs(y1 - y2) < 0.5) {
        if (inside(xm, ym)) {
            x1 = xm; y1 = ym;
            return true;
        }
        return false;
    }

    bool firstHalf = MidpointSubdivisionClip(x1, y1, xm, ym);
    bool secondHalf = MidpointSubdivisionClip(xm, ym, x2, y2);
    return firstHalf || secondHalf;
}

// Define multiple line segments
const int numLines = 7;
double orig_lines[numLines][4] = {
    {-150, 50, 150, 50},   // Crosses horizontally
    {-120, -80, 80, 130},  // Diagonal
    {0, -150, 0, 150},     // Vertical through the center
    {50, -50, 150, -150},  // Partially outside
    {-180, 80, -120, 40},  // Fully outside
    {-90, -90, 90, 90},    // Diagonal inside
    {110, 110, 130, 130}   // Completely outside
};

double clip_lines[numLines][4];

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the clipping window (green rectangle)
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x_min, y_min);
        glVertex2f(x_max, y_min);
        glVertex2f(x_max, y_max);
        glVertex2f(x_min, y_max);
    glEnd();

    // Draw the original lines (red)
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    for (int i = 0; i < numLines; i++) {
        glVertex2f(orig_lines[i][0], orig_lines[i][1]);
        glVertex2f(orig_lines[i][2], orig_lines[i][3]);
    }
    glEnd();

    // Apply Midpoint Subdivision and draw clipped lines (blue)
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    for (int i = 0; i < numLines; i++) {
        clip_lines[i][0] = orig_lines[i][0];
        clip_lines[i][1] = orig_lines[i][1];
        clip_lines[i][2] = orig_lines[i][2];
        clip_lines[i][3] = orig_lines[i][3];

        bool visible = MidpointSubdivisionClip(clip_lines[i][0], clip_lines[i][1], clip_lines[i][2], clip_lines[i][3]);
        if (visible) {
            glVertex2f(clip_lines[i][0], clip_lines[i][1]);
            glVertex2f(clip_lines[i][2], clip_lines[i][3]);
        }
    }
    glEnd();

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 200, -200, 200);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Midpoint Subdivision Line Clipping");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
