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
#include "Universe.h"
#include <stdlib.h>
#include <math.h>

#define PI 180
#define TWO_PI 360
int row,
    col;
int scl = 20;
int ang = 1;
float angle = 40;

void init()
{
    glClearColor(1, 0.75, 0.79, 1);
    glOrtho(-600, 600, -600, 600, -600, 600);
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);

    // glTranslatef(300, 300.0, 0.0);
    Universe *u = new Universe(800, 600);

    // glRotatef(40.0, 0.0, 0.0, 0.0);
    // glRotated(angle, 1.0, 0.0, 0.0);
    u->draw();

    // glRotatef(0.0, 1.0, 0.0, 0.0);

    Planet *sun = new Planet(350, 50, pow(10, 3), 50);
    sun->draw();

    glColor3f(0.85, 0, 0);

    glutSolidSphere(100, 20, 20);
    // glutWireSphere(50, 20, 20);
    angle += 0.2;
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
