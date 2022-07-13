/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
#ifdef __APPLE__
#include <GLUT/glut.h>

#else
#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <math.h>

#endif
#include <stdlib.h>

GLfloat sizes[2];
GLfloat step;
GLfloat curSize;
void retupRC()
{

    curSize = sizes[0];
    //...
}

void init()
{
    glClearColor(1, 0.75, 0.79, 1);
    glOrtho(-100, 100, -100, 100, -100, 100);
}

void line(int x1, int y1, int x2, int y2)
{
    glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glEnd();
}

void squre(int x, int y, double a)
{
    glBegin(GL_LINE_LOOP);
    glVertex2d(x, y);
    glVertex2d(x + a, y);
    glVertex2d(x + a, y - a);
    glVertex2d(x, y - a);
    glEnd();
}

void rect(int x, int y, double h, double w)
{
    glBegin(GL_LINE_LOOP);
    glVertex2d(x, y);
    glVertex2d(x + w, y);
    glVertex2d(x + w, y - h);
    glVertex2d(x, y - h);
    glEnd();
}

void triangle(int x, int y, int b, int h)
{
    glBegin(GL_LINE_LOOP);

    glVertex2d(x, y);
    glVertex2d(x + b, y);
    glVertex2d(x, y + h);

    glEnd();
}

void fillCircle(int x, int y, int r)
{

    glBegin(GL_POLYGON);

    for (int i = 0; i < 360; i++)
    {
        glVertex2d(x + r * cos(i), y + r * sin(i));
    }

    glEnd();
}

void circle(int x, int y, double r)
{

    glBegin(GL_LINE_STRIP);

    for (float i = 0; i < 6.3; i += 0.1)
    {
        glVertex2d(x + r * cos(i), y + r * sin(i));
    }

    glEnd();
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);

    line(10, 10, 40, 40);
    line(33, 33, 34, 55);
    squre(12, 15, 20);
    squre(0, 0, 20);

    rect(-10, -10, 30, 50);

    triangle(-40, -40, 20, 20);

    circle(-50, 15, 15);
    fillCircle(0, -70, 20);

    glFlush();
}

int main()
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(10, 10);

    glutCreateWindow("This is a practice glut program by Mahbub Alam");
    init();
    glutDisplayFunc(myDisplay);

    glutMainLoop();

    return 0;
}
