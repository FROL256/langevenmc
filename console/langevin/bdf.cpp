#include <kiam.hpp>
using namespace Kiam;
#include "bdf.hpp"


OKAY BDF::Create(double gs)
  {
  this->gs = gs;
  if (gs == 0)
    max_theta = PI;
  else
    max_theta = Sqrt(9 / gs);
  return SUCCESS;
  }
double BDF::Luminance(const Vect3d &in, const Vect3d &out, const Vect3d &normal) const
  {
  if (gs == 0)
    return REV_PI;
  else
    {
    const double cos_sigma = DotProd(in, normal);
    const double cos_gamma = DotProd(out, normal);

    const Vect3d s = in - 2 * cos_sigma * normal;

    const double cos_theta = fabs(DotProd(out, s));

    return Pow(cos_theta, gs) / Sqrt(fabs(cos_sigma * cos_gamma));
    }
  }
double BDF::Intensity(const Vect3d &in, const Vect3d &out, const Vect3d &normal) const
  {
  const double cos_gamma = fabs(DotProd(out, normal));

  if (gs == 0)
    return REV_PI * cos_gamma;
  else
    {
    const double cos_sigma = DotProd(in, normal);

    const Vect3d s = in - 2 * cos_sigma * normal;

    const double cos_theta = fabs(DotProd(out, s));

    return (Pow(cos_theta, gs) / Sqrt(fabs(cos_sigma * cos_gamma))) * cos_gamma;
    }
  }

double BDF::GetMaxTheta() const
  {
  return max_theta;
  }

double BDF::GetGs() const
  {
  return gs;
  }


