#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;

// Define the clipping window boundaries
const int x_min = -100, y_min = -100;
const int x_max = 100,  y_max = 100;

struct Point {
    double x, y;
};

typedef vector<Point> Polygon;

// Function to check if a point is inside the clipping window
bool inside(Point p, Point edgeStart, Point edgeEnd) {
    return (edgeEnd.x - edgeStart.x) * (p.y - edgeStart.y) - (edgeEnd.y - edgeStart.y) * (p.x - edgeStart.x) >= 0;
}

// Function to compute intersection of polygon edge with clipping edge
Point intersection(Point p1, Point p2, Point edgeStart, Point edgeEnd) {
    double A1 = p2.y - p1.y;
    double B1 = p1.x - p2.x;
    double C1 = A1 * p1.x + B1 * p1.y;

    double A2 = edgeEnd.y - edgeStart.y;
    double B2 = edgeStart.x - edgeEnd.x;
    double C2 = A2 * edgeStart.x + B2 * edgeStart.y;

    double det = A1 * B2 - A2 * B1;
    if (det == 0) return p1; // Parallel lines

    double x = (B2 * C1 - B1 * C2) / det;
    double y = (A1 * C2 - A2 * C1) / det;
    return {x, y};
}

// Sutherland-Hodgman polygon clipping algorithm
Polygon sutherlandHodgmanClip(Polygon poly, Polygon clipper) {
    Polygon clippedPoly = poly;
    for (size_t i = 0; i < clipper.size(); i++) {
        Point edgeStart = clipper[i];
        Point edgeEnd = clipper[(i + 1) % clipper.size()];
        Polygon newPoly;

        for (size_t j = 0; j < clippedPoly.size(); j++) {
            Point current = clippedPoly[j];
            Point prev = clippedPoly[(j + clippedPoly.size() - 1) % clippedPoly.size()];

            bool currInside = inside(current, edgeStart, edgeEnd);
            bool prevInside = inside(prev, edgeStart, edgeEnd);

            if (prevInside && currInside) {
                newPoly.push_back(current);
            } else if (prevInside && !currInside) {
                newPoly.push_back(intersection(prev, current, edgeStart, edgeEnd));
            } else if (!prevInside && currInside) {
                newPoly.push_back(intersection(prev, current, edgeStart, edgeEnd));
                newPoly.push_back(current);
            }
        }
        clippedPoly = newPoly;
    }
    return clippedPoly;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Define concave polygon to be clipped
    Polygon poly = {{-120, 50}, {-30, 150}, {50, 100}, {30, 30}, {120, 50}, {50, -50}};

    // Define clipping window as polygon
    Polygon clipper = {{x_min, y_min}, {x_max, y_min}, {x_max, y_max}, {x_min, y_max}};

    // Draw clipping window (green rectangle)
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
    for (Point p : clipper) glVertex2f(p.x, p.y);
    glEnd();

    // Draw original concave polygon (red)
//    glColor3f(1.0, 0.0, 0.0);
//    glBegin(GL_LINE_LOOP);
//    for (Point p : poly) glVertex2f(p.x, p.y);
//    glEnd();

    // Clip polygon using Sutherland-Hodgman algorithm
    Polygon clippedPoly = sutherlandHodgmanClip(poly, clipper);

    // Draw clipped polygon (blue)
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    for (Point p : clippedPoly) glVertex2f(p.x, p.y);
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
    glutCreateWindow("Sutherland-Hodgman Polygon Clipping");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
