










#ifndef _KLBC_VECT3_HPP_
#define _KLBC_VECT3_HPP_

#include <base/base.hpp>

#include "math.hpp"

KIAM_NAMESPACE_START


template <class T> class BBox3;
template <class T> class BVect3;
template <class T> class Math3;
template <class T> class TMatrix3;
template <class T> class TMatrix43;
template <class T> class TPoint3;
template <class T> class TVect3;


extern double CIE_SUM_VECT[3]; 




template <class T>
class BVect3
  {
  public:
    
    typedef T BaseType;

  public:
    
    T x,
    
      y,
    
      z;

  public:
    
    
    
    inline BVect3();
    
    inline BVect3(const T &v);
    
    inline BVect3(const T &x0, const T &y0, const T &z0);
    
    inline BVect3(const BVect3<T> &u);
    

    
    
    
    inline T & operator [](int i);
    
    inline const T &operator [](int i) const;
    

    
    
    
    inline BVect3<T> & operator = (const BVect3<T> &u);
    
    inline void Set(const T &x0, const T &y0, const T &z0);
    

    
    
    
    inline bool operator == (const BVect3<T> &u) const;
    
    inline bool operator != (const BVect3<T> &u) const;
    

    
    
    
    inline operator T *();
    
    inline operator const T *() const;
    

    
    
    
    inline static const BVect3<T> &Cast(const T *u);
    
    inline static BVect3<T> &Cast(T *u);
    


    
    inline T MaxElement() const;

    
    
    
    static int NComponents();
    
  };  



template <class T>
class TVect3
  {
  public:
    
    typedef T BaseType;

  public:
    
    T x,
    
      y,
    
      z;

  public:

    
    
    
    inline TVect3();
    
    inline TVect3(const T &v);
    
    inline TVect3(const double x0, const double y0, const double z0);
    
    inline TVect3(const TPoint3<T> &from, const TPoint3<T> &to);
    
    inline TVect3(const TVect3<T> &u);
    
    inline TVect3(const BVect3<BYTE> &u);
    

    
    
    
    inline T & operator [](int i);
    
    inline const T &operator [](int i) const;
    

    
    
    
    inline bool operator == (const TVect3<T> &u) const;
    
    inline bool operator != (const TVect3<T> &u) const;
    
    inline bool LessOrEqual(const TVect3<T> &u) const;
    
    inline bool operator < (const TVect3<T> &u) const;
    
    inline bool IsPositiveComp() const;
    
    inline static bool AboutEqual(const TVect3<T> &v1, const TVect3<T> &v2);
    
    inline static bool AboutEqual(const TVect3<T> &v1, const TVect3<T> &v2,
                       const double tolerance);
    
    inline bool IsZero() const;
    

    
    
    
    inline TVect3<T> & operator = (const TVect3<T> &u);

    

    
    inline TVect3<T> & operator += (const TVect3<T> &u);
    
    inline TVect3<T> & operator -= (const TVect3<T> &u);
    
    inline TVect3<T> & operator *= (const TVect3<T> &u);
    
    inline TVect3<T> & operator /= (const TVect3<T> &u);

    

    
    inline TVect3<T> & operator += (const double d);
    
    inline TVect3<T> & operator -= (const double d);
    
    inline TVect3<T> & operator *= (const double d);
    
    inline TVect3<T> & operator /= (const double d);
    
    inline TVect3<T> &AddWithWeight(const TVect3<T> &u, const double w);

    

    
    TVect3<T> operator * (const TMatrix3<T> &v) const;
    

    
    
    
    inline void Negate();
    
    inline TVect3<T> operator -() const;
    

    
    
    

    
    
    inline TVect3<T> operator + (const TVect3<T> &u) const;
    
    
    inline TVect3<T> operator - (const TVect3<T> &u) const;
    
    
    inline TVect3<T> operator * (const TVect3<T> &u) const;
    
    
    inline TVect3<T> operator / (const TVect3<T> &u) const;
    

    
    
    inline TVect3<T> operator + (const double d) const;
    
    
    inline TVect3<T> operator - (const double d) const;
    
    
    inline TVect3<T> operator * (const double d) const;
    
    
    inline TVect3<T> operator / (const double d) const;
    


    
    
    
    inline void Clip(double vmin, double vmax);
    
    inline bool ClipLower(double vmin);
    
    inline bool ClipHigher(double vmax);
    
    inline TVect3<T> ValToRange(const T &vmin, const T &vmax) const;
    
    inline bool InRange(double vmin, double vmax) const;
    
    void Round(double level = Math<float>::TOLERANCE);
    
    inline bool IsOK() const;
    
    inline int MaxElementIndex() const;
    
    inline int MinElementIndex() const;
    
    inline T MaxElement() const;
    
    inline T MaxVal() const;
    
    inline T MinVal() const;
    
    inline void Set(double x0, double y0, double z0);
    
    inline void Set(double a);
    
    inline double SqrLength() const;
    
    inline double Length() const;
    
    inline T Sum() const;

    
    inline double CIESum() const;
    
    inline double CIENormalize();
    
    inline TVect3<T> Project(const TVect3<T> &u) const;
    
    TVect3<T> AnyOrthogonal() const;
    
    inline TVect3<T> &Normalize();
    
    inline bool Normalized() const;
    
    inline double ModNormalize();
    
    inline double SumNormalize();
    
    
    inline double MaxNormalize();
    
    inline void Orient(const TVect3<T> &v);
    
    static TVect3<T> Axis(int axis_ind);
    
    inline void Sort();
    

    
    
    
    inline operator T *();
    
    inline operator const T *() const;
    

    
    
    
    inline static const TVect3<T> &Cast(const T *u);
    
    inline static TVect3<T> &Cast(T *u);
    

    
    
    
    
    
    
    
    inline const TPoint3<T> &Point() const;
    
    inline TPoint3<T> &Point();
    

    
    
    
    static int NComponents();
    

    
    static void CreateCoordSystem(const TVect3<T> &v1, TVect3<T> &v2, TVect3<T> &v3);
  };  










template <class T>
inline void TVect3<T>::CreateCoordSystem(const TVect3<T> &v1,
                                         TVect3<T> &v2, TVect3<T> &v3)
  {
  if (Abs(v1.x) > Abs(v1.y))
    {
    double invLen = 1.0 / Sqrt(v1.x * v1.x + v1.z * v1.z);
    v2 = TVect3<T>(-v1.z * invLen, 0.0, v1.x * invLen);
    }
  else
    {
    double invLen = 1.0 / Sqrt(v1.y * v1.y + v1.z * v1.z);
    v2 = TVect3<T>(0.0, v1.z * invLen, -v1.y * invLen);
    }
  v3 = CrossProd(v1, v2);
  }












template <class T>
inline bool TVect3<T>::AboutEqual(const TVect3<T> &v1, const TVect3<T> &v2)
  {
  return Math3<T>::AboutZero(v1 - v2, Math<T>::TOLERANCE);
  }













template <class T>
inline bool TVect3<T>::AboutEqual(const TVect3<T> &v1, const TVect3<T> &v2,
                                 const double tolerance)
  {
  return Math3<T>::AboutZero(v1 - v2, tolerance);
  }











template <class T>
inline TVect3<T> operator * (const double d, const TVect3<T> &u)
  {
  return u * d;
  }














template <class T>
inline double DotProd(const TVect3<T> &a, const TVect3<T> &b)
  {
  return (double)a.x * (double)b.x +
         (double)a.y * (double)b.y +
         (double)a.z * (double)b.z;
  }



template <class T>
inline TVect3<T> CrossProd(const TVect3<T> &a, const TVect3<T> &b);






template <class T>
inline TVect3<T> Max(const TVect3<T> &a, const TVect3<T> &b);







template <class T>
inline double SqrLength(const TVect3<T> &u)
  {
  return DotProd(u, u);
  }







template <class T>
inline double Length(const TVect3<T> &u)
  {
  return Sqrt(SqrLength(u));
  }



template <class T>
inline double Cos(const TVect3<T> &a, const TVect3<T> &b);



template <class T>
inline double Sin(const TVect3<T> &a, const TVect3<T> &b);







template <class T>
inline TVect3<int> ConvI(const TVect3<T> &u)
  {
  return TVect3<int>(u.x, u.y, u.z);
  }







template <class T>
inline TVect3<float> ConvF(const TVect3<T> &u)
  {
  return TVect3<float>(u.x, u.y, u.z);
  }







template <class T>
inline TVect3<double> ConvD(const TVect3<T> &u)
  {
  return TVect3<double>(u.x, u.y, u.z);
  }







template <class T>
inline TVect3<WORD> ConvW(const TVect3<T> &u)
  {
  return TVect3<WORD>((WORD)u.x, (WORD)u.y, (WORD)u.z);
  }







template <class T>
inline BVect3<BYTE> ConvB(const TVect3<T> &u)
  {
  return BVect3<BYTE>((BYTE)u.x, (BYTE)u.y, (BYTE)u.z);
  }


template <class T>
class TPoint3
  {
  public:
    
    typedef T BaseType;

  public:
    
    T x,
    
      y,
    
      z;

  public:
    
    
    
    inline TPoint3();
    
    inline TPoint3(const double v);
    
    inline TPoint3(const double x0, const double y0, const double z0);
    
    inline TPoint3(const TPoint3<T> &u);
    

    
    
    
    inline T & operator [](int i);
    
    inline const T &operator [](int i) const;
    

    
    
    
    inline bool operator == (const TPoint3<T> &u) const;
    
    inline bool operator != (const TPoint3<T> &u) const;
    
    inline bool LessOrEqual(const TPoint3<T> &u) const;
    
    inline bool operator < (const TPoint3<T> &u) const;
    
    inline static bool AboutEqual(const TPoint3<T> &v1, const TPoint3<T> &v2);
    
    inline static bool AboutEqual(const TPoint3<T> &v1, const TPoint3<T> &v2,
                       const double tolerance);
    
    inline bool IsOK() const;
    

    
    
    
    inline TPoint3<T> & operator = (const TPoint3<T> &u);
    

    
    
    
    inline TPoint3<T> & operator += (const TPoint3<T> &u);
    

    
    
    
    inline TPoint3<T> & operator += (const TVect3<T> &u);
    
    inline TPoint3<T> & operator -= (const TVect3<T> &u);
    

    
    
    
    inline TPoint3<T> & operator += (const double d);
    
    inline TPoint3<T> & operator -= (const double d);
    
    inline TPoint3<T> & operator *= (const double d);
    
    inline TPoint3<T> & operator /= (const double d);
    
    inline TPoint3<T> &AddWithWeight(const TVect3<T> &u, const double w);
    

    
    
    
    inline void Negate();
    
    inline TPoint3<T> operator -() const;
    

    
    
    
    
    
    inline TPoint3<T> operator + (const TPoint3<T> &u) const;
    
    inline TPoint3<T> operator + (const TVect3<T> &u) const;
    
    inline TPoint3<T> operator - (const TVect3<T> &u) const;
    
    
    inline TVect3<T> operator - (const TPoint3<T> &p) const;
    

    
    
    
    inline TPoint3<T> operator + (const double d) const;
    
    
    inline TPoint3<T> operator - (const double d) const;
    
    
    inline TPoint3<T> operator * (const double d) const;
    
    
    inline TPoint3<T> operator / (const double d) const;
    
    


    
    
    
    inline void Clip(double vmin, double vmax);
    
    inline bool ClipLower(double vmin);
    
    inline TPoint3<T> ValToRange(const T &vmin, const T &vmax) const;
    
    inline void Set(double x0, double y0, double z0);
    
    inline void Set(double a);
    

    
    
    
    inline operator T *();
    
    inline operator const T *() const;
    

    
    
    
    
    
    
    
    
    inline static const TPoint3<T> &Cast(const T *u);
    
    inline static TPoint3<T> &Cast(T *u);
    

    
    
    
    
    
    
    
    inline const TVect3<T> &Vector() const;
    
    inline TVect3<T> &Vector();
    

    
    
    
    static int NComponents();
    
  };  
















template <class T>
inline bool TPoint3<T>::AboutEqual(const TPoint3<T> &v1, const TPoint3<T> &v2)
  {
  return Math3<T>::AboutZero(v1 - v2, Math<T>::TOLERANCE);
  }













template <class T>
inline bool TPoint3<T>::AboutEqual(const TPoint3<T> &v1, const TPoint3<T> &v2,
                                 const double tolerance)
  {
  return Math3<T>::AboutZero(v1 - v2, tolerance);
  }



template <class T>
bool TPoint3<T>::IsOK() const
  {
  return (FloatIsOK(x) && FloatIsOK(y) && FloatIsOK(z));
  }











template <class T>
inline TPoint3<T> operator * (const double d, const TPoint3<T> &u)
  {
  return u * d;
  }







template <class T>
inline double SqrDist(const TPoint3<T> &a, const TPoint3<T> &b)
  {
  return SqrLength(a - b);
  }







template <class T>
inline double Dist(const TPoint3<T> &a, const TPoint3<T> &b)
  {
  return Length(a - b);
  }



template <class T>
inline TPoint3<T> Center(const TPoint3<T> &a, const TPoint3<T> &b);



template <class T>
inline TPoint3<T> Center(const TPoint3<T> &a, const TPoint3<T> &b,
                         const TPoint3<T> &c);


template <class T>
inline double TrgArea(const TPoint3<T> &a, const TPoint3<T> &b,
                         const TPoint3<T> &c);



template <class T>
inline double VertAngle(const TPoint3<T> &a, const TPoint3<T> &b,
                         const TPoint3<T> &c);







template <class T>
inline TPoint3<int> ConvI(const TPoint3<T> &u)
  {
  return TPoint3<int>(u.x, u.y, u.z);
  }







template <class T>
inline TPoint3<float> ConvF(const TPoint3<T> &u)
  {
  return TPoint3<float>(u.x, u.y, u.z);
  }







template <class T>
inline TPoint3<double> ConvD(const TPoint3<T> &u)
  {
  return TPoint3<double>(u.x, u.y, u.z);
  }




template <class T>
class BBox3
  {
  public:
    
    typedef T BaseType;

  public:

    
    TPoint3<T> vmin,
    
               vmax;

  public:

    
    
    
    inline BBox3();
    
    inline BBox3(const TPoint3<T> &point);
    
    inline BBox3(const TPoint3<T> &point1, const TPoint3<T> &point2);
    
    inline BBox3(const BBox3<T> &box);
    

    
    
    
    inline void Init(const TPoint3<T> &point);
    
    inline void Init(const TPoint3<T> &min, const TPoint3<T> &max);
    
    inline BBox3<T> & operator = (const BBox3<T> &box);
    

    
    BBox3<T> & operator *= (const double d);
    
    BBox3<T> & operator /= (const double d);

    
    
    
    inline bool operator == (const BBox3<T> &box) const;
    
    inline bool operator != (const BBox3<T> &box) const;
    

    
    
    
    inline void SetEmpty();
    
    inline bool NotEmpty() const;
    
    inline bool IsEmpty() const;
    
    inline bool IsDot() const;
    

    
    
    
    inline bool Includes(const TPoint3<T> &point) const;
    
    inline bool Includes(const BBox3<T> &box) const;
    
    inline bool Intersects(const BBox3<T> &box) const;
    
    int Intersects(const TPoint3<T> &point, const TVect3<T> &direction, T &distance, int side) const;
    


    
    
    
    inline void Include(const TPoint3<T> &point);
    
    inline void Include(const BBox3<T> &box);
    
    inline void Intersect(const BBox3<T> &box);
    
    inline void Translate(const TVect3<T> &vct);
    
    inline BBox3<T> Translated(const TVect3<T> &vct) const;
    
    BBox3<T> Transformed(const TMatrix43<T> &tm) const;
    
    inline TVect3<T> Diag() const;
    
    inline TPoint3<T> Center() const;
    
    inline double Volume() const;
    
    TPoint3<T> GetVertex(int ind) const;
    

  public:
    
    static const BBox3<T> &CVV();
  };  







template <class T>
inline BBox3<float> ConvF(const BBox3<T> &u)
  {
  return BBox3<float>(ConvF(u.vmin), ConvF(u.vmax));
  }







template <class T>
inline BBox3<double> ConvD(const BBox3<T> &u)
  {
  return BBox3<double>(ConvD(u.vmin), ConvD(u.vmax));
  }


template <class T>
class Math3 : public Math<T>
  {
  public:

    
    

    
    inline static bool AboutZero(const TVect3<T> &v, const double tolerance);

    
    inline static bool AboutZero(const TVect3<T> &v);

    
    inline static bool NearZero(const TVect3<T> &v);

    
    inline static bool AboutZero(const TPoint3<T> &v, const double tolerance);

    
    inline static bool AboutZero(const TPoint3<T> &v);

    
    inline static bool NearZero(const TPoint3<T> &v);

    

    
    

    
    inline static bool AboutEqual(const TVect3<T> &v1, const TVect3<T> &v2,
                       const double tolerance);

    
    inline static bool AboutEqual(const TVect3<T> &v1, const TVect3<T> &v2);

    
    inline static bool NearEqual(const TVect3<T> &v1, const TVect3<T> &v2);

    
    inline static bool AboutEqual(const TPoint3<T> &v1, const TPoint3<T> &v2,
                       const double tolerance);

    
    inline static bool AboutEqual(const TPoint3<T> &v1, const TPoint3<T> &v2);

    
    inline static bool NearEqual(const TPoint3<T> &v1, const TPoint3<T> &v2);

    

  };  







typedef BVect3<BYTE>      Set3b;

typedef BVect3<double>    Set3d;

typedef BVect3<float>     Set3f;



typedef BVect3<int>       Set3i;

typedef BVect3<unsigned>  Set3u;


typedef TVect3<short>     Vect3s;

typedef TVect3<int>       Vect3i;

typedef TVect3<float>     Vect3f;

typedef TVect3<double>    Vect3d;

typedef TVect3<unsigned>  Vect3u;


typedef TVect3<WORD>      Color3w;

typedef TVect3<short>     Color3s;

typedef TVect3<int>       Color3i;

typedef TVect3<float>     Color3f;

typedef TVect3<float>     RGBColor;

typedef TVect3<double>    Color3d;


typedef TPoint3<int>      Point3i;

typedef TPoint3<float>    Point3f;

typedef TPoint3<double>   Point3d;


typedef BBox3<int>        BBox3i;

typedef BBox3<float>      BBox3f;

typedef BBox3<double>     BBox3d;


typedef Math3<float>      Math3f;

typedef Math3<double>     Math3d;


Set3b DistinctColorGenerator(double seed, int col_ind, double v);











template <class T>
BVect3<T>::BVect3()
  {
  }






template <class T>
BVect3<T>::BVect3(const T &v)
  {
  x = v;
  y = v;
  z = v;
  }









template <class T>
BVect3<T>::BVect3(const T &x0, const T &y0, const T &z0)
  {
  x = x0;
  y = y0;
  z = z0;
  }




template <class T>
BVect3<T>::BVect3(const BVect3<T> &u)
  {
  x = u.x;
  y = u.y;
  z = u.z;
  }








template <class T>
T & BVect3<T>::operator [](int i)
  {
  Assert((i >= 0) && (i < 3));
  return (&x)[i];
  }








template <class T>
const T &BVect3<T>::operator [](int i) const
  {
  Assert((i >= 0) && (i < 3));
  return (&x)[i];
  }





template <class T>
int BVect3<T>::NComponents()
  {
  return 3;
  }







template <class T>
BVect3<T> & BVect3<T>::operator = (const BVect3<T> &u)
  {
  x = u.x;
  y = u.y;
  z = u.z;
  return *this;
  }






template <class T>
void BVect3<T>::Set(const T &x0, const T &y0, const T &z0)
  {
  x = x0;
  y = y0;
  z = z0;
  }







template <class T>
bool BVect3<T>::operator == (const BVect3<T> &u) const
  {
  return (x == u.x) && (y == u.y) && (z == u.z);
  }








template <class T>
bool BVect3<T>::operator != (const BVect3<T> &u) const
  {
  return (x != u.x) || (y != u.y) || (z != u.z);
  }









template <class T>
BVect3<T>::operator T *()
  {
  return &x;
  }









template <class T>
BVect3<T>::operator const T *() const
  {
  return &x;
  }








template <class T>
const BVect3<T> &BVect3<T>::Cast(const T *u)
  {
  return *(const BVect3<T> *)u;
  }








template <class T>
BVect3<T> &BVect3<T>::Cast(T *u)
  {
  return *(BVect3<T> *)u;
  }





template <class T>
T BVect3<T>::MaxElement() const
  {
  return Max3(x, y, z);
  }







template <class T>
TVect3<T>::TVect3()
  {
  }






template <class T>
TVect3<T>::TVect3(const T &v)
  {
  x = v;
  y = v;
  z = v;
  }









template <class T>
TVect3<T>::TVect3(const double x0, const double y0, const double z0)
  {
  x = (T)x0;
  y = (T)y0;
  z = (T)z0;
  }









template <class T>
TVect3<T>::TVect3(const TPoint3<T> &from, const TPoint3<T> &to)
  {
  *this = to - from;
  }





template <class T>
TVect3<T>::TVect3(const TVect3<T> &u)
  {
  x = u.x;
  y = u.y;
  z = u.z;
  }




template <class T>
TVect3<T>::TVect3(const BVect3<BYTE> &u)
  {
  x = u.x;
  y = u.y;
  z = u.z;
  }








template <class T>
T & TVect3<T>::operator [](int i)
  {
  Assert((i >= 0) && (i < 3));
  return (&x)[i];
  }








template <class T>
const T &TVect3<T>::operator [](int i) const
  {
  Assert((i >= 0) && (i < 3));
  return (&x)[i];
  }







template <class T>
bool TVect3<T>::operator == (const TVect3<T> &u) const
  {
  return (x == u.x) && (y == u.y) && (z == u.z);
  }








template <class T>
bool TVect3<T>::operator != (const TVect3<T> &u) const
  {
  return (x != u.x) || (y != u.y) || (z != u.z);
  }







template <class T>
bool TVect3<T>::LessOrEqual(const TVect3<T> &u) const
  {
#if 0
  return (x <= u.x) && (y <= u.y) && (z <= u.z);
#else
  return (z <= u.z) && (y <= u.y) && (x <= u.x);
#endif
  }













template <class T>
bool TVect3<T>::operator < (const TVect3<T> &u) const
  {
#if 0
  if (x < u.x)
    return true;
  if (x > u.x)
    return false;
  if (y < u.y)
    return true;
  if (y > u.y)
    return false;
  return z < u.z;
#else
  if (z < u.z)
    return true;
  if (z > u.z)
    return false;
  if (y < u.y)
    return true;
  if (y > u.y)
    return false;
  return x < u.x;
#endif
  }




template <class T>
bool TVect3<T>::IsPositiveComp() const
  {
  return (x > 0.0 || y > 0.0 || z > 0.0);
  }



template <class T>
bool TVect3<T>::IsZero() const
  {
  return x == 0 && y == 0 && z == 0;
  }








template <class T>
TVect3<T> & TVect3<T>::operator = (const TVect3<T> &u)
  {
  x = u.x;
  y = u.y;
  z = u.z;
  return *this;
  }








template <class T>
TVect3<T> & TVect3<T>::operator += (const TVect3<T> &u)
  {
  x += u.x;
  y += u.y;
  z += u.z;
  return *this;
  }









template <class T>
TVect3<T> & TVect3<T>::operator -= (const TVect3<T> &u)
  {
  x -= u.x;
  y -= u.y;
  z -= u.z;
  return *this;
  }








template <class T>
TVect3<T> & TVect3<T>::operator *= (const TVect3<T> &u)
  {
  x *= u.x;
  y *= u.y;
  z *= u.z;
  return *this;
  }











template <class T>
TVect3<T> &TVect3<T>::operator /= (const TVect3<T> &u)
  {
  Assert((u.x != 0) && (u.y != 0) && (u.z != 0));
  x /= u.x;
  y /= u.y;
  z /= u.z;
  return *this;
  }









template <class T>
TVect3<T> & TVect3<T>::operator += (const double d)
  {
  x = (T)(x + d);
  y = (T)(y + d);
  z = (T)(z + d);
  return *this;
  }









template <class T>
TVect3<T> & TVect3<T>::operator -= (const double d)
  {
  x = (T)(x - d);
  y = (T)(y - d);
  z = (T)(z - d);
  return *this;
  }









template <class T>
TVect3<T> & TVect3<T>::operator *= (const double d)
  {
  x = (T)(x * d);
  y = (T)(y * d);
  z = (T)(z * d);
  return *this;
  }











template <class T>
TVect3<T> &TVect3<T>::operator /= (const double d)
  {
  Assert(d != 0.0);
  x = (T)(x / d);
  y = (T)(y / d);
  z = (T)(z / d);
  return *this;
  }










template <class T>
TVect3<T> &TVect3<T>::AddWithWeight(const TVect3<T> &u, const double w)
  {
  x = (T)(x + u.x * w);
  y = (T)(y + u.y * w);
  z = (T)(z + u.z * w);
  return *this;
  }







template <class T>
void TVect3<T>::Negate()
  {
  x = -x;
  y = -y;
  z = -z;
  }









template <class T>
TVect3<T> TVect3<T>::operator -() const
  {
  return TVect3<T>(-x, -y, -z);
  }









template <class T>
TVect3<T> TVect3<T>::operator + (const TVect3<T> &u) const
  {
  return TVect3<T>(x + u.x, y + u.y, z + u.z);
  }









template <class T>
TVect3<T> TVect3<T>::operator - (const TVect3<T> &u) const
  {
  return TVect3<T>(x - u.x, y - u.y, z - u.z);
  }









template <class T>
TVect3<T> TVect3<T>::operator * (const TVect3<T> &u) const
  {
  return TVect3<T>(x * u.x, y * u.y, z * u.z);
  }












template <class T>
TVect3<T> TVect3<T>::operator / (const TVect3<T> &u) const
  {
  Assert((u.x != 0) && (u.y != 0) && (u.z != 0));
  return TVect3<T>(x / u.x, y / u.y, z / u.z);
  }








template <class T>
TVect3<T> TVect3<T>::operator + (const double d) const
  {
  return TVect3<T>((T)(x + d), (T)(y + d), (T)(z + d));
  }









template <class T>
TVect3<T> TVect3<T>::operator - (const double d) const
  {
  return TVect3<T>((T)(x - d), (T)(y - d), (T)(z - d));
  }









template <class T>
TVect3<T> TVect3<T>::operator * (const double d) const
  {
  return TVect3<T>((T)(x * d), (T)(y * d), (T)(z * d));
  }











template <class T>
TVect3<T> TVect3<T>::operator / (const double d) const
  {
  Assert(d != 0);
  return (*this) * (1/d);
  }





template <class T>
int TVect3<T>::NComponents()
  {
  return 3;
  }

















template <class T>
void TVect3<T>::Clip(double vmin, double vmax)
  {
  Assert(vmax >= vmin);
  Kiam::Clip(x, vmin, vmax);
  Kiam::Clip(y, vmin, vmax);
  Kiam::Clip(z, vmin, vmax);
  }






template <class T>
bool TVect3<T>::ClipLower(double vmin)
  {
  bool ret = false;
  if (Kiam::ClipLower(x, vmin))
    ret = true;
  if (Kiam::ClipLower(y, vmin))
    ret = true;
  if (Kiam::ClipLower(z, vmin))
    ret = true;
  return ret;
  }






template <class T>
bool TVect3<T>::ClipHigher(double vmax)
  {
  bool ret = false;
  if (Kiam::ClipHigher(x, vmax))
    ret = true;
  if (Kiam::ClipHigher(y, vmax))
    ret = true;
  if (Kiam::ClipHigher(z, vmax))
    ret = true;
  return ret;
  }














template <class T>
TVect3<T> TVect3<T>::ValToRange(const T &vmin, const T &vmax) const
  {
  Assert(vmax >= vmin);
  return TVect3<T>(
    Kiam::ValToRange(x, vmin, vmax),
    Kiam::ValToRange(y, vmin, vmax),
    Kiam::ValToRange(z, vmin, vmax));
  }














template <class T>
bool TVect3<T>::InRange(double vmin, double vmax) const
  {
  Assert(vmax >= vmin);
  return (x >= vmin && x <= vmax &&
          y >= vmin && y <= vmax &&
          z >= vmin && z <= vmax);
  }




template <class T>
bool TVect3<T>::IsOK() const
  {
  return (FloatIsOK(x) && FloatIsOK(y) && FloatIsOK(z));
  }







template <class T>
int TVect3<T>::MaxElementIndex() const
  {
  if ((Abs(x) >= Abs(y)) && (Abs(x) >= Abs(z)))
    return 0;
  if (Abs(y) >= Abs(z))
    return 1;
  return 2;
  }







template <class T>
int TVect3<T>::MinElementIndex() const
  {
  if ((Abs(x) <= Abs(y)) && (Abs(x) <= Abs(z)))
    return 0;
  if (Abs(y) <= Abs(z))
    return 1;
  return 2;
  }





template <class T>
T TVect3<T>::MaxElement() const
  {
  return Max3(Abs(x), Abs(y), Abs(z));
  }





template <class T>
T TVect3<T>::MaxVal() const
  {
  return Max3(x, y, z);
  }





template <class T>
T TVect3<T>::MinVal() const
  {
  return Min3(x, y, z);
  }










template <class T>
void TVect3<T>::Set(double x0, double y0, double z0)
  {
  x = (T)x0;
  y = (T)y0;
  z = (T)z0;
  }








template <class T>
void TVect3<T>::Set(double a)
  {
  x = y = z = (T)a;
  }






template <class T>
double TVect3<T>::SqrLength() const
  {
  return x * x + y * y + z * z;
  }






template <class T>
double TVect3<T>::Length() const
  {
  return Sqrt(SqrLength());
  }





template <class T>
T TVect3<T>::Sum() const
  {
  return (T)(x + y + z);
  }






template <class T>
double TVect3<T>::CIESum() const
  {
  return x * CIE_SUM_VECT[0] + y * CIE_SUM_VECT[1] + z * CIE_SUM_VECT[2];
  }



















template <class T>
TVect3<T> TVect3<T>::Project(const TVect3<T> &u) const
  {
  double sqr_len = DotProd(u, u);
  Assert(sqr_len > 0.0);
  return u * DotProd((*this), u) / sqr_len;
  }







inline double DotProdDF(const Vect3d &a, const Vect3f &b)
  {
  return a.x * b.x + a.y * b.y + a.z * b.z;
  }










template <class T>
TVect3<T> & TVect3<T>::Normalize()
  {
  double len = Length();
  Assert(len != 0.0);
  x = (T)(x / len);
  y = (T)(y / len);
  z = (T)(z / len);
  return *this;
  }











template <class T>
double TVect3<T>::ModNormalize()
  {
  double len = Length();
  if (len > 0.0)
    {
    x = (T)(x / len);
    y = (T)(y / len);
    z = (T)(z / len);
    }
  return len;
  }











template <class T>
double TVect3<T>::SumNormalize()
  {
  double sum = Sum();
  if (sum != 0.0)
    {
    x = (T)(x / sum);
    y = (T)(y / sum);
    z = (T)(z / sum);
    }
  else
    x = y = z = (T)(1.0 / 3.0);
  return sum;
  }
















template <class T>
double TVect3<T>::MaxNormalize()
  {
  double max = MaxElement();
  if (max != 0.0)
    {
    x = (T)(x / max);
    y = (T)(y / max);
    z = (T)(z / max);
    }
  else
    {
    x = 1;
    y = 1;
    z = 1;
    }
  return max;
  }









template <class T>
double TVect3<T>::CIENormalize()
  {
  double sum = CIESum();
  if (sum > 0.0)
    {
    x = (T)(x / sum);
    y = (T)(y / sum);
    z = (T)(z / sum);
    }
  return sum;
  }









template <class T>
bool TVect3<T>::Normalized() const
  {
  return MathF::AboutEqual(Length(), 1.0);
  }











template <class T>
void TVect3<T>::Orient(const TVect3<T> &v)
  {
  if (DotProd(*this, v) < 0)
    Negate();
  }



template <class T>
void TVect3<T>::Sort()
  {
  if (x > y)
    Swap(x, y);
  if (y > z)
    Swap(y, z);
  if (x > y)
    Swap(x, y);
  }












template <class T>
TVect3<T>::operator T *()
  {
  return &x;
  }












template <class T>
TVect3<T>::operator const T *() const
  {
  return &x;
  }








template <class T>
const TVect3<T> &TVect3<T>::Cast(const T *u)
  {
  return *(const TVect3<T> *)u;
  }








template <class T>
TVect3<T> &TVect3<T>::Cast(T *u)
  {
  return *(TVect3<T> *)u;
  }








template <class T>
const TPoint3<T> &TVect3<T>::Point() const
  {
  return TPoint3<T>::Cast(&x);
  }








template <class T>
TPoint3<T> &TVect3<T>::Point()
  {
  return TPoint3<T>::Cast(&x);
  }




















template <class T>
inline TVect3<T> CrossProd(const TVect3<T> &a, const TVect3<T> &b)
  {
  return TVect3<T>(a.y * b.z - a.z * b.y,
                   a.z * b.x - a.x * b.z,
                   a.x * b.y - a.y * b.x);
  }
  





template <class T>
inline TVect3<T> Max(const TVect3<T> &a, const TVect3<T> &b)
  {
  return TVect3<T>(Max(a.x, b.x), Max(a.y, b.y), Max(a.z, b.z));
  }
  








template <class T>
inline double Cos(const TVect3<T> &a, const TVect3<T> &b)
  {
  Assert((SqrLength(a) != 0) && (SqrLength(b) != 0));
  return Clipped(DotProd(a, b) / Sqrt(SqrLength(a) * SqrLength(b)), -1, 1);
  }









template <class T>
inline double Sin(const TVect3<T> &a, const TVect3<T> &b)
  {
  Assert((SqrLength(a) != 0) && (SqrLength(b) != 0));
  return Clipped(Sqrt(SqrLength(CrossProd(a, b)) /
                      (SqrLength(a) * SqrLength(b))),
                 0, 1);
  }







template <class T>
TPoint3<T>::TPoint3()
  {
  }






template <class T>
TPoint3<T>::TPoint3(const double v)
  {
  x = y = z = (T)v;
  }









template <class T>
TPoint3<T>::TPoint3(const double x0, const double y0, const double z0)
  {
  x = (T)x0;
  y = (T)y0;
  z = (T)z0;
  }





template <class T>
TPoint3<T>::TPoint3(const TPoint3<T> &u)
  {
  x = u.x;
  y = u.y;
  z = u.z;
  }








template <class T>
T & TPoint3<T>::operator [](int i)
  {
  Assert((i >= 0) && (i < 3));
  return (&x)[i];
  }








template <class T>
const T &TPoint3<T>::operator [](int i) const
  {
  Assert((i >= 0) && (i < 3));
  return (&x)[i];
  }





template <class T>
int TPoint3<T>::NComponents()
  {
  return 3;
  }







template <class T>
bool TPoint3<T>::operator == (const TPoint3<T> &u) const
  {
  return (x == u.x) && (y == u.y) && (z == u.z);
  }








template <class T>
bool TPoint3<T>::operator != (const TPoint3<T> &u) const
  {
  return (x != u.x) || (y != u.y) || (z != u.z);
  }







template <class T>
bool TPoint3<T>::LessOrEqual(const TPoint3<T> &u) const
  {
#if 0
  return (x <= u.x) && (y <= u.y) && (z <= u.z);
#else
  return (z <= u.z) && (y <= u.y) && (x <= u.x);
#endif
  }













template <class T>
bool TPoint3<T>::operator < (const TPoint3<T> &u) const
  {
#if 0
  if (x < u.x)
    return true;
  if (x > u.x)
    return false;
  if (y < u.y)
    return true;
  if (y > u.y)
    return false;
  return z < u.z;
#else
  if (z < u.z)
    return true;
  if (z > u.z)
    return false;
  if (y < u.y)
    return true;
  if (y > u.y)
    return false;
  return x < u.x;
#endif
  }







template <class T>
TPoint3<T> & TPoint3<T>::operator = (const TPoint3<T> &u)
  {
  x = u.x;
  y = u.y;
  z = u.z;
  return *this;
  }









template <class T>
TPoint3<T> & TPoint3<T>::operator += (const TPoint3<T> &u)
  {
  x += u.x;
  y += u.y;
  z += u.z;
  return *this;
  }









template <class T>
TPoint3<T> & TPoint3<T>::operator += (const TVect3<T> &u)
  {
  x += u.x;
  y += u.y;
  z += u.z;
  return *this;
  }











template <class T>
TPoint3<T> & TPoint3<T>::operator -= (const TVect3<T> &u)
  {
  x -= u.x;
  y -= u.y;
  z -= u.z;
  return *this;
  }









template <class T>
TPoint3<T> & TPoint3<T>::operator += (const double d)
  {
  x = (T)(x + d);
  y = (T)(y + d);
  z = (T)(z + d);
  return *this;
  }









template <class T>
TPoint3<T> & TPoint3<T>::operator -= (const double d)
  {
  x = (T)(x - d);
  y = (T)(y - d);
  z = (T)(z - d);
  return *this;
  }









template <class T>
TPoint3<T> & TPoint3<T>::operator *= (const double d)
  {
  x = (T)(x * d);
  y = (T)(y * d);
  z = (T)(z * d);
  return *this;
  }











template <class T>
TPoint3<T> &TPoint3<T>::operator /= (const double d)
  {
  Assert(d != 0.0);
  x = (T)(x / d);
  y = (T)(y / d);
  z = (T)(z / d);
  return *this;
  }










template <class T>
TPoint3<T> &TPoint3<T>::AddWithWeight(const TVect3<T> &u,
                                             const double w)
  {
  x = (T)(x + u.x * w);
  y = (T)(y + u.y * w);
  z = (T)(z + u.z * w);
  return *this;
  }








template <class T>
void TPoint3<T>::Negate()
  {
  x = -x;
  y = -y;
  z = -z;
  }









template <class T>
TPoint3<T> TPoint3<T>::operator -() const
  {
  return TPoint3<T>(-x, -y, -z);
  }





template <class T>
TPoint3<T> TPoint3<T>::operator + (const TPoint3<T> &u) const
  {
  return TPoint3<T>(x + u.x, y + u.y, z + u.z);
  }










template <class T>
TPoint3<T> TPoint3<T>::operator + (const TVect3<T> &u) const
  {
  return TPoint3<T>(x + u.x, y + u.y, z + u.z);
  }











template <class T>
TPoint3<T> TPoint3<T>::operator - (const TVect3<T> &u) const
  {
  return TPoint3<T>(x - u.x, y - u.y, z - u.z);
  }












template <class T>
TVect3<T> TPoint3<T>::operator - (const TPoint3<T> &p) const
  {
  return TVect3<T>(x - p.x, y - p.y, z - p.z);
  }








template <class T>
TPoint3<T> TPoint3<T>::operator + (const double d) const
  {
  return TPoint3<T>(x + d, y + d, z + d);
  }









template <class T>
TPoint3<T> TPoint3<T>::operator - (const double d) const
  {
  return TPoint3<T>(x - d, y - d, z - d);
  }









template <class T>
TPoint3<T> TPoint3<T>::operator * (const double d) const
  {
  return TPoint3<T>(x * d, y * d, z * d);
  }











template <class T>
TPoint3<T> TPoint3<T>::operator / (const double d) const
  {
  Assert(d != 0);
  return TPoint3<T>(x / d, y / d, z / d);
  }


















template <class T>
void TPoint3<T>::Clip(double vmin, double vmax)
  {
  Assert(vmax >= vmin);
  Kiam::Clip(x, vmin, vmax);
  Kiam::Clip(y, vmin, vmax);
  Kiam::Clip(z, vmin, vmax);
  }





template <class T>
bool TPoint3<T>::ClipLower(double vmin)
  {
  bool ret = false;
  if (Kiam::ClipLower(x, vmin))
    ret = true;
  if (Kiam::ClipLower(y, vmin))
    ret = true;
  if (Kiam::ClipLower(z, vmin))
    ret = true;
  return ret;
  }














template <class T>
TPoint3<T> TPoint3<T>::ValToRange(const T &vmin, const T &vmax) const
  {
  Assert(vmax >= vmin);
  return TPoint3<T>(
    Kiam::ValToRange(x, vmin, vmax),
    Kiam::ValToRange(y, vmin, vmax),
    Kiam::ValToRange(z, vmin, vmax));
  }










template <class T>
void TPoint3<T>::Set(double x0, double y0, double z0)
  {
  x = (T)x0;
  y = (T)y0;
  z = (T)z0;
  }








template <class T>
void TPoint3<T>::Set(double a)
  {
  x = y = z = (T)a;
  }












template <class T>
TPoint3<T>::operator T *()
  {
  return &x;
  }












template <class T>
TPoint3<T>::operator const T *() const
  {
  return &x;
  }








template <class T>
const TPoint3<T> &TPoint3<T>::Cast(const T *u)
  {
  return *(const TPoint3<T> *)u;
  }








template <class T>
TPoint3<T> &TPoint3<T>::Cast(T *u)
  {
  return *(TPoint3<T> *)u;
  }








template <class T>
const TVect3<T> &TPoint3<T>::Vector() const
  {
  return TVect3<T>::Cast(&x);
  }








template <class T>
TVect3<T> &TPoint3<T>::Vector()
  {
  return TVect3<T>::Cast(&x);
  }











template <class T>
inline TPoint3<T> Center(const TPoint3<T> &a, const TPoint3<T> &b)
  {
  return ((a.Vector() + b.Vector()) / 2.0).Point();
  }












template <class T>
inline TPoint3<T> Center(const TPoint3<T> &a, const TPoint3<T> &b,
                         const TPoint3<T> &c)
  {
  return ((a.Vector() + b.Vector() + c.Vector()) / 3.0).Point();
  }













template <class T>
inline double TrgArea(const TPoint3<T> &a, const TPoint3<T> &b,
                         const TPoint3<T> &c)
  {
  return Length(CrossProd(a - b, a - c)) / 2;
  }











template <class T>
inline double VertAngle(const TPoint3<T> &a, const TPoint3<T> &b,
                         const TPoint3<T> &c)
  {
  TVect3<T> v1 = b - a;
  TVect3<T> v2 = c - a;
  double sin_ang = Length(CrossProd(v1, v2));
  double cos_ang = DotProd(v1, v2);
  return atan2(sin_ang, cos_ang);
  }



















template <class T>
inline Vect3d BaryCoords(const TPoint3<T> &p1, const TPoint3<T> &p2,
                         const TPoint3<T> &p3, const TPoint3<T> &p)
  {
  TVect3<T> cp0 = CrossProd(p2 - p1, p3 - p1); 
  TVect3<T> cp1 = CrossProd(p2 - p, p3 - p); 
  TVect3<T> cp2 = CrossProd(p3 - p, p1 - p); 
  TVect3<T> cp3 = CrossProd(p1 - p, p2 - p); 
  double dp0 = DotProd(cp0, cp0); 
  Vect3d bary(DotProd(cp1, cp0) / dp0, DotProd(cp2, cp0) / dp0, DotProd(cp3, cp0) / dp0);

  return bary;
  }











inline Vect3d operator - (const Point3d &p1, const Point3f &p2) 
  {
  return Vect3d(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
  }







template <class T>
BBox3<T>::BBox3()
  {
  }








template <class T>
BBox3<T>::BBox3(const TPoint3<T> &point)
  {
  vmin = vmax = point;
  }








template <class T>
BBox3<T>::BBox3(const TPoint3<T> &point1, const TPoint3<T> &point2)
  {
  vmin = point1; 
  vmax = point2;
  }





template <class T>
BBox3<T>::BBox3(const BBox3<T> &box)
  {
  vmin = box.vmin;
  vmax = box.vmax;
  }




template <class T>
void BBox3<T>::Init(const TPoint3<T> &point)
  {
  vmin = vmax = point;
  }





template <class T>
void BBox3<T>::Init(const TPoint3<T> &min, const TPoint3<T> &max)
  {
  vmin = min;
  vmax = max;
  }









template <class T>
BBox3<T> & BBox3<T>::operator = (const BBox3<T> &box)
  {
  vmin = box.vmin;
  vmax = box.vmax;
  return *this;
  }









template <class T>
bool BBox3<T>::operator == (const BBox3<T> &box) const
  {
  return (vmin == box.vmin) && (vmax == box.vmax);
  }










template <class T>
bool BBox3<T>::operator != (const BBox3<T> &box) const
  {
  return (vmin != box.vmin) || (vmax != box.vmax);
  }











template <class T>
bool BBox3<T>::NotEmpty() const
  {
  return (vmin.x <= vmax.x) && (vmin.y <= vmax.y) && (vmin.z <= vmax.z);
  }







template <class T>
bool BBox3<T>::IsEmpty() const
  {
  return (vmin.x > vmax.x) || (vmin.y > vmax.y) || (vmin.z > vmax.z);
  }



template <class T>
void BBox3<T>::SetEmpty()
  {
  vmin.x = vmin.y = vmin.z = 1;
  vmax.x = vmax.y = vmax.z = -1;
  }











template <class T>
bool BBox3<T>::IsDot() const
  {
  return vmin == vmax;
  }















template <class T>
bool BBox3<T>::Includes(const TPoint3<T> &point) const
  {
  return (vmin.LessOrEqual(point)) && (point.LessOrEqual(vmax));
  }










template <class T>
bool BBox3<T>::Includes(const BBox3<T> &box) const
  {
  return (vmin.LessOrEqual(box.vmin)) && (box.vmax.LessOrEqual(vmax));
  }









template <class T>
bool BBox3<T>::Intersects(const BBox3<T> &box) const
  {
  return (vmin.LessOrEqual(box.vmax)) && (box.vmin.LessOrEqual(vmax));
  }












template <class T>
void BBox3<T>::Include(const TPoint3<T> &point)
  {
  if (point.x < vmin.x)
    vmin.x = point.x;
  if (vmax.x < point.x)
    vmax.x = point.x;
  if (point.y < vmin.y)
    vmin.y = point.y;
  if (vmax.y < point.y)
    vmax.y = point.y;
  if (point.z < vmin.z)
    vmin.z = point.z;
  if (vmax.z < point.z)
    vmax.z = point.z;
  }














template <class T>
void BBox3<T>::Include(const BBox3<T> &box)
  {
  if (box.IsEmpty())
    return;
  if (this->IsEmpty())
    {
    (*this) = box;
    return;
    }
  if (vmin.x > box.vmin.x)
    vmin.x = box.vmin.x;
  if (vmax.x < box.vmax.x)
    vmax.x = box.vmax.x;
  if (vmin.y > box.vmin.y)
    vmin.y = box.vmin.y;
  if (vmax.y < box.vmax.y)
    vmax.y = box.vmax.y;
  if (vmin.z > box.vmin.z)
    vmin.z = box.vmin.z;
  if (vmax.z < box.vmax.z)
    vmax.z = box.vmax.z;
  }











template <class T>
void BBox3<T>::Intersect(const BBox3<T> &box)
  {
  if (vmin.x < box.vmin.x)
    vmin.x = box.vmin.x;
  if (vmax.x > box.vmax.x)
    vmax.x = box.vmax.x;
  if (vmin.y < box.vmin.y)
    vmin.y = box.vmin.y;
  if (vmax.y > box.vmax.y)
    vmax.y = box.vmax.y;
  if (vmin.z < box.vmin.z)
    vmin.z = box.vmin.z;
  if (vmax.z > box.vmax.z)
    vmax.z = box.vmax.z;
  }











template <class T>
void BBox3<T>::Translate(const TVect3<T> &vct)
  {
  vmin += vct; vmax += vct;
  }











template <class T>
BBox3<T> BBox3<T>::Translated(const TVect3<T> &vct) const
  {
  return BBox3<T>(vmin + vct, vmax + vct);
  }









template <class T>
TVect3<T> BBox3<T>::Diag() const
  {
  return vmax - vmin;
  }









template <class T>
TPoint3<T> BBox3<T>::Center() const
  {
  return Kiam::Center(vmax, vmin);
  }








template <class T>
double BBox3<T>::Volume() const
  {
  return (vmax.x - vmin.x) * (vmax.y - vmin.y) * (vmax.z - vmin.z);
  }












template <class T>
inline bool Math3<T>::AboutZero(const TVect3<T> &v, const double tolerance)
  {
  return Math<T>::AboutZero(v.x, tolerance) &&
         Math<T>::AboutZero(v.y, tolerance) &&
         Math<T>::AboutZero(v.z, tolerance);
  }







template <class T>
inline bool Math3<T>::AboutZero(const TVect3<T> &v)
  {
  return AboutZero(v, Math3<T>::TOLERANCE);
  }








template <class T>
inline bool Math3<T>::NearZero(const TVect3<T> &v)
  {
  return AboutZero(v, EPSILON);
  }








template <class T>
inline bool Math3<T>::AboutZero(const TPoint3<T> &v, const double tolerance)
  {
  return Math<T>::AboutZero(v.x, tolerance) &&
         Math<T>::AboutZero(v.y, tolerance) &&
         Math<T>::AboutZero(v.z, tolerance);
  }







template <class T>
inline bool Math3<T>::AboutZero(const TPoint3<T> &v)
  {
  return AboutZero(v, Math3<T>::TOLERANCE);
  }








template <class T>
inline bool Math3<T>::NearZero(const TPoint3<T> &v)
  {
  return AboutZero(v, EPSILON);
  }













template <class T>
inline bool Math3<T>::AboutEqual(const TVect3<T> &v1, const TVect3<T> &v2,
                                 const double tolerance)
  {
  return AboutZero(v1 - v2, tolerance);
  }












template <class T>
inline bool Math3<T>::AboutEqual(const TVect3<T> &v1, const TVect3<T> &v2)
  {
  return AboutZero(v1 - v2, Math3<T>::TOLERANCE);
  }













template <class T>
inline bool Math3<T>::NearEqual(const TVect3<T> &v1, const TVect3<T> &v2)
  {
  return AboutZero(v1 - v2, EPSILON);
  }













template <class T>
inline bool Math3<T>::AboutEqual(const TPoint3<T> &v1, const TPoint3<T> &v2,
                                 const double tolerance)
  {
  return AboutZero(v1 - v2, tolerance);
  }












template <class T>
inline bool Math3<T>::AboutEqual(const TPoint3<T> &v1, const TPoint3<T> &v2)
  {
  return AboutZero(v1 - v2, Math3<T>::TOLERANCE);
  }













template <class T>
inline bool Math3<T>::NearEqual(const TPoint3<T> &v1, const TPoint3<T> &v2)
  {
  return AboutZero(v1 - v2, EPSILON);
  }

KIAM_NAMESPACE_END
#endif

