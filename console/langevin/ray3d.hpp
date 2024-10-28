#ifndef _RAY3D_HPP_INCLUDED
#define _RAY3D_HPP_INCLUDED

#include <math/vect3.hpp>

struct Ray3d
  {
  public:
    
    Point3d org;
    
    Vect3d dir;
  };

#endif