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

void init()
{
  glClearColor(1, 0.75, 0.79, 1);
  glOrtho(-600, 600, -600, 600, -600, 600);
}

void mousePress(int button, int state, int x, int y) {}

void keyboardPress(unsigned char key, int x, int y) {}

void myDisplay()
{
  glClear(GL_COLOR_BUFFER_BIT);
  sky();
  ground();

  glColor3f(1, .5, 0);
  tree(-100, 100, 0.5, 0.2);
  stall(-100,-100,1,1);
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
  glutMouseFunc(mousePress);
  glutKeyboardFunc(keyboardPress);
  glutMainLoop();
  return 0;
}
