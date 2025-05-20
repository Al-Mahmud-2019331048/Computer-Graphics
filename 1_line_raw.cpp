#include<GL/gl.h>
#include<GL/glut.h>

#include<bits/stdc++.h>
using namespace std;

void setPixel(float x,float y){
    glVertex3f(x,y,0.0);
}

void directEquation(double x1,double y1,double x2, double y2){

    if(x1==x2){
        double y_mini=min(y1,y2);
        double y_maxi=max(y1,y2);
        for(double y=y_mini;y<y_maxi;y++) setPixel(x1,y);
        return;
    }

    double m=(y2-y1)/(x2-x1);
    double c=y1-m*x1;

    if(fabs(m) <= 1){
        double x_st=min(x1,x2);
        double x_end=max(x1,x2);

        for(double x=x_st;x<=x_end;x++){
            double y=m*x+c;
            setPixel(x,y);
        }
    }
    else{
        double y_st=min(y1,y2);
        double y_end=max(y1,y2);

        for(double y=y_st;y<=y_end;y++){
            double x=(y-c)/m;
            setPixel(x,y);
        }
    }

}

void DDA(double x1,double y1,double x2,double y2)
{
    double dx=x2-x1;
    double dy=y2-y1;

    double m=dy/dx;

    if(fabs(m) <=1 ){
        double y=y1;
        for(double x=x1;x<=x2;x++){
            setPixel(x,y);
            x++;
            y+=m;
        }
    }
    else{
        double x=x1;
        for(double y=y1;y<=y2;y++){
            setPixel(x,y);
            y++;
            x+=(1/m);
        }
    }
}

void bresenham(double x1,double y1, double x2, double y2){
    double dx=x2-x1;
    double dy=y2-y1;
    double d=2*dy-dx;

    double x=x1,y=y1;

    while(x<=x2){
        setPixel(-y,x);
        if(d<0){
            d+=2*dy; x++;
        }
        else{
            d+= 2*(dy-dx);
            x++; y++;
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
    bresenham(-6.0 * c, -1.0 * c, 6.0 * c, 1 * c);
    glEnd();
    glFlush();
}


void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glOrtho(-100,100,-100,100,-2,2);
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(1024,1024);
    glutInitWindowPosition(10, 10);

    glutCreateWindow("Graphics:");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return EXIT_SUCCESS;
}
