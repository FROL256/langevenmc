#ifndef _LMCSOLVER_HPP_INCLUDED
#define _LMCSOLVER_HPP_INCLUDED

#include <base/matrix.hpp>
#include <math/vect2.hpp>
#include <math/vect3.hpp>
#include <math/matrix3.hpp>
#include <math/matrix4.hpp>
#include <math/rnd.hpp>
#include "bdf.hpp"
#include "iscene.hpp"




class LMCSolver
  {
  public:
    
    struct BasePathDataSpecDir
      {
      
      Vect3d v1;
      
      Vect2d omega1;
      };

    
    struct FullPathData
      {
      
      inline BasePathDataSpecDir VaryBaseData(const Vect2d &dv1, const Vect2d &domega1) const;
      
      inline double ImportanceFunctionSpecDir() const;

      
      inline Vect3d ConvertDv1(const Vect2d &dv1) const;
      
      inline Vect2d ConvertDv1(const Vect3d &dv1) const;
      
      inline operator BasePathDataSpecDir() const;

      
      Vect3d p0, q0;

      
      
      
      Point3d x1;
      
      Vect3d v1;
      
      Vect3d n1;
      
      Matrix3d R1;
      
      const BDF *bdf1;
      

      
      
      
      Point3d x2;
      
      Vect3d v2;
      
      Vect3d n2;
      
      Matrix3d R2;
      
      const BDF *bdf2;
      
      Vect3d s1;
      
      Vect3d p1, q1;
      
      Vect2d omega1;
      
      double cos_theta1;
      
      double rev_sqr_max_theta1;
      

      
      
      
      Vect3d v3;
      
      Vect3d s2;
      
      Vect3d p2, q2;
      
      Vect2d omega2;
      
      Vect3d omega2_3d; 
      
      double cos_theta2;
      
      double rev_sqr_max_theta2;
      

      
      Point3d xa;
      
      double rev_sqr_ra;
      
      };

  public:
    
    struct LMCOptions
      {
      
      inline LMCOptions();

      
      enum HASTINGS
        {
        HASTINGS_FULL = 0,
        HASTINGS_PARTIAL = 1,
        };
      
      enum DRIFT
        {
        DRIFT_FULL = 0,
        DRIFT_NONE = 1,
        DRIFT_GRAD = 2,
        DRIFT_DIV  = 3,
        };

      
      HASTINGS hastings;
      
      DRIFT    drift;
      
      bool matrices;
      
      bool auto_dt_max;
      
      double dt;
      };

    struct StepData
      {
      inline StepData();

      FullPathData fpd;
      Matrix4d T, TT;
      Vect4d div, grad, drift;
      double dt_max;
      
      bool is_valid;
      };

  public:
    
    OKAY Create(const IScene *scene);

    
    inline void SetOptions(const LMCOptions &options);
    
    inline const LMCOptions &GetOptions() const;

    
    bool DoOneStep(INOUT BasePathDataSpecDir &bpd, INOUT StepData &sd, OUT double &dt, INOUT Rnd &rng) const;

  protected:
    
    OKAY CalcPathData(const BasePathDataSpecDir &bpd, OUT FullPathData &fpd) const;
    
    OKAY CalcGradUAndConstr(const FullPathData &fpd, OUT Vect4d &grad, OUT Matrix4d &C_x1, OUT Matrix4d &C_x2, OUT Matrix4d &C_xa) const;
    
    OKAY CalcGradUAndTransf(const FullPathData &fpd, OUT Vect4d &grad, OUT Matrix4d &T, OUT Matrix4d &TT) const;

    
    OKAY CalcAllTerms(const FullPathData &fpd, OUT Vect4d &drift, OUT Matrix4d &T, OUT double &dt_max) const;
  protected:
    
    static inline Matrix3d Product(const Vect3d &a, const Vect3d &b);


  private:
    
    LMCOptions options;

    
    const IScene *scene;
  };


Vect3d LMCSolver::FullPathData::ConvertDv1(const Vect2d &dv1) const
  {
  return dv1[0] * p0 + dv1[1] * q0;
  }

Vect2d LMCSolver::FullPathData::ConvertDv1(const Vect3d &dv1) const
  {
  return Vect2d(DotProd(dv1, p0), DotProd(dv1, q0));
  }


LMCSolver::FullPathData::operator LMCSolver::BasePathDataSpecDir() const
  {
  BasePathDataSpecDir bpd;
  bpd.v1 = v1;
  bpd.omega1 = omega1;
  return bpd;
  }


LMCSolver::BasePathDataSpecDir LMCSolver::FullPathData::VaryBaseData(const Vect2d &dv1, const Vect2d &domega1) const
  {
  BasePathDataSpecDir bpd;
  if (fabs(dv1.x) + fabs(dv1.y) < MathD::EPS_VALUE)
    bpd.v1 = v1;
  else
    {
    bpd.v1 = Sqrt(1 - dv1.SqrLength()) * v1 + dv1[0] * p0 + dv1[1] * q0;

    }
  bpd.omega1 = omega1 + domega1;
  return bpd;
  }


double LMCSolver::FullPathData::ImportanceFunctionSpecDir() const
  {
#if 0
  return bdf1->Intensity(v1, v2, n1) * bdf2->Intensity(v2, v3, n2);
#else
  return bdf1->Luminance(v1, v2, n1) * DotProd(v2, n1) * bdf2->Luminance(v2, v3, n2) * DotProd(v3, n2);
#endif
  }



LMCSolver::LMCOptions::LMCOptions()
  {
  hastings = HASTINGS::HASTINGS_FULL;
  drift    = DRIFT::DRIFT_FULL;

  matrices = true;
  auto_dt_max = true;
  dt = 0.01;
  }

void LMCSolver::SetOptions(const LMCSolver::LMCOptions &options)
  {
  this->options = options;
  }

const LMCSolver::LMCOptions &LMCSolver::GetOptions() const
  {
  return options;
  }

LMCSolver::StepData::StepData()
  {
  is_valid = false;
  }


Matrix3d LMCSolver::Product(const Vect3d &a, const Vect3d &b)
  {
#if 1
  Matrix3d p(b, b, b);
  p.r0 *= a.x;
  p.r1 *= a.y;
  p.r2 *= a.z;
#else
  Matrix3d p;
  p[0][0] = a[0] * b[0];
  p[0][1] = a[0] * b[1];
  p[0][2] = a[0] * b[2];
  p[1][0] = a[1] * b[0];
  p[1][1] = a[1] * b[1];
  p[1][2] = a[1] * b[2];
  p[2][0] = a[2] * b[0];
  p[2][1] = a[2] * b[1];
  p[2][2] = a[2] * b[2];
#endif
  return p;
  }

#endif