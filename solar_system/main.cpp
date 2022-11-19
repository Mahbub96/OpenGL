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
#include <iostream>

double X = 0, Y = 0;
double I;

class Planet
{
    int posX, posY;

public:
    double radius;
    double r, g, b;

    Planet()
    {
        posX = posY = 0;
        radius = 10;
        r = g = b = 1;
    }
    Planet(int x, int y, double r)
    {
        posX = x;
        posY = y;
        radius = r;
        r = g = b = 1;
    }

    void color(double r, double g, double b)
    {
        this->r = r / 255;
        this->g = g / 255;
        this->b = b / 255;
    }
    static void start_rotate()
    {
        X = cos(I);
        Y = sin(I);
        I += 0.006;
        glutPostRedisplay();
    }

    void draw()
    {

        glColor3d(r, g, b);
        glutSolidSphere(radius, 50, 50);
    }
};

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

void circle(int x, int y, double r)
{

    glBegin(GL_LINE_STRIP);

    for (float i = 0; i < 10; i += 0.1)
    {
        glVertex2d(x + r * cos(i), y + r * sin(i));
    }

    glEnd();
}

void encreaseRadius()
{
    X++;
    glutPostRedisplay();
}
void decreaseRadius()
{
    X--;
    glutPostRedisplay();
}

void keyPress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
        glutIdleFunc(encreaseRadius);
        glutPostRedisplay();
        break;
    case 'd':
        decreaseRadius();
        glutPostRedisplay();
        glutIdleFunc(NULL);
        break;
    case 'r':
        glutIdleFunc(Planet::start_rotate);
        glutPostRedisplay();
    default:
        break;
    }
}
void myDisplay()
{
    double angle = 70;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, .5, 0);
    glPushMatrix();
    glRotated(angle, 1, 0, 0);

    // making sun
    glPushMatrix();
    Planet *sun = new Planet(0, 0, 100);
    sun->color(200, 0, 0);
    sun->draw();
    glPopMatrix();

    // making marcury and circle line for marcury
    glPushMatrix();
    circle(0, 0, 200);
    glTranslated(X * 200, Y * 200, 0);
    Planet *murcary = new Planet(0, 0, 50);
    murcary->color(255, 0, 0);
    murcary->draw();
    glPopMatrix();

    // marking venus and it's circle line
    glPushMatrix();

    circle(0, 0, 400);

    glTranslated(X * 400, Y * 400, 0);
    Planet *earth = new Planet(0, 0, 70);
    earth->color(10, 200, 0);
    earth->draw();

    // moon
    glPushMatrix();
    glTranslated(X * 30, Y * 30, 0);
    circle(0, 0, 30);
    Planet *moon = new Planet(0, 0, 30);
    moon->color(180, 180, 180);
    moon->draw();
    glPopMatrix();

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

    glutCreateWindow("Canvas Using GLUT");
    init();

    glutDisplayFunc(myDisplay);
    // glutSpecialFunc(keyPress);
    glutKeyboardFunc(keyPress);
    glutMainLoop();

    return 0;
}
