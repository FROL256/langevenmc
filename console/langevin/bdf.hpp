#ifndef _BDF_HPP_INCLUDED
#define _BDF_HPP_INCLUDED

#include <math/math.hpp>
#include <math/vect3.hpp>


class BDF
  {
  public:
    OKAY Create(double gs);

    double Luminance(const Vect3d &in, const Vect3d &out, const Vect3d &normal) const;
    double Intensity(const Vect3d &in, const Vect3d &out, const Vect3d &normal) const;
    double GetMaxTheta() const;
    double GetGs() const;

  private:
    double gs;
    double max_theta;
  };


#endif