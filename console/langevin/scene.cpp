#include <kiam.hpp>
using namespace Kiam;
#include <base/time.hpp>
#include <math/vect2.hpp>
#include <math/vect3.hpp>
#include "scene.hpp"


OKAY Scene::Create(double zf1, double ecc1, double zf2, double ecc2, double za, double ra,
                   const Vect3d &ls_shift, const Vect3d &cam_shift, double cam_view_angle,
                   double gs1, double gs2)
  {
  if (mirror1.CreateFromFocuses(zf1, ecc1) != SUCCESS)
    {
    Assert(false);
    return FAILURE;
    }
  zc1 = 0;
#if 1
  const double t1 = 0;
  zmax_mirror1 = zc1 - t1 * mirror1.Radii()[1]; 
#else
  zmax_mirror1 = zc1; 
#endif



  if (mirror2.CreateFromFocuses(zf2, ecc2) != SUCCESS)
    {
    Assert(false);
    return FAILURE;
    }
  zc2 = zc1 + zf1 + zf2;
#if 0
  const double t2 = 0.98;
  zmin_mirror2 = zc2 + t2 * mirror2.Radii()[1];
#else
  zmin_mirror2 = zc2; 
#endif

  
  this->za = za;
  this->ra = ra;

  this->ls_pos  = Point3d(0, 0, zc1 - zf1) + ls_shift;
  this->cam_pos = Point3d(0, 0, zc2 + zf2) + cam_shift;

  this->cam_view_angle = cam_view_angle;

  bdf1.Create(gs1);
  bdf2.Create(gs2);


  return SUCCESS;
  }




bool Scene::FindIntersection(const Ray3d &ray, OUT IScene::RaySegmData &rsd, int segm_idx) const
  {
  double t;
  Ray3d ray_ = ray;
  rsd.org = ray.org;
  if (segm_idx == 0)
    {
    

    
    ray_.org.z -= zc1;
    t = mirror1.FindIntersection(ray_.org, ray_.dir);
    if (t < 0)
      return false;

    rsd.length = t;
    rsd.end = rsd.org + ray_.dir * t; 
    if (rsd.end.z > zmax_mirror1)
      return false; 

    rsd.normal = mirror1.Normal(rsd.end - Vect3d(0, 0, zc1));
    rsd.curvature  = mirror1.Curvature(rsd.end - Vect3d(0, 0, zc1));
    rsd.bdf = &bdf1;

    
    rsd.max_point_dev = 0.1 * Min(mirror1.Radii()[0], mirror1.Radii()[1]);
    rsd.dist2hole = -1;
    rsd.hole_size = -1;
    return true;
    }
  else if (segm_idx == 1)
    {
    

    
    const double dist2hole = (za - ray_.org.z) / ray_.dir.z;

    const Point3d xa = ray_.org + dist2hole * ray_.dir;
    if (SqrLength(xa - Point3d(0, 0, za)) > ra * ra)
      return false; 

    ray_.org = xa;

    
    ray_.org.z -= zc2;
    t = mirror2.FindIntersection(ray_.org, ray_.dir);
    if (t < 0)
      return false;

    rsd.length = t + dist2hole;
    rsd.end = xa + ray_.dir * t; 
    if (rsd.end.z < zmin_mirror2)
      return false; 
      
    rsd.normal    = mirror2.Normal(rsd.end - Vect3d(0, 0, zc2));
    rsd.curvature = mirror2.Curvature(rsd.end - Vect3d(0, 0, zc2));
    rsd.bdf       = &bdf2;

    
    rsd.max_point_dev = 0.1 * Min(mirror2.Radii()[0], mirror2.Radii()[1]);
    rsd.dist2hole = dist2hole;
    rsd.hole_size = ra;

    return true;
    }
  else
    {
    Assert(false);
    return false;
    }
  }


bool Scene::IsVisible(const Point3d &pt, OUT Vect3d &view) const
  {
  view = (pt - cam_pos).Normalize();
  return true; 
  }


const Point3d& Scene::GetLightPos() const
  {
  return ls_pos;
  }

  

