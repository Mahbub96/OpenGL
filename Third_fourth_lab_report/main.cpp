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

/*
#ifdef __APPLE__
#include <GLUT/glut.h>

#else
#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glext.h>

#endif
*/

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <math.h>

void init()
{
    glClearColor(1, 1, 1, 1);
    glOrtho(-600, 600, -600, 600, -600, 600);
}

void direct_line(float x1, float y1, float x2, float y2)
{

    double m = (y2 - y1) / (x2 - x1);
    float b = y1 - m * x1;

    glColor3ub(0, 0, 0);
    glBegin(GL_POINTS);
    glVertex2d(x1, y1);
    if (abs(m) > 1)
    {
        while (y1 < y2)
        {

            x1 = (1 / m) * (++y1 - b);
            glVertex2d(x1, y1);
        }
    }
    else
    {
        while (x1 < x2)
        {
            y1 = m * ++x1 + b;
            glVertex2d(x1, y1);
        }
    }

    glVertex2d(x2, y2);
    glEnd();
}

void dda_line(float x1, float y1, float x2, float y2)
{
    float m = (y2 - y1) / (x2 - x1);

    glBegin(GL_POINTS);
    if (abs(m) > 1)
    {
        while (y1 != y2)
        {
            x1 += (1 / m);
            glVertex2d(x1, ++y1);
        }
    }
    else
    {
        while (y1 != y2)
        {
            y1 += m;
            glVertex2d(++x1, y1);
        }
    }
    glEnd();
}

void Bresenhem(float x1, float y1, float x2, float y2)
{
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);
    int x1 = 0, y1 = 0;
    int x2 = 250, y2 = 450;

    direct_line(x1, y1, x2, y2);
    dda_line(x1 + 100, y1, x2 + 100, y2);

    glFlush();
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(10, 10);

    glutCreateWindow("This is a practice glut program by Mahbub Alam");
    init();

    glutDisplayFunc(myDisplay);

    glutMainLoop();

    return 0;
}
