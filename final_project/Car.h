#include <GL/freeglut.h>
#include <GL/gl.h>

class Car
{
    double posX, posY;

public:
    Car(float x, float y)
    {
        this->posX = x;
        this->posY = y;
    }

    void chechis()
    {
        glPushMatrix();
        glColor3d(1, 0, 0);
        glBegin(GL_POLYGON);

        glVertex2d(posX + -100, posY + 0);
        glVertex2d(posX + 100, posY + 0);
        glVertex2d(posX + 100, posY + 50);
        glVertex2d(posX + 75, posY + 50);
        glVertex2d(posX + 35, posY + 75);
        glVertex2d(posX + -35, posY + 75);
        glVertex2d(posX + -100, posY + 50);

        glEnd();
        glPopMatrix();
    }

    void window()
    {
        glPushMatrix();
        glTranslatef(posX, posY, 0);
        glColor3d(0, 0, 0);

        glBegin(GL_POLYGON);
        glVertex2d(5, 40);
        glVertex2d(40, 40);
        glVertex2d(25, 65);
        glVertex2d(5, 65);
        glEnd();

        glPushMatrix();
        glRotated(180, 0, 1, 0);
        glTranslatef(0, 0, 0);
        glBegin(GL_POLYGON);
        glVertex2d(5, 40);
        glVertex2d(40, 40);
        glVertex2d(25, 65);
        glVertex2d(5, 65);
        glEnd();
        glPopMatrix();

        glPopMatrix();
    }

    void wheel(float X, float Y, float r)
    {

        glBegin(GL_POLYGON);

        for (float i = 0; i < 360; i++)
        {
            float x = cos(i) * r + X + posX;
            float y = sin(i) * r + Y + posY;
            glVertex2d(x, y);
        }

        glEnd();
    }
    void draw()
    {
        this->chechis();
        this->window();
        this->wheel(-40, 0, 18);
        this->wheel(40, 0, 18);
    }
};