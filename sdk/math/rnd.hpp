










#ifndef _KSML_RND_HPP_
#define _KSML_RND_HPP_

#include <base/arrays.hpp>
#include <base/base.hpp>
#include <base/time.hpp>

#include "vect2.hpp"

KIAM_NAMESPACE_START


class Rnd
  {
  public:

    
    enum
      {
      STRING_LEN = 30
      };

    
    
    
    Rnd(const char *str);
    
    
    Rnd(unsigned iseed = Time::Get());
    
    Rnd(const Rnd &u);
    

    
    
    
    virtual inline double DRnd();
    
    virtual inline double DRndP();
    
    inline double DRnd(double a, double b);
    
    virtual inline double *DRndPtr();
    
    virtual inline void ReNorm(double &prob, double pp, double pp_prev);
    
    inline int IRnd(int n);
    
    void RndStore(char *buf);
    
    double Gauss();
    
    
    inline Point2d SphrUnif(const double phi[2], const double cos_theta[2]);
    
    
    inline Point2d SphrBiLin(const double phi[2], const double theta[2],
                             const double cos_theta[2], const double f[2][2]);
    
    
    inline double SphrLin(const double theta[2],
                          const double cos_theta[2],
                          const double f[2]);
    

    
    
    
    inline bool operator == (const Rnd &u) const;
    
    inline bool operator != (const Rnd &u) const;
    
    
    static void CreateSeedsMultiRnd(int num, TArray<unsigned> &rnd_seeds);

  private:
    enum
      {
      MOD1  = 30269,
      MOD2  = 30307,
      MOD3  = 30323,
      MULT1 = 171,
      MULT2 = 172,
      MULT3 = 170
      };

    
    inline void Gen();
    
    static bool IsRndSeedUnique(unsigned seed, int last, const TArray<unsigned> &rnd_seeds);

  private:
    
    double dvalue;
    
    long m1;
    
    long m2;
    
    long m3;
    
    double gauss_prev;
    
    bool   has_gauss_prev;
  }; 








void Rnd::Gen()
  {
  dvalue = (double)m1 / MOD1 + (double)m2 / MOD2 + (double)m3 / MOD3;
  dvalue -= (int)dvalue;  
  Assert(0.0 <= dvalue && dvalue < 1.0);
  }  








double Rnd::DRnd()
  {
  
  m1 = (m1 * MULT1) % MOD1;
  m2 = (m2 * MULT2) % MOD2;
  m3 = (m3 * MULT3) % MOD3;
  double result = dvalue;
  Gen();  
  return result;
  }  









double Rnd::DRndP()
  {
  return DRnd();
  }  










double Rnd::DRnd(double a, double b)
  {
  return (a + (b - a) * DRnd());
  }  


















double *Rnd::DRndPtr()
  {
  Assert(0.0 <= dvalue && dvalue < 1.0);
  return &dvalue;
  }









void Rnd::ReNorm(double &prob, double pp, double pp_prev)
  {
  }







int Rnd::IRnd(int n)
  {
  Assert(n > 0);

  
  int nx = (int)(n * DRnd());
  Assert(nx < n);
  return (nx == n) ? 0 : nx;
  } 

























Point2d Rnd::SphrUnif(const double phi[2], const double cos_theta[2])
  {
  Point2d p;
  p[0] = phi[0] + (phi[1] - phi[0]) * DRnd(); 
  p[1] = cos_theta[0] + (cos_theta[1] - cos_theta[0]) * DRnd(); 
  p[1] = ACos(p[1]);
  return p;
  } 


































Point2d Rnd::SphrBiLin(const double phi[2], const double theta[2],
                       const double cos_theta[2], const double f[2][2])
  {
  double fmax = Max(f[0][0], Max3(f[0][1], f[1][0], f[1][1]));
  Assert(fmax > 0);

  double sp = 1 / (phi[1]   - phi[0]);
  double st = 1 / (theta[1] - theta[0]);

  
  
  Point2d p;
  for ( ; ; ) 
    {
    p = SphrUnif(phi, cos_theta); 
    if (fmax <= 0)
      return p;

    
    double cp = sp * (p[0] - phi[0]);
    double ct = st * (p[1] - theta[0]);
    double fp = (1 - cp) * ((1 - ct) * f[0][0] + ct * f[0][1])
                + cp  * ((1 - ct) * f[1][0] + ct * f[1][1]);

    
    
    if (fp >= fmax * DRnd())
      break;
    }
  return p;
  } 




























double Rnd::SphrLin(const double theta[2],
                    const double cos_theta[2], const double f[2])
  {
  double fmax = Max(f[0], f[1]);
  double st = 1 / (theta[1] - theta[0]);

  Assert(fmax > 0);

  
  
  double t;
  for ( ; ; ) 
    {
    
    t = cos_theta[0] + (cos_theta[1] - cos_theta[0]) * DRnd(); 
    t = ACos(t); 

    
    double ct = st * (t - theta[0]);
    double fp = (1 - ct) * f[0] + ct * f[1];

    
    
    if (fp >= fmax * DRnd())
      break;
    }
  return t;
  } 








bool Rnd::operator == (const Rnd &u) const
  {
  return (dvalue == u.dvalue) && (m1 == u.m1) && (m2 == u.m2) && (m3 == u.m3) &&
         (gauss_prev == u.gauss_prev) && (has_gauss_prev == u.has_gauss_prev);
  }








bool Rnd::operator != (const Rnd &u) const
  {
  return (dvalue != u.dvalue) || (m1 != u.m1) || (m2 != u.m2) || (m3 != u.m3) ||
         (gauss_prev != u.gauss_prev) || (has_gauss_prev != u.has_gauss_prev);
  }

KIAM_NAMESPACE_END
#endif 

