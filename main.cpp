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
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void printLineWithColor(double x1, double y1, double x2, double y2, int R, int G, int B)
{

    glColor3f(R, G, B);

    glBegin(GL_LINES);

    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glEnd();
}

void printLine(double x1, double y1, double x2, double y2)
{

    glColor3f(0, 0, 0);

    glBegin(GL_LINES);

    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glEnd();
}

void printLike3dBox()
{
    // print first layer
    printLine(-50, 50, 50, 50);
    printLine(-50, 50, -50, -50);
    printLine(-50, -50, 50, -50);
    printLine(50, -50, 50, 50);

    // second layer
    printLine(-30, 70, 70, 70);
    printLine(-30, 70, -30, -30);
    printLine(-30, -30, 70, -30);
    printLine(70, -30, 70, 70);

    // connected corner
    printLine(-30, 70, -50, 50);
    printLine(-30, -30, -50, -50);
    printLine(50, -50, 70, -30);
    printLine(50, 50, 70, 70);
}

void init()
{
    glClearColor(1, 0.75, 0.79, 1);
    glOrtho(-100, 100, -100, 100, -100, 100);
}

void myDisplay()
{

    glClear(GL_COLOR_BUFFER_BIT);

    printLike3dBox();

    // for printing Door
    printLineWithColor(-15, -50, -15, 10, 1, 0, 0);
    printLineWithColor(15, -50, 15, 10, 1, 0, 0);
    printLineWithColor(-15, 10, 15, 10, 1, 0, 0);

    printLineWithColor(-2, -50, -2, 10, 1, 0, 0);
    printLineWithColor(2, -50, 2, 10, 1, 0, 0);

    glFlush();
}

// simple line drawing
int main()
{

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(10, 10);

    glutCreateWindow("First Glut Line");
    init();
    glutDisplayFunc(myDisplay);

    glutMainLoop();

    return 0;
}
