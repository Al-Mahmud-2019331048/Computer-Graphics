#include <GL/gl.h>
#include <GL/glut.h>

#include <bits/stdc++.h>
using namespace std;

// Function to plot a pixel at (x, y)
void setPixel(float x, float y)
{
    glVertex3f(x, y, 0.0);
}

void DirectEqn(double x1, double y1, double x2, double y2) {
    // Handle vertical line case separately to avoid division by zero
    if (x1 == x2) {
        // Line is vertical; iterate through y
        double yStart = min(y1, y2);
        double yEnd = max(y1, y2);
        for (double y = yStart; y <= yEnd; y++) {
            setPixel(round(x1), round(y));
        }
        return;
    }

    double m = (y2 - y1) / (x2 - x1);           // Slope
    double c = y1 - m * x1;                     // Intercept

    // Choose to iterate over x if slope is gentle, else iterate over y
    if (fabs(m) <= 1) {
        // Gentle slope — iterate through x
        double xStart = min(x1, x2);
        double xEnd = max(x1, x2);
        for (double x = xStart; x <= xEnd; x++) {
            double y = m * x + c;
            setPixel(round(x), round(y));
        }
    } else {
        // Steep slope — iterate through y
        double yStart = min(y1, y2);
        double yEnd = max(y1, y2);
        for (double y = yStart; y <= yEnd; y++) {
            double x = (y - c) / m;
            setPixel(round(x), round(y));
        }
    }
}


// Function to draw a line using the DDA Algorithm
void DDA(double x1, double y1, double x2, double y2)
{
    double dx = x2 - x1;
    double dy = y2 - y1;

    int steps = max(fabs(dx), fabs(dy)); // Number of steps is the maximum change in x or y
    double x_inc = dx / steps;  // Increment value for x
    double y_inc = dy / steps;  // Increment value for y

    double x = x1, y = y1;

    for (int i = 0; i <= steps; i++)
    {
        setPixel(round(x), round(y));  // Set pixel at rounded (x, y)
        x += x_inc;
        y += y_inc;
    }
}


// Function to draw a line using Bresenham’s Algorithm
void Bresenham(double x1, double y1, double x2, double y2)
{
    bool steep = fabs(y2 - y1) > fabs(x2 - x1);  // Check if the slope is >=1 or not

    if (steep)    //if |m|>1
    {
        swap(x1, y1);  //mirror to m=1
        swap(x2, y2);
    }

    if (x1 > x2)    // Always draw left to right
    {
        swap(x1, x2);
        swap(y1, y2);
    }

    double dx = x2 - x1, dy = fabs(y2 - y1);
    double p = 2 * dy - dx;  // Decision parameter
    double y = y1;
    int y_step = (y1 < y2) ? 1 : -1;  // Adjust for negative slopes

    for (double x = x1; x <= x2; x++)
    {
        if (steep)
            setPixel(y, x);  // Swap back for steep lines cz we mirroed for |m|>1
        else
            setPixel(x, y);

        if (p >= 0)
        {
            y += y_step;  //dx and dy moves to opposite direction
            p -= 2 * dx;
        }
        p += 2 * dy;
    }
}

// Display function to draw lines
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);  // Green color

    glBegin(GL_POINTS);

    double c = 1.0;  // Scaling factor

    // Test cases for different slopes
//    DDA(-5.0 * c, 5.00 * c, 5.0 * c, -5.00 * c);  // Positive slope (0 < m < 1)
//    DDA(5.0 * c, 5.0 * c, -5.0 * c, -5.0 * c);       // Steep slope (m > 1)
//    DDA(4.0 * c, 6.0 * c, 2.0 * c, 2.0 * c);       // Negative slope (-1 < m < 0)
//    DDA(-5.0 * c, 10.0 * c, 5.0 * c, 0.0 * c);     // m = -1 case
//    DirectEqn(0.0 * c, 0.0 * c, 5.0 * c, 8.0 * c);     // m < -1 case
//
//    directEqn(-5.0 * c, 5.00 * c, 5.0 * c, -5.00 * c);  // Positive slope (0 < m < 1)
//    directEqn(5.0 * c, 5.0 * c, -5.0 * c, -5.0 * c);       // Steep slope (m > 1)
//    directEqn(4.0 * c, 6.0 * c, 2.0 * c, 2.0 * c);       // Negative slope (-1 < m < 0)
    DDA(10.0 * c, 6.0 * c, 10.0 * c, -6.0 * c);     //vertical line
//    Bresenham(2.0 * c, 2.0 * c, -3.0 * c, -6.0 * c);     // m < -1 case

//    Bresenham(-2.0 * c, 8.00 * c, -4.0 * c, 10.00 * c);  // Positive slope (0 < m < 1)
//    Bresenham(3.0 * c, 3.0 * c, 5.0 * c, 8.0 * c);       // Steep slope (m > 1)
//    Bresenham(4.0 * c, 6.0 * c, 2.0 * c, 2.0 * c);       // Negative slope (-1 < m < 0)
//    Bresenham(-5.0 * c, 10.0 * c, 5.0 * c, 0.0 * c);     // m = -1 case
//    Bresenham(2.0 * c, 2.0 * c, -3.0 * c, -6.0 * c);     // m < -1 case

    glEnd();
    glFlush();
}

// OpenGL initialization
void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);  // Set background color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0, 100.0, -100.0, 100.0, -2.0, 2.0);  // Define coordinate system}
}

// Main function
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1024, 1024);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("DDA Line Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS;
}
