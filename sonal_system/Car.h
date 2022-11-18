#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <math.h>

class Car
{
private:
    int x, y;
    double height, width;

public:
    Car(double, double);
    void line(double, double, double, double);
    void squre(double, double, double);
    void circle(double, double, double);
    void half_circle(double, double, double, double);
    void wheel(double, double, double);
    void draw()
    {
        glPushMatrix();

        glPushMatrix();

        // upper line start
        glTranslated(-200, 100, 0);
        line(0, 0, 100, 0);
        line(100, 0, 100, -100); // front screen line
        line(0, 0, 0, -120);
        line(0, -120, -5, -200);

        // front light bar
        line(0, 0, 10, -100);
        glPopMatrix();

        glPushMatrix();
        glTranslated(0, 100, 0);
        squre(0, 0, 100);
        // front
        line(0, 100, -100, 0);
        line(0, 0, -100, -100);

        // back
        line(100, 100, 200, 0);
        line(100, 0, 200, -100);

        glPopMatrix();

        glPushMatrix();
        glTranslated(200, 100, 0);
        line(0, 0, 100, 0);
        line(0, 0, 0, -100); // back screen line
        line(100, 0, 100, -120);
        line(100, -120, 90, -200);

        glPopMatrix();

        // upper line end

        // mid layer start
        glPushMatrix();
        glTranslated(-200, 0, 0);
        line(10, 0, 100, 0);

        // light bar
        line(10, 0, -5, -100);
        glPopMatrix();

        glPushMatrix();
        glTranslated(0, 0, 0);
        line(-100, 0, 300, 0);

        // front door
        line(0, 0, 0, 80);
        line(100, 0, 100, 80);
        glPopMatrix();

        glPushMatrix();
        glTranslated(200, 0, 0);
        line(0, 0, 90, 0);

        //  back bonet
        line(90, 0, 100, 100);
        line(90, 0, 90, -100);

        glPopMatrix();

        // bottom layer
        glPushMatrix();
        glTranslated(-200, -100, 0);
        line(0, 0, 100, 0);

        // wheel guard
        half_circle(150, 0, 50, 0);
        wheel(150, 0, 40);
        glPopMatrix();

        glPushMatrix();
        glTranslated(0, -100, 0);
        line(0, 0, 100, 0);
        half_circle(150, 0, 50, 0);
        wheel(150, 0, 40);
        glPopMatrix();

        glPushMatrix();
        glTranslated(200, -100, 0);
        line(-5, 0, 90, 0);
        glPopMatrix();

        glPopMatrix();
    }
};

void Car::line(double x1, double y1, double x2, double y2)
{
    glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glEnd();
}
void Car::squre(double x, double y, double a)
{
    glBegin(GL_LINE_LOOP);
    glVertex2d(x, y);
    glVertex2d(x, y + a);
    glVertex2d(x + a, y + a);
    glVertex2d(x + a, y);

    glEnd();
}
void Car::circle(double x, double y, double r)
{

    glBegin(GL_LINE_STRIP);

    for (float i = 0; i < 10; i += 0.1)
    {
        glVertex2d(x + r * cos(i), y + r * sin(i));
    }

    glEnd();
}
void Car::half_circle(double x, double y, double r, double angle)
{
    glPushMatrix();
    glTranslated(x, y, 0);
    glRotated(angle, 0, 0, 1);

    // making half circle
    glBegin(GL_LINES);
    for (double i = 0; i < 3.14; i += 0.001)
    {
        /* code */
        double x = r * cos(i);
        double y = r * sin(i);
        glVertex2d(x, y);
    }
    glEnd();

    glPushMatrix();
    glPopMatrix();

    glPopMatrix();
}
void Car::wheel(double x, double y, double r)
{
    glPushMatrix();
    double times = 0;
    glTranslated(x, y, 0);
    glBegin(GL_LINE_STRIP);
    double finish_line = 3.14 * 2 * 1000;
    for (int i = 0; i < finish_line; i++)
    {
        double x1 = r * cos(i / 1000);
        double y1 = r * sin(i / 1000);

        if (!(i % 500))
        {
            glPushMatrix();
            glRotated(times, 0, 0, 1);
            line(0, 0, x1, y1);
            glPopMatrix();
            times += finish_line / 50;
        }
        glVertex2d(x1, y1);
    }

    glEnd();
    glPopMatrix();
}

Car::Car(double height, double width)
{
    this->height = height;
    this->width = width;
}
