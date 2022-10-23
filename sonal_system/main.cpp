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
    glClearColor(1, 0.75, 0.79, 1);
    glOrtho(-600, 600, -600, 600, -600, 600);
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
    glBegin(GL_QUADS);
    glVertex2d(x, y);         // initial position
    glVertex2d(x + a, y);     // Right side line
    glVertex2d(x + a, y - a); // Right to down side line
    glVertex2d(x - a, y - a); // initial to down side

    glEnd();
}

void rect(int x, int y, double h, double w)
{
    glBegin(GL_QUADS);
    glVertex2d(x, y);
    glVertex2d(x + w, y);
    glVertex2d(x + w, y - h);
    glVertex2d(x - w, y - h);
    glEnd();
}

void circle(int x, int y, double r)
{

    glBegin(GL_LINE_STRIP);

    for (float i = 0; i < 10; i += 0.1)
    {
        glVertex2d(x + r * cos(i), y + r * sin(i));
    }

    glEnd();
}


void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, .5, 0);

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(10, 10);

    glutCreateWindow("Canvas Using GLUT");
    init();

    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 0;
}
