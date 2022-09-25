#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>
#include <cmath>

int noise(int x)
{
    int val = random() % 100 > 50 ? 10 : -10;
    // std::cout << random() % 10 << std::endl;
    return val + x;
}

class Universe
{
    int height, width;

public:
    Universe(int h, int w)
    {
        height = h;
        width = w;
    }

    void draw()
    {
        glColor3f(0, 0, 0);
        int xOff = 20, yOff = 10;

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glPushMatrix();

        glRotatef(20.0, 1.0, 0.0, 0.0);

        for (int j = -width; j < width; j += yOff)
        {

            glBegin(GL_TRIANGLE_STRIP);
            for (int i = -height; i < height; i += xOff)
            {
                glColor3f(0.0, 0.0, 0.0);

                glVertex3d(i, j, 0);
                glColor3f(0, 0, 0);
                glVertex3d(i, j + yOff, 0);
            }
            glEnd();
        }
        glPopMatrix();
    }
    int getHeight()
    {
        return height;
    }
};

class Planet
{
    double radius;
    double mass;
    int X, Y;

public:
    Planet(int x, int y, double mass, double r)
    {
        this->X = x;
        this->Y = y;
        this->mass = mass;
        this->radius = r;
    }

    void draw()
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glPushMatrix();
        glBegin(GL_POLYGON);
        for (float i = 0; i < 10; i += 0.01)
        {
            float x = cos(i);
            float y = sin(i);
            glVertex3d(radius * x + X, radius * y + Y, 0);
        }
        glEnd();
        glPopMatrix();
    }
};
