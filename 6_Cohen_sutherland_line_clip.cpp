#include <GL/glut.h>
#include <iostream>
using namespace std;

// Define the clipping window boundaries
const int x_min = -100, y_min = -100;
const int x_max = 100,  y_max = 100;

// Region codes (4-bit)
const int INSIDE = 0;   //0000
const int LEFT   = 1;   //0001
const int RIGHT  = 2;   //0010
const int BOTTOM = 4;   //0100
const int TOP    = 8;   //1000

// Function to compute the region code for a point (x, y)
int computeCode(double x, double y) {
    int code = INSIDE;
    if (x < x_min)       code |= LEFT;
    if (x > x_max)       code |= RIGHT;
    if (y < y_min)       code |= BOTTOM;
    if (y > y_max)       code |= TOP;
    return code;
}

// Cohen-Sutherland algorithm for line clipping
bool CohenSutherlandClip(double &x1, double &y1, double &x2, double &y2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    bool accept = false;

    while (true) {
        if (code1 == 0 && code2 == 0) {  //both true , fully visible
            accept = true;
            break;
        } else if (code1 & code2) {  // not visible, single &
            break;
        } else {  //clipping candidate
            double x, y;
            int codeOut = code1 ? code1 : code2;  //if code1=1, code1, else code2
            double slope = (x2 - x1) != 0 ? (y2 - y1) / (x2 - x1) : 1e9;

            if (codeOut & TOP) {
                x = x1 + (y_max - y1) / slope;
                y = y_max;
            } else if (codeOut & BOTTOM) {
                x = x1 + (y_min - y1) / slope;
                y = y_min;
            } else if (codeOut & RIGHT) {
                y = y1 + slope * (x_max - x1);
                x = x_max;
            } else if (codeOut & LEFT) {
                y = y1 + slope * (x_min - x1);
                x = x_min;
            }

            if (codeOut == code1) {
                x1 = x; y1 = y;
                code1 = computeCode(x1, y1);
            } else {
                x2 = x; y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }
    return accept;
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

    // Apply Cohen-Sutherland and draw clipped lines (blue)
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    for (int i = 0; i < numLines; i++) {
        clip_lines[i][0] = orig_lines[i][0];
        clip_lines[i][1] = orig_lines[i][1];
        clip_lines[i][2] = orig_lines[i][2];
        clip_lines[i][3] = orig_lines[i][3];

        bool visible = CohenSutherlandClip(clip_lines[i][0], clip_lines[i][1], clip_lines[i][2], clip_lines[i][3]);
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
    glutCreateWindow("Cohen-Sutherland Line Clipping");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
