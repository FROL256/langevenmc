#include <kiam.hpp>
using namespace Kiam;
#include <base/time.hpp>
#include <math/matrix2.hpp>
#include <math/vect2.hpp>
#include <math/vect3.hpp>
#include <math/rnd.hpp>
START_C_DECLS
#include <math/inal/inal.h>
END_C_DECLS

#include "lmcsolver.hpp"


static const double epsilon = 1e-6;


inline void CalcOrts(const Vect3d &v, const Vect3d &n, OUT Vect3d &p, OUT Vect3d &q)
  {
  p = (n - DotProd(n, v) * v).Normalize();
  q = CrossProd(n, p).Normalize();
  }




OKAY choldc(const Matrix4d &a, OUT Matrix4d &L)
  {
  const int n = 4;
  int i, j, k;
  for (i = 0; i < n; i++)
    {
    for (j = i; j < n; j++)
      L[i][j] = 0;
    }

  Vect4d p;
  double sum;
  for (i = 0; i < n; i++) 
    {
    for (j = i; j < n; j++) 
      {
      for (sum = a[i][j], k = i - 1; k >= 0; k--) 
        sum -= L[i][k] * L[j][k];

      if (i == j) 
        {
        if (sum <= 0.0) 
          {
          printf("choldc failed\n");
          sum = -sum;


          }
        p[i] = Sqrt(sum);
        }
      else 
        L[j][i] = sum / p[i];
      }
    }

  for (i = 0; i < n; i++)
    {
    
    for (j = i; j < n; j++)
      L[i][j] = 0;
    L[i][i] = p[i];
    }

  return SUCCESS;
  }


OKAY LMCSolver::Create(const IScene *scene)
  {
  this->scene = scene;
  return SUCCESS;
  }


bool LMCSolver::DoOneStep(INOUT BasePathDataSpecDir &bpd, INOUT StepData &sd, OUT double &dt, INOUT Rnd &rng) const
  {
  BasePathDataSpecDir X_new;
  FullPathData &fpd = sd.fpd;
  Matrix4d &T = sd.T;
  Vect4d dX, &drift = sd.drift;
  double &dt_max = sd.dt_max;
  if (!sd.is_valid) 
    {
    if (CalcPathData(bpd, fpd) != SUCCESS)
      {
      Assert(false);
      return false;
      }
    if (CalcAllTerms(fpd, drift, T, dt_max) != SUCCESS)
      return false;
    sd.is_valid = true;
    }
  if (options.auto_dt_max)
    dt = Min(options.dt, dt_max);
  else
    dt = options.dt;

  const double sc = Sqrt(2 * dt);

  const Vect4d csi(rng.Gauss(), rng.Gauss(), rng.Gauss(), rng.Gauss());
  dX = dt * drift + sc * T * csi;

  const Vect2d &dv1 = *(Vect2d *)&dX[0];
  const Vect2d &domega1 = *(Vect2d *)&dX[2];

  
  if (dv1.SqrLength() > 0.99 || domega1.SqrLength() > 0.99)
    return false;

  X_new = fpd.VaryBaseData(dv1, domega1);

  StepData sd_new;
  FullPathData &fpd_new = sd_new.fpd;
  if (CalcPathData(X_new, fpd_new) != SUCCESS)
    {
    
    return false;
    }

  
  Vect4d dX_new;
  Vect2d &dv1_new = *(Vect2d *)&dX_new[0];
  Vect2d &domega1_new = *(Vect2d *)&dX_new[2];
  domega1_new = -domega1;

  
  const Vect3d dv1_3d = fpd.ConvertDv1(dv1);
  dv1_new = fpd_new.ConvertDv1(-Sqrt(1 - SqrLength(dv1)) * dv1_3d + SqrLength(dv1) * fpd.v1);


  
  

  
  const double detT = T[0][0] * T[1][1] * T[2][2] * T[3][3];

  
  


  
  const double p_fwd = exp(-0.5 * (csi[0] * csi[0] + csi[1] * csi[1] + csi[2] * csi[2] + csi[3] * csi[3]))
                     / (sc * sc * sc * sc * detT);


  
  Matrix4d &T_new = sd_new.T;
  Vect4d &drift_new = sd_new.drift;
  double &dt_max_new = sd_new.dt_max;
  if (CalcAllTerms(fpd_new, drift_new, T_new, dt_max_new) != SUCCESS)
    {
    printf("CalcAllTerms(fpd_new,...) failed\n");
    Assert(false);
    return false;
    }
  sd_new.is_valid = true;

  const double dt_new = options.auto_dt_max ? Min(options.dt, dt_max_new) : options.dt;
  const double sc_new = Sqrt(2 * dt_new);

  
  
  

  if (options.hastings == LMCOptions::HASTINGS_PARTIAL)
    {
    
    
    sd = sd_new;
    bpd = fpd_new;
    return true;
    }

  
  const double detT_new = T_new[0][0] * T_new[1][1] * T_new[2][2] * T_new[3][3];

  
  
  
  Vect4d eta, rhs;
  rhs = (dX_new - dt_new * drift_new);
  rhs *= 1 / sc_new;

  
  
  Matrix4d matrix = T_new; 
  if (resol((double *)&matrix, eta, rhs, 4, false, NULL) != SUCCESS)
    {
    printf("resol() failed\n");
    Assert(false);
    return false;
    }

#if 0 
  const Vect4d dX_bwd = dt_new * drift_new + sc_new * T_new * eta;
  const Vect2d &dv1_bwd = *(const Vect2d *)&dX_bwd.x;
  const Vect2d &domega1_bwd = *(Vect2d *)&dX_bwd.z;

  BasePathDataSpecDir bpd_bwd; 
  bpd_bwd = fpd_new.VaryBaseData(dv1_bwd, domega1_bwd);

  if (Length(bpd_bwd.v1 - bpd.v1) > MathF::EPS_VALUE ||
      Length(bpd_bwd.omega1 - bpd.omega1) > MathF::EPS_VALUE)
    {
    printf("Test on BWD transition failure #1\n");


    }
#endif


  
  


  
  const double p_bwd = exp(-0.5 * (eta[0] * eta[0] + eta[1] * eta[1] + eta[2] * eta[2] + eta[3] * eta[3]))
                     / (sc_new * sc_new * sc_new * sc_new * detT_new);

  
  const double imp_func     = fpd.ImportanceFunctionSpecDir();
  
  const double imp_func_new = fpd_new.ImportanceFunctionSpecDir();

  
  bool accept = true;
  if (p_fwd * imp_func == 0)
    accept = true;
  else
    {
    const double pr_acc = (p_bwd * imp_func_new) / (p_fwd * imp_func);
    accept = (rng.DRnd() <= pr_acc);
    }

  if (accept)
    {
    sd = sd_new;
    bpd = fpd_new;
    return true;
    }
  else
    return false;
  }


OKAY LMCSolver::CalcPathData(const BasePathDataSpecDir &bpd, OUT FullPathData &fpd) const
  {
  Ray3d ray;

  IScene::RaySegmData rsd;

  fpd.omega1 = bpd.omega1;
  fpd.v1 = bpd.v1;
  fpd.v1.Normalize();


  
  const Vect3d n0(0, 0, 1);
  CalcOrts(fpd.v1, n0, fpd.p0, fpd.q0);


  
  ray.org = scene->GetLightPos();
  ray.dir = bpd.v1;
  if (!scene->FindIntersection(ray, rsd, 0))
    return FAILURE;
  fpd.bdf1 = rsd.bdf;
  fpd.x1 = rsd.end;
  fpd.n1 = rsd.normal;
  fpd.R1 = rsd.curvature;

  fpd.s1 = fpd.v1 - 2 * DotProd(fpd.v1, fpd.n1) * fpd.n1;

  
  CalcOrts(fpd.s1, fpd.n1, fpd.p1, fpd.q1);

  
  fpd.rev_sqr_max_theta1 = 1 / Sqr(rsd.bdf->GetMaxTheta());

  fpd.cos_theta1 = Sqrt(1 - fpd.omega1.SqrLength());
  fpd.v2 = fpd.cos_theta1 * fpd.s1 + fpd.omega1[0] * fpd.p1 + fpd.omega1[1] * fpd.q1;

  
  ray.org = fpd.x1;
  ray.dir = fpd.v2;
  if (!scene->FindIntersection(ray, rsd, 1))
    return FAILURE;
  fpd.bdf2 = rsd.bdf;
  fpd.x2 = rsd.end;
  fpd.n2 = rsd.normal;
  fpd.R2 = rsd.curvature;
  fpd.xa = rsd.org + rsd.dist2hole * ray.dir;

  
  fpd.rev_sqr_max_theta2 = 1 / Sqr(rsd.bdf->GetMaxTheta());
  fpd.rev_sqr_ra = 1 / Sqr(rsd.hole_size);


  
  Vect3d view;
  if (!scene->IsVisible(fpd.x2, view))
    return false;
  fpd.v3 = -view;

  fpd.s2 = fpd.v2 - 2 * DotProd(fpd.v2, fpd.n2) * fpd.n2;
  fpd.cos_theta2 = DotProd(fpd.v3, fpd.s2);

  
  CalcOrts(fpd.s2, fpd.n2, fpd.p2, fpd.q2);

  fpd.omega2_3d = fpd.v3 - fpd.cos_theta2 * fpd.s2;

  fpd.omega2[0] = DotProd(fpd.v3 - fpd.cos_theta2 * fpd.s2, fpd.p2);
  fpd.omega2[1] = DotProd(fpd.v3 - fpd.cos_theta2 * fpd.s2, fpd.q2);

  return SUCCESS;
  }

#if 0

OKAY LMSSolver::CalcGradUAndConstr(const FullPathData &fpd, OUT BasePathDataCoord   &grad, OUT Matrix3d &C_x1, OUT Matrix3d &C_x2, OUT Matrix3d &C_xa) const
  {
  }
#endif

OKAY LMCSolver::CalcGradUAndConstr(const FullPathData &fpd, OUT Vect4d &grad, OUT Matrix4d &C_x1, OUT Matrix4d &C_x2, OUT Matrix4d &C_xa) const
  {
  const Vect3d na(0, 0, 1);

  double eps;
  
  FullPathData fpd1;
  Vect4d grad_cos_theta2;
  Vect2d dv1, domega1; 
  Matrix2d dv1_xa, domega1_xa;


#ifdef OMEGA2_AS_2D
  Matrix2d dv1_omega2, domega1_omega2;
#else
  Matrix3d dv1_omega2_3d, domega1_omega2_3d;
  dv1_omega2_3d = 0.0;
  domega1_omega2_3d = 0.0;
#endif

  const double imp_func0 = fpd.ImportanceFunctionSpecDir();


  eps = epsilon;
  dv1 = domega1 = 0;
  dv1[0] = eps;
  if (CalcPathData(fpd.VaryBaseData(dv1, domega1), fpd1) != SUCCESS)
    {
    eps = -epsilon;
    dv1 = domega1 = 0;
    dv1[0] = eps;
    if (CalcPathData(fpd.VaryBaseData(dv1, domega1), fpd1) != SUCCESS)
      {
      Assert(false);
      return FAILURE;
      }
    }

  grad[0] = -log(fpd1.ImportanceFunctionSpecDir() / imp_func0) / eps;
  grad_cos_theta2[0] = (fpd1.cos_theta2 - fpd.cos_theta2) / eps;
#ifdef OMEGA2_AS_2D
  dv1_omega2[0][0] = (fpd1.omega2[0] - fpd.omega2[0]) / eps;
  dv1_omega2[1][0] = (fpd1.omega2[1] - fpd.omega2[1]) / eps;
#else
  dv1_omega2_3d[0][0] = (fpd1.omega2_3d[0] - fpd.omega2_3d[0]) / eps;
  dv1_omega2_3d[1][0] = (fpd1.omega2_3d[1] - fpd.omega2_3d[1]) / eps;
  dv1_omega2_3d[2][0] = (fpd1.omega2_3d[2] - fpd.omega2_3d[2]) / eps;
#endif
  dv1_xa[0][0]     = (fpd1.xa[0] - fpd.xa[0]) / eps;
  dv1_xa[1][0]     = (fpd1.xa[1] - fpd.xa[1]) / eps;

  eps = epsilon;
  dv1 = domega1 = 0;
  dv1[1] = eps;
  if (CalcPathData(fpd.VaryBaseData(dv1, domega1), fpd1) != SUCCESS)
    {
    eps = -epsilon;
    dv1 = domega1 = 0;
    dv1[1] = eps;
    if (CalcPathData(fpd.VaryBaseData(dv1, domega1), fpd1) != SUCCESS)
      {
      Assert(false);
      return FAILURE;
      }
    }
  grad[1] = -log(fpd1.ImportanceFunctionSpecDir() / imp_func0) / eps;
  grad_cos_theta2[1] = (fpd1.cos_theta2 - fpd.cos_theta2) / eps;
#ifdef OMEGA2_AS_2D
  dv1_omega2[0][1] = (fpd1.omega2[0] - fpd.omega2[0]) / eps;
  dv1_omega2[1][1] = (fpd1.omega2[1] - fpd.omega2[1]) / eps;
#else
  dv1_omega2_3d[0][1] = (fpd1.omega2_3d[0] - fpd.omega2_3d[0]) / eps;
  dv1_omega2_3d[1][1] = (fpd1.omega2_3d[1] - fpd.omega2_3d[1]) / eps;
  dv1_omega2_3d[2][1] = (fpd1.omega2_3d[2] - fpd.omega2_3d[2]) / eps;
#endif
  dv1_xa[0][1]     = (fpd1.xa[0] - fpd.xa[0]) / eps;
  dv1_xa[1][1]     = (fpd1.xa[1] - fpd.xa[1]) / eps;

  eps = epsilon;
  dv1 = domega1 = 0;
  domega1[0] = eps;
  if (CalcPathData(fpd.VaryBaseData(dv1, domega1), fpd1) != SUCCESS)
    {
    eps = -epsilon;
    dv1 = domega1 = 0;
    domega1[0] = eps;
    if (CalcPathData(fpd.VaryBaseData(dv1, domega1), fpd1) != SUCCESS)
      {
      Assert(false);
      return FAILURE;
      }
    }
  grad[2] = -log(fpd1.ImportanceFunctionSpecDir() / imp_func0) / eps;
  grad_cos_theta2[2] = (fpd1.cos_theta2 - fpd.cos_theta2) / eps;
#ifdef OMEGA2_AS_2D
  domega1_omega2[0][0] = (fpd1.omega2[0] - fpd.omega2[0]) / eps;
  domega1_omega2[1][0] = (fpd1.omega2[1] - fpd.omega2[1]) / eps;
#else
  domega1_omega2_3d[0][0] = (fpd1.omega2_3d[0] - fpd.omega2_3d[0]) / eps;
  domega1_omega2_3d[1][0] = (fpd1.omega2_3d[1] - fpd.omega2_3d[1]) / eps;
  domega1_omega2_3d[2][0] = (fpd1.omega2_3d[2] - fpd.omega2_3d[2]) / eps;
#endif
  domega1_xa[0][0]     = (fpd1.xa[0] - fpd.xa[0]) / eps;
  domega1_xa[1][0]     = (fpd1.xa[1] - fpd.xa[1]) / eps;

  eps = epsilon;
  dv1 = domega1 = 0;
  domega1[1] = eps;
  if (CalcPathData(fpd.VaryBaseData(dv1, domega1), fpd1) != SUCCESS)
    {
    eps = -epsilon;
    dv1 = domega1 = 0;
    domega1[1] = eps;
    if (CalcPathData(fpd.VaryBaseData(dv1, domega1), fpd1) != SUCCESS)
      {
      Assert(false);
      return FAILURE;
      }
    }
  grad[3] = -log(fpd1.ImportanceFunctionSpecDir() / imp_func0) / eps;
  grad_cos_theta2[3] = (fpd1.cos_theta2 - fpd.cos_theta2) / eps;
#ifdef OMEGA2_AS_2D
  domega1_omega2[0][1] = (fpd1.omega2[0] - fpd.omega2[0]) / eps;
  domega1_omega2[1][1] = (fpd1.omega2[1] - fpd.omega2[1]) / eps;
#else
  domega1_omega2_3d[0][1] = (fpd1.omega2_3d[0] - fpd.omega2_3d[0]) / eps;
  domega1_omega2_3d[1][1] = (fpd1.omega2_3d[1] - fpd.omega2_3d[1]) / eps;
  domega1_omega2_3d[2][1] = (fpd1.omega2_3d[2] - fpd.omega2_3d[2]) / eps;
#endif
  domega1_xa[0][1] = (fpd1.xa[0] - fpd.xa[0]) / eps;
  domega1_xa[1][1] = (fpd1.xa[1] - fpd.xa[1]) / eps;

#if 0
  
  const double sqr_cos_theta1 = Sqr(fpd.cos_theta1);
  const double sqr_cos_theta2 = Sqr(fpd.cos_theta1);
  const double cos_theta2 = fpd.cos_theta2;
  Vect4d grad_;
  grad_                    = -(gs2 / cos_theta2) * grad_cos_theta2;
  *((Vect2d *)&(grad_[2])) += (gs1 / sqr_cos_theta1) * fpd.omega1;


#endif
  
  
  const double scale1 = fpd.rev_sqr_max_theta1; 
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      C_x1[i][j] = 0;
    }
#if 1
  C_x1[0][0] = 1;
  C_x1[1][1] = 1;
#endif
  C_x1[2][2] = scale1;
  C_x1[3][3] = scale1;

  Matrix2d block11, block12, block21, block22;
  
  
#ifdef OMEGA2_AS_2D
  block11 = dv1_omega2.Transposed() * dv1_omega2;
  block12 = dv1_omega2.Transposed() * domega1_omega2;
  block21 = block12.Transposed();
  block22 = domega1_omega2.Transposed() * domega1_omega2;
#else
  Matrix3d block11_3d, block12_3d, block21_3d, block22_3d;
  block11_3d = dv1_omega2_3d.Transposed() * dv1_omega2_3d;
  block12_3d = dv1_omega2_3d.Transposed() * domega1_omega2_3d;
  block21_3d = block12_3d.Transposed();
  block22_3d = domega1_omega2_3d.Transposed() * domega1_omega2_3d;
  for (int i = 0; i < 2; i++)
    {
    for (int j = 0; j < 2; j++)
      {
      block11[i][j] = block11_3d[i][j];
      block12[i][j] = block12_3d[i][j];
      block21[i][j] = block21_3d[i][j];
      block22[i][j] = block22_3d[i][j];
      }
    }
#endif

  const double scale2 = fpd.rev_sqr_max_theta2; 
  for (int i = 0; i < 2; i++)
    {
    for (int j = 0; j < 2; j++)
      {
      C_x2[i    ][j]     = scale2 * block11[i][j];
      C_x2[i    ][j + 2] = scale2 * block12[i][j];
      C_x2[i + 2][j]     = scale2 * block21[i][j];
      C_x2[i + 2][j + 2] = scale2 * block22[i][j];
      }
    }



  
  
  block11 = dv1_xa.Transposed() * dv1_xa;
  block12 = dv1_xa.Transposed() * domega1_xa;
  block21 = block12.Transposed();
  block22 = domega1_xa.Transposed() * domega1_xa;
  const double scale3 = fpd.rev_sqr_ra; 
  for (int i = 0; i < 2; i++)
    {
    for (int j = 0; j < 2; j++)
      {
      C_xa[i    ][j]     = scale3 * block11[i][j];
      C_xa[i    ][j + 2] = scale3 * block12[i][j];
      C_xa[i + 2][j]     = scale3 * block21[i][j];
      C_xa[i + 2][j + 2] = scale3 * block22[i][j];
      }
    }

  return SUCCESS;
  }


OKAY LMCSolver::CalcGradUAndTransf(const FullPathData &fpd, OUT Vect4d &grad, OUT Matrix4d &T, OUT Matrix4d &TT) const
  {
  Matrix4d C_x1, C_x2, C_xa, C;
  if (CalcGradUAndConstr(fpd, grad, C_x1, C_x2, C_xa) != SUCCESS)
    return FAILURE;

  if (!options.matrices)
    {
    T.Identity();
    TT.Identity();
    return SUCCESS;
    }

  
  for (int i = 0; i < 4; i++)
    {
    for (int j = 0; j < 4; j++)
      C[i][j] = C_x1[i][j] + C_x2[i][j] + C_xa[i][j];
    C[i][i] += 1; 
    }

  
  TT = C;
  if (invert((double *)&TT, 4) != SUCCESS)
    {
    Assert(false);
    return FAILURE;
    }

  if (choldc(TT, T) != SUCCESS)
    {
    Assert(false);
    return FAILURE;
    }
  return SUCCESS;
  }


OKAY LMCSolver::CalcAllTerms(const FullPathData &fpd, OUT Vect4d &drift, OUT Matrix4d &T, OUT double &dt_max) const
  {
  Vect4d grad, div;
  Matrix4d TT;
  if (CalcGradUAndTransf(fpd, grad, T, TT) != SUCCESS)
    return FAILURE;

  if (options.drift == LMCOptions::DRIFT_FULL || options.drift == LMCOptions::DRIFT_GRAD)
    {
    drift = options.matrices ? TT * grad : grad;
    drift.Negate();
    }
  else
    drift.Set(0);

  if (options.drift == LMCOptions::DRIFT_FULL || options.drift == LMCOptions::DRIFT_DIV)
    {
    
    Vect4d grad1, dX;
    Vect2d &dv1 = *(Vect2d *)&dX[0];
    Vect2d &domega1 = *(Vect2d *)&dX[2];

    BasePathDataSpecDir bpd1;
    FullPathData fpd1;
    Matrix4d T1, TT1;


    
    div.Set(0);
    double eps;

    for (int j = 0; j < 4; j++)
      {
      eps = epsilon;
      dX.Set(0);
      dX[j] = eps;
      bpd1 = fpd.VaryBaseData(dv1, domega1);
      if (CalcPathData(bpd1, fpd1) != SUCCESS)
        {
        eps = -epsilon;
        dX[j] = eps;
        bpd1 = fpd.VaryBaseData(dv1, domega1);
        if (CalcPathData(bpd1, fpd1) != SUCCESS)
          {
          Assert(false);
          return FAILURE;
          }
        }
      if (CalcGradUAndTransf(fpd1, grad1, T1, TT1) != SUCCESS)
        {
        Assert(false);
        return FAILURE;
        }
      div[0] += (TT1[0][j] - TT[0][j]) / eps;
      div[1] += (TT1[1][j] - TT[1][j]) / eps;
      div[2] += (TT1[2][j] - TT[2][j]) / eps;
      div[3] += (TT1[3][j] - TT[3][j]) / eps;
      }
    drift += div;
    }

  if (options.auto_dt_max && options.drift != LMCOptions::DRIFT_NONE)
    {
    
    double prod1 = 0; 
    double prod2 = 0; 
    double prod3 = 0; 
    for (int i = 0; i < 4; i++)
      {
      prod1 += drift[i] * drift[i];
      prod3 += drift[i] * grad[i];
      double sum = 0;
      for (int j = 0; j < 4; j++)
        sum += T[j][i] * drift[j];
      prod2 += sum * sum;
      }
    dt_max = Min(2 * prod2 / (prod1 * prod1), 0.1 / fabs(prod3));
    }
  else
    dt_max = 1e10;

  return SUCCESS;
  }

