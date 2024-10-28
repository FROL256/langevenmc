#include <kiam.hpp>
using namespace Kiam;
#include <math/vect2.hpp>
#include <math/vect3.hpp>

#include "ellipsoid.hpp"


OKAY Ellipsoid::CreateFromRadii(double a, double b)
  {
  if (b < a)
    {
    Assert(false);
    return FAILURE;
    }
  this->a = a;
  this->b = b;
  this->zf = Sqrt(b * b - a * a);
  return SUCCESS;
  }


OKAY Ellipsoid::CreateFromFocuses(double zf, double eccentricity)
  {
  if (zf < 0 || eccentricity < 1)
    {
    Assert(false);
    return FAILURE;
    }
  this->zf = zf;
  a = zf / Sqrt(eccentricity * eccentricity - 1);
  b = a * eccentricity;
  return SUCCESS;
  }


Vect3d Ellipsoid::Normal(const Point3d &pt) const
  {
  Vect3d n(pt.x, pt.y, Sqr(a / b) * pt.z);
  n.Normalize();
  return n;
  }





Matrix3d Ellipsoid::TangentAndNormal(const Point3d &pt) const
  {
  Matrix3d cs;
  Vect3d &tau1 = cs.r0, &tau2 = cs.r1, &n = cs.r2;

  n = Vect3d(pt.x, pt.y, Sqr(a / b) * pt.z);
  n.Normalize();

  tau2 = Vect3d(pt.y, -pt.x, 0);
  tau2.Normalize();

  tau1 = CrossProd(tau2, n);
  return cs;
  }


Matrix3d Ellipsoid::Curvature(const Point3d &pt) const
  {
  Matrix3d R;
  const double &x = pt.x, &y = pt.y, &z = pt.z;

  const double c = a * a / (b * b);
  const double zeta = c * z, zeta2 = zeta * zeta;

  R[0][0] = x * x + zeta2;
  R[0][1] = -x * y;
  R[0][2] = -c * x * zeta;

  R[1][0] = -x * y;
  R[1][1] = y * y + zeta2;
  R[1][2] = -c * y * zeta;

  R[2][0] = -x * zeta;
  R[2][1] = -y * zeta;
  R[2][2] = -a * a * c - zeta2;

  R *= 1 / Sqrt(a * a + (c - 1) * zeta2);
  return R;
  }




double Ellipsoid::FindIntersection(const Point3d &org, const Vect3d &dir) const
  {
  const Vect3d V(dir.x  / a, dir.y / a, dir.z / b);
  const Vect3d X0(org.x / a, org.y / a, org.z / b);
  const double X0V  = DotProd(X0, V);
  const double X0X0 = DotProd(X0, X0);
  const double VV   = DotProd(V, V);
  if (X0X0 > 1) 
    {
    Assert(false);
    return FAILURE;
    }

  const double t = (-X0V + Sqrt(X0V * X0V - VV * (X0X0 - 1))) / VV;
#if 0 
  const Point3d hit = org + t * dir;
  const double r2 = Sqr(hit.x / a) + Sqr(hit.y / a) + Sqr(hit.z / b);
  const Vect3d HIT = X0 + t * V;
  const double R2 = SqrLength(HIT);

  const double err = VV * t * t + 2 * X0V * t + (X0X0 - 1);
#endif
  return t;
  }


