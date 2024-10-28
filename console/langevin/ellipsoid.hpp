#ifndef _ELLIPSOID_HPP_INCLUDED
#define _ELLIPSOID_HPP_INCLUDED

#include <math/vect2.hpp>
#include <math/vect3.hpp>
#include <math/matrix3.hpp>
#include "ray3d.hpp"






class Ellipsoid
  {
  public:
    
    OKAY CreateFromRadii(double a, double b);
    
    OKAY CreateFromFocuses(double zf, double eccentricity);

    
    
    
    inline Vect2d Radii() const;
    
    inline double Focus() const;
    

    
    
    
    Vect3d Normal(const Point3d &pt) const;
    
    Matrix3d TangentAndNormal(const Point3d &pt) const;
    
    Matrix3d Curvature(const Point3d &pt) const;
    

    
    double FindIntersection(const Point3d &org, const Vect3d &dir) const;

  private:
    
    double a;
    
    double b;
    
    double zf;
  };


Vect2d Ellipsoid::Radii() const
  {
  return Vect2d(a, b);
  }

double Ellipsoid::Focus() const
  {
  return zf;
  }

#endif