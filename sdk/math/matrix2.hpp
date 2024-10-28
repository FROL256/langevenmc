










#ifndef _KLBC_MATRIX2_HPP_
#define _KLBC_MATRIX2_HPP_

#include <base/base.hpp>

#include "vect2.hpp"

KIAM_NAMESPACE_START


template <class T>
class TMatrix2
  {
  public:
    
    
    
    inline TMatrix2();
    
    inline TMatrix2(const double a);
    
    inline TMatrix2(const double a, const double b);
    
    inline TMatrix2(double a00, double a01, double a10, double a11);
    
    inline TMatrix2(const TVect2<T> &x, const TVect2<T> &y);
    
    inline TMatrix2(const TMatrix2<T> &mat);
    

    
    
    
    inline bool operator == (const TMatrix2<T> &u) const;
    
    inline bool operator != (const TMatrix2<T> &u) const;
    

    
    
    
    inline static bool AboutZero(const TMatrix2<T> &u, const double tolerance);
    
    inline static bool AboutZero(const TMatrix2<T> &u);
    
    inline static bool AboutEqual(const TMatrix2<T> &a, const TMatrix2<T> &b, const double tolerance);
    
    inline static bool AboutEqual(const TMatrix2<T> &a, const TMatrix2<T> &b);
    

    
    
    
    inline TVect2<T> & operator [] (int i);
    
    inline const TVect2<T> &operator [] (int i) const;
    

    
    
    
    inline TMatrix2<T> operator + (const TMatrix2<T> &v) const;
    
    inline TMatrix2<T> operator - (const TMatrix2<T> &v) const;
    
    inline TMatrix2<T> operator * (const double d) const;
    
    inline TVect2<T> operator * (const TVect2<T> &u) const;
    
    TMatrix2<T> operator * (const TMatrix2<T> &v) const;
    
    inline TMatrix2<T> operator / (const double d) const;
    

    
    
    
    inline TMatrix2<T> & operator = (const TMatrix2<T> &u);
    
    inline TMatrix2<T> & operator += (const TMatrix2<T> &u);
    
    inline TMatrix2<T> & operator -= (const TMatrix2<T> &u);
    
    inline TMatrix2<T> & operator *= (const double d);
    
    inline TMatrix2<T> & operator *= (const TMatrix2<T> &u);
    
    inline TMatrix2<T> & operator /= (const double d);
    

    
    
    
    inline void SetCol(int j, const TVect2<T> &u);
    
    inline TVect2<T> GetCol(int j) const;
    
    inline double Det() const;
    
    inline TMatrix2<T> Inversed() const;
    
    TMatrix2<T> Transposed() const;
    
    inline void Transpose();
    

    
    
    
    
    Vect2d Normalize();
    
    TMatrix2<T> &Rotation(double angle);
    

    
    
    
    static const TMatrix2<T> &E();
    

  public:
    
    

    
    TVect2<T> r0,
    
              r1;
  };






typedef TMatrix2<float>  Matrix2f;

typedef TMatrix2<double> Matrix2d;




template <class T>
TMatrix2<T>::TMatrix2()
  {
  }








template <class T>
TMatrix2<T>::TMatrix2(const double a)
  {
  r0[0] = r1[1] = (T)a;
  r0[1] = r1[0] = 0;
  }










template <class T>
TMatrix2<T>::TMatrix2(const double a, const double b)
  {
  r0[0] = (T)a;
  r1[1] = (T)b;
  r0[1] = r1[0] = 0.0;
  }








template <class T>
TMatrix2<T>::TMatrix2(double a00, double a01, double a10, double a11)
  {
  r0[0] = (T)a00;
  r0[1] = (T)a01;
  r1[0] = (T)a10;
  r1[1] = (T)a11;
  }









template <class T>
TMatrix2<T>::TMatrix2(const TVect2<T> &x, const TVect2<T> &y)
  {
  r0 = x;
  r1 = y;
  }






template <class T>
TMatrix2<T>::TMatrix2(const TMatrix2<T> &mat)
  {
  r0 = mat.r0;
  r1 = mat.r1;
  }











template <class T>
bool TMatrix2<T>::operator == (const TMatrix2<T> &u) const
  {
  return (r0 == u.r0) && (r1 == u.r1);
  }












template <class T>
bool TMatrix2<T>::operator != (const TMatrix2<T> &u) const
  {
  return (r0 != u.r0) || (r1 != u.r1);
  }









template <class T>
bool TMatrix2<T>::AboutZero(const TMatrix2<T> &u, const double tolerance)
  {
  return (Math2<T>::AboutZero(u[0], tolerance) &&
          Math2<T>::AboutZero(u[1], tolerance));
  }









template <class T>
bool TMatrix2<T>::AboutZero(const TMatrix2<T> &u)
  {
  return AboutZero(u, Math<T>::TOLERANCE);
  }















template <class T>
bool TMatrix2<T>::AboutEqual(const TMatrix2<T> &a, const TMatrix2<T> &b,
                              const double tolerance)
  {
  return AboutZero(a - b, tolerance);
  }













template <class T>
bool TMatrix2<T>::AboutEqual(const TMatrix2<T> &a,
                             const TMatrix2<T> &b)
  {
  return AboutZero(a - b, Math<T>::TOLERANCE);
  }









template <class T>
TVect2<T> & TMatrix2<T>::operator [] (int i)
  {
  Assert(i >= 0 && i < 2);;
  return ((TVect2<T> *)&r0)[i];
  }









template <class T>
const TVect2<T> &TMatrix2<T>::operator [] (int i) const
  {
  Assert(i >= 0 && i < 2);;
  return ((const TVect2<T> *)&r0)[i];
  }












template <class T>
void TMatrix2<T>::SetCol(int j, const TVect2<T> &u)
  {
  Assert(j >= 0 && j < 2);
  r0[j] = u[0];
  r1[j] = u[1];
  }











template <class T>
TVect2<T> TMatrix2<T>::GetCol(int j) const
  {
  Assert(j >= 0 && j < 2);
  TVect2<T> u;
  u[0] = r0[j];
  u[1] = r1[j];
  return u;
  }











template <class T>
TMatrix2<T> TMatrix2<T>::operator + (const TMatrix2<T> &v) const
  {
  TMatrix2<T> res;
  res.r0 = r0 + v.r0;
  res.r1 = r1 + v.r1;
  return res;
  }











template <class T>
TMatrix2<T> TMatrix2<T>::operator - (const TMatrix2<T> &v) const
  {
  TMatrix2<T> res;
  res.r0 = r0 - v.r0;
  res.r1 = r1 - v.r1;
  return res;
  }










template <class T>
TMatrix2<T> TMatrix2<T>::operator * (const double d) const
  {
  TMatrix2<T> res;
  res.r0 = r0 * d;
  res.r1 = r1 * d;
  return res;
  }











template <class T>
TVect2<T> TMatrix2<T>::operator * (const TVect2<T> &u) const
  {
  TVect2<T> res;
  res[0] = (T)DotProd(r0, u);
  res[1] = (T)DotProd(r1, u);
  return res;
  }












template <class T>
TMatrix2<T> TMatrix2<T>::operator / (const double d) const
  {
  TMatrix2<T> res;
  Assert(d != 0);
  res.r0 = r0 / d;
  res.r1 = r1 / d;
  return res;
  }









template <class T>
TMatrix2<T> &TMatrix2<T>::operator = (const TMatrix2<T> &u)
  {
  r0 = u.r0;
  r1 = u.r1;
  return *this;
  }










template <class T>
TMatrix2<T> &TMatrix2<T>::operator += (const TMatrix2<T> &u)
  {
  r0 += u.r0;
  r1 += u.r1;
  return *this;
  }










template <class T>
TMatrix2<T> &TMatrix2<T>::operator -= (const TMatrix2<T> &u)
  {
  r0 -= u.r0;
  r1 -= u.r1;
  return *this;
  }










template <class T>
TMatrix2<T> &TMatrix2<T>::operator *= (const double d)
  {
  r0 *= d;
  r1 *= d;
  return *this;
  }













template <class T>
TMatrix2<T> &TMatrix2<T>::operator *= (const TMatrix2<T> &u)
  {
  *this = (*this) * u;
  return *this;
  }












template <class T>
TMatrix2<T> &TMatrix2<T>::operator /= (const double d)
  {
  Assert(d != 0);
  r0 /= d;
  r1 /= d;
  return *this;
  }





template <class T>
double TMatrix2<T>::Det() const
  {
  return r0[0] * r1[1] - r0[1] * r1[0];
  }











template <class T>
TMatrix2<T> TMatrix2<T>::Inversed() const
  {
  double det = Det();
  Assert(det != 0);
  TMatrix2<T> res;
  const double rdet = 1 / det;
  res[0][0] =  (T)(r1[1] * rdet);
  res[1][0] = (T)(-r1[0] * rdet);
  res[0][1] = (T)(-r0[1] * rdet);
  res[1][1] =  (T)(r0[0] * rdet);
  return res;
  }










template <class T>
void TMatrix2<T>::Transpose()
  {
  Swap(r0[1], r1[0]);
  }















template <class T>
inline TMatrix2<T> operator * (const double d, const TMatrix2<T> &u)
  {
  return u * d;
  }












template <class T>
inline TVect2<T> operator * (const TVect2<T> &u, const TMatrix2<T> &a)
  {
  TVect2<T> res;
  res[0] = u[0] * a[0][0] + u[1] * a[1][0];
  res[1] = u[0] * a[0][1] + u[1] * a[1][1];
  return res;
  }












template <class T>
inline TPoint2<T> operator * (const TPoint2<T> &u, const TMatrix2<T> &a)
  {
  TPoint2<T> res;
  res[0] = u[0] * a[0][0] + u[1] * a[1][0];
  res[1] = u[0] * a[0][1] + u[1] * a[1][1];
  return res;
  }








template <class T>
inline TMatrix2<float> ConvF(const TMatrix2<T> &v)
  {
  TMatrix2<float> res;

  
  res[0] = ConvF(v[0]);
  res[1] = ConvF(v[1]);

  return res;
  }








template <class T>
inline TMatrix2<double> ConvD(const TMatrix2<T> &v)
  {
  TMatrix2<double> res;

  
  res[0] = ConvD(v[0]);
  res[1] = ConvD(v[1]);

  return res;
  }

KIAM_NAMESPACE_END

#endif 
