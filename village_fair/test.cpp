#include "mylib.h"

void init();
void draw();
void reshape(int w, int h);
void normalKeypress(unsigned char key, int x, int y);
void specialKeypress(int key, int x, int y);
void mousePress(int button, int state, int x, int y);

static GLfloat spinAngle = 0.0;

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
    gluOrtho2D(-600, 600, -600, 600);
    glMatrixMode(GL_MODELVIEW);
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // draw base of nagordola
    glColor3f(0.196, 0.15, 0.15);
    glRectf(-125, -450, 175, -600);

    // draw bar of nagordola
    glColor3f(0.188, 0.192, 0.44);
    glRectf(0, 100, 50, -450);

    // body that hold every nagordola seat
    glColor3f(0.6, 0.04, .90);
    glRectf(-100, 350, 150, 100);

    glPushMatrix();
    glRotatef(spinAngle, 0.0, 0.0, 1.0);
    // left seat handler of nagor dola
    glColor3f(.95, .44, 0.47);
    glRectf(-150, 300, -100, 150);

    // left seat of nagor dola
    glColor3f(0.37, .88, 0.03);
    glRectf(-450, 350, -150, 100);

    // right seat handler of nagor dola
    glColor3f(.95, .44, 0.47);
    glRectf(150, 300, 200, 150);

    // right seat of nagor dola
    glColor3f(0.45, 0.32, 0.886);
    glRectf(200, 350, 500, 100);
    glPopMatrix();

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