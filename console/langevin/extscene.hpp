#ifndef _EXTSCENE_HPP_INCLUDED
#define _EXTSCENE_HPP_INCLUDED

#include "scene.hpp"



class ExtScene : public Scene
  {
  public:
    
    struct BasePathDataSpecDir
      {
      
      Vect3d v1;
      
      Vect2d omega1;
      };

  public:
    
    OKAY GeneratePath(OUT BasePathDataSpecDir &bpd, INOUT Rnd &rng) const;

    
    OKAY CalcDistr(const int nrays, OUT TMatrix<double> &hist, INOUT double &tol, INOUT Rnd &rng) const;

    OKAY CalcMapping(const Vect3d &v3, OUT Vect3d &v1) const;

  protected:
    
    OKAY CalcDistr(const int nrays, const Vect3d &v3, OUT double &avr, OUT double &avr_sqr, INOUT Rnd &rng) const;
  };

#endif