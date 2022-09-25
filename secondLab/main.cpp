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
    glOrtho(-400, 350, -300, 300, -300, 300);
}

void Triangle(float angle)
{
    glPushMatrix();

    glTranslatef(0, 0, 0);
    glRotatef(angle, 0.0, 0.0, 1.0);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2d(45, 75);
    glVertex2d(-45, 75);
    glVertex2d(0, 0);
    glEnd();

    glPopMatrix();
}

void halfTriangle(float angle)
{
    glPushMatrix();

    glTranslatef(0, 0, 0);
    glRotatef(angle, 0.0, 0.0, 1.0);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex2d(45, 75);
    glVertex2d(-45, 75);
    glVertex2d(0, 0);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex2d(45, 75);
    glVertex2d(-45, 75);
    glVertex2d(0, 0);
    glEnd();

    glPopMatrix();
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.1, 0.1);

    // create n
    glPushMatrix();
    glTranslatef(-300, 0, 0);
    halfTriangle(31);
    halfTriangle(91);
    halfTriangle(-29);
    halfTriangle(-89);

    glPopMatrix();

    // create O
    glPushMatrix();
    glTranslatef(-120, 0, 0);

    Triangle(31);
    Triangle(91);
    Triangle(150);
    Triangle(210);
    Triangle(270);
    Triangle(330);

    glPopMatrix();

    // create d
    glPushMatrix();
    glTranslatef(60, 0, 0);

    halfTriangle(31);
    halfTriangle(91);
    halfTriangle(150);
    halfTriangle(210);
    halfTriangle(270);
    halfTriangle(330);

    // making top of d
    glPushMatrix();
    glTranslatef(0, 86, 0);
    halfTriangle(-89);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(112, 120, 0);
    halfTriangle(89);
    glPopMatrix();

    glPopMatrix();

    // create e
    glPushMatrix();
    glTranslatef(240, 0, 0);

    halfTriangle(31);
    halfTriangle(91);
    halfTriangle(150);
    halfTriangle(-29);
    glPopMatrix();

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
