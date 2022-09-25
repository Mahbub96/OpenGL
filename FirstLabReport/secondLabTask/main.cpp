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
    glOrtho(-400, 350, -400, 400, -300, 300);
}

void Triangle(float angle, float scale)
{
    float xCord = 45 / scale;
    float yCord = 75 / scale;
    glPushMatrix();

    glTranslatef(0, 0, 0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glColor3f(0, 0, 0);
    glColor3ub(156, 156, 89);

    glBegin(GL_TRIANGLES);
    glVertex2d(xCord, yCord);
    glColor3ub(128, 128, 65);
    glVertex2d(-xCord, yCord);
    glColor3ub(156, 156, 89);
    glVertex2d(0, 0);
    glEnd();

    glPopMatrix();
}

void halfTriangle(float angle)
{
    glPushMatrix();

    glTranslatef(0, 0, 0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    // glColor3f(1.0, 0.1, 0.1);

    glColor3ub(48, 48, 45);
    glBegin(GL_TRIANGLES);
    glVertex2d(45, 75);
    glVertex2d(-45, 75);
    glVertex2d(0, 0);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex2d(45 / 2.3, 75 / 2.3);
    glVertex2d(-45 / 2.3, 75 / 2.3);
    glVertex2d(0, 0);
    glEnd();

    glPopMatrix();
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.1, 0.1, 0.1);

    // create n
    glPushMatrix();
    glTranslatef(-300, 0, 0);
    halfTriangle(30);
    halfTriangle(90);
    halfTriangle(-30);
    halfTriangle(-90);

    glPopMatrix();

    // create O
    glPushMatrix();
    glTranslatef(-120, 0, 0);

    Triangle(30, 1);
    Triangle(90, 1);
    Triangle(150, 1);
    Triangle(210, 1);
    Triangle(270, 1);
    Triangle(330, 1);

    glPopMatrix();

    // create d
    glPushMatrix();
    glTranslatef(60, 0, 0);

    halfTriangle(30);
    halfTriangle(90);
    halfTriangle(150);
    halfTriangle(210);
    halfTriangle(270);
    halfTriangle(330);

    // making top of d
    glPushMatrix();
    glTranslatef(0, 86, 0);
    halfTriangle(-90);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(108, 120, 0);
    halfTriangle(90);
    glPopMatrix();

    glPopMatrix();

    // create e
    glPushMatrix();
    glTranslatef(240, 0, 0);

    halfTriangle(-30);
    halfTriangle(30);
    halfTriangle(90);
    halfTriangle(150);

    // extra part of e
    glPushMatrix();
    glTranslatef(30, 0, 0);
    glColor3ub(48, 48, 45);
    glBegin(GL_POLYGON);
    glVertex2d(0, 0);
    glVertex2d(45, 25);
    glVertex2d(45, 45);
    glVertex2d(0, 45);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-30, -106, 0);
    halfTriangle(-30);
    glPopMatrix();

    glPushMatrix();

    Triangle(30, 4);
    Triangle(90, 4);
    Triangle(150, 4);
    Triangle(210, 4);
    Triangle(270, 4);
    Triangle(330, 4);
    glPopMatrix();

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
