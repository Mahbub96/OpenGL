#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

double running = 1, isLight0On = 1, isLight1On = 1;
double dx = 0.01, dy, c1 = -48, c2 = -48, c3 = -48, bx = 0, by = 0, posSun = -3;
double width, height;
double angle = 0;

void human_for_stall();
// Initializes 3D rendering
void initRendering()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);   // Enable lighting
    glEnable(GL_LIGHT0);     // Enable light #0    // Enable light #1
    glEnable(GL_NORMALIZE);  // Automatically normalize normals
    glShadeModel(GL_SMOOTH); // Enable smooth shading
}

// Called when the window is resized
void handleResize(int w, int h)
{
    width = w;
    height = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 5.0, -40.0);
    glShadeModel(GL_SMOOTH);
}

void update()
{

    c1 > 48 ? c1 = -48 : c1 += 0.03 * running;
    c2 > 48 ? c2 = -48 : c2 += 0.02 * running;
    c3 > 48 ? c3 = -48 : c3 += 0.01 * running;

    posSun < -7 ? posSun = -3 : posSun -= 0.001 * running;
    angle > 360 ? angle = -360 : angle += 1 * running;

    glutPostRedisplay();
}

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
    glTranslated(0, 0, -3);
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
    glTranslated(0, -100, 10);
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
    glTranslated(0, 0, -6);
    glScaled(0.3, 0.06, 0);
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
    glTranslated(0, -0.3, 5);
    human_for_stall();
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
    glTranslated(0, 0, 10);
    glRotated(90, 1, 0, 0);
    glScaled(1, 1, 5);
    glutSolidTorus(0.2, 0.8, 36, 36);
    glPopMatrix();
}

void pole(double x, double y, double z, double w, double h)
{
    glPushMatrix();
    glTranslated(x, y, z + 5);
    glScaled(w, h, 1);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(0.2, 0.8, 36, 36);
    glPopMatrix();
}

void nagordola()
{

    double inc = 12;
    double subInc = inc / 3;
    pole(0, 0, 0, 1, 34);

    // making center circle using torus
    glTranslated(0.4, 6.5, 13);
    glRotated(angle, 0, 0, 1); /*Rotating Whole Nagordola*/
    glutSolidTorus(0.4, 1.4, 30, 30);

    /* Rotating Pole for bucket 1 and 4 */
    glRotated(120, 0, 0, 1);
    pole(0, 0, 0, 0.4, 34 + inc);
    glPushMatrix();
    /*Bucket 1*/
    glPushMatrix();
    glTranslated(0, -5.5 - subInc, 0);
    glRotated(-angle - 30, 0, 0, 1);
    bucketOfNagordola();
    glPopMatrix();
    /*Bucket 2*/
    glPushMatrix();
    glTranslated(0, 5.5 + subInc, 0);
    glRotated(-angle - 30, 0, 0, 1);
    bucketOfNagordola();
    glPopMatrix();
    glPopMatrix();

    /* Rotating Pole for bucket 2 and 5 */
    glRotated(120, 0, 0, 1);
    pole(0, 0, 0, 0.4, 34 + inc);
    glPushMatrix();
    /*Bucket 2*/
    glPushMatrix();
    glTranslated(0, -5.5 - subInc, 0);
    glRotated(-angle + 30, 0, 0, 1);
    bucketOfNagordola();
    glPopMatrix();
    /*Bucket 5*/
    glPushMatrix();
    glTranslated(0, 5.5 + subInc, 0);
    glRotated(-angle + 30, 0, 0, 1);
    bucketOfNagordola();
    glPopMatrix();
    glPopMatrix();

    /* Rotating Pole for bucket 3 and 6 */
    glRotated(120, 0, 0, 1);
    pole(0, 0, 0, 0.4, 34 + inc);
    glPushMatrix();
    /*Bucket 3*/
    glPushMatrix();
    glTranslated(0, -5.5 - subInc, 0);
    glRotated(-angle, 0, 0, 1);
    bucketOfNagordola();
    glPopMatrix();
    /*Bucket 6*/
    glPushMatrix();
    glTranslated(0, 5.5 + subInc, 0);
    glRotated(-angle, 0, 0, 1);
    bucketOfNagordola();
    glPopMatrix();
    glPopMatrix();
}

void sun()
{

    GLfloat sp = sin(posSun);
    sp > 0.15 ? sp : sp -= 0.2; /* Making forcefully Deep night */
    GLfloat xSunLightPos = cos(posSun);
    GLfloat ySunLightPos = sin(posSun);
    GLfloat ambientColor[] = {1, 1, 1, 0.1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    // Add positioned light
    GLfloat diffuseLightColor0[] = {0.8, 0.8, 0.8, 0.9};
    GLfloat specularLightColor0[] = {0.2, 0.2, 0.2, 0.1f};
    GLfloat lightPos0[] = {xSunLightPos * 45, ySunLightPos * 25, 1, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLightColor0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    // glNormal3f(0.0, -1.0, -1.0);
    glTranslated(0, 0, -20);
    glNormal3d(0, 0, -1);
    glutSolidSphere(10, 100, 100);
}

void belun()
{
    glPushMatrix();
    glColor3ub(51, 153, 255);
    glScaled(1, 2, 1);
    glutSolidSphere(3, 100, 100);
    glPopMatrix();

    /* handle of belun */
    glPushMatrix();
    glColor3ub(220, 25, 25);
    glTranslated(0, -5, 0);
    glRotated(90, 1, 0, 0);
    glScaled(0.1, 0.1, 10);
    glutSolidTorus(1, 1, 20, 20);
    glPopMatrix();
}

void background()
{
    sky();

    glPushMatrix();
    glColor3ub(249, 215, 25);
    glTranslated(cos(posSun) * 45, sin(posSun) * 25, 3.0);
    glScaled(0.3, 0.3, 0.3);
    sun();
    glPopMatrix();

    ground();
}

void circle(float radiusX, float radiusY, float z, int loop)
{
    float angle = 0.0;
    glPushMatrix();
    glBegin(GL_POLYGON);
    for (int i = 0; i < loop; i++)
    {
        angle = 2 * 3.1416 * i / 100;
        glVertex3d(radiusX * cos(angle), radiusY * sin(angle), z);
    }
    glEnd();
    glPopMatrix();
}

void human_for_stall()
{
    glPushMatrix();
    /// head
    glColor3ub(238, 213, 183);
    glScaled(0.9, 1.0, 0.01);
    glutSolidTorus(0.7, 0.7, 10, 10);
    /// hair
    glColor3ub(0, 0, 0);

    circle(1.3, 1.4, 1.1, 50);

    glPushMatrix();
    glTranslated(-0.4, -0.5, 1);
    glRotated(45, 1, 1, 0);
    glPopMatrix();

    /// neck
    glColor3ub(238, 213, 183);
    glTranslated(0, -1.2, 0);
    glScaled(0.6, 1.0, 0.01);
    glutSolidTorus(0.6, 0.6, 10, 10);
    /// body
    glPushMatrix();
    glColor3d(0, 0, 1);
    glTranslated(0, -0.7, 0);
    glBegin(GL_POLYGON);
    glVertex3d(0, 0, 1);
    glVertex3d(1.2, 0.3, 1);
    glVertex3d(2.5, -0.5, 1);
    glVertex3d(2.5, -1.5, 1);
    glVertex3d(1.8, -1.5, 1);
    glVertex3d(-1.8, -1.5, 1);
    glVertex3d(-2.5, -1.5, 1);
    glVertex3d(-2.5, -0.5, 1);
    glVertex3d(-1.2, 0.3, 1);

    glEnd();
    glPopMatrix();
    glPopMatrix();
}
