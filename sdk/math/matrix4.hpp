









#ifndef _ELGO_MATRIX4_HPP_
#define _ELGO_MATRIX4_HPP_

#include "matrix43.hpp"
#include "vect4.hpp"

KIAM_NAMESPACE_START






template <class T>
class TMatrix4
  {
  public:
    
    
    
    inline TMatrix4();
    
    inline TMatrix4(const double a);
    
    inline TMatrix4(const double a, const double b,
                    const double c, const double d);
    
    inline TMatrix4(const TVect4<T> &x, const TVect4<T> &y,
                    const TVect4<T> &z, const TVect4<T> &w);
    
    inline TMatrix4(const TMatrix4<T> &mat);
    
    explicit inline TMatrix4(const TMatrix43<T> &mat);
    
    explicit inline TMatrix4(const TMatrix3<T> &mat);
    

    
    
    
    inline TVect4<T> & operator [] (int i);
    
    inline const TVect4<T> &operator [] (int i) const;
    
    
    inline void SetCol(int j, const TVect4<T> &u);
    
    inline TVect4<T> GetCol(int j) const;
    

    
    
    
    inline bool operator == (const TMatrix4<T> &u) const;
    
    inline bool operator != (const TMatrix4<T> &u) const;
    

    
    
    
    inline TMatrix4<T> operator + (const TMatrix4<T> &v) const;
    
    inline TMatrix4<T> operator - (const TMatrix4<T> &v) const;
    
    inline TMatrix4<T> operator * (const double d) const;
    
    inline TVect4<T> operator * (const TVect4<T> &u) const;
    
    TMatrix4<T> operator * (const TMatrix4<T> &v) const;
    
    inline TMatrix4<T> operator / (const double d) const;
    

    
    
    
    inline TMatrix4<T> & operator = (const TMatrix4<T> &u);
    
    inline TMatrix4<T> & operator += (const TMatrix4<T> &u);
    
    inline TMatrix4<T> & operator -= (const TMatrix4<T> &u);
    
    TMatrix4<T> & operator *= (const TMatrix4<T> &u);
    
    inline TMatrix4<T> & operator *= (const double d);
    
    inline TMatrix4<T> & operator /= (const double d);
    

    
    
    
    inline static bool AboutZero(const TMatrix4<T> &u, const double tolerance);
    
    inline static bool AboutZero(const TMatrix4<T> &u);
    
    inline static bool AboutEqual(const TMatrix4<T> &a, const TMatrix4<T> &b,
                                  const double tolerance);
    
    inline static bool AboutEqual(const TMatrix4<T> &a,
                                  const TMatrix4<T> &b);
    

    
    
    
    inline TMatrix43<T> Matrix43() const;
    
    inline void Transpose();
    
    TMatrix4<T> Transposed() const;
    
    inline void Identity();
    
    
    Vect4d Normalize();
    
    inline TMatrix4<T> &Scale(const double a, const double b,
                              const double c, const double d);
    
    TMatrix4<T> Inversed() const;
    
    double Det() const;
    
    bool IsOK() const;
    

    
    
    
    
    void Perspective(double fovy, double aspect, double z_near, double z_far);
    
    
    void InfinitePerspective(double fovy, double aspect, double z_near);
    
    
    void Frustum(double left, double right, double bottom, double top,
                 double z_near, double z_far);
    
    void InfiniteFrustum(double left, double right, double bottom, double top,
                         double z_near);
    
    void Ortho(double left, double right, double bottom, double top,
               double z_near, double z_far);
    
    void InfiniteOrtho(double left, double right, double bottom, double top,
               double z_near, double z_far);
    

    
    
    
    TVect4<T> PointTransform(const TPoint3<T> &p) const;
    
    bool Includes(const TPoint3<T> &point) const;
    
    bool Visible(const BBox3<T> &bbox) const;
    

  public:
    

    
    TVect4<T> r0,
    
              r1,
    
              r2,
    
              r3;
  };






typedef TMatrix4<float>   Matrix4f;

typedef TMatrix4<double>  Matrix4d;




template <class T>
TMatrix4<T>::TMatrix4()
  {
  }









template <class T>
TMatrix4<T>::TMatrix4(const double a)
  {
  r0[0] = r1[1] = r2[2] = r3[3] = (T)a;
          r0[1] = r0[2] = r0[3] = 0.0;
  r1[0]         = r1[2] = r1[3] = 0.0;
  r2[0] = r2[1]         = r2[3] = 0.0;
  r3[0] = r3[1] = r3[2]         = 0.0;
  }













template <class T>
TMatrix4<T>::TMatrix4(const double a, const double b,
                      const double c, const double d)
  {
  r0[0] = (T)a;  r1[1] = (T)b;  r2[2] = (T)c;  r3[3] = (T)d;
          r0[1] = r0[2] = r0[3] = 0.0;
  r1[0]         = r1[2] = r1[3] = 0.0;
  r2[0] = r2[1]         = r2[3] = 0.0;
  r3[0] = r3[1] = r3[2]         = 0.0;
  }












template <class T>
TMatrix4<T>::TMatrix4(const TVect4<T> &x, const TVect4<T> &y,
                      const TVect4<T> &z, const TVect4<T> &w)
  {
  r0 = x;
  r1 = y;
  r2 = z;
  r3 = w;
  }






template <class T>
TMatrix4<T>::TMatrix4(const TMatrix4<T> &mat)
  {
  r0 = mat.r0;
  r1 = mat.r1;
  r2 = mat.r2;
  r3 = mat.r3;
  }










template <class T>
TMatrix4<T>::TMatrix4(const TMatrix43<T> &mat)
  {
  r0[0] = mat[0][0]; r0[1] = mat[0][1]; r0[2] = mat[0][2]; r0[3] = 0;
  r1[0] = mat[1][0]; r1[1] = mat[1][1]; r1[2] = mat[1][2]; r1[3] = 0;
  r2[0] = mat[2][0]; r2[1] = mat[2][1]; r2[2] = mat[2][2]; r2[3] = 0;
  r3[0] = mat[3][0]; r3[1] = mat[3][1]; r3[2] = mat[3][2]; r3[3] = 1;
  }











template <class T>
TMatrix4<T>::TMatrix4(const TMatrix3<T> &mat)
  {
  r0[0] = mat[0][0]; r0[1] = mat[0][1]; r0[2] = mat[0][2]; r0[3] = 0;
  r1[0] = mat[1][0]; r1[1] = mat[1][1]; r1[2] = mat[1][2]; r1[3] = 0;
  r2[0] = mat[2][0]; r2[1] = mat[2][1]; r2[2] = mat[2][2]; r2[3] = 0;
  r3[0] = 0;         r3[1] = 0;         r3[2] = 0;         r3[3] = 1;
  }









template <class T>
TVect4<T> &TMatrix4<T>::operator [] (int i)
  {
  Assert(i >= 0 && i < 4);;
  return (&r0)[i];
  }









template <class T>
const TVect4<T> &TMatrix4<T>::operator [] (int i) const
  {
  Assert(i >= 0 && i < 4);
  return (&r0)[i];
  }













template <class T>
void TMatrix4<T>::SetCol(int j, const TVect4<T> &u)
  {
  Assert(j >= 0 && j < 4);
  r0[j] = u[0];
  r1[j] = u[1];
  r2[j] = u[2];
  r3[j] = u[3];
  }











template <class T>
TVect4<T> TMatrix4<T>::GetCol(int j) const
  {
  Assert(j >= 0 && j < 4);
  TVect4<T> u;
  u[0] = r0[j];
  u[1] = r1[j];
  u[2] = r2[j];
  u[3] = r3[j];
  return u;
  }











template <class T>
bool TMatrix4<T>::operator == (const TMatrix4<T> &u) const
  {
  return (r0 == u.r0) && (r1 == u.r1) && (r2 == u.r2) && (r3 == u.r3);
  }












template <class T>
bool TMatrix4<T>::operator != (const TMatrix4<T> &u) const
  {
  return (r0 != u.r0) || (r1 != u.r1) || (r2 != u.r2) || (r3 != u.r3);
  }









template <class T>
bool TMatrix4<T>::AboutZero(const TMatrix4<T> &u, const double tolerance)
  {
  return (Math4<T>::AboutZero(u[0], tolerance) &&
          Math4<T>::AboutZero(u[1], tolerance) &&
          Math4<T>::AboutZero(u[2], tolerance) &&
          Math4<T>::AboutZero(u[3], tolerance));
  }









template <class T>
bool TMatrix4<T>::AboutZero(const TMatrix4<T> &u)
  {
  return AboutZero(u, Math<T>::TOLERANCE);
  }















template <class T>
bool TMatrix4<T>::AboutEqual(const TMatrix4<T> &a, const TMatrix4<T> &b,
                              const double tolerance)
  {
  return AboutZero(a - b, tolerance);
  }














template <class T>
bool TMatrix4<T>::AboutEqual(const TMatrix4<T> &a,
                             const TMatrix4<T> &b)
  {
  return AboutZero(a - b, Math<T>::TOLERANCE);
  }











template <class T>
TMatrix4<T> TMatrix4<T>::operator + (const TMatrix4<T> &v) const
  {
  TMatrix4<T> res;
  res.r0 = r0 + v.r0;
  res.r1 = r1 + v.r1;
  res.r2 = r2 + v.r2;
  res.r3 = r3 + v.r3;
  return res;
  }











template <class T>
TMatrix4<T> TMatrix4<T>::operator - (const TMatrix4<T> &v) const
  {
  TMatrix4<T> res;
  res.r0 = r0 - v.r0;
  res.r1 = r1 - v.r1;
  res.r2 = r2 - v.r2;
  res.r3 = r3 - v.r3;
  return res;
  }










template <class T>
TMatrix4<T> TMatrix4<T>::operator * (const double d) const
  {
  TMatrix4<T> res;
  res.r0 = r0 * d;
  res.r1 = r1 * d;
  res.r2 = r2 * d;
  res.r3 = r3 * d;
  return res;
  }











template <class T>
TVect4<T> TMatrix4<T>::operator * (const TVect4<T> &u) const
  {
  TVect4<T> res;
  res.x = (T)DotProd4(r0, u);
  res.y = (T)DotProd4(r1, u);
  res.z = (T)DotProd4(r2, u);
  res.w = (T)DotProd4(r3, u);
  return res;
  }












template <class T>
TMatrix4<T> TMatrix4<T>::operator / (const double d) const
  {
  TMatrix4<T> res;
  Assert(d != 0);
  res.r0 = r0 / d;
  res.r1 = r1 / d;
  res.r2 = r2 / d;
  res.r3 = r3 / d;
  return res;
  }









template <class T>
TMatrix4<T> & TMatrix4<T>::operator = (const TMatrix4<T> &u)
  {
  r0 = u.r0;
  r1 = u.r1;
  r2 = u.r2;
  r3 = u.r3;
  return *this;
  }










template <class T>
TMatrix4<T> &TMatrix4<T>::operator += (const TMatrix4<T> &u)
  {
  r0 += u.r0;
  r1 += u.r1;
  r2 += u.r2;
  r3 += u.r3;
  return *this;
  }










template <class T>
TMatrix4<T> &TMatrix4<T>::operator -= (const TMatrix4<T> &u)
  {
  r0 -= u.r0;
  r1 -= u.r1;
  r2 -= u.r2;
  r3 -= u.r3;
  return *this;
  }













template <class T>
TMatrix4<T> &TMatrix4<T>::operator *= (const TMatrix4<T> &u)
  {
  *this = (*this) * u;
  return *this;
  }










template <class T>
TMatrix4<T> &TMatrix4<T>::operator *= (const double d)
  {
  r0 *= d;
  r1 *= d;
  r2 *= d;
  r3 *= d;
  return *this;
  }












template <class T>
TMatrix4<T> &TMatrix4<T>::operator /= (const double d)
  {
  Assert(d != 0);
  r0 /= d;
  r1 /= d;
  r2 /= d;
  r3 /= d;
  return *this;
  }










template <class T>
void TMatrix4<T>::Transpose()
  {
  Swap(r0[1], r1[0]);
  Swap(r0[2], r2[0]);
  Swap(r1[2], r2[1]);

  Swap(r0[3], r3[0]);
  Swap(r1[3], r3[1]);
  Swap(r2[3], r3[2]);
  }









template <class T>
void TMatrix4<T>::Identity()
  {
  r0[0] = r1[1] = r2[2] = r3[3] = 1;
          r0[1] = r0[2] = r0[3] = 0.0;
  r1[0]         = r1[2] = r1[3] = 0.0;
  r2[0] = r2[1]         = r2[3] = 0.0;
  r3[0] = r3[1] = r3[2]         = 0.0;
  }















template <class T>
TMatrix4<T> &TMatrix4<T>::Scale(const double a, const double b,
                             const double c, const double d)
  {
  r0[0] = (T)a;  r1[1] = (T)b;  r2[2] = (T)c;  r3[3] = (T)d;
          r0[1] = r0[2] = r0[3] = 0.0;
  r1[0]         = r1[2] = r1[3] = 0.0;
  r2[0] = r2[1] =         r2[3] = 0.0;
  r3[0] = r3[1] = r3[2]         = 0.0;
  return *this;
  }







template <class T>
inline TMatrix43<T> TMatrix4<T>::Matrix43() const
  {
  TMatrix43<T> m;

  m[0][0] = r0.x; m[0][1] = r0.y; m[0][2] = r0.z;
  m[1][0] = r1.x; m[1][1] = r1.y; m[1][2] = r1.z;
  m[2][0] = r2.x; m[2][1] = r2.y; m[2][2] = r2.z;
  m[3][0] = r3.x; m[3][1] = r3.y; m[3][2] = r3.z;

  return m;
  }















template <class T>
TMatrix4<T> operator * (const double d, const TMatrix4<T> &u)
  {
  return u * d;
  }












template <class T>
TVect4<T> operator * (const TVect4<T> &u, const TMatrix4<T> &a)
  {
  TVect4<T> res;
  res.x = u.x * a.r0.x + u.y * a.r1.x + u.z * a.r2.x + u.w * a.r3.x;
  res.y = u.x * a.r0.y + u.y * a.r1.y + u.z * a.r2.y + u.w * a.r3.y;
  res.z = u.x * a.r0.z + u.y * a.r1.z + u.z * a.r2.z + u.w * a.r3.z;
  res.w = u.x * a.r0.w + u.y * a.r1.w + u.z * a.r2.w + u.w * a.r3.w;
  return res;
  }








template <class T>
TMatrix4<float> ConvF(const TMatrix4<T> &v)
  {
  return TMatrix4<float>(ConvF(v[0]), ConvF(v[1]), ConvF(v[2]));
  }








template <class T>
TMatrix4<double> ConvD(const TMatrix4<T> &v)
  {
  return TMatrix4<double>(ConvD(v[0]), ConvD(v[1]), ConvD(v[2]));
  }

KIAM_NAMESPACE_END
#endif 

