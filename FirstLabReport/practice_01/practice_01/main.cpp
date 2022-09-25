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


#ifdef __APPLE__
#include <GLUT/glut.h>

#else
#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glext.h>

#endif


//#include <GL/freeglut.h>
//#include <GL/gl.h>
#include <stdlib.h>
#include <math.h>

#define PI 180
#define TWO_PI 360
int row, col;
int scl = 20;
int ang = 1;

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
    glBegin(GL_LINE_LOOP);
    glVertex2d(x, y);
    glVertex2d(x + a, y);
    glVertex2d(x + a, y - a);
    glVertex2d(x, y - a);
    glEnd();
}

void rect(int x, int y, double h, double w)
{
    glBegin(GL_LINE_LOOP);
    glVertex2d(x, y);
    glVertex2d(x + w, y);
    glVertex2d(x + w, y - h);
    glVertex2d(x, y - h);
    glEnd();
}

void triangle(int x, int y, int b, int h)
{
    glBegin(GL_LINE_LOOP);

    glVertex2d(x, y);
    glVertex2d(x + b, y);
    glVertex2d(x, y + h);

    glEnd();
}

void fillCircle(int x, int y, int r)
{

    //glBegin(GL_POLYGON);

    for (int i = 0; i < 360; i++)
    {
        glBegin(GL_POINTS);
        glVertex2d(x + r * cos(i), y + r * sin(i));
        glEnd();
    }

    //glEnd();
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

void love(int X, int Y, float r)
{
    glBegin(GL_TRIANGLES);

    for (float i = 0; i < TWO_PI; i += 0.01)
    {
        float x = X + r * (16 * pow(sin(i), 3));

        float y = Y + r * (13 * cos(i) - 5 * cos(2 * i) - 2 * cos(3 * i) - cos(4 * i));
        glVertex2d(x, y);
    }

    glEnd();
}

void printGraph(int x, int y)
{

    // print cord system
    glLineWidth(2);
    glBegin(GL_LINES);

    glVertex2d(-x, 0);
    glVertex2d(x, 0);

    glVertex2d(0, -y);
    glVertex2d(0, y);

    glEnd();

    // print cord system
    glLineWidth(1);

    glBegin(GL_LINES);
    for (int i = -x; i < x; i++)
    {
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3d(i, y, 20);
        glVertex3d(i, -y, -20);

        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3d(x, i, -50);
        glVertex3d(-x, i, 50);
    }
    glEnd();

    // for (int i = -y; i < y; i++)
    // {

    //     for (int j = -x; j < x; j++)
    //     {
    //         squre(j, i, 1);
    //     }
    // }
}

void visualRandom(int x, int y)
{

    glLineWidth(0.01);
    glBegin(GL_LINE_STRIP);
    for (int i = -50; i < x; i++)
    {
        int a = i;
        int b = rand() % y;
        glVertex2d(a, b);
    }

    glEnd();
}

void terrain_generation()
{

    int w = 600;
    int h = 600;
    col = w / scl;
    row = h / scl;
    ang += 10;
    glRotated(PI / 3, ang++, PI, PI);

    for (int y = -row; y <= row; y++)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_TRIANGLE_STRIP);
        glColor3f(1, 0.0f, 0.0f);

        for (int x = -col; x <= col; x++)
        {

            glVertex2d(x * scl, y * scl);
            glVertex2d(x * scl, (y + 1) * scl);
        }
        glEnd();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}
void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);

    // printGraph(600, 600);

        line(10, 10, 40, 40);
        line(33, 33, 34, 55);
        squre(12, 15, 20);
        squre(0, 0, 20);
        rect(-10, -10, 30, 50);
        triangle(-40, -40, 20, 20);
        circle(-50, 15, 15);
        fillCircle(0, 30, 20);


    // love(0, 20, 26.2);

    // visualRandom(600, 300);
    // terrain_generation();

    glFlush();
}

void setup(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(10, 10);

    glutCreateWindow("This is a practice glut program by Mahbub Alam");
    init();
}

void draw()
{

    glutDisplayFunc(myDisplay);

    glutMainLoop();
}

int main(int argc, char **argv)
{

    setup(argc, argv);

    while (true)
    {
        draw();
    }

    return 0;
}
