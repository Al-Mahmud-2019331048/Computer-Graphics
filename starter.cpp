#include <GL/glut.h>
#include <iostream>

using namespace std;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    // Draw the original lines (red)
    glColor3f(1.0, 0.0, 0.0);


    glFlush();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1000, 0, 1000);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Graphics");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
