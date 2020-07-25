#include <cstring>

#include "atom.hpp"

atom::atom(const char *p, int order, float x, float y, float z)
  : order(order), x(x), y(y), z(z)
{
  aa[0] = p[0];
  aa[1] = p[1];
  aa[2] = p[2];
}

bool atom::interacting(const atom& o) const
{
  float d_x = o.x - x;
  float d_y = o.y - y;
  float d_z = o.z - z;
  
  // distance less than 8
  return d_x*d_x + d_y*d_y + d_z*d_z <= 64.0f;
}

std::ostream& operator<<(std::ostream& o, const atom& a)
{
  o << a.aa[0] << a.aa[1] << a.aa[2]
    << '(' << a.order << ')';
  return o;
}

int atom::compare(const atom& a) const
{
  if (order < a.order)
    return -1;
  else if (order > a.order)
    return 1;
  else
    return 0;
}
