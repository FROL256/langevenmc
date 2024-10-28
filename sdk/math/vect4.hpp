








#ifndef _KLBC_VECT4_HPP_
#define _KLBC_VECT4_HPP_

#include "math.hpp"
#include "vect3.hpp"

KIAM_NAMESPACE_START


template <class T> class BVect4;
template <class T> class TMatrix4;



template <class T>
class BVect4
  {
  public:
    
    typedef T BaseType;

  public:
    
    T x,
    
      y,
    
      z,
    
      w;

  public:
    
    
    
    inline BVect4();
    
    inline BVect4(T a);
    
    inline BVect4(const BVect3<T> &v, T a);
    
    inline BVect4(const T &x0, const T &y0, const T &z0, const T &w0);
    
    inline BVect4(const BVect4<T> &u);
    

    
    
    
    
    inline T & operator [](int i);
    
    
    inline const T &operator [](int i) const;
    

    
    
    
    inline BVect4<T> & operator = (const BVect4<T> &u);
    

    
    
    
    inline bool operator == (const BVect4<T> &u) const;
    
    inline bool operator != (const BVect4<T> &u) const;
    

    
    
    
    inline operator T *();
    
    inline operator const T *() const;
    

    
    
    
    inline static const BVect4<T> &Cast(const T *u);
    
    inline static BVect4<T> &Cast(T *u);
    

    
    
    
    inline const BVect3<T> &GetVect3() const;
    
    inline void SetVect3(const BVect3<T> &v);
    

    
    inline T MaxElement() const;

    
    
    
    inline static int NComponents();
    
  };  



template <class T>
class TVect4
  {
  public:
    
    typedef T BaseType;

  public:
    
    T x,
    
      y,
    
      z,
    
      w;

  public:
    
    
    
    inline TVect4();
    
    inline TVect4(const double v);
    
    inline TVect4(const double x0, const double y0,
                  const double z0, const double w0 = 1);
    
    inline TVect4(const TPoint3<T> &from, const TPoint3<T> &to);
    
    inline TVect4(const TVect4<T> &u);
    
    inline TVect4(const TVect3<T> &u, T w0 = 1);
    

    
    
    
    
    inline T & operator [](int i);
    
    
    inline T   operator [](int i) const;
    

    
    
    
    inline bool operator == (const TVect4<T> &u) const;
    
    inline bool operator != (const TVect4<T> &u) const;
    
    inline bool LessOrEqual(const TVect4<T> &u) const;
    
    inline bool operator < (const TVect4<T> &u) const;
    

    
    
    
    inline TVect4<T> & operator = (const TVect4<T> &u);

    
    
    inline TVect4<T> & operator += (const TVect4<T> &u);
    
    inline TVect4<T> & operator -= (const TVect4<T> &u);
    
    inline TVect4<T> & operator *= (const TVect4<T> &u);
    
    inline TVect4<T> & operator /= (const TVect4<T> &u);

    
    
    inline TVect4<T> & operator += (const double d);
    
    inline TVect4<T> & operator -= (const double d);
    
    inline TVect4<T> & operator *= (const double d);
    
    inline TVect4<T> & operator /= (const double d);
    
    inline TVect4<T> &AddWithWeight(const TVect4<T> &u, const double w);
    

    
    
    
    inline void Negate();
    
    inline TVect4<T> operator -() const;
    

    
    
    
    
    
    inline TVect4<T> operator + (const TVect4<T> &u) const;
    
    
    inline TVect4<T> operator - (const TVect4<T> &u) const;
    
    
    inline TVect4<T> operator * (const TVect4<T> &u) const;
    
    
    inline TVect4<T> operator / (const TVect4<T> &u) const;

    
    
    
    inline TVect4<T> operator + (const double d) const;
    
    
    inline TVect4<T> operator - (const double d) const;
    
    
    inline TVect4<T> operator * (const double d) const;
    
    
    inline TVect4<T> operator / (const double d) const;

    
    
    TVect4<T> operator * (const TMatrix4<T> &v) const;
    


    
    
    
    inline void Clip(const double vmin, const double vmax);
    
    inline void ClipLower(double vmin);
    
    inline void ClipHigher(double vmax);
    
    inline TVect4<T> ValToRange(const T vmin, const T vmax) const;
    
    inline bool InRange(double vmin, double vmax) const;
    
    inline int MaxElementIndex() const;
    
    inline T MaxElement() const;
    
    inline void Set(double x0, double y0, double z0, double w0);
    
    inline void Set(double a);
    
    inline T Sum() const;
    
    inline TVect4<T> Project(const TVect4<T> &u) const;
    
    inline TVect4<T> &Normalize();
    
    inline bool Normalized() const;
    
    inline double ModNormalize();
    
    inline double SumNormalize();
    
    
    inline double MaxNormalize();
    
    inline void Orient(const TVect4<T> &v);
    
    bool IsOK() const;
    

    
    
    
    inline operator T *();
    
    inline operator const T *() const;
    

    
    
    
    inline static const TVect4<T> &Cast(const T *u);
    
    inline static TVect4<T> &Cast(T *u);
    

    
    
    
    inline const TVect3<T> &GetVect3() const;
    
    inline void SetVect3(const TVect3<T> &v);
    

    
    
    
    static int NComponents();
    
  };  















template <class T>
inline TVect4<T> operator * (const double d, const TVect4<T> &u)
  {
  return u * d;
  }










template <class T>
inline double DotProd(const TVect4<T> &a, const TVect4<T> &b)
  {
  return (double)a.x * (double)b.x +
         (double)a.y * (double)b.y +
         (double)a.z * (double)b.z;
  }









template <class T>
inline double DotProd4(const TVect4<T> &a, const TVect4<T> &b)
  {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
  }



template <class T>
inline TVect4<T> CrossProd(const TVect4<T> &a, const TVect4<T> &b);











template <class T>
inline double SqrLength(const TVect4<T> &u)
  {
  return DotProd(u, u);
  }











template <class T>
inline double Length(const TVect4<T> &u)
  {
  return Sqrt(SqrLength(u));
  }



template <class T>
inline double Cos(const TVect4<T> &a, const TVect4<T> &b);



template <class T>
inline double Sin(const TVect4<T> &a, const TVect4<T> &b);







template <class T>
inline TVect4<int> ConvI(const TVect4<T> &u)
  {
  return TVect4<int>(u.x, u.y, u.z, u.w);
  }







template <class T>
inline TVect4<float> ConvF(const TVect4<T> &u)
  {
  return TVect4<float>(u.x, u.y, u.z, u.w);
  }







template <class T>
inline TVect4<double> ConvD(const TVect4<T> &u)
  {
  return TVect4<double>(u.x, u.y, u.z, u.w);
  }


template <class T>
class Math4 : public Math<T>
  {
  public:
    
    
    
    inline static bool AboutZero(const TVect4<T> &v, const double tolerance);
    
    inline static bool AboutZero(const TVect4<T> &v);
    

    
    
    
    inline static bool AboutEqual(const TVect4<T> &v1, const TVect4<T> &v2, const double tolerance);
    
    inline static bool AboutEqual(const TVect4<T> &v1, const TVect4<T> &v2);
    

  };  






typedef BVect4<BYTE>      Set4b;



typedef BVect4<int>       Set4i;

typedef BVect4<unsigned>  Set4u;

typedef BVect4<float>     Set4f;




typedef TVect4<int>       Vect4i;

typedef TVect4<float>     Vect4f;

typedef TVect4<double>    Vect4d;


typedef TVect4<WORD>      Color4w;



typedef TVect4<int>       Color4i;

typedef TVect4<float>     Color4f;

typedef TVect4<float>     RGBAColor;

typedef TVect4<double>    Color4d;









template <class T>
BVect4<T>::BVect4()
  {
  }



template <class T>
BVect4<T>::BVect4(T a)
  {
  x = a;
  y = a;
  z = a;
  w = a;
  }









template <class T>
BVect4<T>::BVect4(const BVect3<T> &v, T a)
  {
  x = v.x;
  y = v.y;
  z = v.z;
  w = a;
  }










template <class T>
BVect4<T>::BVect4(const T &x0, const T &y0, const T &z0, const T &w0)
  {
  x = x0;
  y = y0;
  z = z0;
  w = w0;
  }





template <class T>
BVect4<T>::BVect4(const BVect4<T> &u)
  {
  x = u.x;
  y = u.y;
  z = u.z;
  w = u.w;
  }









template <class T>
T &BVect4<T>::operator [](int i)
  {
  Assert((i >= 0) && (i < 4));
  return (&x)[i];
  }









template <class T>
const T &BVect4<T>::operator [](int i) const
  {
  Assert((i >= 0) && (i < 4));
  return (&x)[i];
  }





template <class T>
int BVect4<T>::NComponents()
  {
  return 4;
  }








template <class T>
const BVect3<T> &BVect4<T>::GetVect3() const
  {
  return BVect3<T>::Cast(&x);
  }




template <class T>
void BVect4<T>::SetVect3(const BVect3<T> &v)
  {
  x = v.x;
  y = v.y;
  z = v.z;
  }







template <class T>
BVect4<T> &BVect4<T>::operator = (const BVect4<T> &u)
  {
  x = u.x;
  y = u.y;
  z = u.z;
  w = u.w;
  return *this;
  }







template <class T>
bool BVect4<T>::operator == (const BVect4<T> &u) const
  {
  return (x == u.x) && (y == u.y) && (z == u.z) && (w == u.w);
  }








template <class T>
bool BVect4<T>::operator != (const BVect4<T> &u) const
  {
  return (x != u.x) || (y != u.y) || (z != u.z) || (w != u.w);
  }









template <class T>
BVect4<T>::operator T *()
  {
  return &x;
  }









template <class T>
BVect4<T>::operator const T *() const
  {
  return &x;
  }








template <class T>
const BVect4<T> &BVect4<T>::Cast(const T *u)
  {
  return *(const BVect4<T> *)u;
  }








template <class T>
BVect4<T> &BVect4<T>::Cast(T *u)
  {
  return *(BVect4<T> *)u;
  }





template <class T>
T BVect4<T>::MaxElement() const
  {
  return Max(Max(x, y), Max(z, w));
  }







template <class T>
TVect4<T>::TVect4()
  {
  }






template <class T>
TVect4<T>::TVect4(const double v)
  {
  x = y = z = w = (T)v;
  }











template <class T>
TVect4<T>::TVect4(const double x0, const double y0,
                  const double z0, const double w0)
  {
  x = (T)x0;
  y = (T)y0;
  z = (T)z0;
  w = (T)w0;
  }











template <class T>
TVect4<T>::TVect4(const TPoint3<T> &from, const TPoint3<T> &to)
  {
  *this = to - from;
  }





template <class T>
TVect4<T>::TVect4(const TVect4<T> &u)
  {
  x = u.x;
  y = u.y;
  z = u.z;
  w = u.w;
  }









template <class T>
TVect4<T>::TVect4(const TVect3<T> &u, T w0)
  {
  x = u.x;
  y = u.y;
  z = u.z;
  w = w0;
  }









template <class T>
T &TVect4<T>::operator [](int i)
  {
  Assert((i >= 0) && (i < 4));
  return (&x)[i];
  }









template <class T>
T TVect4<T>::operator [](int i) const
  {
  Assert((i >= 0) && (i < 4));
  return (&x)[i];
  }








template <class T>
const TVect3<T> &TVect4<T>::GetVect3() const
  {
  return TVect3<T>::Cast(&x);
  }




template <class T>
void TVect4<T>::SetVect3(const TVect3<T> &v)
  {
  x = v.x;
  y = v.y;
  z = v.z;
  }





template <class T>
int TVect4<T>::NComponents()
  {
  return 4;
  }







template <class T>
bool TVect4<T>::operator == (const TVect4<T> &u) const
  {
  return (x == u.x) && (y == u.y) && (z == u.z) && (w == u.w);
  }








template <class T>
bool TVect4<T>::operator != (const TVect4<T> &u) const
  {
  return (x != u.x) || (y != u.y) || (z != u.z) || (w != u.w);
  }







template <class T>
bool TVect4<T>::LessOrEqual(const TVect4<T> &u) const
  {
  return (x <= u.x) && (y <= u.y) && (z <= u.z) && (w <= u.w);
  }













template <class T>
bool TVect4<T>::operator < (const TVect4<T> &u) const
  {
  if (x < u.x)
    return true;
  if (x > u.x)
    return false;
  if (y < u.y)
    return true;
  if (y > u.y)
    return false;
  if (z < u.z)
    return true;
  if (z > u.z)
    return false;
  return w < u.w;
  }







template <class T>
TVect4<T> &TVect4<T>::operator = (const TVect4<T> &u)
  {
  x = u.x;
  y = u.y;
  z = u.z;
  w = u.w;
  return *this;
  }








template <class T>
TVect4<T> &TVect4<T>::operator += (const TVect4<T> &u)
  {
  x += u.x;
  y += u.y;
  z += u.z;
  w += u.w;
  return *this;
  }









template <class T>
TVect4<T> &TVect4<T>::operator -= (const TVect4<T> &u)
  {
  x -= u.x;
  y -= u.y;
  z -= u.z;
  w -= u.w;
  return *this;
  }








template <class T>
TVect4<T> &TVect4<T>::operator *= (const TVect4<T> &u)
  {
  x *= u.x;
  y *= u.y;
  z *= u.z;
  w *= u.w;
  return *this;
  }











template <class T>
TVect4<T> &TVect4<T>::operator /= (const TVect4<T> &u)
  {
  Assert((u.x != 0) && (u.y != 0) && (u.z != 0) && (u.w != 0));
  x /= u.x;
  y /= u.y;
  z /= u.z;
  w /= u.w;
  return *this;
  }









template <class T>
TVect4<T> &TVect4<T>::operator += (const double d)
  {
  x = (T)(x + d);
  y = (T)(y + d);
  z = (T)(z + d);
  w = (T)(w + d);
  return *this;
  }









template <class T>
TVect4<T> &TVect4<T>::operator -= (const double d)
  {
  x = (T)(x - d);
  y = (T)(y - d);
  z = (T)(z - d);
  w = (T)(w - d);
  return *this;
  }









template <class T>
TVect4<T> &TVect4<T>::operator *= (const double d)
  {
  x = (T)(x * d);
  y = (T)(y * d);
  z = (T)(z * d);
  w = (T)(w * d);
  return *this;
  }











template <class T>
TVect4<T> &TVect4<T>::operator /= (const double d)
  {
  Assert(d != 0.0);
  x = (T)(x / d);
  y = (T)(y / d);
  z = (T)(z / d);
  w = (T)(w / d);
  return *this;
  }










template <class T>
TVect4<T> &TVect4<T>::AddWithWeight(const TVect4<T> &u, const double wt)
  {
  x = (T)(x + u.x * wt);
  y = (T)(y + u.y * wt);
  z = (T)(z + u.z * wt);
  w = (T)(w + u.w * wt);
  return *this;
  }







template <class T>
void TVect4<T>::Negate()
  {
  x = -x;
  y = -y;
  z = -z;
  w = -w;
  }








template <class T>
TVect4<T> TVect4<T>::operator -() const
  {
  return TVect4<T>(-x, -y, -z, -w);
  }









template <class T>
TVect4<T> TVect4<T>::operator + (const TVect4<T> &u) const
  {
  return TVect4<T>(x + u.x, y + u.y, z + u.z, w + u.w);
  }









template <class T>
TVect4<T> TVect4<T>::operator - (const TVect4<T> &u) const
  {
  return TVect4<T>(x - u.x, y - u.y, z - u.z, w - u.w);
  }









template <class T>
TVect4<T> TVect4<T>::operator * (const TVect4<T> &u) const
  {
  return TVect4<T>(x * u.x, y * u.y, z * u.z, w * u.w);
  }












template <class T>
TVect4<T> TVect4<T>::operator / (const TVect4<T> &u) const
  {
  Assert((u.x != 0) && (u.y != 0) && (u.z != 0) && (u.w != 0));
  return TVect4<T>(x / u.x, y / u.y, z / u.z, w / u.w);
  }








template <class T>
TVect4<T> TVect4<T>::operator + (const double d) const
  {
  return TVect4<T>(x + d, y + d, z + d, w + d);
  }









template <class T>
TVect4<T> TVect4<T>::operator - (const double d) const
  {
  return TVect4<T>(x - d, y - d, z - d, w - d);
  }









template <class T>
TVect4<T> TVect4<T>::operator * (const double d) const
  {
  return TVect4<T>(x * d, y * d, z * d, w * d);
  }











template <class T>
TVect4<T> TVect4<T>::operator / (const double d) const
  {
  Assert(d != 0);
  return TVect4<T>(x / d, y / d, z / d, w / d);
  }

















template <class T>
void TVect4<T>::Clip(const double vmin, const double vmax)
  {
  Assert(vmax >= vmin);
  Kiam::Clip(x, vmin, vmax);
  Kiam::Clip(y, vmin, vmax);
  Kiam::Clip(z, vmin, vmax);
  Kiam::Clip(w, vmin, vmax);
  }





template <class T>
void TVect4<T>::ClipLower(double vmin)
  {
  Kiam::ClipLower(x, vmin);
  Kiam::ClipLower(y, vmin);
  Kiam::ClipLower(z, vmin);
  Kiam::ClipLower(w, vmin);
  }





template <class T>
void TVect4<T>::ClipHigher(double vmax)
  {
  Kiam::ClipHigher(x, vmax);
  Kiam::ClipHigher(y, vmax);
  Kiam::ClipHigher(z, vmax);
  Kiam::ClipHigher(w, vmax);
  }














template <class T>
TVect4<T> TVect4<T>::ValToRange(const T vmin, const T vmax) const
  {
  Assert(vmax >= vmin);
  return TVect4<T>(
    Kiam::ValToRange(x, vmin, vmax),
    Kiam::ValToRange(y, vmin, vmax),
    Kiam::ValToRange(z, vmin, vmax),
    Kiam::ValToRange(w, vmin, vmax));
  }














template <class T>
bool TVect4<T>::InRange(double vmin, double vmax) const
  {
  Assert(vmax >= vmin);
  return (x >= vmin && x <= vmax &&
          y >= vmin && y <= vmax &&
          z >= vmin && z <= vmax &&
          w >= vmin && w <= vmax);
  }







template <class T>
int TVect4<T>::MaxElementIndex() const
  {
  if ((Abs(x) >= Abs(y)) && (Abs(x) >= Abs(z)) && (Abs(x) >= Abs(w)))
    return 0;
  if ((Abs(y) >= Abs(z)) && (Abs(y) >= Abs(w)))
    return 1;
  if (Abs(z) >= Abs(w))
    return 2;
  return 3;
  }





template <class T>
T TVect4<T>::MaxElement() const
  {
  return Max( Max3(Abs(x), Abs(y), Abs(z)), Abs(w));
  }












template <class T>
void TVect4<T>::Set(double x0, double y0, double z0, double w0)
  {
  x = (T)x0;
  y = (T)y0;
  z = (T)z0;
  w = (T)w0;
  }








template <class T>
void TVect4<T>::Set(double a)
  {
  x = y = z = w = (T)a;
  }





template <class T>
T TVect4<T>::Sum() const
  {
  return (T)(x + y + z + w);
  }



















template <class T>
TVect4<T> TVect4<T>::Project(const TVect4<T> &u) const
  {
  double sqr_len = DotProd(u, u);
  Assert(sqr_len > 0.0);;
  return u * DotProd((*this), u) / sqr_len;
  }











template <class T>
TVect4<T> &TVect4<T>::Normalize()
  {
  double len = Length(*this);
  Assert(len != 0.0);
  x = (T)(x / len);
  y = (T)(y / len);
  z = (T)(z / len);
  return *this;
  }














template <class T>
double TVect4<T>::ModNormalize()
  {
  double len = Length(*this);
  if (len > 0.0)
    {
    x = (T)(x / len);
    y = (T)(y / len);
    z = (T)(z / len);
    }
  return len;
  }












template <class T>
double TVect4<T>::SumNormalize()
  {
  double sum = Sum();
  if (sum != 0.0)
    {
    x = (T)(x / sum);
    y = (T)(y / sum);
    z = (T)(z / sum);
    }
  return sum;
  }
















template <class T>
double TVect4<T>::MaxNormalize()
  {
  double len = MaxElement();
  if (len != 0.0)
    {
    x = (T)(x / len);
    y = (T)(y / len);
    z = (T)(z / len);
    }
  else
    {
    x = 1;
    y = 1;
    z = 1;
    }
  return len;
  }










template <class T>
bool TVect4<T>::Normalized() const
  {
  return MathF::AboutEqual(Length(*this), 1.0);
  }












template <class T>
void TVect4<T>::Orient(const TVect4<T> &v)
  {
  if (DotProd(*this, v) < 0)
    Negate();
  }












template <class T>
TVect4<T>::operator T *()
  {
  return &x;
  }












template <class T>
TVect4<T>::operator const T *() const
  {
  return &x;
  }








template <class T>
const TVect4<T> &TVect4<T>::Cast(const T *u)
  {
  return *(const TVect4<T> *)u;
  }








template <class T>
TVect4<T> &TVect4<T>::Cast(T *u)
  {
  return *(TVect4<T> *)u;
  }
























template <class T>
inline TVect4<T> CrossProd(const TVect4<T> &a, const TVect4<T> &b)
  {
  return TVect4<T>(a.y * b.z - a.z * b.y,
                   a.z * b.x - a.x * b.z,
                   a.x * b.y - a.y * b.x);
  }










template <class T>
inline double Cos(const TVect4<T> &a, const TVect4<T> &b)
  {
  Assert((SqrLength(a) != 0) && (SqrLength(b) != 0));
  return Clipped(DotProd(a, b) / Sqrt(SqrLength(a) * SqrLength(b)), -1, 1);
  }











template <class T>
inline double Sin(const TVect4<T> &a, const TVect4<T> &b)
  {
  Assert((SqrLength(a) != 0) && (SqrLength(b) != 0));
  return Clipped(Sqrt(SqrLength(CrossProd(a, b)) /
                      (SqrLength(a) * SqrLength(b))),
                 0, 1);
  }













template <class T>
inline bool Math4<T>::AboutZero(const TVect4<T> &v, const double tolerance)
  {
  return Math<T>::AboutZero(v.x, tolerance) &&
         Math<T>::AboutZero(v.y, tolerance) &&
         Math<T>::AboutZero(v.z, tolerance) &&
         Math<T>::AboutZero(v.w, tolerance);
  }








template <class T>
inline bool Math4<T>::AboutZero(const TVect4<T> &v)
  {
  return AboutZero(v, Math4<T>::TOLERANCE);
  }














template <class T>
inline bool Math4<T>::AboutEqual(const TVect4<T> &v1, const TVect4<T> &v2,
                                 const double tolerance)
  {
  return AboutZero(v1 - v2, tolerance);
  }













template <class T>
inline bool Math4<T>::AboutEqual(const TVect4<T> &v1, const TVect4<T> &v2)
  {
  return AboutZero(v1 - v2, Math4<T>::TOLERANCE);
  }

KIAM_NAMESPACE_END
#endif
