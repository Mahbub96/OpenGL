/*
#ifdef __APPLE__
#include <GLUT/glut.h>

#else
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>
#include <windows.h>

#endif
*/

#include "mylib.h"
#include <iostream>
using namespace std;

double dx = 0.01, dy, c1 = -10, c2 = -10, c3 = 6;
double width, height;

// Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y)
{

  switch (key)
  {
  case 'a':
    glDisable(GL_LIGHT0);
    break;
  case 's':
    glEnable(GL_LIGHT0);
    break;

  case 'd':
    glDisable(GL_LIGHT1);
    break;
  case 'f':
    glEnable(GL_LIGHT1);
    break;
  case 27: // Escape key
    exit(0);
  default:
    break;
  }
  glutPostRedisplay();
}

// Initializes 3D rendering
void initRendering()
{
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);  // Enable lighting
  glEnable(GL_LIGHT0);    // Enable light #0
  glEnable(GL_LIGHT1);    // Enable light #1
  glEnable(GL_NORMALIZE); // Automatically normalize normals
  // glShadeModel(GL_SMOOTH); // Enable smooth shading
}

// Called when the window is resized
void handleResize(int w, int h)
{
  width = w;
  height = h;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (double)w / (double)h, 10.0, 100.0);
}

void updateX(int value)
{

  c1 += 0.01;
  c2 += 0.02;
  c3 += 0.03;

  if (c1 > 13)
    c1 = -10;
  if (c2 > 13)
    c2 = -10;
  if (c3 > 13)
    c3 = -10;

  glutPostRedisplay();
  glutTimerFunc(25, updateX, 0);
}

// Draws the 3D scene
void drawScene()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -20.0f);

  // Add ambient light
  GLfloat ambientColor[] = {0.5f, 0.5f, 0.5f, 1.0f}; // Color (0.2, 0.2, 0.2)
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

  // Add positioned light
  GLfloat diffuseLightColor0[] = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat specularLightColor0[] = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat lightPos0[] = {1.0f, 1.0f, 0.0f, 1.0f};
  // glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLightColor0);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specularLightColor0);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

  // Add directed light
  GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; // Color (0.5, 0.2, 0.2)
  // Coming from the direction (-1, 0.5, 0.5)
  GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
  glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
  glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

  glColor3f(1.0f, 1.0f, 0.0f);

  glPushMatrix();

  sky();
  ground();

  hill(-12, 2, 4, 1.5);
  hill(-8, 1.3, 6, 2);
  hill(-6, 2, 5, 1);

  glPushMatrix();

  glRotated(40, 1, 0, 0);
  river(5, -25, 5);
  glPopMatrix();
  glColor3d(1, 0, 1);
  boat(0, 0, 10, 10);

  tree(-6.0, 1.2, 0.13, 10);
  tree(-5.5, 1.1, 0.12, 10);
  tree(-5.0, 1.2, 0.15, 10);
  // tree(-5, 2.7, 0.2, 10);
  tree(-5, 3.7, 0.5, 3);

  cloud(c1, 5.7, 0.5, 1.3);
  cloud(c2, 4.2, 0.10, 1.3);
  cloud(c3, 5.5, 0.9, 1.3);

  tree(0, 3, 1.5, 10);

  glPushMatrix();
  glTranslated(3, -5, 0);
  // pond(25, 10, -5, 2);
  glPopMatrix();

  glPushMatrix();
  stall(-6.2, -0.7, 5, 0.15);
  stall(-5, 0, 5, 0.1);
  stall(-4, 0.5, 5, 0.08);
  stall(-3.2, 0.9, 5, 0.06);
  stall(-2.8, 1.2, 5, 0.05);
  glPopMatrix();

  glPopMatrix();

  glutSwapBuffers();
}

int main(int argc, char **argv)
{

  // Initialize GLUT
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1200, 800);

  // Create the window
  glutCreateWindow("Lighting Example");
  initRendering();

  // Set handler functions
  glutDisplayFunc(drawScene);
  glutKeyboardFunc(handleKeypress);
  glutReshapeFunc(handleResize);
  // glutTimerFunc(25, update, 0);  // Add a timer
  glutTimerFunc(25, updateX, 0); // Add a timer

  glutMainLoop();
  return 0;
}
