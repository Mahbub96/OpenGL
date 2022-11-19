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

  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (double)w / (double)h, 10.0, 100.0);
}

float _angle = 0.0f;

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
  glRotatef(_angle, 0.0f, 1.0f, 0.3f);
  glColor3f(1.0f, 1.0f, 0.0f);

  glPushMatrix();
  sky();
  ground();
  cloud(0, 2.7, 0.15, 10);
  cloud(2, 2.2, 0.10, 8);
  tree(-3, 0, 0.4, 10);
  glutSwapBuffers();
}

void update(int value)
{
  _angle += 0.0f;
  if (_angle > 360)
  {
    _angle -= 360;
  }

  glutPostRedisplay();
  glutTimerFunc(25, update, 0);
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
  glutTimerFunc(25, update, 0); // Add a timer

  glutMainLoop();
  return 0;
}
