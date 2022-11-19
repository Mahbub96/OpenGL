#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <math.h>

void circle(int x, int y, double h, double w, double d)
{

    glBegin(GL_LINE_STRIP);

    for (float i = 0; i < 10; i += 0.1)
    {
        glVertex3d(x + w * cos(i), y + h * sin(i), d);
    }

    glEnd();
}
void circleFill(int x, int y, double h, double w, double d)
{

    glBegin(GL_POLYGON);

    for (float i = 0; i < 10; i += 0.1)
    {
        glVertex3d(x + w * cos(i), y + h * sin(i), d);
    }

    glEnd();
}

void rect(int x, int y, double h, double w, double d)
{
    glPushMatrix();
    glTranslated(x, y, d);
    glBegin(GL_QUADS);
    glVertex3d(0, 0, d);
    glVertex3d(0 + w, 0, d);
    glVertex3d(0 + w, 0 - h, d);
    glVertex3d(0, 0 - h, d);
    glEnd();
    glPopMatrix();
}

void cloud(double x, double y, double ratio, double d)
{
    double w = ratio * 0.01;
    double h = ratio * 0.01;
    glPushMatrix();
    glTranslated(x, y, d);
    glScaled(w, h, d);
    glColor3ub(255, 255, 255);
    circleFill(0, 0, 100, 100, 0);
    circleFill(100, 0, 100, 100, 0);
    circleFill(200, 0, 100, 100, 0);
    circleFill(80, 50, 130, 130, 0);
    glBegin(GL_POLYGON);
    glVertex2d(0, 80);
    glVertex2d(200, 80);
    glVertex2d(200, -100);
    glVertex2d(0, -100);
    glEnd();

    glPopMatrix();
}

void tree(double x, double y, double ratio, double d)
{

    double w = ratio * 0.01;
    double h = ratio * 0.01;
    glPushMatrix();
    glTranslated(x, y, d);
    glScaled(w, h, d);

    glColor3ub(0, 180, 0);
    circleFill(0, 0, 100, 100, 0);
    circleFill(20, 60, 95, 95, 0);
    circleFill(80, 100, 75, 75, 0);

    glColor3ub(0, 200, 0);
    circleFill(50, 20, 120, 120, 0);
    circleFill(200, -10, 90, 90, 0);
    circleFill(60, 80, 80, 80, 0);
    circleFill(150, 70, 110, 110, 0);
    circleFill(100, -10, 100, 100, 0);

    glColor3ub(75, 45, 11);
    glBegin(GL_POLYGON);
    glVertex2d(100, 0);
    glVertex2d(110, 0);
    glVertex2d(75, -300);
    glVertex2d(125, -300);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2d(100, -20);
    glVertex2d(200, 0);
    glVertex2d(100, -40);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2d(100, -50);
    glVertex2d(-50, 30);
    glVertex2d(100, -80);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2d(100, 0);
    glVertex2d(50, 80);
    glVertex2d(110, 0);
    glEnd();
    glPopMatrix();
}

void ground()
{
    glPushMatrix();
    glScaled(0.1, 0.1, 0.0);
    glTranslated(0, 0, -100);
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
    glScaled(0.03, 0.03, 0);
    glTranslated(0, 0, -100);
    glRotated(-30, 1, 0, 0);
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
    rect(0, 0, 100, 180, -10);
    glPopMatrix();

    rect(0, -300, 100, 180, -10);

    glPopMatrix();
}

void pond()
{
    glPushMatrix();
    circleFill(0, 0, 10, 10, 5);
    glPopMatrix();
}