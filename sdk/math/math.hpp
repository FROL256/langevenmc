











#ifndef _KLBC_MATH_HPP_
#define _KLBC_MATH_HPP_


#include <math.h>
#include <float.h>

KIAM_NAMESPACE_START

#ifdef EPSILON
#undef EPSILON
#endif

#ifdef EPSILON_DIV_10
#undef EPSILON_DIV_10  
#endif

#ifdef EPSILON_POW_2
#undef EPSILON_POW_2
#endif

#ifdef PI
#undef PI
#endif

#ifdef REV_PI
#undef REV_PI
#endif

#ifdef PI2
#undef PI2
#endif

#ifdef HALFPI
#undef HALFPI
#endif

#ifdef SQRT2
#undef SQRT2
#endif

#ifdef SQRT3
#undef SQRT3
#endif

#ifdef REV_BYTE
#undef REV_BYTE
#endif








#define EPSILON                0.0001


#define EPSILON_POW_2          0.00000001




#define PI                     3.1415926535897932


#define REV_PI                 0.3183098861837907   


#define PI2                    6.2831853071795865   
#define HALFPI                 1.5707963267948966192313216916398

#define SQRT2                  1.4142135623730950


#define SQRT3                  1.7320508075688773




#define REV_BYTE               0.0039215686274510   







inline int NumLen(INT64 a);


inline int Round(double a);

inline double PRound(double a, int prec);


inline double Rad(double a);


inline double Deg(double a);


inline int Sign(double a);


inline double Sqrt(double a);


inline double Cbrt(double a);


inline double Log(double a);


inline double Log10(double a);


inline double Log2(double a);


inline double Pow(double x, double y);


inline double Sin(double v);

inline double Cos(double v);

inline double Tan(double v);


inline double ASin(double x);

inline double ACos(double x);

inline double ATan(double x);

inline double ATan2(double y, double x);


inline double Exp(double x);







template <class T>
inline T Abs(const T &a);


template <class T>
inline T Sqr(const T &a);


template <class T>
inline T Cube(const T &a);


template <class T>
inline void Clip(T &v, const double a_min, const double a_max);


template <class T>
inline bool ClipLower(T &v, double a_min);


template <class T>
inline bool ClipHigher(T &v, double a_max);


template <class T>
inline T ValToRange(const T &v, const T &vmin, const T &vmax);


template <class T>
inline T Clipped(const T &v, const double a_min, const double a_max);


template <class T>
inline bool InRange(const T &v, const double a_min, const double a_max);


template <class T>
inline bool FloatIsOK(const T val)
  {
  return (_finite(val) != 0);
  }


template<class T>
class Math
  {

  public:

    
    
    
    static const double TOLERANCE;
    
    static const double MIN_VALUE;
    
    static const double MAX_VALUE;
    
    static const double EPS_VALUE;
    


    
    
    
    inline static bool AboutZero(const double v, const double tolerance);
    
    inline static bool AboutZero(const double v);
    
    inline static bool NearZero(const double v);
    

    
    
    
    inline static bool AboutEqual(const double v1, const double v2,
                       const double tolerance);
    
    inline static bool AboutEqual(const double v1, const double v2);
    
    inline static bool NearEqual(const double v1, const double v2);
    

    
    
    
    inline static int SignAbout(const double v, const double tolerance);
    
    inline static int SignAbout(const double v);
    
    inline static int SignNear(const double v);
    

  };  


template <class T>
class BBox1
  {

  public:

    
    T vmin,
    
      vmax;

  public:

    
    
    
    inline BBox1();

    
    inline BBox1(const double point);

    
    inline BBox1(const double point1, const double point2);

    

    
    

    
    inline BBox1<T> & operator = (const BBox1<T> &box);

    

    
    

    
    inline bool operator == (const BBox1<T> &box) const;

    
    inline bool operator != (const BBox1<T> &box) const;

    

    
    

    
    inline bool NotEmpty() const;

    
    inline bool IsDot() const;

    

    
    

    
    inline bool Includes(const double point) const;

    
    inline bool Includes(const BBox1<T> &box) const;

    
    inline bool Intersects(const BBox1<T> &box) const;

    

    
    

    
    inline void Include(const double point);

    
    inline void Include(const BBox1<T> &box);

    
    inline void Intersect(const BBox1<T> &box);

    
    inline void Translate(const double vct);

    
    inline BBox1<T> Translated(const double vct) const;

    
    inline double Diag() const;

    
    inline double Center() const;

    

  };  






typedef Math<double> MathD;

typedef Math<float>  MathF;

typedef Math<int>  MathI;

typedef Math<WORD>  MathW;


typedef BBox1<int>    BBox1i;

typedef BBox1<float>  BBox1f;

typedef BBox1<double> BBox1d;







inline int NumLen(INT64 a)
  {
  a = abs(a);
  if (a == 0)
    return 1;
  return (int)Log10((double)a) + 1;
  }





int Round(double a)
  {
  return (int)((a) > 0.0 ? (a) + 0.5 : (a) - 0.5);
  }






double PRound(double a, int prec)
  {
  if (a == 0)
    return 0;
  double p = prec - 1 - floor(Log10(fabs(a)));
  double p10 = Pow(10, p);
  return floor(a * p10 + 0.5 ) / p10;
  }





double Rad(double a)
  {
  return a * PI / 180.0;
  }





double Deg(double a)
  {
  return a * 180.0 / PI;
  }








int Sign(double a)
  {
  return (a > 0.0) ? 1 : ((a == 0.0) ? 0 : -1);
  }






double Sqrt(double a)
  {
  Assert(a >= 0);  
  
  
  a = (a > 0.0) ? a : 0.0;
  return sqrt(a);
  }






double Cbrt(double a)
  {
  static const double THIRD = 1.0 / 3.0;
  if (a > 0)
    return Pow(a, THIRD);
  if (a < 0)
    return -Pow(-a, THIRD);
  return 0;
  }








double Log(double a)
  {
  Assert((0.0 < a) && (a < MathD::MAX_VALUE));  
  return log(a);
  }








double Log10(double a)
  {
  Assert((0.0 < a) && (a < MathD::MAX_VALUE));  
  return log10(a);
  }








double Log2(double a)
  {
  static const double c = 1 / log(2.0);
  Assert((0.0 < a) && (a < MathD::MAX_VALUE));  
  return c * log(a);
  }







double Pow(double x, double y)
  {
  
  
  
  
  Assert(x < MathF::MAX_VALUE);
  Assert(Abs(y) < MathF::MAX_VALUE);
  return pow(x, y);
  }





double Sin(double v)
  {
  return sin(v);
  }





double Cos(double v)
  {
  return cos(v);
  }





double Tan(double v)
  {
  return tan(v);
  }









double ASin(double x)
  {
  Assert((-1.0 <= x) && (x <= 1.0));
  return asin(x);
  }  









double ACos(double x)
  {
  Assert((-1.0 <= x) && (x <= 1.0));
  return acos(x);
  }  





double ATan(double x)
  {
  return atan(x);
  }





double ATan2(double y, double x)
  {
  return atan2(y, x);
  }





double Exp(double x)
  {
  return exp(x);
  }













template <class T>
T Abs(const T &a)
  {
  return ((a) >= (T)0) ? (a) : -(a);
  }







template <class T>
T Sqr(const T &a)
  {
  return a * a;
  }







template <class T>
T Cube(const T &a)
  {
  return a * a * a;
  }














template <class T>
void Clip(T &v, const double a_min, const double a_max)
  {
  if (v < (T)a_min)
    v = (T)a_min;
  if (v > (T)a_max)
    v = (T)a_max;
  }






template <class T>
bool ClipLower(T &v, double a_min)
  {
  if (v < (T)a_min)
    {
    v = (T)a_min;
    return true;
    }
  return false;
  }






template <class T>
bool ClipHigher(T &v, double a_max)
  {
  if (v > (T)a_max)
    {
    v = (T)a_max;
    return true;
    }
  return false;
  }














template <class T>
inline T ValToRange(const T &v, const T &vmin, const T &vmax)
  {
  if (v < vmin)
    return vmin;
  if (v > vmax)
    return vmax;
  return v;
  }














template <class T>
T Clipped(const T &v, const double a_min, const double a_max)
  {
  if (v < (T)a_min)
    return (T)a_min;
  if (v > (T)a_max)
    return (T)a_max;
  return v;
  }










template <class T>
bool InRange(const T &v, const double a_min, const double a_max)
  {
  return (v >= a_min && v <= a_max);
  }





template <class T>
void Round(T &v, double level)
  {
  Assert(level != 0);
  if (v >= 0)
    v = T(floor(v / level + 0.5) * level);
  else
    v = T(ceil(v / level - 0.5) * level);
  }












template <class T>
bool Math<T>::AboutZero(const double v, const double tolerance)
  {
  return ((-tolerance <= v) && (v <= tolerance));
  }








template <class T>
bool Math<T>::AboutZero(const double v)
  {
  return AboutZero(v, TOLERANCE);
  }








template <class T>
bool Math<T>::NearZero(const double v)
  {
  return AboutZero(v, EPSILON);
  }









template <class T>
bool Math<T>::AboutEqual(const double v1, const double v2,
                            const double tolerance)
  {
  return AboutZero(v1 - v2, tolerance);
  }









template <class T>
bool Math<T>::AboutEqual(const double v1, const double v2)
  {
  return AboutZero(v1 - v2, TOLERANCE);
  }









template <class T>
bool Math<T>::NearEqual(const double v1, const double v2)
  {
  return AboutZero(v1 - v2, EPSILON);
  }










template <class T>
int Math<T>::SignAbout(const double v, const double tolerance)
  {
  if (v >= tolerance)
    return 1;
  if (v <= -tolerance)
    return -1;
  return 0;
  }









template <class T>
int Math<T>::SignAbout(const double v)
  {
  return SignAbout(v, TOLERANCE);
  }










template <class T>
int Math<T>::SignNear(const double v)
  {
  return SignAbout(v, EPSILON);
  }







template <class T>
BBox1<T>::BBox1()
  {
  }







template <class T>
BBox1<T>::BBox1(const double point)
  {
  vmin = vmax = (T)point;
  }








template <class T>
BBox1<T>::BBox1(const double point1, const double point2)
  {
  vmin = (T)point1;
  vmax = (T)point2;
  }









template <class T>
BBox1<T> & BBox1<T>::operator = (const BBox1<T> &box)
  {
  vmin = box.vmin;
  vmax = box.vmax; return *this;
  }









template <class T>
bool BBox1<T>::operator == (const BBox1<T> &box) const
  {
  return (vmin == box.vmin) && (vmax == box.vmax);
  }










template <class T>
bool BBox1<T>::operator != (const BBox1<T> &box) const
  {
  return (vmin != box.vmin) || (vmax != box.vmax);
  }









template <class T>
bool BBox1<T>::NotEmpty() const
  {
  return (vmin <= vmax) ? true : false;
  }










template <class T>
bool BBox1<T>::IsDot() const
  {
  return vmin == vmax;
  }











template <class T>
bool BBox1<T>::Includes(const double point) const
  {
  return (vmin <= point && point <= vmax) ? true : false;
  }










template <class T>
bool BBox1<T>::Includes(const BBox1<T> &box) const
  {
  return (vmin <= box.vmin && box.vmax <= vmax) ? true : false;
  }











template <class T>
bool BBox1<T>::Intersects(const BBox1<T> &box) const
  {
  return (vmin <= box.vmax && box.vmin <= vmax) ? true : false;
  }











template <class T>
void BBox1<T>::Include(const double point)
  {
  if (point < vmin)
    vmin = (T)point;
  if (vmax < point)
    vmax = (T)point;
  }










template <class T>
void BBox1<T>::Include(const BBox1<T> &box)
  {
  if (vmin > box.vmin)
    vmin = box.vmin;
  if (vmax < box.vmax)
    vmax = box.vmax;
  }











template <class T>
void BBox1<T>::Intersect(const BBox1<T> &box)
  {
  if (vmin < box.vmin)
    vmin = box.vmin;
  if (vmax > box.vmax)
    vmax = box.vmax;
  }















template <class T>
void BBox1<T>::Translate(const double vct)
  {
  vmin = (T)(vmin + vct);
  vmax = (T)(vmax + vct);
  }














template <class T>
BBox1<T> BBox1<T>::Translated(const double vct) const
  {
  return BBox1<T>(vmin + vct, vmax + vct);
  }









template <class T>
double BBox1<T>::Diag() const
  {
  return (double)vmax - (double)vmin;
  }








template <class T>
double BBox1<T>::Center() const
  {
  return ((double)vmax + (double)vmin) / 2;
  }

KIAM_NAMESPACE_END
#endif

