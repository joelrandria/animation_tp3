#include "CAViewer.h"
#include <BVH.h>
#include <BVHChannel.h>
#include <Mat4.h>
#include <Quaternion.h>

#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace chara;
using namespace std;

CAViewer::CAViewer()
  :Viewer(),
   m_lastUpdateMsTime(0)
{
}
CAViewer::~CAViewer()
{
}

void CAViewer::help()
{
  printf("Animation:\n");
  printf("   n: Next character pose\n");
  printf("   b: Back(Previous) character pose");
  printf("   shift+arrows: Move the target point");
  Viewer::help();
}

void CAViewer::init()
{
  Viewer::init();

  m_water.initialize(100, 100);
}

void CAViewer::draw()
{
  m_water.draw();
}
void CAViewer::animate()
{
  m_water.animate(20);
}

void CAViewer::keyPressed(unsigned char key, int x, int y)
{
  bool handled = false;

  if ((key=='n'))
  {
    // Do something
    handled = true;
  }
  else
    if ((key=='b'))
    {
      // Do something
      handled = true;
    }
    else
      if (key=='w')
      {
	bWireframe = !bWireframe;

	if (bWireframe)
	  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
	  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	handled = true;
      }

  if (!handled)
    Viewer::keyPressed(key,x,y);

  updateGL();
}
void CAViewer::specialKeyPressed(int key, int x, int y)
{
  bool handled = false;

  if (glutGetModifiers()==GLUT_ACTIVE_SHIFT)
  {
    switch (key)
    {
    case GLUT_KEY_UP:

      handled=true;
      break;
    case GLUT_KEY_DOWN:

      handled=true;
      break;
    case GLUT_KEY_LEFT:

      handled=true;
      break;
    case GLUT_KEY_RIGHT:

      handled=true;
      break;
    case GLUT_KEY_PAGE_UP:

      handled=true;
      break;
    case GLUT_KEY_PAGE_DOWN:

      handled=true;
      break;
    }
  }

  if (!handled)
    Viewer::specialKeyPressed(key,x,y);

  updateGL();
}
