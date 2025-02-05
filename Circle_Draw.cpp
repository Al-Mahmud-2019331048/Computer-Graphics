#include <GL/glut.h>   // OpenGL Library for Rendering
#include <cmath>
#include <iostream>

using namespace std;

int centerX = 0, centerY = 0; // Center of the circle
int radius = 100; // Radius of the circle

// Function to plot symmetrical points
void plotPoint(float x, float y)
{
    glVertex3f(x, y, 0.0);
}

// 1️⃣ Cartesian Equation Method: (x-h)^2 + (y-k)^2 = r^2
void drawCircle_Cartesian(int h, int k, int r)
{
    int x, y;
    for (x = -r; x <= r; x++)
    {
        y = round(sqrt(r * r - x * x));
        plotPoint(h + x, k + y);
        plotPoint(h + x, k - y);
    }
}

// 2️⃣ Polar Coordinates Method: x = r * cos(θ), y = r * sin(θ)
void drawCircle_Polar(int h, int k, int r)
{
    float theta;
    for (theta = 0; theta <= 2 * M_PI; theta += 0.01)
    {
        int x = round(r * cos(theta));
        int y = round(r * sin(theta));
        plotPoint(h + x, k + y);
    }
}

// 3️⃣ Bresenham's Circle Algorithm 90-45
void drawCircle_Bresenham(int h, int k, int r)
{
    int x = 0, y = r;
    int d = 3 - 2 * r;

    while (x <= y)
    {
//        plotPoint(h + x, k + y);  //90 45
        plotPoint(h - x, k + y);  //
//        plotPoint(h + x, k - y);
//        plotPoint(h - x, k - y);
//        plotPoint(h + y, k + x);
//        plotPoint(h - y, k + x);
//        plotPoint(h + y, k - x);
//        plotPoint(h - y, k - x);

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

void drawCircle_Bresenham_15_60(int h,int k,int r)
{
    // 60 to 45
    int x=(r * cos(60*M_PI/180.0));
    int y=(r * sin(60*M_PI/180.0));
    int d = 3 - 2 * r;
    while(x<=y)
    {
        plotPoint(h + x, k + y);
        if (d < 0)
            d += 4 * x + 6;
        else
        {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
    // 15 to 45
    x=(r * cos(15*M_PI/180.0));
    y=(r * sin(15*M_PI/180.0));
    d = 3 - 2 * r;
    while(y<=x)
    {
        plotPoint(h + x, k + y);
        if (d < 0)
            d += 4 * y + 6;
        else
        {
            d += 4 * (y - x) + 10;
            x--;
        }
        y++;
    }
}

void drawCircle_Bresenham_120_150(int h,int k,int r)
{
    // 60 to 45 - for reflection
    int x=(r * cos(60*M_PI/180.0));
    int y=(r * sin(60*M_PI/180.0));
    int d = 3 - 2 * r;
    while(x<=y)
    {
        plotPoint(h - x, k + y);  // -x for reflection
        if (d < 0)
            d += 4 * x + 6;
        else
        {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
    // 30 to 45
    x=(r * cos(30*M_PI/180.0));
    y=(r * sin(30*M_PI/180.0));
    d = 3 - 2 * r;
    while(y<=x)
    {
        plotPoint(h - x, k + y);  //-x
        if (d < 0)
            d += 4 * y + 6;
        else
        {
            d += 4 * (y - x) + 10;
            x--;
        }
        y++;
    }
}

void drawCircle_Bresenham_210_260(int h,int k,int r)
{
    // 80 to 30 - for reflection
    int x=(r * cos(80*M_PI/180.0));
    int y=(r * sin(80*M_PI/180.0));
    int d = 3 - 2 * r;
    while(x<=y)
    {
        plotPoint(h - x, k - y);  // -x and -y for reflection
        if (d < 0)
            d += 4 * x + 6;
        else
        {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
    // 30 to 45
    x=(r * cos(30*M_PI/180.0));
    y=(r * sin(30*M_PI/180.0));
    d = 3 - 2 * r;
    while(y<=x)
    {
        plotPoint(h - x, k - y);  //-x and -y for reflection
        if (d < 0)
            d += 4 * y + 6;
        else
        {
            d += 4 * (y - x) + 10;
            x--;
        }
        y++;
    }
}

void drawCircle_Bresenham_280_340(int h,int k,int r)
{
    // 80 to 45 - for reflection
    int x=(r * cos(80*M_PI/180.0));
    int y=(r * sin(80*M_PI/180.0));
    int d = 3 - 2 * r;
    while(x<=y)
    {
        plotPoint(h + x, k - y);  // -x and -y for reflection
        if (d < 0)
            d += 4 * x + 6;
        else
        {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
    // 20 to 45
    x=(r * cos(20*M_PI/180.0));
    y=(r * sin(20*M_PI/180.0));
    d = 3 - 2 * r;
    while(y<=x)
    {
        plotPoint(h + x, k - y);  //-x and -y for reflection
        if (d < 0)
            d += 4 * y + 6;
        else
        {
            d += 4 * (y - x) + 10;
            x--;
        }
        y++;
    }
}

void drawCircle_BresenhamArc0to30(int h, int k, int r) {
    int x = r;
    int y  = 0;
    int d = 3 - 2 * r;
    int limit = r*cos(30*M_PI/180.0);

    while (x >= limit) {
        plotPoint(h + x, k + y);
        if (d < 0)
            d += 4 * y + 6;
        else {
            d += 4 * (y - x) + 10;
            x--;
        }
        y++;
    }
}

void drawCircle_Bresenham_150_250(int h, int k, int r)
{
    // 0-30 for 150 - 180
    int x = r;
    int y  = 0;
    int d = 3 - 2 * r;
    int limit = r*cos(30*M_PI/180.0);

    while (x >= limit) {
        plotPoint(h - x, k + y);
        if (d < 0)
            d += 4 * y + 6;
        else {
            d += 4 * (y - x) + 10;
            x--;
        }
        y++;
    }

    //0 - 45 for 180 - 225
    x=(r * cos(0*M_PI/180.0));
    y=(r * sin(0*M_PI/180.0));
    d = 3 - 2 * r;
    while(y<=x)
    {
        plotPoint(h - x, k - y);  // -x and -y for reflection
        if (d < 0)
            d += 4 * y + 6;
        else
        {
            d += 4 * (y - x) + 10;
            x--;
        }
        y++;
    }
    //70- 45 for 225 - 250
    x=(r * cos(70*M_PI/180.0));
    y=(r * sin(70*M_PI/180.0));
    d = 3 - 2 * r;
    while(x<=y)
    {
        plotPoint(h - x, k - y);  // -x and -y for reflection
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




// 4️⃣ Midpoint Circle Algorithm
void drawCircle_Midpoint(int h, int k, int r)
{
    int x = 0, y = r;
    int d = 1 - r;

    while (x <= y)
    {
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
        else
        {
            d += 2 * (x - y) + 5;
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
    drawCircle_Bresenham_150_250(centerX, centerY, radius);

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
