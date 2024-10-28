











#ifndef _KLBC_VECT2_HPP_
#define _KLBC_VECT2_HPP_

#include <base/base.hpp>

#include "math.hpp"

KIAM_NAMESPACE_START


template <class T> class BBox2;
template <class T> class BVect2;
template <class T> class Math2;
template <class T> class TMatrix2;
template <class T> class TPoint2;
template <class T> class TVect2;



template <class T>
class BVect2
  {
  public:
    
    typedef T BaseType;

  public:
    
    T x;
    
    T y;

  public:
    
    
    
    inline BVect2();
    
    inline BVect2(const double v);
    
    inline BVect2(const double x0, const double y0);
    
    inline BVect2(const BVect2<T> &u);
    

    
    
    
    inline T & operator [](int i);
    
    inline const T &operator [](int i) const;
    

    
    
    
    inline BVect2<T> & operator = (const BVect2<T> &u);
    

    
    
    
    inline bool operator == (const BVect2<T> &u) const;
    
    inline bool operator != (const BVect2<T> &u) const;
    


    
    
    
    inline operator T *();
    
    inline operator const T *() const;
    

    
    
    
    inline static const BVect2<T> &Cast(const T *u);
    
    inline static BVect2<T> &Cast(T *u);
    

    
    
    
    static int NComponents();
    
  };  


template <class T>
class TVect2
  {
  public:
    
    typedef T BaseType;

  public:
    
    T x;
    
    T y;

  public:
    
    
    
    inline TVect2();
    
    inline TVect2(const double v);
    
    inline TVect2(const double x0, const double y0);
    
    inline TVect2(const TPoint2<T> &from, const TPoint2<T> &to);
    
    inline TVect2(const TPoint2<T> &p);
    
    inline TVect2(const TVect2<T> &u);
    

    
    
    
    inline T & operator [](int i);
    
    inline const T &operator [](int i) const;
    

    
    
    
    inline bool operator == (const TVect2<T> &u) const;
    
    inline bool operator != (const TVect2<T> &u) const;
    
    inline bool LessOrEqual(const TVect2<T> &u) const;
    
    inline bool Less(const TVect2<T> &u) const;
    
    inline bool operator < (const TVect2<T> &u) const;
    
    inline bool IsOK() const;
    

    
    
    
    inline TVect2<T> & operator = (const TVect2<T> &u);

    

    
    inline TVect2<T> & operator += (const TVect2<T> &u);
    
    inline TVect2<T> & operator -= (const TVect2<T> &u);
    
    inline TVect2<T> & operator *= (const TVect2<T> &u);
    
    inline TVect2<T> & operator /= (const TVect2<T> &u);
    

    
    inline TVect2<T> & operator += (const double d);
    
    inline TVect2<T> & operator -= (const double d);
    
    inline TVect2<T> & operator *= (const double d);
    
    inline TVect2<T> & operator /= (const double d);
    
    inline TVect2<T> &AddWithWeight(const TVect2<T> &u, const double w);
    

    
    
    
    inline void Negate();
    
    inline TVect2<T> operator -() const;
    

    
    
    

    
    
    inline TVect2<T> operator + (const TVect2<T> &u) const;
    
    
    inline TVect2<T> operator - (const TVect2<T> &u) const;
    
    
    inline TVect2<T> operator * (const TVect2<T> &u) const;
    
    
    inline TVect2<T> operator / (const TVect2<T> &u) const;

    

    
    
    inline TVect2<T> operator + (const double d) const;
    
    
    inline TVect2<T> operator - (const double d) const;
    
    
    inline TVect2<T> operator * (const double d) const;
    
    
    inline TVect2<T> operator / (const double d) const;

    

    
    TVect2<T> operator * (const TMatrix2<T> &v) const;
    


    
    
    
    inline void Clip(const double vmin, const double vmax);
    
    inline bool ClipLower(double vmin);
    
    inline bool ClipHigher(double vmax);
    
    inline TVect2<T> ValToRange(const T vmin, const T vmax) const;
    
    inline bool InRange(double vmin, double vmax) const;
    
    inline int MaxElementIndex() const;
    
    inline T MaxElement() const;
    
    inline void Set(double x0, double y0);
    
    inline void Set(double a);
    
    inline double SqrLength() const;
    
    inline double Length() const;
    
    inline T Sum() const;
    
    inline TVect2<T> Project(const TVect2<T> &u) const;
    
    TVect2<T> AnyOrthogonal() const;
    
    inline TVect2<T> &Normalize();
    
    inline double ModNormalize();
    
    inline double SumNormalize();
    
    
    inline double MaxNormalize();
    
    inline bool Normalized() const;
    
    inline void Orient(const TVect2<T> &v);
    

    
    
    
    inline operator T *();
    
    inline operator const T *() const;
    

    
    
    
    inline static const TVect2<T> &Cast(const T *u);
    
    inline static TVect2<T> &Cast(T *u);
    

    
    
    
    
    
    
    
    inline const TPoint2<T> &Point() const;
    
    inline TPoint2<T> &Point();
    

    
    
    
    static int NComponents();
    
  };  















template <class T>
inline TVect2<T> operator * (const double d, const TVect2<T> &u)
  {
  return u * d;
  }














template <class T>
inline double DotProd(const TVect2<T> &a, const TVect2<T> &b)
  {
  return (double)a.x * (double)b.x + (double)a.y * (double)b.y;
  }



template <class T>
inline double CrossProd(const TVect2<T> &a, const TVect2<T> &b);







template <class T>
inline double SqrLength(const TVect2<T> &u)
  {
  return DotProd(u, u);
  }







template <class T>
inline double Length(const TVect2<T> &u)
  {
  return Sqrt(SqrLength(u));
  }



template <class T>
inline double Cos(const TVect2<T> &a, const TVect2<T> &b);



template <class T>
inline double Sin(const TVect2<T> &a, const TVect2<T> &b);







template <class T>
inline TVect2<int> ConvI(const TVect2<T> &u)
  {
  return TVect2<int>(u.x, u.y);
  }







template <class T>
inline TVect2<float> ConvF(const TVect2<T> &u)
  {
  return TVect2<float>(u.x, u.y);
  }







template <class T>
inline TVect2<double> ConvD(const TVect2<T> &u)
  {
  return TVect2<double>(u.x, u.y);
  }


template <class T>
class TPoint2
  {
  public:
    
    typedef T BaseType;

  public:

    
    T x;
    
    T y;

  public:

    
    
    
    inline TPoint2();
    
    inline TPoint2(const double v);
    
    inline TPoint2(const double x0, const double y0);
    
    inline TPoint2(const TVect2<T> &v);
    
    inline TPoint2(const TPoint2<T> &u);
    

    
    
    
    inline T & operator [](int i);
    
    inline const T &  operator [](int i) const;
    

    
    
    
    inline bool operator == (const TPoint2<T> &u) const;
    
    inline bool operator != (const TPoint2<T> &u) const;
    
    inline bool LessOrEqual(const TPoint2<T> &u) const;
    
    inline bool Less(const TPoint2<T> &u) const;
    
    inline bool operator < (const TPoint2<T> &u) const;
    
    inline static bool AboutEqual(const TPoint2<T> &v1, const TPoint2<T> &v2);
    
    inline static bool AboutEqual(const TPoint2<T> &v1, const TPoint2<T> &v2,
                       const double tolerance);
    
    inline bool IsOK() const;
    

    
    
    
    inline TPoint2<T> & operator = (const TPoint2<T> &u);
    

    
    
    
    inline TPoint2<T> & operator += (const TPoint2<T> &u);
    

    
    
    
    inline TPoint2<T> & operator += (const TVect2<T> &u);
    
    inline TPoint2<T> & operator -= (const TVect2<T> &u);
    

    
    
    
    inline TPoint2<T> & operator += (const double d);
    
    inline TPoint2<T> & operator -= (const double d);
    
    inline TPoint2<T> & operator *= (const double d);
    
    inline TPoint2<T> & operator /= (const double d);
    
    inline TPoint2<T> &AddWithWeight(const TVect2<T> &u, const double w);
    

    
    
    
    inline void Negate();
    
    inline TPoint2<T> operator -() const;
    

    
    

    
    
    
    inline TPoint2<T> operator + (const TPoint2<T> &u) const;
    
    inline TPoint2<T> operator + (const TVect2<T> &u) const;
    
    inline TPoint2<T> operator - (const TVect2<T> &u) const;
    
    
    inline TVect2<T> operator - (const TPoint2<T> &p) const;
    

    
    
    
    inline TPoint2<T> operator + (const double d) const;
    
    
    inline TPoint2<T> operator - (const double d) const;
    
    
    inline TPoint2<T> operator * (const double d) const;
    
    
    inline TPoint2<T> operator / (const double d) const;
    
    


    
    
    
    inline void Clip(const double vmin, const double vmax);
    
    inline void ClipLower(double vmin);
    
    inline TPoint2<T> ValToRange(const T vmin, const T vmax) const;
    
    inline void Set(double x0, double y0);
    
    inline void Set(double a);
    

    
    
    
    inline operator T *();
    
    inline operator const T *() const;
    

    
    
    
    
    
    
    
    
    inline static const TPoint2<T> &Cast(const T *u);
    
    inline static TPoint2<T> &Cast(T *u);
    

    
    
    
    
    
    
    
    inline const TVect2<T> &Vector() const;
    
    inline TVect2<T> &Vector();
    

    
    
    
    static int NComponents();
    
  };  

















template <class T>
inline TPoint2<T> operator * (const double d, const TPoint2<T> &u)
  {
  return u * d;
  }







template <class T>
inline double SqrDist(const TPoint2<T> &a, const TPoint2<T> &b)
  {
  return SqrLength(a - b);
  }








template <class T>
inline double Dist(const TPoint2<T> &a, const TPoint2<T> &b)
  {
  return Length(a - b);
  }



template <class T>
inline TPoint2<T> Center(const TPoint2<T> &a, const TPoint2<T> &b);



template <class T>
inline TPoint2<T> Center(const TPoint2<T> &a, const TPoint2<T> &b,
                         const TPoint2<T> &c);







template <class T>
inline TPoint2<int> ConvI(const TPoint2<T> &u)
  {
  return TPoint2<int>(u.x, u.y);
  }







template <class T>
inline TPoint2<float> ConvF(const TPoint2<T> &u)
  {
  return TPoint2<float>(u.x, u.y);
  }







template <class T>
inline TPoint2<double> ConvD(const TPoint2<T> &u)
  {
  return TPoint2<double>(u.x, u.y);
  }


template <class T>
class BBox2
  {
  public:
    
    typedef T BaseType;

  public:
    
    TPoint2<T> vmin;
    
    TPoint2<T> vmax;

  public:
    
    
    
    inline BBox2();
    
    inline BBox2(const TPoint2<T> &point);
    
    inline BBox2(const TPoint2<T> &point1, const TPoint2<T> &point2);
    
    inline BBox2(T vmin_x, T vmin_y, T vmax_x, T vmax_y);
    
    inline BBox2(const BBox2<T> &box);
    

    
    
    
    inline BBox2<T> & operator = (const BBox2<T> &box);
    

    
    
    
    inline bool operator == (const BBox2<T> &box) const;
    
    inline bool operator != (const BBox2<T> &box) const;
    

    
    
    
    inline bool NotEmpty() const;
    
    inline bool IsEmpty() const;
    
    inline bool IsDot() const;
    

    
    
    
    inline bool Includes(const TPoint2<T> &point) const;
    
    inline bool Includes(const BBox2<T> &box) const;
    
    inline bool Intersects(const BBox2<T> &box) const;
    

    
    
    
    inline void Include(const TPoint2<T> &point);
    
    inline void Include(const BBox2<T> &box);
    
    inline void Intersect(const BBox2<T> &box);
    
    inline void Translate(const TVect2<T> &vct);
    
    inline BBox2<T> Translated(const TVect2<T> &vct) const;
    
    inline TVect2<T> Diag() const;
    
    inline TPoint2<T> Center() const;
    
    inline T Width() const;
    
    inline T Height() const;
    
    inline T Area() const;
    
  };  







template <class T>
inline BBox2<float> ConvF(const BBox2<T> &u)
  { return BBox2<float>(ConvF(u.vmin), ConvF(u.vmax)); }







template <class T>
inline BBox2<double> ConvD(const BBox2<T> &u)
  { return BBox2<double>(ConvD(u.vmin), ConvD(u.vmax)); }






template <class T>
class Math2 : public Math<T>
  {
  public:
    
    
    
    inline static bool AboutZero(const TVect2<T> &v, const double tolerance);
    
    inline static bool AboutZero(const TVect2<T> &v);
    
    inline static bool NearZero(const TVect2<T> &v);
    
    inline static bool AboutZero(const TPoint2<T> &v, const double tolerance);
    
    inline static bool AboutZero(const TPoint2<T> &v);
    
    inline static bool NearZero(const TPoint2<T> &v);
    

    
    
    
    inline static bool AboutEqual(const TVect2<T> &v1, const TVect2<T> &v2,
                       const double tolerance);
    
    inline static bool AboutEqual(const TVect2<T> &v1, const TVect2<T> &v2);
    
    inline static bool NearEqual(const TVect2<T> &v1, const TVect2<T> &v2);
    
    inline static bool AboutEqual(const TPoint2<T> &v1, const TPoint2<T> &v2,
                       const double tolerance);
    
    inline static bool AboutEqual(const TPoint2<T> &v1, const TPoint2<T> &v2);
    
    inline static bool NearEqual(const TPoint2<T> &v1, const TPoint2<T> &v2);
    
  };  






typedef BVect2<BYTE>      Set2b;

typedef BVect2<float>     Set2f;

typedef BVect2<short>     Set2s;

typedef BVect2<WORD>     Set2w;

typedef BVect2<int>       Set2i;

typedef BVect2<unsigned>  Set2u;

typedef BVect2<double>    Set2d;


typedef TVect2<WORD>     Vect2w;

typedef TVect2<short>     Vect2s;

typedef TVect2<int>       Vect2i;

typedef TVect2<float>     Vect2f;

typedef TVect2<double>    Vect2d;


typedef TPoint2<int>      Point2i;

typedef TPoint2<float>    Point2f;

typedef TPoint2<double>   Point2d;

typedef TPoint2<INT64>    Point2l;


typedef BBox2<int>        BBox2i;

typedef BBox2<float>      BBox2f;

typedef BBox2<double>     BBox2d;


typedef Math2<float>      Math2f;

typedef Math2<double>     Math2d;







template <class T>
BVect2<T>::BVect2()
  {
  }






template <class T>
BVect2<T>::BVect2(const double v)
  {
  x = y = (T)v;
  }








template <class T>
BVect2<T>::BVect2(const double x0, const double y0)
  {
  x = (T)x0;
  y = (T)y0;
  }




template <class T>
BVect2<T>::BVect2(const BVect2<T> &u)
  {
  x = u.x;
  y = u.y;
  }








template <class T>
T & BVect2<T>::operator [](int i)
  {
  Assert((i >= 0) && (i < 2));
  return (&x)[i];
  }








template <class T>
const T &BVect2<T>::operator [](int i) const
  {
  Assert((i >= 0) && (i < 2));
  return (&x)[i];
  }





template <class T>
int BVect2<T>::NComponents()
  {
  return 2;
  }







template <class T>
BVect2<T> & BVect2<T>::operator = (const BVect2<T> &u)
  {
  x = u.x;
  y = u.y;
  return *this;
  }







template <class T>
bool BVect2<T>::operator == (const BVect2<T> &u) const
  {
  return (x == u.x) && (y == u.y);
  }








template <class T>
bool BVect2<T>::operator != (const BVect2<T> &u) const
  {
  return (x != u.x) || (y != u.y);
  }









template <class T>
BVect2<T>::operator T *()
  {
  return &x;
  }









template <class T>
BVect2<T>::operator const T *() const
  {
  return &x;
  }








template <class T>
const BVect2<T> &BVect2<T>::Cast(const T *u)
  {
  return *(const BVect2<T> *)u;
  }








template <class T>
BVect2<T> &BVect2<T>::Cast(T *u)
  {
  return *(BVect2<T> *)u;
  }







template <class T>
TVect2<T>::TVect2()
  {
  }






template <class T>
TVect2<T>::TVect2(const double v)
  {
  x = y = (T)v;
  }







template <class T>
TVect2<T>::TVect2(const double x0, const double y0)
  {
  x = (T)x0;
  y = (T)y0;
  }









template <class T>
TVect2<T>::TVect2(const TPoint2<T> &from, const TPoint2<T> &to)
  {
  *this = to - from;
  }






template <class T>
TVect2<T>::TVect2(const TPoint2<T> &p)
  {
  x = p.x;
  y = p.y;
  }





template <class T>
TVect2<T>::TVect2(const TVect2<T> &u)
  {
  x = u.x;
  y = u.y;
  }








template <class T>
T & TVect2<T>::operator [](int i)
  {
  Assert((i >= 0) && (i < 2));
  return (&x)[i];
  }








template <class T>
const T &TVect2<T>::operator [](int i) const
  {
  Assert((i >= 0) && (i < 2));
  return (&x)[i];
  }





template <class T>
int TVect2<T>::NComponents()
  {
  return 2;
  }







template <class T>
bool TVect2<T>::operator == (const TVect2<T> &u) const
  {
  return (x == u.x) && (y == u.y);
  }








template <class T>
bool TVect2<T>::operator != (const TVect2<T> &u) const
  {
  return (x != u.x) || (y != u.y);
  }







template <class T>
bool TVect2<T>::LessOrEqual(const TVect2<T> &u) const
  {
  return (x <= u.x) && (y <= u.y);
  }







template <class T>
bool TVect2<T>::Less(const TVect2<T> &u) const
  {
  return (x < u.x) && (y < u.y);
  }













template <class T>
bool TVect2<T>::operator < (const TVect2<T> &u) const
  {
  if (x < u.x)
    return true;
  if (x > u.x)
    return false;
  return y < u.y;
  }






template <class T>
bool TVect2<T>::IsOK() const
  {
  return (FloatIsOK(x) && FloatIsOK(y));
  }







template <class T>
TVect2<T> & TVect2<T>::operator = (const TVect2<T> &u)
  {
  x = u.x;
  y = u.y;
  return *this;
  }








template <class T>
TVect2<T> & TVect2<T>::operator += (const TVect2<T> &u)
  {
  x += u.x;
  y += u.y;
  return *this;
  }









template <class T>
TVect2<T> & TVect2<T>::operator -= (const TVect2<T> &u)
  {
  x -= u.x;
  y -= u.y;
  return *this;
  }








template <class T>
TVect2<T> & TVect2<T>::operator *= (const TVect2<T> &u)
  {
  x *= u.x;
  y *= u.y;
  return *this;
  }











template <class T>
TVect2<T> &TVect2<T>::operator /=(const TVect2<T> &u)
  {
  Assert((u.x != 0) && (u.y != 0));
  x /= u.x;
  y /= u.y;
  return *this;
  }









template <class T>
TVect2<T> & TVect2<T>::operator += (const double d)
  {
  x = (T)(x + d);
  y = (T)(y + d);
  return *this;
  }









template <class T>
TVect2<T> & TVect2<T>::operator -= (const double d)
  {
  x = (T)(x - d);
  y = (T)(y - d);
  return *this;
  }









template <class T>
TVect2<T> & TVect2<T>::operator *= (const double d)
  {
  x = (T)(x * d);
  y = (T)(y * d);
  return *this;
  }











template <class T>
TVect2<T> &TVect2<T>::operator /= (const double d)
  {
  Assert(d != 0.0);
  x = (T)(x / d);
  y = (T)(y / d);
  return *this;
  }










template <class T>
TVect2<T> &TVect2<T>::AddWithWeight(const TVect2<T> &u, const double w)
  {
  x = (T)(x + u.x * w);
  y = (T)(y + u.y * w);
  return *this;
  }







template <class T>
void TVect2<T>::Negate()
  {
  x = -x;
  y = -y;
  }









template <class T>
TVect2<T> TVect2<T>::operator -() const
  {
  return TVect2<T>(-x, -y);
  }









template <class T>
TVect2<T> TVect2<T>::operator + (const TVect2<T> &u) const
  {
  return TVect2<T>(x + u.x, y + u.y);
  }









template <class T>
TVect2<T> TVect2<T>::operator - (const TVect2<T> &u) const
  {
  return TVect2<T>(x - u.x, y - u.y);
  }









template <class T>
TVect2<T> TVect2<T>::operator * (const TVect2<T> &u) const
  {
  return TVect2<T>(x * u.x, y * u.y);
  }












template <class T>
TVect2<T> TVect2<T>::operator / (const TVect2<T> &u) const
  {
  Assert((u.x != 0) && (u.y != 0));
  return TVect2<T>(x / u.x, y / u.y);
  }








template <class T>
TVect2<T> TVect2<T>::operator + (const double d) const
  {
  return TVect2<T>(x + d, y + d);
  }









template <class T>
TVect2<T> TVect2<T>::operator - (const double d) const
  {
  return TVect2<T>(x - d, y - d);
  }









template <class T>
TVect2<T> TVect2<T>::operator * (const double d) const
  {
  return TVect2<T>(x * d, y * d);
  }











template <class T>
TVect2<T> TVect2<T>::operator / (const double d) const
  {
  Assert(d != 0);
  return TVect2<T>(x / d, y / d);
  }

















template <class T>
void TVect2<T>::Clip(const double vmin, const double vmax)
  {
  Assert(vmax >= vmin);
  Kiam::Clip(x, vmin, vmax);
  Kiam::Clip(y, vmin, vmax);
  }






template <class T>
bool TVect2<T>::ClipLower(double vmin)
  {
  bool ret = false;
  if (Kiam::ClipLower(x, vmin))
    ret = true;
  if (Kiam::ClipLower(y, vmin))
    ret = true;
  return ret;
  }






template <class T>
bool TVect2<T>::ClipHigher(double vmax)
  {
  bool ret = false;
  if (Kiam::ClipHigher(x, vmax))
    ret = true;
  if(Kiam::ClipHigher(y, vmax))
    ret = true;
  return ret;
  }














template <class T>
TVect2<T> TVect2<T>::ValToRange(const T vmin, const T vmax) const
  {
  Assert(vmax >= vmin);
  return TVect2<T>(
    Kiam::ValToRange(x, vmin, vmax),
    Kiam::ValToRange(y, vmin, vmax));
  }














template <class T>
bool TVect2<T>::InRange(double vmin, double vmax) const
  {
  Assert(vmax >= vmin);
  return (x >= vmin && x <= vmax &&
          y >= vmin && y <= vmax);
  }






template <class T>
int TVect2<T>::MaxElementIndex() const
  {
  return (Abs(x) >= Abs(y)) ? 0 : 1;
  }





template <class T>
T TVect2<T>::MaxElement() const
  {
  return Max(Abs(x), Abs(y));
  }









template <class T>
void TVect2<T>::Set(double x0, double y0)
  {
  x = (T)x0;
  y = (T)y0;
  }








template <class T>
void TVect2<T>::Set(double a)
  {
  x = y = (T)a;
  }






template <class T>
double TVect2<T>::SqrLength() const
  {
  return x * x + y * y;
  }






template <class T>
double TVect2<T>::Length() const
  {
  return Sqrt(SqrLength());
  }





template <class T>
T TVect2<T>::Sum() const
  {
  return (T)(x + y);
  }



















template <class T>
TVect2<T> TVect2<T>::Project(const TVect2<T> &u) const
  {
  double sqr_len = DotProd(u, u);
  Assert(sqr_len > 0.0);;
  return u * DotProd((*this), u) / sqr_len;
  }








template <class T>
TVect2<T> TVect2<T>::AnyOrthogonal() const
  {
  Assert(Length() != 0.0);
  return TVect2<T>(y, -x) / Length();
  }










template <class T>
TVect2<T> & TVect2<T>::Normalize()
  {
  double len = Length();
  Assert(len != 0.0);
  x = (T)(x / len);
  y = (T)(y / len);
  return *this;
  }











template <class T>
double TVect2<T>::ModNormalize()
  {
  double len = Length();
  if (len > 0.0)
    {
    x = (T)(x / len);
    y = (T)(y / len);
    }
  return len;
  }












template <class T>
double TVect2<T>::SumNormalize()
  {
  double sum = Sum();
  if (sum != 0.0)
    {
    x = (T)(x / sum);
    y = (T)(y / sum);
    }
  else
    x = y = (T)0.5;

  return sum;
  }

















template <class T>
double TVect2<T>::MaxNormalize()
  {
  double max = MaxElement();
  if (max != 0.0)
    {
    x = (T)(x / max);
    y = (T)(y / max);
    }
  else
    {
    x = 1;
    y = 1;
    }
  return max;
  }








template <class T>
bool TVect2<T>::Normalized() const
  {
  return MathF::AboutEqual(Length(), 1.0);
  }











template <class T>
void TVect2<T>::Orient(const TVect2<T> &v)
  {
  if (DotProd(*this, v) < 0)
    Negate();
  }












template <class T>
TVect2<T>::operator T *()
  {
  return &x;
  }












template <class T>
TVect2<T>::operator const T *() const
  {
  return &x;
  }








template <class T>
const TVect2<T> &TVect2<T>::Cast(const T *u)
  {
  return *(const TVect2<T> *)u;
  }








template <class T>
TVect2<T> &TVect2<T>::Cast(T *u)
  {
  return *(TVect2<T> *)u;
  }








template <class T>
const TPoint2<T> &TVect2<T>::Point() const
  {
  return TPoint2<T>::Cast(&x);
  }








template <class T>
TPoint2<T> &TVect2<T>::Point()
  {
  return TPoint2<T>::Cast(&x);
  }
















template <class T>
inline double CrossProd(const TVect2<T> &a, const TVect2<T> &b)
  {
  return a.x * b.y - a.y * b.x;
  }









template <class T>
inline double Cos(const TVect2<T> &a, const TVect2<T> &b)
  {
  Assert((SqrLength(a) != 0) && (SqrLength(b) != 0));
  return Clipped(DotProd(a, b) / Sqrt(SqrLength(a) * SqrLength(b)), -1, 1);
  }









template <class T>
inline double Sin(const TVect2<T> &a, const TVect2<T> &b)
  {
  Assert((SqrLength(a) != 0) && (SqrLength(b) != 0));
  return Clipped(Abs(CrossProd(a, b)) / Sqrt((SqrLength(a) * SqrLength(b))),
                 0, 1);
  }







template <class T>
TPoint2<T>::TPoint2()
  {
  }






template <class T>
TPoint2<T>::TPoint2(const double v)
  {
  x = y = (T)v;
  }








template <class T>
TPoint2<T>::TPoint2(const double x0, const double y0)
  {
  x = (T)x0;
  y = (T)y0;
  }








template <class T>
TPoint2<T>::TPoint2(const TVect2<T> &v)
  {
  x = v.x;
  y = v.y;
  }





template <class T>
TPoint2<T>::TPoint2(const TPoint2<T> &u)
  {
  x = u.x;
  y = u.y;
  }








template <class T>
T & TPoint2<T>::operator [](int i)
  {
  Assert((i >= 0) && (i < 2));
  return (&x)[i];
  }








template <class T>
const T &TPoint2<T>::operator [](int i) const
  {
  Assert((i >= 0) && (i < 2));
  return (&x)[i];
  }





template <class T>
int TPoint2<T>::NComponents()
  {
  return 2;
  }







template <class T>
bool TPoint2<T>::operator == (const TPoint2<T> &u) const
  {
  return (x == u.x) && (y == u.y);
  }








template <class T>
bool TPoint2<T>::operator != (const TPoint2<T> &u) const
  {
  return (x != u.x) || (y != u.y);
  }







template <class T>
bool TPoint2<T>::LessOrEqual(const TPoint2<T> &u) const
  {
  return (x <= u.x) && (y <= u.y);
  }







template <class T>
bool TPoint2<T>::Less(const TPoint2<T> &u) const
  {
  return (x < u.x) && (y < u.y);
  }













template <class T>
bool TPoint2<T>::operator < (const TPoint2<T> &u) const
  {
  if (x < u.x)
    return true;
  if (x > u.x)
    return false;
  return y < u.y;
  }












template <class T>
bool TPoint2<T>::AboutEqual(const TPoint2<T> &v1, const TPoint2<T> &v2)
  {
  return Math2<T>::AboutZero(v1 - v2, Math2<T>::TOLERANCE);
  }













template <class T>
bool TPoint2<T>::AboutEqual(const TPoint2<T> &v1, const TPoint2<T> &v2,
                                 const double tolerance)
  {
  return Math2<T>::AboutZero(v1 - v2, tolerance);
  }






template <class T>
bool TPoint2<T>::IsOK() const
  {
  return (FloatIsOK(x) && FloatIsOK(y));
  }







template <class T>
TPoint2<T> & TPoint2<T>::operator = (const TPoint2<T> &u)
  {
  x = u.x;
  y = u.y;
  return *this;
  }









template <class T>
TPoint2<T> & TPoint2<T>::operator += (const TPoint2<T> &u)
  {
  x += u.x;
  y += u.y;
  return *this;
  }









template <class T>
TPoint2<T> & TPoint2<T>::operator += (const TVect2<T> &u)
  {
  x += u.x;
  y += u.y;
  return *this;
  }











template <class T>
TPoint2<T> & TPoint2<T>::operator -= (const TVect2<T> &u)
  {
  x -= u.x;
  y -= u.y;
  return *this;
  }









template <class T>
TPoint2<T> & TPoint2<T>::operator += (const double d)
  {
  x = (T)(x + d);
  y = (T)(y + d);
  return *this;
  }









template <class T>
TPoint2<T> & TPoint2<T>::operator -= (const double d)
  {
  x = (T)(x - d);
  y = (T)(y - d);
  return *this;
  }









template <class T>
TPoint2<T> & TPoint2<T>::operator *= (const double d)
  {
  x = (T)(x * d);
  y = (T)(y * d);
  return *this;
  }











template <class T>
TPoint2<T> &TPoint2<T>::operator /= (const double d)
  {
  Assert(d != 0.0);
  x = (T)(x / d);
  y = (T)(y / d);
  return *this;
  }










template <class T>
TPoint2<T> &TPoint2<T>::AddWithWeight(const TVect2<T> &u, const double w)
  {
  x = (T)(x + u.x * w);
  y = (T)(y + u.y * w);
  return *this;
  }








template <class T>
void TPoint2<T>::Negate()
  {
  x = -x;
  y = -y;
  }








template <class T>
TPoint2<T> TPoint2<T>::operator -() const
  {
  return TPoint2<T>(-x, -y);
  }










template <class T>
inline TPoint2<T> TPoint2<T>::operator + (const TPoint2<T> &u) const
  {
  return TPoint2<T>(x + u.x, y + u.y);
  }










template <class T>
inline TPoint2<T> TPoint2<T>::operator + (const TVect2<T> &u) const
  {
  return TPoint2<T>(x + u.x, y + u.y);
  }











template <class T>
TPoint2<T> TPoint2<T>::operator - (const TVect2<T> &u) const
  {
  return TPoint2<T>(x - u.x, y - u.y);
  }












template <class T>
TVect2<T> TPoint2<T>::operator - (const TPoint2<T> &p) const
  {
  return TVect2<T>(x - p.x, y - p.y);
  }








template <class T>
TPoint2<T> TPoint2<T>::operator + (const double d) const
  {
  return TPoint2<T>(x + d, y + d);
  }









template <class T>
TPoint2<T> TPoint2<T>::operator - (const double d) const
  {
  return TPoint2<T>(x - d, y - d);
  }









template <class T>
TPoint2<T> TPoint2<T>::operator * (const double d) const
  {
  return TPoint2<T>(x * d, y * d);
  }











template <class T>
TPoint2<T> TPoint2<T>::operator / (const double d) const
  {
  Assert(d != 0);
  return TPoint2<T>(x / d, y / d);
  }

















template <class T>
void TPoint2<T>::Clip(const double vmin, const double vmax)
  {
  Assert(vmax >= vmin);
  Kiam::Clip(x, vmin, vmax);
  Kiam::Clip(y, vmin, vmax);
  }





template <class T>
void TPoint2<T>::ClipLower(double vmin)
  {
  Kiam::ClipLower(x, vmin);
  Kiam::ClipLower(y, vmin);
  }














template <class T>
TPoint2<T> TPoint2<T>::ValToRange(const T vmin, const T vmax) const
  {
  Assert(vmax >= vmin);
  return TPoint2<T>(
    Kiam::ValToRange(x, vmin, vmax),
    Kiam::ValToRange(y, vmin, vmax));
  }









template <class T>
void TPoint2<T>::Set(double x0, double y0)
  {
  x = (T)x0;
  y = (T)y0;
  }








template <class T>
void TPoint2<T>::Set(double a)
  {
  x = y = (T)a;
  }












template <class T>
TPoint2<T>::operator T *()
  {
  return &x;
  }












template <class T>
TPoint2<T>::operator const T *() const
  {
  return &x;
  }








template <class T>
const TPoint2<T> &TPoint2<T>::Cast(const T *u)
  {
  return *(const TPoint2<T> *)u;
  }








template <class T>
TPoint2<T> &TPoint2<T>::Cast(T *u)
  {
  return *(TPoint2<T> *)u;
  }








template <class T>
const TVect2<T> &TPoint2<T>::Vector() const
  {
  return TVect2<T>::Cast(&x);
  }








template <class T>
TVect2<T> &TPoint2<T>::Vector()
  {
  return TVect2<T>::Cast(&x);
  }











template <class T>
inline TPoint2<T> Center(const TPoint2<T> &a, const TPoint2<T> &b)
  {
  return ((a.Vector() + b.Vector()) / 2.0).Point();
  }












template <class T>
inline TPoint2<T> Center(const TPoint2<T> &a, const TPoint2<T> &b,
                         const TPoint2<T> &c)
  {
  return ((a.Vector() + b.Vector() + c.Vector()) / 3.0).Point();
  }








template <class T>
BBox2<T>::BBox2()
  {
  }








template <class T>
BBox2<T>::BBox2(const TPoint2<T> &point)
  {
  vmin = vmax = point;
  }









template <class T>
BBox2<T>::BBox2(const TPoint2<T> &point1, const TPoint2<T> &point2)
  {
  vmin = point1;
  vmax = point2;
  }







template <class T>
BBox2<T>::BBox2(T vmin_x, T vmin_y, T vmax_x, T vmax_y)
  {
  vmin.x = vmin_x;
  vmin.y = vmin_y;
  vmax.x = vmax_x;
  vmax.y = vmax_y;
  }







template <class T>
BBox2<T>::BBox2(const BBox2<T> &box)
  {
  vmin = box.vmin;
  vmax = box.vmax;
  }









template <class T>
BBox2<T> & BBox2<T>::operator = (const BBox2<T> &box)
  {
  vmin = box.vmin;
  vmax = box.vmax;
  return *this;
  }









template <class T>
bool BBox2<T>::operator == (const BBox2<T> &box) const
  {
  return (vmin == box.vmin) && (vmax == box.vmax);
  }










template <class T>
bool BBox2<T>::operator != (const BBox2<T> &box) const
  {
  return (vmin != box.vmin) || (vmax != box.vmax);
  }











template <class T>
bool BBox2<T>::NotEmpty() const
  {
  return (vmin.x <= vmax.x) && (vmin.y <= vmax.y);
  }







template <class T>
bool BBox2<T>::IsEmpty() const
  {
  return (vmin.x > vmax.x) || (vmin.y > vmax.y);
  }










template <class T>
bool BBox2<T>::IsDot() const
  {
  return vmin == vmax;
  }












template <class T>
bool BBox2<T>::Includes(const TPoint2<T> &point) const
  {
  return (vmin.LessOrEqual(point)) && (point.LessOrEqual(vmax));
  }










template <class T>
bool BBox2<T>::Includes(const BBox2<T> &box) const
  {
  return (vmin.LessOrEqual(box.vmin)) && (box.vmax.LessOrEqual(vmax));
  }









template <class T>
bool BBox2<T>::Intersects(const BBox2<T> &box) const
  {
  return (vmin.LessOrEqual(box.vmax)) && (box.vmin.LessOrEqual(vmax));
  }











template <class T>
void BBox2<T>::Include(const TPoint2<T> &point)
  {
  if (point.x < vmin.x)
    vmin.x = point.x;
  if (vmax.x < point.x)
    vmax.x = point.x;
  if (point.y < vmin.y)
    vmin.y = point.y;
  if (vmax.y < point.y)
    vmax.y = point.y;
  }












template <class T>
void BBox2<T>::Include(const BBox2<T> &box)
  {
  if (vmin.x > box.vmin.x)
    vmin.x = box.vmin.x;
  if (vmax.x < box.vmax.x)
    vmax.x = box.vmax.x;
  if (vmin.y > box.vmin.y)
    vmin.y = box.vmin.y;
  if (vmax.y < box.vmax.y)
    vmax.y = box.vmax.y;
  }










template <class T>
void BBox2<T>::Intersect(const BBox2<T> &box)
  {
  if (vmin.x < box.vmin.x)
    vmin.x = box.vmin.x;
  if (vmax.x > box.vmax.x)
    vmax.x = box.vmax.x;
  if (vmin.y < box.vmin.y)
    vmin.y = box.vmin.y;
  if (vmax.y > box.vmax.y)
    vmax.y = box.vmax.y;
  }










template <class T>
void BBox2<T>::Translate(const TVect2<T> &vct)
  {
  vmin += vct;
  vmax += vct;
  }










template <class T>
BBox2<T> BBox2<T>::Translated(const TVect2<T> &vct) const
  {
  return BBox2<T>(vmin + vct, vmax + vct);
  }










template <class T>
TVect2<T> BBox2<T>::Diag() const
  {
  return vmax - vmin;
  }








template <class T>
TPoint2<T> BBox2<T>::Center() const
  {
  return Kiam::Center(vmax, vmin);
  }






template <class T>
T BBox2<T>::Width() const
  {
  return (vmax.x - vmin.x);
  }






template <class T>
T BBox2<T>::Height() const
  {
  return (vmax.y - vmin.y);
  }






template <class T>
T BBox2<T>::Area() const
  {
  return Width() * Height();
  }












template <class T>
bool Math2<T>::AboutZero(const TVect2<T> &v, const double tolerance)
  {
  return Math<T>::AboutZero(v.x, tolerance) &&
         Math<T>::AboutZero(v.y, tolerance);
  }







template <class T>
bool Math2<T>::AboutZero(const TVect2<T> &v)
  {
  return AboutZero(v, Math2<T>::TOLERANCE);
  }








template <class T>
bool Math2<T>::NearZero(const TVect2<T> &v)
  {
  return AboutZero(v, EPSILON);
  }








template <class T>
bool Math2<T>::AboutZero(const TPoint2<T> &v, const double tolerance)
  {
  return Math<T>::AboutZero(v.x, tolerance) &&
         Math<T>::AboutZero(v.y, tolerance);
  }







template <class T>
bool Math2<T>::AboutZero(const TPoint2<T> &v)
  {
  return AboutZero(v, Math2<T>::TOLERANCE);
  }








template <class T>
bool Math2<T>::NearZero(const TPoint2<T> &v)
  {
  return AboutZero(v, EPSILON);
  }













template <class T>
bool Math2<T>::AboutEqual(const TVect2<T> &v1, const TVect2<T> &v2,
                                 const double tolerance)
  {
  return AboutZero(v1 - v2, tolerance);
  }












template <class T>
bool Math2<T>::AboutEqual(const TVect2<T> &v1, const TVect2<T> &v2)
  {
  return AboutZero(v1 - v2, Math2<T>::TOLERANCE);
  }













template <class T>
bool Math2<T>::NearEqual(const TVect2<T> &v1, const TVect2<T> &v2)
  {
  return AboutZero(v1 - v2, EPSILON);
  }













template <class T>
bool Math2<T>::AboutEqual(const TPoint2<T> &v1, const TPoint2<T> &v2,
                                 const double tolerance)
  {
  return AboutZero(v1 - v2, tolerance);
  }












template <class T>
bool Math2<T>::AboutEqual(const TPoint2<T> &v1, const TPoint2<T> &v2)
  {
  return AboutZero(v1 - v2, Math2<T>::TOLERANCE);
  }













template <class T>
bool Math2<T>::NearEqual(const TPoint2<T> &v1, const TPoint2<T> &v2)
  {
  return AboutZero(v1 - v2, EPSILON);
  }










template <class T>
inline double TrgArea(const TPoint2<T> &a, const TPoint2<T> &b, const TPoint2<T> &c)
  {
  return Abs(0.5 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)));
  }










template <class T>
inline double TrgPerimeter(const TPoint2<T> &a, const TPoint2<T> &b, const TPoint2<T> &c)
  {
  return Length(b - a) + Length(c - b) + Length(a - c);
  }

KIAM_NAMESPACE_END
#endif
