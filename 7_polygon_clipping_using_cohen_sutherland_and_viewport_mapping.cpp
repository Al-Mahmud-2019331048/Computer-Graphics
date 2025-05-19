#include <GL/glut.h>
#include <iostream>

using namespace std;

//window boundaries
const int x_min = 200, y_min = 250;
const int x_max = 650,  y_max = 650;

//viewport boundaries
const int vx_min = 20, vy_min = 20;
const int vx_max = 220,  vy_max = 120;

const double sx = (vx_max - vx_min * 1.0)  / (x_max - x_min);
const double sy = (vy_max - vy_min * 1.0) / (y_max - y_min);

const int INSIDE = 0;
const int LEFT   = 1;
const int RIGHT  = 2;
const int BOTTOM = 4;
const int TOP    = 8;



int computeCode(double x, double y)
{
    int code = INSIDE;
    if (x < x_min)       code |= LEFT;
    if (x > x_max)       code |= RIGHT;
    if (y < y_min)       code |= BOTTOM;
    if (y > y_max)       code |= TOP;
    return code;
}


bool CohenSutherlandClip(double &x1, double &y1, double &x2, double &y2)
{
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    bool accept = false;

    while (true)
    {
        if (code1 == 0 && code2 == 0)
        {
            accept = true;
            break;
        }
        else if (code1 & code2)
        {
            break;
        }
        else
        {
            double x, y;
            int codeOut = code1 ? code1 : code2;
            double slope = (x2 - x1) != 0 ? (y2 - y1) / (x2 - x1) : 1e9;

            if (codeOut & TOP)
            {
                x = x1 + (y_max - y1) / slope;
                y = y_max;
            }
            else if (codeOut & BOTTOM)
            {
                x = x1 + (y_min - y1) / slope;
                y = y_min;
            }
            else if (codeOut & RIGHT)
            {
                y = y1 + slope * (x_max - x1);
                x = x_max;
            }
            else if (codeOut & LEFT)
            {
                y = y1 + slope * (x_min - x1);
                x = x_min;
            }

            if (codeOut == code1)
            {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            }
            else
            {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }
    return accept;
}


const int numLines = 11;
double orig_lines[numLines][4] =
{
    {100, 420, 320, 200},
    {320, 200, 600, 150},
    {600, 150, 825, 400},
    {825, 400, 675, 750},
    {675, 750, 675, 720},
    {675, 720, 600, 500},
    {600, 500, 600, 850},
    {600, 850, 400, 675},
    {400, 675, 325, 650},
    {325, 650, 250, 450},
    {250, 450, 100, 420}
};

double clip_lines[numLines][4];



pair<double, double> windowToViewportMapping(double x, double y)
{
    double vx = sx * (x - x_min) + vx_min;
    double vy = sy * (y - y_min) + vy_min;

    return {vx, vy};
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

//    cout << "sx: " << sx << " sy: " << sy << endl;

    // Draw the viewport
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(vx_min, vy_min);
    glVertex2f(vx_max, vy_min);
    glVertex2f(vx_max, vy_max);
    glVertex2f(vx_min, vy_max);
    glEnd();

    // Draw the window (yellow)
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x_min, y_min);
    glVertex2f(x_max, y_min);
    glVertex2f(x_max, y_max);
    glVertex2f(x_min, y_max);
    glEnd();

    // Draw the original lines (red)
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    for (int i = 0; i < numLines; i++)
    {
        glVertex2f(orig_lines[i][0], orig_lines[i][1]);
        glVertex2f(orig_lines[i][2], orig_lines[i][3]);
    }
    glEnd();



    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    for (int i = 0; i < numLines; i++)
    {
        clip_lines[i][0] = orig_lines[i][0];
        clip_lines[i][1] = orig_lines[i][1];
        clip_lines[i][2] = orig_lines[i][2];
        clip_lines[i][3] = orig_lines[i][3];

        bool visible = CohenSutherlandClip(clip_lines[i][0], clip_lines[i][1], clip_lines[i][2], clip_lines[i][3]);
        if (visible)
        {
            pair<double, double> p1 = windowToViewportMapping(clip_lines[i][0], clip_lines[i][1]);
            pair<double, double> p2 = windowToViewportMapping(clip_lines[i][2], clip_lines[i][3]);
            //draw the clipped lines in window
            glColor3f(1.0, 0.0, 1.0);
            glVertex2f(clip_lines[i][0], clip_lines[i][1]);
            glVertex2f(clip_lines[i][2], clip_lines[i][3]);

            cout << p1.first << " " << p1.second << endl;
            cout << p2.first << " " << p2.second << endl;
            //draw the clipped lines in viewport
            glVertex2f(p1.first, p1.second);
            glVertex2f(p2.first, p2.second);
        }
    }
    glEnd();

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
    glutCreateWindow("Cohen-Sutherland Line Clipping");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
