#include <GL/glut.h>   // OpenGL Library for Rendering
#include <cmath>
#include <iostream>

using namespace std;

int centerX = 2, centerY = 6; // Center of the circle
int radius = 3*30; // Radius of the circle

// Function to plot symmetrical points
void setPixel(float x, float y)
{
    glVertex3f(x, y, 0.0);
}

// 3️⃣ Bresenham's Circle Algorithm 90-45
void drawCircle_Bresenham(int h, int k, int r)
{
    int x = 0, y = r;
    int d = 3 - 2 * r;

    while (x <= y)
    {
        setPixel(h + x, k + y-6*30);  //- 6*30
        setPixel(h - x+6*30, k + y-6*30);  //+r,-r
        setPixel(h + x, k - y);
        setPixel(h - x+6*30, k - y);  // +6*30
        setPixel(h + y, k + x-6*30);
        setPixel(h - y+6*30, k + x-6*30);  //+r,-r
        setPixel(h + y, k - x); //-6*30
        setPixel(h - y+6*30, k - x);  // +6*30

        if (d < 0)
            d += 4 * x + 6;
        else
        {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

// Display Function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw X and Y axes in Green
    glColor3f(0.0, 1.0, 0.0);

    //draw coordinate lines (x and y)
    glBegin(GL_LINES);
    glVertex2f(-200, 0);
    glVertex2f(200, 0); // X-axis
    glVertex2f(0, -200);
    glVertex2f(0, 200); // Y-axis
    glVertex2f(200, 200);
    glVertex2f(-200, -200); // X=Y-axis
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);

    glColor3f(0.0, 0.0, 1.0); // Blue
    drawCircle_Bresenham(2, 6, 3*30);

    glEnd();
    glFlush();

}

// Initialize OpenGL
void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 200, -200, 200);
}

// Main Function
int main(int argc, char **argv)
{
//    cout << "Enter center (h, k): ";
//    cin >> centerX >> centerY;
//    cout << "Enter radius: ";
//    cin >> radius;

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
