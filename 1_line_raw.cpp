#include<GL/gl.h>
#include<GL/glut.h>

#include<bits/stdc++.h>
using namespace std;

void setPixel(float x, float y)
{
    glVertex3f(x,y,0.0);
}

void directEqn(double x1, double y1, double x2, double y2)
{
    if(x1==x2)
    {
        for(double y=min(y1,y2); y<=max(y1,y2); y++) setPixel(x1,y);
        return;
    }

    double m=(y2-y1)/(x2-x1);
    double c=y1-m*x1;

    if(fabs(m)<=1){
        double y;
        for(double x=min(x1,x2);x<=max(x1,x2);x++){
            y=m*x+c;
            setPixel(x,y);
        }
    }
    else{
        double x;
        for(double y=min(y1,y2);y<=max(y1,y2);y++){
            x=(y-c)/m;
            setPixel(x,y);
        }
    }
}

void DDA(double x1,double y1,double x2,double y2){
    double dx=x2-x1;
    double dy=y2-y1;

    double m=dy/dx;

    if(fabs(m)<=1){
        double y=y1;
        for(double x=x1;x<x2;x++){
            setPixel(x,y);
            y+=m;
        }
    }
    else{
        double x=x1;
        for(double y=y1;y<=y2;y++){
            setPixel(-y,x);
            x+=1/m;
        }
    }
}

void bresenham(double x1, double y1, double x2, double y2){
    double x=x1,y=y1;
    double dx=x2-x1;
    double dy=y2-y1;
    double d=2*dy-dx;

    while(x<=x2){
        setPixel(-x,y);
        if(d<0){
            dx+=2*dy; x++;
        }
        else{
            dx+=2*(dy-dx);
            x++;y++;
        }
    }
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINES);
    glVertex2f(-100, 0);
    glVertex2f(100, 0); // X-axis
    glVertex2f(0, -100);
    glVertex2f(0, 100); // Y-axis
    glEnd();

    glBegin(GL_POINTS);
    int c=5;
    bresenham(-6.0 * c, 1.0 * c, 6.0 * c, 10 * c);
    glEnd();
    glFlush();
}


void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    glOrtho(-100,100,-100,100,-2.0,2.0);
}


int main(int argc,char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1024,1024);
    glutInitWindowPosition(10,10);

    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Compiler");

    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS;
}
