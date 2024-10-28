#ifndef _ISCENE_HPP_INCLUDED
#define _ISCENE_HPP_INCLUDED

#include <math/vect3.hpp>
#include <math/matrix3.hpp>
#include "ray3d.hpp"

class BDF;



class IScene
  {
  public:
    struct RaySegmData
      {
      
      Point3d org, end;
      
      double length;
      
      Vect3d normal;
      
      Matrix3d curvature;
      
      const BDF *bdf;

      
      double max_point_dev;
      
      
      
      double dist2hole, hole_size;
      };

  public:
    
    virtual bool FindIntersection(const Ray3d &ray, OUT RaySegmData &rsd, int segm_idx) const = 0;
    
    virtual bool IsVisible(const Point3d &pt, OUT Vect3d &view) const = 0;
    
    virtual const Point3d& GetLightPos() const = 0;
  };



#endif