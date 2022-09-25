#include <GL/freeglut.h>

#include <GL/gl.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

#define WIDTH 60
#define HEIGHT 60

void init()
{
    glClearColor(1, 0.75, 0.79, 1);
    glOrtho(-WIDTH, HEIGHT, -WIDTH, HEIGHT, -WIDTH, HEIGHT);
}

void ShowGraph(int x, int y)
{
    glLineWidth(1.5);
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);

    glVertex2d(-x, 0);
    glVertex2d(x, 0);

    glVertex2d(0, y);
    glVertex2d(0, -y);

    glEnd();
    glLineWidth(1);
}

void myDisplay()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, .5, 0);
    ShowGraph(WIDTH, HEIGHT);
    // making sine wave
    glBegin(GL_LINE_STRIP);
    float r = 20;
    for (float i = 0; i <= (M_PI * 2); i += .01)
    {

        float y = sin(i);
        // std::cout << y << std::endl;
        glVertex2d(i, r * y);
    }

    glEnd();

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
    glutMainLoop();
    return 0;
}
