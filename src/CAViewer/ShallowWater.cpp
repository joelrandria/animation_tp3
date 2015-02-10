#include "ShallowWater.h"

#include <stdio.h>

ShallowWater::ShallowWater()
  :_waterColor(0, 0, 1, 0.5f),
   _groundColor(1, 1, 0, 1)
{
}

void ShallowWater::initialize(const int DIMX, const int DIMY)
{
  m_dimx = DIMX;
  m_dimy = DIMY;

  m_g.init(m_dimx, m_dimy);
  m_g.setAll(0);

  m_vX.init(m_dimx, m_dimy);
  m_vX.setAll(0);
  m_vY.init(m_dimx, m_dimy);
  m_vY.setAll(0);

  initializeWaterLevel();

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  ///////////////////////////////////////////////////////////////////////////////////////

  // m_g.write("g.txt");
  // m_h.write("h.txt");
  // m_n.write("n.txt");
  // m_vX.write("vx.txt");
  // m_vY.write("vy.txt");
}
void ShallowWater::initializeWaterLevel()
{
  int x;
  int y;

  m_h.init(m_dimx, m_dimy);
  m_h.setAll(10);

  ///////////////////////////////////////////////////////////////////////////////////////

  // for (int xh = 30; xh < 40; ++xh)
  //   for (int yh = 30; yh < 40; ++yh)
  //     m_g(xh, yh) = 20;

  for (int xh = 60; xh < 70; ++xh)
    for (int yh = 60; yh < 70; ++yh)
      m_h(xh, yh) = 40;

  ///////////////////////////////////////////////////////////////////////////////////////

  m_n.init(m_dimx, m_dimy);
  for (x = 0; x < m_dimx; ++x)
    for (y = 0; y < m_dimy; ++y)
      m_n(x, y) = m_h(x, y) - m_g(x, y);
}

void ShallowWater::draw() const
{
  //drawHeightArray(m_g, _groundColor);
  drawHeightArray(m_h, _waterColor);
}
void ShallowWater::drawHeightArray(const Array2D& array, const math::Vec4f& color) const
{
  uint x;
  uint z;

  math::Vec3f n;

  glBegin(GL_QUADS);

  glColor4f(color.x, color.y, color.z, color.w);

  for (z = 0; z < (m_dimy - 1); ++z)
  {
    for (x = 0; x < (m_dimx - 1); ++x)
    {
      normal(array, x, z, n);
      glNormal3f(n.x, n.y, n.z);
      glVertex3f(x, array(x, z), z);

      normal(array, x + 1, z, n);
      glNormal3f(n.x, n.y, n.z);
      glVertex3f(x + 1, array(x + 1, z), z);

      normal(array, x + 1, z + 1, n);
      glNormal3f(n.x, n.y, n.z);
      glVertex3f(x + 1, array(x + 1, z + 1), z + 1);

      normal(array, x, z + 1, n);
      glNormal3f(n.x, n.y, n.z);
      glVertex3f(x, array(x, z + 1), z + 1);
    }
  }

  glEnd();
}
void ShallowWater::normal(const Array2D& y, int x, int z, math::Vec3f& normal) const
{
  int x1;
  int x2;
  int z1;
  int z2;

  math::Vec3f xvec;
  math::Vec3f zvec;

  x1 = (x == 0) ? x : x - 1;
  x2 = (x == (m_dimx - 1)) ? x : x + 1;
  z1 = (z == 0) ? z : z - 1;
  z2 = (z == (m_dimy - 1)) ? z : z + 1;

  xvec.x = x2 - x1;
  xvec.y = y(x2, z) - y(x1, z);
  xvec.z = 0;
  xvec.normalize();

  zvec.x = 0;
  zvec.y = y(x, z2) - y(x, z1);
  zvec.z = z2 - z1;
  zvec.normalize();

  normal = zvec^xvec;
}

void ShallowWater::animate(float elapsedMilliseconds)
{
  Array2D advectedN;
  Array2D advectedVx;
  Array2D advectedVy;

  const float dt = 1.0f / elapsedMilliseconds;

  advect(m_n, m_vX, m_vY, dt, advectedN);
  advect(m_vX, m_vX, m_vY, dt, advectedVx);
  advect(m_vY, m_vX, m_vY, dt, advectedVy);

  m_n = advectedN;
  m_vX = advectedVx;
  m_vY = advectedVy;

  updateHeights(m_n, m_vX, m_vY, dt);

  m_h = m_n + m_g;

  updateVelocities(m_h, m_vX, m_vY, dt);

  ///////////////////////////////////////////////////////////////////////////////////////

  // m_g.write("g.txt");
  // m_h.write("h.txt");
  // m_n.write("n.txt");
  // m_vX.write("vx.txt");
  // m_vY.write("vy.txt");
}

void ShallowWater::advect(const Array2D& src, const Array2D& vx, const Array2D& vy, const float dt, Array2D& dst)
{
  int x;
  int y;

  float advectx;
  float advecty;

  dst = src;

  for (x = 1; x < (m_dimx - 1); ++x)
  {
    for (y = 1; y < (m_dimy - 1); ++y)
    {
      advectx = x - dt * vx(x, y);
      advecty = y - dt * vy(x, y);

      dst(x, y) = src.interpolate(advectx, advecty);
    }
  }
}

void ShallowWater::updateHeights(Array2D& heights, const Array2D& vx, const Array2D& vy, const float dt)
{
  int x;
  int y;

  for (x = 1; x < (m_dimx - 1); ++x)
    for (y = 1; y < (m_dimy - 1); ++y)
      heights(x, y) = heights(x, y) - (heights(x, y) * dt * ((vx(x + 1, y) - vx(x, y)) + (vy(x, y + 1) - vy(x, y))));
}
void ShallowWater::updateVelocities(const Array2D& heights, Array2D& vx, Array2D& vy, const float dt)
{
  int x;
  int y;

  const float a = 9.81f;

  for (x = 1; x < (m_dimx - 1); ++x)
  {
    for (y = 1; y < (m_dimy - 1); ++y)
    {
      vx(x, y) += a * dt * (heights(x - 1, y) - heights(x, y));
      vy(x, y) += a * dt * (heights(x, y - 1) - heights(x, y));
    }
  }
}
