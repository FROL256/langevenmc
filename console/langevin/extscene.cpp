#include <kiam.hpp>
using namespace Kiam;
#include <base/time.hpp>
#include <math/vect2.hpp>
#include <math/vect3.hpp>
#include "extscene.hpp"



OKAY ExtScene::GeneratePath(OUT BasePathDataSpecDir &bpd, INOUT Rnd &rng) const
  {
  const Vect2d radii1 = mirror1.Radii();

  Point3d x1, xa;
  double z, r, phi;
  for (int iter = 0; iter < 1000; iter++)
    {
    
  
    z = -radii1[1] * rng.DRnd(0.0, 1.0);
    r = radii1[0] * Sqrt(1 - Sqr(z / radii1[1]));
    phi = 2 * PI * rng.DRnd();

    x1.z = z + zc1;
    x1.x = r * cos(phi);
    x1.y = r * sin(phi);

    
    const double dist1 = Length(x1 - ls_pos);
    bpd.v1 = (x1 - ls_pos) * (1 / dist1);

    
    const Vect3d n1 = mirror1.Normal(Point3d(x1.x, x1.y, x1.z - zc1));

    
    const Vect3d s1 = bpd.v1 - 2 * DotProd(bpd.v1, n1) * n1;

    
#if 0
    r = 0;
#else

    r = 0.9 * ra * rng.DRnd();
#endif

    phi = 2 * PI * rng.DRnd();
    xa.z = za;
    xa.x = r * cos(phi);
    xa.y = r * sin(phi);

    
    const Vect3d v2 = (xa - x1).Normalize();

    
    const Vect3d p1 = (n1 - DotProd(n1, s1) * s1).Normalize();
    const Vect3d q1 = CrossProd(n1, p1).Normalize();

    bpd.omega1[0] = DotProd(v2, p1);
    bpd.omega1[1] = DotProd(v2, q1);

    Ray3d ray;
    ray.org = xa;
    ray.dir = v2;

    
    ray.org.z -= zc2;
    const double t = mirror2.FindIntersection(ray.org, ray.dir);
    if (t < 0)
      {
      Assert(false);
      return FAILURE;
      }
    const Point3d x2 = xa + v2 * t; 
    
    if (x2.z >= zmin_mirror2)
      return SUCCESS;
    }
  Assert(false);
  return FAILURE;
  }



OKAY ExtScene::CalcDistr(const int nrays, OUT TMatrix<double> &hist, INOUT double &tol, INOUT Rnd &rng) const
  {
  if (hist.Length() == 0)
    {
    hist.Allocate(301, 3);
    hist = 0;
    }

  const int ntheta = hist.NRows();
  const int nphi   = hist.NColumns();
  Vect3d v1, v3;
  double avr, avr_sqr, avr_, avr_sqr_, rms, theta, phi;
  INT64 nr;


#if 0
  for (int itheta = 0; itheta < ntheta; itheta++)
    {
    
    theta = (itheta + 0.5) * PI / (ntheta - 1);
    v3.z = cos(theta);
    v3.x = sin(theta);
    v3.y = 0;

    if (CalcMapping(v3, v1) == SUCCESS)
      printf("%8.5f %8.5f\n", theta, ACos(v1.z));
    }
#endif

  double err_max = 0;
  Timer timer;
  for (int itheta = 0; itheta < ntheta; itheta++)
    {
    
    theta = (itheta + 0.5) * PI / (ntheta - 1);
    v3.z = cos(theta);
    for (int iphi = 0; iphi < 1/*nphi*/; iphi++)
      {
      
      phi = (iphi + 0.5) * PI2 / (nphi - 1);
      v3.x = cos(phi) * sin(theta);
      v3.y = sin(phi) * sin(theta);

      avr = avr_sqr = 0;
      for (int iter = 0; iter < 100; iter++)
        {
        if (CalcDistr(nrays, v3, avr, avr_sqr, rng) != SUCCESS)
          {
          Assert(false);
          return FAILURE;
          }
        nr = nrays * (iter + 1);
        avr_ = avr / nr;
        avr_sqr_ = avr_sqr / nr;
        rms = Sqrt(fabs(avr_sqr_ - avr_ * avr_) / nr);
        if (rms <= tol * avr_)
          break;
        }
      if (avr_ > 0)
        err_max = Max(err_max, rms / avr_);

      printf("%4i %4i %12I64i %10.6f %10.6f    %8.5f sec\n", itheta, iphi, nr, avr_, rms / (avr_ + 1e-50), timer.Elapsed() * 0.001);
      hist(itheta, iphi) = avr_;
      hist(itheta, 0) = avr_;
      hist(itheta, 1) = avr_;
      hist(itheta, 2) = avr_;
      }
    }

  tol = err_max;
  return SUCCESS;
  }



OKAY ExtScene::CalcDistr(const int nrays, const Vect3d &v3, OUT double &avr, OUT double &avr_sqr, INOUT Rnd &rng) const
  {
  Ray3d ray;
  double phi, t;
  Point3d x1, xa;
  Vect3d v2, v1, n1;

  const Vect3d na(0, 0, 1);

  ray.org = cam_pos;
  ray.dir = -v3;
  
  ray.org.z -= zc2;
  t = mirror2.FindIntersection(ray.org, ray.dir);
  if (t < 0)
    {
    Assert(false);
    return FAILURE;
    }
  const Point3d x2 = cam_pos + ray.dir * t; 
  if (x2.z < zmin_mirror2)
    return SUCCESS; 

  const double len2 = t;
  const Vect3d n2 = mirror2.Normal(Point3d(x2.x, x2.y, x2.z - zc2));

  
  const Vect3d s2 = ray.dir - 2 * DotProd(ray.dir, n2) * n2;

  const double cos_gamma2 = fabs(DotProd(n2, v3));



  const Vect3d p2 = (n2 - DotProd(n2, s2) * s2).Normalize();
  const Vect3d q2 = CrossProd(n2, p2).Normalize();
  for (int iray = 0; iray < nrays; iray++)
    {
#if 0
    phi = PI2 * rng.DRnd(); 
    const double cos_theta = 1 + (cos_theta2_max - 1) * rng.DRnd();
    const double theta = ACos(cos_theta);
    Vect2d omega2 = Vect2d(cos(phi), sin(phi)) * sin(theta);
    v2 = cos_theta * s2 + omega2.x * p2 + omega2.y * q2;
    t = (za - x2.z) / v2.z;
    xa = x2 + t * v2;
    if (xa.x * xa.x + xa.y * xa.y > ra * ra)
      continue;

    const double len = Length(xa - x2);

    
    const double p_v2 = 1;


#else
    
    const double r = ra * Sqrt(rng.DRnd());
    phi = 2 * PI * rng.DRnd();
    xa.z = za;
    xa.x = r * cos(phi);
    xa.y = r * sin(phi);

    
    const double len = Length(xa - x2);
    v2 = (xa - x2) * (1 / len);

    
    const double p_v2 = (len * len) / fabs(DotProd(v2, na));
#endif

    const double cos_sigma2 = fabs(DotProd(n2, v2));

    
    double bdf2 = this->bdf2.Luminance(v3, v2, n2);


    
    const double p0_v2 = (REV_PI * bdf2) * cos_sigma2;

    
    const double prbb_scale = p0_v2 / p_v2;



    ray.org = xa;
    ray.dir = v2;
    
    ray.org.z -= zc1;
    t = mirror1.FindIntersection(ray.org, ray.dir);
    if (t < 0)
      continue;

    x1 = xa + ray.dir * t; 
    if (x1.z > zmax_mirror1)
      continue; 

    const Vect3d n1 = mirror1.Normal(Point3d(x1.x, x1.y, x1.z - zc1));


    
    const double len1 = Length(ls_pos - x1);
    v1 = (ls_pos - x1) * (1 / len1);

    
    const Vect3d s1 = ray.dir - 2 * DotProd(ray.dir, n1) * n1;


    const double cos_sigma1 = fabs(DotProd(n1, v1));

    
    double bdf1 = this->bdf1.Luminance(v2, v1, n1);

    
    const double lum1 = (REV_PI * bdf1) * cos_sigma1 / (len1 * len1);

    
    const double dlum2 = prbb_scale * lum1;
    
    const double contrib = dlum2 * Sqr(len2);

    
    avr     += contrib;
    avr_sqr += Sqr(contrib);
    }
  return SUCCESS;
  }
OKAY ExtScene::CalcMapping(const Vect3d &v3, OUT Vect3d &v1) const
  {
  Ray3d ray;
  double t;
  Point3d x1, xa;
  Vect3d v2;

  ray.org = cam_pos;
  ray.dir = -v3;
  
  ray.org.z -= zc2;
  t = mirror2.FindIntersection(ray.org, ray.dir);
  if (t < 0)
    return FAILURE;
  const Point3d x2 = cam_pos + ray.dir * t; 
  if (x2.z < zmin_mirror2)
    return FAILURE; 


  xa.z = za;
  xa.x = 0;
  xa.y = 0;

  
  const double len = Length(xa - x2);
  v2 = (xa - x2) * (1 / len);

  ray.org = xa;
  ray.dir = v2;
  
  ray.org.z -= zc1;
  t = mirror1.FindIntersection(ray.org, ray.dir);
  if (t < 0)
    return FAILURE;

  x1 = xa + ray.dir * t; 
  if (x1.z > zmax_mirror1)
    return FAILURE; 

  
  const double len1 = Length(ls_pos - x1);
  v1 = (ls_pos - x1) * (1 / len1);
  return SUCCESS;
  }

  

