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

// Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y)
{

  switch (key)
  {

  case 'f':
    running *= 2;
    break;
  case 's':
    running /= 2;
    break;
  case 'b':
    running = !running;
    break;

  case 'l':
    isLight0On ? glDisable(GL_LIGHT0) : glEnable(GL_LIGHT0);
    isLight0On = !isLight0On;
    break;

  case 'k':
    isLight1On ? glDisable(GL_LIGHT1) : glEnable(GL_LIGHT1);
    isLight1On = !isLight1On;
    break;
  case 27: // Escape key
    exit(0);
  default:
    break;
  }
  glutPostRedisplay();
}

// Draws the 3D scene
void drawScene()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -70.0f);

  // glColor3f(1.0f, 1.0f, 0.0f);

  glPushMatrix();
  glScaled(0.5, 0.5, 0.5); /*This is a 3d obj so we have to need Z axis too*/
  glColor3ub(0, 0, 0);
  drawComponent(-3, -10, 200, 200, nagordola);
  glPopMatrix();

  drawComponent(-12.0, 2.2, 1, 1, tree);
  drawComponent(-10.10, 1.1, 1, 1, tree);
  drawComponent(-10.0, 1.2, 1, 1, tree);
  drawComponent(-10.8, 1.0, 1, 1, tree);
  drawComponent(-10, 3.7, 1, 1, tree);

  // glPushMatrix();

  // glRotated(40, 1, 0, 0);
  // glRotated(70, 1, 0, 0);
  // river(2, -7, 5, 1);
  // // boat(0, 0, 10, 1);
  // glPopMatrix();

  drawComponent(c1 + 0, 20.5 + 2 + sin(c1 / 5), 1.5, 1.5, cloud);
  drawComponent(c1 + 3, 20.5 + 3 + sin(c1 / 7), 1.5, 1.5, cloud);
  drawComponent(c1 + 5, 20.5 + 0 + sin(c1 / 3), 1.5, 1.5, cloud);
  drawComponent(c2, 16.4, 1.10, 1.10, cloud);
  drawComponent(c3, 10.5, 0.9, 0.9, cloud);

  drawComponent(3.2, 0.3, 1.5, 1.5, tree); /*jumbo tree*/

  drawComponent(-6.2, -0.7, 10, 10, stall);
  drawComponent(-5, 0, 9, 9, stall);
  drawComponent(-4, 0.5, 8, 8, stall);
  drawComponent(-3.2, 0.9, 7, 7, stall);
  drawComponent(-2.8, 1.2, 6, 6, stall);

  /* Rendering Hills */

  drawComponent(-20, 5.5, 6, 12, hill);
  drawComponent(-9, 7, 8, 8, hill);
  drawComponent(8, 7, 7, 14, hill);
  drawComponent(-3, 7, 6, 14, hill);
  drawComponent(-40, 6.5, 7, 12, hill);

  drawComponent(-20, 0, 100, 100, belun);

  glPushMatrix();
  drawComponent(0, 0, 100, 100, background);
  glPopMatrix();
  update();

  glutSwapBuffers();
}

int main(int argc, char **argv)
{

  // Initialize GLUT
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  glutInitWindowPosition(10, 10);
  glutInitWindowSize(1200, 800);

  // Create the window
  glutCreateWindow("Village Fair Mini Project By Mahbub And Rakiba !");
  initRendering();

  // Set handler functions
  glutDisplayFunc(drawScene);
  glutKeyboardFunc(handleKeypress);
  glutReshapeFunc(handleResize);
  // glutTimerFunc(25, update, 0);  // Add a timer

  glutMainLoop();
  return 0;
}
