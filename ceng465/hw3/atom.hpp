#ifndef _ATOM_HPP_
#define _ATOM_HPP_

#include <iostream>

class atom {
  int order;
  float x, y, z;
  char aa[3];

public:
  atom(const char *p, int order, float x, float y, float z);

  int compare(const atom& a) const;

  bool interacting(const atom& o) const;

  friend std::ostream& operator<<(std::ostream& o, const atom& a);
};

#endif
