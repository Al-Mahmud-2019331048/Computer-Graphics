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

void rectangle(int x1,int y1,int x2,int y2){
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x1, y2);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
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

    int a=3,b=4,c=10,d=16;

    rectangle(a, b, c, d);
    glFlush();
}

// OpenGL initialization
void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);  // Set background color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0, 20.0, -20.0, 20.0, -10.0, 10.0);  // Define coordinate system
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
