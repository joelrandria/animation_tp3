#ifndef _CAVIEWER_H
#define _CAVIEWER_H

#include "ShallowWater.h"

#include <Viewer.h>
#include <BVH.h>
#include <Vec3.h>

class CAViewer : public Viewer
{
protected:

  unsigned long m_lastUpdateMsTime;

  ShallowWater m_water;

public:

  CAViewer();
  virtual ~CAViewer();

  virtual void help();

  virtual void init();

  virtual void draw();
  virtual void animate();

  virtual void keyPressed(unsigned char key, int x, int y);
  virtual void specialKeyPressed(int key, int x, int y);
};

#endif
