#ifndef __SHALLOWWATER_H__
#define __SHALLOWWATER_H__

#include "Array2D.h"

#include "Mat4.h"

#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

class ShallowWater
{
protected:

  int m_dimx;
  int m_dimy;

  Array2D m_g;     // height of the ground (0 if flat)
  Array2D m_n;     // m_n = m_h - m_g : amount of water above the ground
  Array2D m_h;     // height of the water : the thing to compute and to draw
  Array2D m_vX;    // velocity along X
  Array2D m_vY;    // velocity along Y

  const math::Vec4f _waterColor;
  const math::Vec4f _groundColor;

public:

  ShallowWater();

  void initialize(const int DIMX, const int DIMY);

  void draw() const;
  void animate(float elapsedMilliseconds);

private:

  void initializeWaterLevel();

  void drawHeightArray(const Array2D& array, const math::Vec4f& color) const;

  void normal(const Array2D& y, int x, int z, math::Vec3f& normal) const;

  void advect(const Array2D& src, const Array2D& vx, const Array2D& vy, const float dt, Array2D& dst);

  void updateHeights(Array2D& heights, const Array2D& vx, const Array2D& vy, const float dt);
  void updateVelocities(const Array2D& heights, Array2D& vx, Array2D& vy, const float dt);
};

#endif
