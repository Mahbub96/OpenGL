#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <math.h>

void drawComponent(double x, double y, double h, double w, void (*component)())
{
    glPushMatrix();
    glTranslated(x, y, 0);
    glScaled(w * 0.01, h * 0.01, 1);
    component();
    glPopMatrix();
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

void cloud()
{
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
}

void tree()
{

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
}

void ground()
{
    glPushMatrix();
    glScaled(0.1, 0.1, 0.0);
    glTranslated(0, 0, -100);
    glRotated(-30, 1, 0, 0);

    glBegin(GL_QUADS);
    glColor3d(0.996, 1, -1);
    glVertex3d(-600, -1200, -1);
    glVertex3d(600, -1200, -1);

    glColor3d(0, 0.9, 0);
    glVertex3d(600, 220, -1);
    glVertex3d(-600, 220, -1);
    glEnd();

    glPopMatrix();
}

void sky()
{
    glPushMatrix();
    glScaled(0.03, 0.03, 0);
    glTranslated(0, 0, 1000);
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

void stand(float x, float y)
{
    glPushMatrix();
    glColor3f(0.3, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3d(x - 0.3, y, 5);
    glVertex3d(x - 0.5, y - 12, 5);
    glVertex3d(x, y - 12, 5);
    glVertex3d(x, y, 5);
    glEnd();
    glPopMatrix();
}

void square_table(float x1, float y1, float x2, float y2)
{
    glPushMatrix();
    glBegin(GL_QUADS);
    glVertex3d(x1, y1, 5);
    glVertex3d(x1, y2, 5);
    glVertex3d(x2, y2, 5);
    glVertex3d(x2, y1, 5);
    glEnd();
    glPopMatrix();
}

void stall()
{

    glPushMatrix();
    glColor3f(1.0f, 0.92f, 0.75f);
    glBegin(GL_QUADS);
    glVertex3d(6, 6, 5);
    glVertex3d(-6, 6, 5);
    glVertex3d(-10, 2, 5);
    glVertex3d(3, 2, 5);
    glEnd();
    glPopMatrix();

    /// triangle side
    glPushMatrix();
    glColor3f(1.0f, 0.95f, 0.80f);
    glBegin(GL_TRIANGLES);
    glVertex3d(6, 6, 5);
    glVertex3d(3, 2, 5);
    glVertex3d(10, 4, 5);
    glEnd();
    glPopMatrix();

    stand(-9.0, 2.0);
    stand(3.0, 2.0);
    stand(9.5, 4.0);

    glPushMatrix();
    glColor3f(1.0f, 0.95f, 0.80f);
    glBegin(GL_QUADS);
    glVertex3d(2.5, -4, 5);
    glVertex3d(2.5, -9.5, 5);
    glVertex3d(9, -7.5, 5);
    glVertex3d(9, -2, 5);
    glEnd();
    glPopMatrix();

    square_table(3, -4, -9, -9.5);
    glColor3f(0.7f, 0.5f, 0.0f);
    square_table(3, -2, -9, -7.5);
    square_table(2.5, -2, 9, -7.5);

    glPopMatrix();
}

void hill()
{

    glBegin(GL_POLYGON);
    glColor3ub(171, 97, 84);
    glVertex2d(0, 200);
    glColor3ub(83, 40, 31);
    glVertex2d(150, 0);
    glVertex2d(-150, 0);
    glEnd();
}

void river()
{

    glColor3ub(0, 0, 200);

    glBegin(GL_POLYGON);

    glVertex3d(0, 0, 5);
    glVertex3d(300, 0, 5);
    glVertex3d(300, 500, 5);
    glVertex3d(0, 500, 5);

    glEnd();

    glPopMatrix();
}

void boat()
{

    glColor3ub(0, 0, 200);

    glBegin(GL_POLYGON);
    glVertex3d(0, 0, 5.5);
    glVertex3d(10, 0, 5.5);
    glVertex3d(10, 10, 5.5);
    glVertex3d(0, 10, 5.5);

    glEnd();
}

void bucketOfNagordola()
{
    glPushMatrix();
    glRotated(30, 1, 0, 0);
    glutSolidTorus(0.2, 0.8, 360, 360);
    glPopMatrix();
}

void pole(double x, double y, double z, double w, double h)
{
    glPushMatrix();
    glTranslated(x, y, z);
    glScaled(w, h, 1);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(0.2, 0.8, 360, 360);
    // bucketOfNagordola();
    glPopMatrix();
}

void roundablePole()
{
}

void nagordola()
{
    pole(0, 4, 1, 1, 14);
}