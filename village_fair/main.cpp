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

// Draws the 3D scene
void drawScene()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -70.0f);

  // Add ambient light
  GLfloat sp = sin(posSun);
  GLfloat lightDepth = sin(posSun);
  GLfloat ambientColor[] = {sp, sp, sp, 1}; // Color (0.2, 0.2, 0.2)
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

  // Add positioned light
  GLfloat diffuseLightColor0[] = {-1, -1, -1, 1.0};
  GLfloat specularLightColor0[] = {lightDepth, lightDepth, lightDepth, 0.1f};
  GLfloat lightPos0[] = {sp, sp, sp, 1.0};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLightColor0);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specularLightColor0);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

  // Add directed light
  GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; // Color (0.5, 0.2, 0.2)
  // Coming from the direction (-1, 0.5, 0.5)
  GLfloat lightPos1[] = {-10.0f, 10.5f, 10.5f, 1.0f};
  glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
  glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

  glColor3f(1.0f, 1.0f, 0.0f);
  // drawComponent(1.0, 1.2, 100, 100, nagordola);

  drawComponent(-12.0, 2.2, 1, 1, tree);
  drawComponent(-10.10, 1.1, 1, 1, tree);
  drawComponent(-10.0, 1.2, 1, 1, tree);
  drawComponent(-10.8, 1.0, 1, 1, tree);
  drawComponent(-10, 3.7, 1, 1, tree);

  drawComponent(-40, 2, 8, 8, hill);
  drawComponent(-32, 2.8, 7, 7, hill);
  drawComponent(-50, 1.3, 10, 10, hill);

  // glPushMatrix();

  // glRotated(40, 1, 0, 0);
  // glRotated(70, 1, 0, 0);
  // river(2, -7, 5, 1);
  // // boat(0, 0, 10, 1);
  // glPopMatrix();

  drawComponent(c1 + 0, 20.5 + 2 + sin(c1 / 5), 1.5, 1.5, cloud);
  drawComponent(c1 + 3, 20.5 + 3 + sin(c1 / 6), 1.5, 1.5, cloud);
  drawComponent(c1 + 5, 20.5 + 0 + sin(c1 / 3), 1.5, 1.5, cloud);
  drawComponent(c2, 16.4, 1.10, 1.10, cloud);
  drawComponent(c3, 10.5, 0.9, 0.9, cloud);

  drawComponent(3.2, 0.3, 1.5, 1.5, tree); /*jumbo tree*/

  drawComponent(-6.2, -0.7, 10, 10, stall);
  drawComponent(-5, 0, 9, 9, stall);
  drawComponent(-4, 0.5, 8, 8, stall);
  drawComponent(-3.2, 0.9, 7, 7, stall);
  drawComponent(-2.8, 1.2, 6, 6, stall);

  glPushMatrix();

  drawComponent(0, 0, 100, 100, background);

  update();

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

  glutMainLoop();
  return 0;
}
