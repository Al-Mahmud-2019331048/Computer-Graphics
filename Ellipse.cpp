//Abdulla Al Mahmud

#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>
#include <bits/stdc++.h>
using namespace std;

// Function to plot a pixel at (x, y)
void setPixel(float x, float y)
{
    glVertex3f(x, y, 0.0);
}

// Equation method for ellipse
void polynomial_method(double a, double b, double h, double k)
{
    float x, y;
    for (x = h - a; x <= h + a; x += 0.01)    // Loop over x from h-a to h+a
    {
        if ((x - h) * (x - h) <= a * a)    // Check if x is within the valid range
        {
            y = k + b * sqrt(1 - (x - h) * (x - h) / (a * a)); // Upper half of the ellipse
            glVertex2f(x, y);  // Plot upper half
            y = k - b * sqrt(1 - (x - h) * (x - h) / (a * a)); // Lower half of the ellipse
            glVertex2f(x, y);  // Plot lower half
        }
    }

}

// Trigonometric method for ellipse
void trigonometric_method(double a, double b, double h, double k)
{
    for (double theta = 0; theta <= 2 * M_PI; theta += 0.001)
    {
        double x = a * cos(theta) + h;
        double y = b * sin(theta) + k;
        setPixel(x, y);
    }
}

// Midpoint method for ellipse
void midpoint_method(double a, double b, double h, double k)
{
    double x = 0, y = b;
    double dx = 0, dy = 2 * a * a * y;
    double d1 = (b * b) - (a * a * b) + (0.25 * a * a);  // Initial decision parameter

    // First region: When slope is less than 1 (x moves faster than y)
    while (dx < dy)
    {
        setPixel(x + h, y + k);
        setPixel(-x + h, y + k);
        setPixel(x + h, -y + k);
        setPixel(-x + h, -y + k);

        x++;
        dx += 2 * b * b;

        if (d1 < 0)
        {
            d1 += b * b + dx;
        }
        else
        {
            y--;
            dy -= 2 * a * a;
            d1 += b * b + dx - dy;
        }
    }

    // Second region: When slope is greater than 1 (y moves faster than x)
    double d2 = (b * b) * (x + 0.5) * (x + 0.5) + (a * a) * (y - 1) * (y - 1) - (a * a * b * b);  // Initial decision parameter

    while (y >= 0)
    {
        setPixel(x + h, y + k);
        setPixel(-x + h, y + k);
        setPixel(x + h, -y + k);
        setPixel(-x + h, -y + k);

        y--;
        dy -= 2 * a * a;

        if (d2 > 0)
        {
            d2 += a * a - dy;
        }
        else
        {
            x++;
            dx += 2 * b * b;
            d2 += a * a - dy + dx;
        }
    }
}

// Function to rotate a point (x, y) around center (h, k) by angle alpha
void rotatePoint(double &x, double &y, double h, double k, double alpha)
{
    double rad = alpha * M_PI / 180.0; // Convert degrees to radians
    double x_new = h + (x - h) * cos(rad) - (y - k) * sin(rad);
    double y_new = k + (x - h) * sin(rad) + (y - k) * cos(rad);
    x = x_new;
    y = y_new;
}
// Bresenham method for ellipse with rotation
void midpoint_method_rotate(double a, double b, double h, double k, double alpha)
{
    double x = 0, y = b;
    double dx = 0, dy = 2 * a * a * y;
    double d1 = (b * b) - (a * a * b) + (0.25 * a * a);  // Initial decision parameter

    // First region: When slope is less than 1 (x moves faster than y)
    while (dx < dy)
    {
        //shift
        double x1 = x + h, y1 = y + k;
        double x2 = -x + h, y2 = y + k;
        double x3 = x + h, y3 = -y + k;
        double x4 = -x + h, y4 = -y + k;

        //rotate
        rotatePoint(x1, y1, h, k, alpha);
        rotatePoint(x2, y2, h, k, alpha);
        rotatePoint(x3, y3, h, k, alpha);
        rotatePoint(x4, y4, h, k, alpha);

        setPixel(x1, y1);
        setPixel(x2, y2);
        setPixel(x3, y3);
        setPixel(x4, y4);

        x++;
        dx += 2 * b * b;

        if (d1 < 0)
        {
            d1 += b * b + dx;
        }
        else
        {
            y--;
            dy -= 2 * a * a;
            d1 += b * b + dx - dy;
        }
    }

    // Second region: When slope is greater than 1 (y moves faster than x)
    double d2 = (b * b) * (x + 0.5) * (x + 0.5) + (a * a) * (y - 1) * (y - 1) - (a * a * b * b);  // Initial decision parameter

    while (y >= 0)
    {
        double x1 = x + h, y1 = y + k;
        double x2 = -x + h, y2 = y + k;
        double x3 = x + h, y3 = -y + k;
        double x4 = -x + h, y4 = -y + k;

        rotatePoint(x1, y1, h, k, alpha);
        rotatePoint(x2, y2, h, k, alpha);
        rotatePoint(x3, y3, h, k, alpha);
        rotatePoint(x4, y4, h, k, alpha);

        setPixel(x1, y1);
        setPixel(x2, y2);
        setPixel(x3, y3);
        setPixel(x4, y4);

        y--;
        dy -= 2 * a * a;

        if (d2 > 0)
        {
            d2 += a * a - dy;
        }
        else
        {
            x++;
            dx += 2 * b * b;
            d2 += a * a - dy + dx;
        }
    }
}

// Display function to draw ellipse
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw X and Y axes in Green
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-200, 0);
    glVertex2f(200, 0); // X-axis
    glVertex2f(0, -200);
    glVertex2f(0, 200); // Y-axis
    glVertex2f(200, 200);
    glVertex2f(-200, -200); // X=Y-axis
    glEnd();

    glColor3f(0.0, 1.0, 0.0);  // Green color
    glBegin(GL_POINTS);

    double a = 100.0, b = 50.0;  // Semi-major and semi-minor axes
    double h = 40.0, k = 0.0;  // Ellipse center
    double alpha=60.0; //in degree


    midpoint_method(a, b, h, k);
    //midpoint_method_rotate(a,b,h,k,alpha);

    glEnd();
    glFlush();
}

// OpenGL initialization
void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);  // Set background color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-200.0, 200.0, -200.0, 200.0, -10.0, 10.0);  // Define coordinate system
}

// Main function
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1024, 1024);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("Ellipse Drawing - Equation and Trigonometric Methods");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS;
}
