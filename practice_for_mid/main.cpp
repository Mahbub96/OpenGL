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
#define PI 3.1416
#include <stdlib.h>
#include "Car.h"

void init()
{
    glClearColor(1, 1, 1, 0);
    glOrtho(-600, 600, -600, 600, -600, 600);
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);

    for (float i = -500; i < 600; i += 300)
    {
        for (float j = -500; j < 600; j += 300)
        {
            Car(i, j).draw();
        }
    }

    glFlush();
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(500, 300);

    glutCreateWindow("This is a practice glut program by Mahbub Alam");
    init();

    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}
