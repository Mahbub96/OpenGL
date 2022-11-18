#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <math.h>

void circle(int x, int y, double h, double w)
{

    glBegin(GL_LINE_STRIP);

    for (float i = 0; i < 10; i += 0.1)
    {
        glVertex2d(x + w * cos(i), y + h * sin(i));
    }

    glEnd();
}
void circleFill(int x, int y, double h, double w)
{

    glBegin(GL_POLYGON);

    for (float i = 0; i < 10; i += 0.1)
    {
        glVertex2d(x + w * cos(i), y + h * sin(i));
    }

    glEnd();
}

void rect(int x, int y, double h, double w)
{
    glPushMatrix();
    glTranslated(x, y, 0);
    glBegin(GL_QUADS);
    glVertex2d(0, 0);
    glVertex2d(0 + w, 0);
    glVertex2d(0 + w, 0 - h);
    glVertex2d(0, 0 - h);
    glEnd();
    glPopMatrix();
}

void tree(int x, int y, double h, double w)
{

    glPushMatrix();
    glTranslated(x, y, 0);
    glScaled(w, h, 0);

    // tree body
    glPushMatrix();
    rect(-20, 70, 300, 50);

    glPopMatrix();

    // leafs
    glPushMatrix();
    glColor3f(0, 0.8, 0);
    circleFill(-100, 70, 100, 100);
    circleFill(-50, 120, 100, 100);
    circleFill(0, 170, 80, 80);
    circleFill(100, 70, 100, 100);
    circleFill(50, 120, 100, 100);
    glPopMatrix();

    // root

    glPopMatrix();
}

void ground()
{
    glPushMatrix();

    glRotated(-30, 1, 0, 0);
    glBegin(GL_QUADS);
    glColor3d(0.996, 1, 0.901);
    glVertex3d(-600, -1200, 0);
    glVertex3d(600, -1200, 0);

    glColor3d(0, 0.9, 0);
    glVertex3d(600, 220, 0);
    glVertex3d(-600, 220, 0);
    glEnd();
    glPopMatrix();
}

void sky()
{
    glPushMatrix();
    glRotated(-10, 1, 0, 0);
    glColor3d(0, 0.4, 0);
    glBegin(GL_QUADS);
    glColor3d(0, 0, 0.8);
    glVertex3d(-600, 600, 0);

    glColor3d(0, 0, 0.8);
    glVertex3d(600, 600, 0);

    glColor3d(0.6, 1, 1);
    glVertex3d(600, 120, 0);

    glColor3d(0.6, 1, 1);
    glVertex3d(-600, 120, 0);

    glEnd();
    glPopMatrix();
}

void stall(int x, int y, double h, double w)
{
    glPushMatrix();
    glScaled(w, h, 0);
    glTranslated(x, y, 0);
    glPushMatrix();
    glRotated(80, 1, 0, 0);
    rect(0, 0, 100, 180);
    glPopMatrix();

    rect(0, -300, 100, 180);

    glPopMatrix();
}