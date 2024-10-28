#ifndef _SCENE_HPP_INCLUDED
#define _SCENE_HPP_INCLUDED

#include <base/matrix.hpp>
#include <math/vect2.hpp>
#include <math/vect3.hpp>
#include <math/matrix3.hpp>
#include <math/matrix4.hpp>
#include <math/rnd.hpp>
#include "ray3d.hpp"
#include "ellipsoid.hpp"
#include "bdf.hpp"
#include "iscene.hpp"



class Scene : public IScene
  {
  public:
    
    OKAY Create(double zf1, double ecc1, double zf2, double ecc2, double za, double ra,
                const Vect3d &ls_shift, const Vect3d &cam_shift, double cam_view_angle,
                double gs1, double gs2);

    
    virtual bool FindIntersection(const Ray3d &ray, OUT IScene::RaySegmData &rsd, int segm_idx) const;
    
    virtual bool IsVisible(const Point3d &pt, OUT Vect3d &view) const;
    
    virtual const Point3d& GetLightPos() const;

  protected:
    
    Ellipsoid mirror1;
    
    double zc1;
    
    double zmax_mirror1;
    
    Ellipsoid mirror2;
    
    double zc2;
    
    double zmin_mirror2;

    
    double za;
    
    double ra;

    
    Point3d ls_pos;

    
    Point3d cam_pos;

    
    double cam_view_angle;

    
    BDF bdf1;

    
    BDF bdf2;
  };


#endif