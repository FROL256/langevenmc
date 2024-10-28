










#ifndef _KLBC_MATRIX3_HPP_
#define _KLBC_MATRIX3_HPP_

#include "vect3.hpp"

KIAM_NAMESPACE_START


template <class T>
class TMatrix3
  {
  public:
    
    
    
    inline TMatrix3();
    
    inline TMatrix3(const double a);
    
    inline TMatrix3(const double a, const double b, const double c);
    
    inline TMatrix3(const TVect3<T> &x, const TVect3<T> &y, const TVect3<T> &z);
    
    inline TMatrix3(const TMatrix3<T> &mat);
    

    
    
    
    inline static const TMatrix3<T> &Cast(const T *u);
    
    inline static TMatrix3<T> &Cast(T *u);
    

    
    
    
    inline TVect3<T> &operator [] (int i);
    
    inline const TVect3<T> &operator [] (int i) const;
    

    
    
    
    inline bool operator == (const TMatrix3<T> &u) const;
    
    inline bool operator != (const TMatrix3<T> &u) const;
    
    inline bool operator < (const TMatrix3<T> &u) const;
    
    inline T MaxElement() const;
    
    inline bool IsIdentity() const;
    

    
    
    
    inline static bool AboutZero(const TMatrix3<T> &u, const double tolerance);
    
    inline static bool AboutZero(const TMatrix3<T> &u);
    
    inline static bool AboutEqual(const TMatrix3<T> &a, const TMatrix3<T> &b,
                                  const double tolerance);
    
    inline static bool AboutEqual(const TMatrix3<T> &a,
                                  const TMatrix3<T> &b);
    
    inline static bool AboutIdentity(const TMatrix3<T> &a,
                                     const double tolerance);
    
    
    inline static bool AboutIdentity(const TMatrix3<T> &a);
    
    
    inline bool AboutIdentity() const;
    

    
    
    
    inline TMatrix3<T> operator + (const TMatrix3<T> &v) const;
    
    inline TMatrix3<T> operator - (const TMatrix3<T> &v) const;
    
    inline TMatrix3<T> operator * (const double d) const;
    
    inline TVect3<T> operator * (const TVect3<T> &u) const;
    
    TMatrix3<T> operator * (const TMatrix3<T> &v) const;
    
    inline TMatrix3<T> operator / (const double d) const;
    

    
    
    
    inline TPoint3<T> &Rotate(TPoint3<T> &p) const;
    
    inline TVect3<T> &Rotate(TVect3<T> &u) const;
    
    inline TVect3<T> Rotated(const TVect3<T> &u) const;
    
    inline TVect3<T> VectorScaled(const TVect3<T> &u) const;
    
    inline TPoint3<T> Rotated(const TPoint3<T> &p) const;
    
    inline TVect3<T> BackRotated(const TVect3<T> &u) const;
    
    inline TPoint3<T> BackRotated(const TPoint3<T> &p) const;
    

    
    
    
    inline TMatrix3<T> & operator = (const TMatrix3<T> &u);
    
    inline TMatrix3<T> & operator += (const TMatrix3<T> &u);
    
    inline TMatrix3<T> & operator -= (const TMatrix3<T> &u);
    
    inline TMatrix3<T> & operator *= (const TMatrix3<T> &u);
    
    inline TMatrix3<T> & operator *= (const double d);
    
    inline TMatrix3<T> & operator /= (const double d);
    

    
    
    
    Vect3d GetScale() const;
    
    void SetScale(const Vect3d &scale);
    

    
    
    
    
    inline void SetCol(int j, const TVect3<T> &u);
    
    inline TVect3<T> GetCol(int j) const;
    
    double Minor(int i, int j) const;
    
    double Det() const;
    
    TMatrix3<T> Inversed() const;
    
    TMatrix3<T> Transposed() const;
    
    inline void Transpose();
    

    
    
    
    
    static TMatrix3<T> LeftTransposeMultiply(const TMatrix3<T> &u, const TMatrix3<T> &v);
    
    
    static TMatrix3<T> RightTransposeMultiply(const TMatrix3<T> &u, const TMatrix3<T> &v);
    

    
    
    
    
    
    
    inline void Identity();
    
    
    Vect3d Normalize();
    
    TMatrix3<T> &RotationX(double angle);
    
    TMatrix3<T> &RotationY(double angle);
    
    TMatrix3<T> &RotationZ(double angle);
    
    TMatrix3<T> &RotationXYZ(const Vect3d &angles);
    
    
    void RotationToXYZAngles(Vect3d &angles) const;

#if 0  
    
    TMatrix3<T> &RotationZYX(const Vect3d &angles);
    
    
    void RotationToZYXAngles(Vect3d &angles) const;
    
    
    void MatrixToZYXAnglesScale(Vect3d &angles, Vect3d &scale) const;
#endif

    
    TMatrix3<T> &RotationAxis(const TVect3<T> &u, double angle);
    
    void RotAngAxis(Vect3d &axis, double &angle) const;
    
    TMatrix3<T> &GenRotation(const TVect3<T> &u, const TVect3<T> &v,
                             const TVect3<T> &w);
    
    TMatrix3<T> &EulerRotation(double alpha, double beta, double gamma);
    
    void RotationToEuler(double &alpha, double &beta, double &gamma) const;
    
    
    TMatrix3<T> &EulerRotationForCamera(double alpha, double beta, double gamma);
    
    
    void RotationToEulerForCamera(double &alpha, double &beta, double &gamma) const;
    
    
    TMatrix3<T> &EulerRotationForLight(double alpha, double beta, double gamma);
    
    
    void RotationToEulerForLight(double &alpha, double &beta, double &gamma) const;
    
    TMatrix3<T> &DirTwistRotation(const TVect3<T> &s_dir, const TVect3<T> &d_dir,
                                  const TVect3<T> &s_up, const TVect3<T> &d_up,
                                  const TVect3<T> &add_r_nm, const double &twist);
    void RotationToDirTwist(const TVect3<T> &s_dir, TVect3<T> &d_dir,  
                            const TVect3<T> &s_up, const TVect3<T> &d_up,
                            const TVect3<T> &add_r_nm, double &twist) const;
    
    TMatrix3<T> &Rotation(const TVect3<T> &source, const TVect3<T> &target);
    
    TMatrix3<T> &Rotation(const TVect3<T> &source, const TVect3<T> &target,
                          const TVect3<T> &def_rot_dir);
    
    inline TMatrix3<T> &Scale(const double x, const double y, const double z);
    


    
    
    
    static const TMatrix3<T> &E();
    
    static const TVect3<T> DefCamTwistDir();
    

  private:
    
    TMatrix3<T> &RotationAxis(const TVect3<T> &u,
                              double cos_ang, double sin_ang);

  public:
    
    
    
    TVect3<T> r0,
    
              r1,
    
              r2;
    
  };






typedef TMatrix3<float>   Matrix3f;

typedef TMatrix3<double>  Matrix3d;








template <class T>
TMatrix3<T>::TMatrix3()
  {
  }








template <class T>
TMatrix3<T>::TMatrix3(const double a)
  {
  r0[0] = r1[1] = r2[2] = (T)a;
  r0[1] = r0[2] = r1[0] = r1[2] = r2[0] = r2[1] = 0.0;
  }











template <class T>
TMatrix3<T>::TMatrix3(const double a, const double b, const double c)
  {
  r0[0] = (T)a;
  r1[1] = (T)b;
  r2[2] = (T)c;
  r0[1] = r0[2] = r1[0] = r1[2] = r2[0] = r2[1] = 0.0;
  }








template <class T>
TMatrix3<T>::TMatrix3(const TVect3<T> &x, const TVect3<T> &y, const TVect3<T> &z)
  {
  r0 = x;
  r1 = y;
  r2 = z;
  }









template <class T>
const TMatrix3<T> &TMatrix3<T>::Cast(const T *u)
  {
  return *(const TMatrix3<T> *)u;
  }









template <class T>
TMatrix3<T> &TMatrix3<T>::Cast(T *u)
  {
  return *(TMatrix3<T> *)u;
  }






template <class T>
TMatrix3<T>::TMatrix3(const TMatrix3<T> &mat)
  {
  r0 = mat.r0;
  r1 = mat.r1;
  r2 = mat.r2;
  }









template <class T>
TVect3<T> &TMatrix3<T>::operator [] (int i)
  {
  Assert(i >= 0 && i < 3);;
  return (&r0)[i];
  }









template <class T>
const TVect3<T> &TMatrix3<T>::operator [] (int i) const
  {
  Assert(i >= 0 && i < 3);;
  return (&r0)[i];
  }












template <class T>
void TMatrix3<T>::SetCol(int j, const TVect3<T> &u)
  {
  Assert(j >= 0 && j < 3);
  r0[j] = u[0];
  r1[j] = u[1];
  r2[j] = u[2];
  }











template <class T>
TVect3<T> TMatrix3<T>::GetCol(int j) const
  {
  Assert(j >= 0 && j < 3);
  TVect3<T> u;
  u[0] = r0[j];
  u[1] = r1[j];
  u[2] = r2[j];
  return u;
  }











template <class T>
bool TMatrix3<T>::operator == (const TMatrix3<T> &u) const
  {
  return (r0 == u.r0) && (r1 == u.r1) && (r2 == u.r2);
  }












template <class T>
bool TMatrix3<T>::operator != (const TMatrix3<T> &u) const
  {
  return (r0 != u.r0) || (r1 != u.r1) || (r2 != u.r2);
  }













template <class T>
bool TMatrix3<T>::operator < (const TMatrix3<T> &u) const
  {
  if (r0 < u.r0)
    return true;
  if (u.r0 < r0)
    return false;
  if (r1 < u.r1)
    return true;
  if (u.r1 < r1)
    return false;
  return r2 < u.r2;
  }





template <class T>
T TMatrix3<T>::MaxElement() const
  {
  return Max3(r0.MaxElement(), r1.MaxElement(), r2.MaxElement());
  }






template <class T>
bool TMatrix3<T>::IsIdentity() const
  {
  return (*this == E());
  }









template <class T>
bool TMatrix3<T>::AboutZero(const TMatrix3<T> &u, const double tolerance)
  {
  return (Math3<T>::AboutZero(u[0], tolerance) &&
          Math3<T>::AboutZero(u[1], tolerance) &&
          Math3<T>::AboutZero(u[2], tolerance));
  }









template <class T>
bool TMatrix3<T>::AboutZero(const TMatrix3<T> &u)
  {
  return AboutZero(u, Math<T>::TOLERANCE);
  }















template <class T>
bool TMatrix3<T>::AboutEqual(const TMatrix3<T> &a, const TMatrix3<T> &b,
                              const double tolerance)
  {
  return AboutZero(a - b, tolerance);
  }














template <class T>
bool TMatrix3<T>::AboutEqual(const TMatrix3<T> &a,
                             const TMatrix3<T> &b)
  {
  return AboutZero(a - b, Math<T>::TOLERANCE);
  }














template <class T>
bool TMatrix3<T>::AboutIdentity(const TMatrix3<T> &a,
                                 const double tolerance)
  {
  return AboutZero(a - E(), tolerance);
  }














template <class T>
bool TMatrix3<T>::AboutIdentity(const TMatrix3<T> &a)
  {
  return AboutIdentity(a, Math<T>::TOLERANCE);
  }














template <class T>
bool TMatrix3<T>::AboutIdentity() const
  {
  return AboutIdentity(*this, Math<T>::TOLERANCE);
  }











template <class T>
TMatrix3<T> TMatrix3<T>::operator + (const TMatrix3<T> &v) const
  {
  TMatrix3<T> res;
  res.r0 = r0 + v.r0;
  res.r1 = r1 + v.r1;
  res.r2 = r2 + v.r2;
  return res;
  }











template <class T>
TMatrix3<T> TMatrix3<T>::operator - (const TMatrix3<T> &v) const
  {
  TMatrix3<T> res;
  res.r0 = r0 - v.r0;
  res.r1 = r1 - v.r1;
  res.r2 = r2 - v.r2;
  return res;
  }










template <class T>
TMatrix3<T> TMatrix3<T>::operator * (const double d) const
  {
  TMatrix3<T> res;
  res.r0 = r0 * d;
  res.r1 = r1 * d;
  res.r2 = r2 * d;
  return res;
  }













template <class T>
TVect3<T> TMatrix3<T>::operator * (const TVect3<T> &u) const
  {
  TVect3<T> res;
  res.x = (T)DotProd(r0, u);
  res.y = (T)DotProd(r1, u);
  res.z = (T)DotProd(r2, u);
  return res;
  }












template <class T>
TMatrix3<T> TMatrix3<T>::operator / (const double d) const
  {
  TMatrix3<T> res;
  Assert(d != 0);
  res.r0 = r0 / d;
  res.r1 = r1 / d;
  res.r2 = r2 / d;
  return res;
  }
















template <class T>
TPoint3<T> &TMatrix3<T>::Rotate(TPoint3<T> &p) const
  {
  p.Vector() = p.Vector() * (*this);
  return p;
  }
















template <class T>
TVect3<T> &TMatrix3<T>::Rotate(TVect3<T> &u) const
  {
  u = u * (*this);
  return u;
  }















template <class T>
TVect3<T> TMatrix3<T>::Rotated(const TVect3<T> &u) const
  {
  return u * (*this);
  }










template <class T>
TVect3<T> TMatrix3<T>::VectorScaled(const TVect3<T> &u) const
  {
  return TVect3<T>(u.x * r0.x, u.y * r1.y, u.z * r2.z);
  }















template <class T>
TPoint3<T> TMatrix3<T>::Rotated(const TPoint3<T> &p) const
  {
  return (p.Vector() * (*this)).Point();
  }















template <class T>
TVect3<T> TMatrix3<T>::BackRotated(const TVect3<T> &u) const
  {
  return *this * u;
  }















template <class T>
TPoint3<T> TMatrix3<T>::BackRotated(const TPoint3<T> &p) const
  {
  return (*this * p.Vector()).Point();
  }









template <class T>
TMatrix3<T> &TMatrix3<T>::operator = (const TMatrix3<T> &u)
  {
  r0 = u.r0;
  r1 = u.r1;
  r2 = u.r2;
  return *this;
  }










template <class T>
TMatrix3<T> &TMatrix3<T>::operator += (const TMatrix3<T> &u)
  {
  r0 += u.r0;
  r1 += u.r1;
  r2 += u.r2;
  return *this;
  }










template <class T>
TMatrix3<T> &TMatrix3<T>::operator -= (const TMatrix3<T> &u)
  {
  r0 -= u.r0;
  r1 -= u.r1;
  r2 -= u.r2;
  return *this;
  }














template <class T>
TMatrix3<T> &TMatrix3<T>::operator *= (const TMatrix3<T> &u)
  {
  *this = (*this) * u;
  return *this;
  }










template <class T>
TMatrix3<T> &TMatrix3<T>::operator *= (const double d)
  {
  r0 *= d;
  r1 *= d;
  r2 *= d;
  return *this;
  }












template <class T>
TMatrix3<T> &TMatrix3<T>::operator /= (const double d)
  {
  Assert(d != 0);
  r0 /= d;
  r1 /= d;
  r2 /= d;
  return *this;
  }










template <class T>
void TMatrix3<T>::Transpose()
  {
  Swap(r0[1], r1[0]);
  Swap(r0[2], r2[0]);
  Swap(r1[2], r2[1]);
  }









template <class T>
void TMatrix3<T>::Identity()
  {
  r0[0] = r1[1] = r2[2] = 1;
  r0[1] = r0[2] = r1[0] = r1[2] = r2[0] = r2[1] = 0;
  }















template <class T>
TMatrix3<T> &TMatrix3<T>::Scale(const double x, const double y, const double z)
  {
  r0[0] = (T)x;
  r1[1] = (T)y;
  r2[2] = (T)z;
  r0[1] = r0[2] = r1[0] = r1[2] = r2[0] = r2[1] = 0;
  return *this;
  }











template <class T>
TMatrix3<T> operator * (const double d, const TMatrix3<T> &u)
  {
  return u * d;
  }













template <class T>
inline TVect3<T> operator * (const TVect3<T> &u, const TMatrix3<T> &a)
  {
  TVect3<T> res;
  res.x = u.x * a.r0.x + u.y * a.r1.x + u.z * a.r2.x;
  res.y = u.x * a.r0.y + u.y * a.r1.y + u.z * a.r2.y;
  res.z = u.x * a.r0.z + u.y * a.r1.z + u.z * a.r2.z;
  return res;
  }








template <class T>
TMatrix3<float> ConvF(const TMatrix3<T> &v)
  {
  return TMatrix3<float>(ConvF(v[0]), ConvF(v[1]), ConvF(v[2]));
  }








template <class T>
TMatrix3<double> ConvD(const TMatrix3<T> &v)
  {
  return TMatrix3<double>(ConvD(v[0]), ConvD(v[1]), ConvD(v[2]));
  }

KIAM_NAMESPACE_END

#endif 

