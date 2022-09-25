/*
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>

#else
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

void color(int r, int g, int b)
{
    float r1 = r / 255;
    float g1 = g / 255;
    float b1 = b / 255;
    glColor3f(r1, g1, b1);
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);
    // top

    glColor3f(1, 0.6, 0.4);
    glBegin(GL_POLYGON);
    glVertex2d(0, 400);
    glVertex2d(100, 340);
    glVertex2d(0, 290);
    glVertex2d(-100, 340);
    glEnd();

    // top cube right

    glColor3f(0.8, 0.4, 0.2);
    glBegin(GL_POLYGON);
    glVertex2d(0, 290);
    glVertex2d(100, 340);
    glVertex2d(100, 240);
    glVertex2d(0, 190);
    glEnd();

    // top cube left

    glColor3f(0.8, 0.2, 0.2);
    glBegin(GL_POLYGON);
    glVertex2d(0, 290);
    glVertex2d(0, 190);
    glVertex2d(-100, 240);
    glVertex2d(-100, 340);
    glEnd();

    // top hex

    glColor3f(1, 0.6, 0.4);
    glBegin(GL_POLYGON);
    glVertex2d(0, 190);
    glVertex2d(200, 290);
    glVertex2d(300, 210);
    glVertex2d(0, 60);
    glVertex2d(-300, 210);
    glVertex2d(-200, 290);
    glEnd();

    // left hex

    glColor3f(0.8, 0.2, 0.2);
    glBegin(GL_POLYGON);
    glVertex2d(-300, 210);
    glVertex2d(0, 60);
    glVertex2d(0, -40);
    glVertex2d(-200, 50);
    glVertex2d(-200, -190);
    glVertex2d(-300, -110);
    glEnd();

    // left bottom rect

    glColor3f(0.8, 0.4, 0.2);
    glBegin(GL_POLYGON);
    glVertex2d(-200, 50);
    glVertex2d(-100, 10);
    glVertex2d(-100, -110);
    glVertex2d(-200, -190);
    glEnd();

    // right hex

    glColor3f(0.8, 0.4, 0.2);
    glBegin(GL_POLYGON);
    glVertex2d(0, 60);
    glVertex2d(300, 210);
    glVertex2d(300, -110);
    glVertex2d(200, -190);
    glVertex2d(200, 50);
    glVertex2d(0, -40);
    glEnd();

    // right bottom rect

    glColor3f(0.8, 0.2, 0.2);
    glBegin(GL_POLYGON);
    glVertex2d(100, 0);
    glVertex2d(200, 50);
    glVertex2d(200, -190);
    glVertex2d(100, -110);
    glEnd();

    // bottom cube -----

    // top

    glColor3f(1, 0.6, 0.4);
    glBegin(GL_POLYGON);
    glVertex2d(0, -40);
    glVertex2d(100, -100);
    glVertex2d(0, -150);
    glVertex2d(-100, -100);
    glEnd();

    // top cube right

    glColor3f(0.8, 0.4, 0.2);
    glBegin(GL_POLYGON);
    glVertex2d(0, -150);
    glVertex2d(100, -100);
    glVertex2d(100, -200);
    glVertex2d(0, -265);
    glEnd();

    // top cube left

    glColor3f(0.8, 0.2, 0.2);
    glBegin(GL_POLYGON);
    glVertex2d(0, -150);
    glVertex2d(0, -265);
    glVertex2d(-100, -200);
    glVertex2d(-100, -100);
    glEnd();
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
