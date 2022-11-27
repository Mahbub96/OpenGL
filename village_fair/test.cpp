#include "mylib.h"

double spinAngle = 0;
void init();
void draw();
void reshape(int w, int h);
void normalKeypress(unsigned char key, int x, int y);
void specialKeypress(int key, int x, int y);
void mousePress(int button, int state, int x, int y);

void update1()
{
    spinAngle += 1;
    glutPostRedisplay();
}

void cube()
{

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(3, 3, 3);
    glVertex3f(-3, 3, 3);
    glVertex3f(-3, -3, 3);
    glVertex3f(3, -3, 3);

    /// back
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(3, 3, -3);
    glVertex3f(-3, 3, -3);
    glVertex3f(-3, -3, -3);
    glVertex3f(3, -3, -3);

    /// left side
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-3, 3, 3);
    glVertex3f(-3, 3, -3);
    glVertex3f(-3, -3, -3);
    glVertex3f(-3, -3, 3);

    /// right side
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(3, 3, 3);
    glVertex3f(3, 3, -3);
    glVertex3f(3, -3, -3);
    glVertex3f(3, -3, 3);

    /// top side
    glColor3f(0.5f, 0.7f, 1.0f);
    glVertex3f(-3, 3, -3);
    glVertex3f(3, 3, -3);
    glVertex3f(3, 3, 3);
    glVertex3f(-3, 3, 3);

    /// bottom side
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-3, -3, -3);
    glVertex3f(3, -3, -3);
    glVertex3f(3, -3, 3);
    glVertex3f(-3, -3, 3);
    glEnd();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(300, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Nagor-Dola");

    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    init();

    glutKeyboardFunc(normalKeypress);
    glutSpecialFunc(specialKeypress);
    glutMouseFunc(mousePress);

    glutMainLoop();
}

void init()
{
    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // draw base of nagordola
    glRotated(spinAngle, 1, 1, 1);
    cube();

    update1();
    glutSwapBuffers();
}
// spin to left
void spinToLeft()
{
    spinAngle += 3;
    if (spinAngle > 360.0)
    {
        spinAngle -= 360.0;
    }

    glutPostRedisplay();
}
// spin to right
void spinToRight()
{
    spinAngle -= 3;
    if (spinAngle > 360.0)
    {
        spinAngle -= 360.0;
    }

    glutPostRedisplay();
}

// for keypress l key to spin left , r key to spin right and s to stop the spin

void normalKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'l':
        spinToLeft();
        break;

    case 'r':
        spinToRight();
        break;

    case 's':
        glutIdleFunc(NULL);

    default:
        break;
    }
}

// implementation of right arrow and left arrow

void specialKeypress(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        spinToRight();
        break;

    case GLUT_KEY_LEFT:
        spinToLeft();
        break;

    default:
        break;
    }
}

// implementation of mouse button
void mousePress(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
        {
            glutIdleFunc(spinToLeft);
        }
        break;

    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
        {
            glutIdleFunc(spinToRight);
        }

    default:
        break;
    }
}
