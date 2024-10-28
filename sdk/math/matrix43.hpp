










#ifndef _KLBC_MATRIX43_HPP_
#define _KLBC_MATRIX43_HPP_

#include "matrix3.hpp"

KIAM_NAMESPACE_START






template <class T>
class TMatrix43
  {
  public:

    
    enum TransformationType
      {
      
      GENERAL_TRANSFORM,
      
      TRANSLATION_TRANSFORM,
      
      IDENTITY_TRANSFORM,
      
      SCALE_TRANSLATION_TRANSFORM
      };

    
    
    
    inline TMatrix43();
    
    inline explicit TMatrix43(const double val);
    
    inline TMatrix43(const double a, const double b, const double c);
    
    inline TMatrix43(const TMatrix3<T> &rm, const TVect3<T> &tr);
    
    inline TMatrix43(const TVect3<T> &x_vect, const TVect3<T> &y_vect, const TVect3<T> &z_vect, const TVect3<T> &tr);
    
    

    
    
    
    inline TVect3<T> &operator [] (int i);
    
    inline const TVect3<T> &operator [] (int i) const;
    
    inline const TMatrix3<T> &Matrix3() const;
    
    inline TMatrix3<T> &Matrix3();
    
    inline void SetMatrix3(const TMatrix3<T> &mat);
    
    inline const TVect3<T> &GetTrans() const;
    
    inline void SetTrans(const TVect3<T> &transl);
    
    inline void SetTrans(const TPoint3<T> &transl);
    

    
    
    
    inline bool operator == (const TMatrix43<T> &u) const;
    
    inline bool operator != (const TMatrix43<T> &u) const;
    

    
    
    
    inline static bool AboutEqual(const TMatrix43<T> &a, const TMatrix43<T> &b);
    
    inline static bool AboutEqual(const TMatrix43<T> &a, const TMatrix43<T> &b, const double tolerance);
    

    
    
    
    inline TMatrix43<T> operator + (const TMatrix43<T> &u) const;
    
    inline TMatrix43<T> operator - (const TMatrix43<T> &u) const;
    
    inline TMatrix43<T> operator * (const double d) const;
    
    inline TMatrix43<T> operator * (const TMatrix43<T> &u) const;
    
    inline TMatrix43<T> operator / (const double d) const;
    

    
    
    
    inline void VectorTransform(TVect3<T> &u) const;
    
    inline TVect3<T> VectorTransformed(const TVect3<T> &u) const;
    
    inline TVect3<T> VectorScaled(const TVect3<T> &u) const;
    
    inline TVect3<T> VectorBackRotTransformed(const TVect3<T> &u) const;
    
    inline TPoint3<T> PointBackRotTransformed(const TPoint3<T> &p) const;
    
    inline void PointTransform(TPoint3<T> &p) const;
    
    inline TPoint3<T> PointTransformed(const TPoint3<T> &p) const;
    
    inline TPoint3<T> PointScaledAndTranslated(const TPoint3<T> &p) const;
    
    inline TPoint3<T> PointTranslated(const TPoint3<T> &p) const;
    
    void BBoxTransform(BBox3<T> &bbox) const;
    

    
    
    
    inline void Identity();
    
    inline bool IsIdentity() const;
    
    inline bool AboutIdentity(const double tolerance = Math<T>::TOLERANCE) const;
    
    inline bool IsOnlyTranslation() const;
    
    inline bool IsOnlyScaleAndTranslation() const;
    
    inline TransformationType GetTransformationType() const;
    

    
    
    
    inline TMatrix43<T> & operator = (const TMatrix43<T> &u);
    
    inline TMatrix43<T> & operator += (const TMatrix43<T> &u);
    
    inline TMatrix43<T> & operator -= (const TMatrix43<T> &u);
    
    inline TMatrix43<T> & operator *= (const double d);
    
    inline TMatrix43<T> & operator *= (const TMatrix43<T> &u);
    
    inline TMatrix43<T> & operator /= (const double d);
    

    
    
    
    inline TMatrix43<T> Inversed() const;
    
    inline void InverseRot();
    
    inline TMatrix43<T> InversedForRotMat() const;
    

    
    
    
    
    
    
    inline TMatrix43<T> &RotationX(double angle);
    
    inline TMatrix43<T> &RotationY(double angle);
    
    inline TMatrix43<T> &RotationZ(double angle);
    
    inline TMatrix43<T> &RotationAxis(const TVect3<T> &u, double angle);
    
    inline TMatrix43<T> &GenRotation(const TVect3<T> &ux, const TVect3<T> &uy, const TVect3<T> &uz);
    
    inline TMatrix43<T> &Translation(const TVect3<T> &u);
    
    inline TMatrix43<T> &Scale(const double x, const double y, const double z);
    
    TMatrix43<T> &ViewMatrix(const TVect3<T> &obs, const TVect3<T> &view, const TVect3<T> &up);
    


    
    
    
    static const TMatrix43<T> &E();
    

    
    void ConvertToEulerTransformValues(Vect3d &translation, 
      double &azimuth, double &tilt, double &rotation, Vect3d &scale) const;

  private:
    
    
    
    TMatrix3<T> m;
    
    TVect3<T> v;
    
  };  






typedef TMatrix43<float>  Matrix43f;

typedef TMatrix43<double> Matrix43d;



template <class T>
TMatrix43<T>::TMatrix43()
  {
  }








template <class T>
TMatrix43<T>::TMatrix43(const double val) 
  : 
  m(val), 
  v(0)
  {
  }












template <class T>
TMatrix43<T>::TMatrix43(const double a, const double b, const double c)
  : 
  m(a, b, c), 
  v(0)
  {
  }










template <class T>
TMatrix43<T>::TMatrix43(const TMatrix3<T> &rm, const TVect3<T> &tr)
  : 
  m(rm), 
  v(tr)
  {
  }







template <class T>
TMatrix43<T>::TMatrix43(const TVect3<T> &x_vect, const TVect3<T> &y_vect, const TVect3<T> &z_vect, const TVect3<T> &tr)
  : 
  m(x_vect, y_vect, z_vect), 
  v(tr)
  {
  }
  







template <class T>
TVect3<T> &TMatrix43<T>::operator [] (int i)
  {
  Assert(i >= 0 && i < 4);;
  return (i < 3) ? m[i] : v;
  }








template <class T>
const TVect3<T> &TMatrix43<T>::operator [] (int i) const
  {
  Assert(i >= 0 && i < 4);;
  return (i < 3) ? m[i] : v;
  }









template <class T>
const TMatrix3<T> &TMatrix43<T>::Matrix3() const
  {
  return m;
  }









template <class T>
TMatrix3<T> &TMatrix43<T>::Matrix3()
  {
  return m;
  }









template <class T>
void TMatrix43<T>::SetMatrix3(const TMatrix3<T> &mat)
  {
  m = mat;
  }









template <class T>
const TVect3<T> &TMatrix43<T>::GetTrans() const
  {
  return v;
  }









template <class T>
void TMatrix43<T>::SetTrans(const TVect3<T> &transl)
  {
  v = transl;
  }









template <class T>
void TMatrix43<T>::SetTrans(const TPoint3<T> &transl)
  {
  v = transl.Vector();
  }











template <class T>
bool TMatrix43<T>::operator == (const TMatrix43<T> &u) const
  {
  return (m == u.m) && (v == u.v);
  }











template <class T>
bool TMatrix43<T>::operator != (const TMatrix43<T> &u) const
  {
  return (m != u.m) || (v != u.v);
  }













template <class T>
bool TMatrix43<T>::AboutEqual(const TMatrix43<T> &a, const TMatrix43<T> &b)
  { return (TMatrix3<T>::AboutEqual(a.Matrix3(), b.Matrix3()) &&
           Math3<T>::AboutEqual(a.GetTrans(), b.GetTrans()));
  }













template <class T>
bool TMatrix43<T>::AboutEqual(const TMatrix43<T> &a, const TMatrix43<T> &b,
                              const double tolerance)
  { return (TMatrix3<T>::AboutEqual(a.Matrix3(), b.Matrix3(), tolerance) &&
           Math3<T>::AboutEqual(a.GetTrans(), b.GetTrans(), tolerance));
  }










template <class T>
TMatrix43<T> TMatrix43<T>::operator + (const TMatrix43<T> &u) const
  {
  TMatrix43<T> res;
  res.m = m + u.m;
  res.v = v + u.v;
  return res;
  }










template <class T>
TMatrix43<T> TMatrix43<T>::operator - (const TMatrix43<T> &u) const
  {
  TMatrix43<T> res;
  res.m = m - u.m;
  res.v = v - u.v;
  return res;
  }









template <class T>
TMatrix43<T> TMatrix43<T>::operator * (const double d) const
  {
  TMatrix43<T> res;
  res.m = m * d;
  res.v = v * d;
  return res;
  }











template <class T>
void TMatrix43<T>::VectorTransform(TVect3<T> &u) const
  {
  u = u * m;
  }












template <class T>
TVect3<T> TMatrix43<T>::VectorTransformed(const TVect3<T> &u) const
  {
  return u * m;
  }









template <class T>
TVect3<T> TMatrix43<T>::VectorScaled(const TVect3<T> &u) const
  {
  return m.VectorScaled(u);
  }

















template <class T>
TVect3<T> TMatrix43<T>::VectorBackRotTransformed(const TVect3<T> &u) const
  {
  return m * u;
  }


















template <class T>
TPoint3<T> TMatrix43<T>::PointBackRotTransformed(const TPoint3<T> &p) const
  {
  return (m.BackRotated(p - v));
  }













template <class T>
void TMatrix43<T>::PointTransform(TPoint3<T> &p) const
  {
  p.Vector() = p.Vector() * m + v;
  }














template <class T>
TPoint3<T> TMatrix43<T>::PointTransformed(const TPoint3<T> &p) const
  {
  return  (p.Vector() * m + v).Point();
  }















template <class T>
TPoint3<T> TMatrix43<T>::PointScaledAndTranslated(const TPoint3<T> &p) const
  {
  return TPoint3<T>(p.x * m[0][0] + v.x, p.y * m[1][1] + v.y,
                    p.z * m[2][2] + v.z);
  }












template <class T>
TPoint3<T> TMatrix43<T>::PointTranslated(const TPoint3<T> &p) const
  {
  return  p + v;
  }





















template <class T>
TMatrix43<T> TMatrix43<T>::operator * (const TMatrix43<T> &u) const
  {
  TMatrix43<T> res;
  
  res.m = m * u.m;

  
  
  
  res.v = v * u.m + u.v;
  return res;
  }











template <class T>
TMatrix43<T> TMatrix43<T>::operator / (const double d) const
  {
  TMatrix43<T> res;
  Assert(d != 0);
  res.m = m / d;
  res.v = v / d;
  return res;
  }









template <class T>
void TMatrix43<T>::Identity()
  {
  m.Identity();
  v = 0;
  }







template <class T>
bool TMatrix43<T>::IsIdentity() const
  {
  return (m == TMatrix3<T>::E()) && (v == TVect3<T>(0));
  }

#if !defined(_WIN32) || (_MSC_VER >= 1400) || defined(DOXYGEN)






template <class T>
bool TMatrix43<T>::AboutIdentity(const double tolerance) const
  {
  return TMatrix3<T>::AboutIdentity(m, tolerance) && v == TVect3<T>(0); 
  }
#endif







template <class T>
bool TMatrix43<T>::IsOnlyTranslation() const
  {
  return (m == TMatrix3<T>::E());
  }



template <class T>
bool TMatrix43<T>::IsOnlyScaleAndTranslation() const
  {
  return (m[0][1] == 0 && m[0][2] == 0 &&
          m[1][0] == 0 && m[1][2] == 0 &&
          m[2][0] == 0 && m[2][1] == 0);
  }






template <class T> typename TMatrix43<T>::TransformationType
TMatrix43<T>::GetTransformationType() const
  {
  return IsIdentity() ? IDENTITY_TRANSFORM :
         IsOnlyTranslation() ? TRANSLATION_TRANSFORM : 
         IsOnlyScaleAndTranslation() ? SCALE_TRANSLATION_TRANSFORM : 
         GENERAL_TRANSFORM;
  }








template <class T>
TMatrix43<T> &TMatrix43<T>::operator = (const TMatrix43<T> &u)
  {
  m = u.m;
  v = u.v;
  return *this;
  }









template <class T>
TMatrix43<T> & TMatrix43<T>::operator += (const TMatrix43<T> &u)
  {
  m += u.m;
  v += u.v;
  return *this;
  }









template <class T>
TMatrix43<T> & TMatrix43<T>::operator -= (const TMatrix43<T> &u)
  {
  m -= u.m;
  v -= u.v;
  return *this;
  }









template <class T>
TMatrix43<T> & TMatrix43<T>::operator *= (const double d)
  {
  m *= d;
  v *= d;
  return *this;
  }





















template <class T>
TMatrix43<T> & TMatrix43<T>::operator *= (const TMatrix43<T> &u)
  {
  v = v * u.m + u.v;
  m *= u.m;
  return *this;
  }











template <class T>
TMatrix43<T> & TMatrix43<T>::operator /= (const double d)
  {
  Assert(d != 0);
  m /= d;
  v /= d;
  return *this;
  }






















template <class T>
TMatrix43<T> TMatrix43<T>::Inversed() const
  {
  TMatrix43<T> res;
  res.m = this->m.Inversed();
  res.v = -(this->v * res.m);
  return res;
  }












template <class T>
void TMatrix43<T>::InverseRot()
  {
  m.Transpose();
  v = -(v * m);
  }










template <class T>
TMatrix43<T> TMatrix43<T>::InversedForRotMat() const
  {
  TMatrix43<T> res;
  res.m = m.Transposed();
  res.v = -(v * res.m);

  return res;
  }















template <class T>
TMatrix43<T> &TMatrix43<T>::RotationX(double angle)
  {
  m.RotationX(angle);  
  v = 0;               
  return *this;
  }















template <class T>
TMatrix43<T> &TMatrix43<T>::RotationY(double angle)
  {
  m.RotationY(angle);  
  v = 0;               
  return *this;
  }















template <class T>
TMatrix43<T> &TMatrix43<T>::RotationZ(double angle)
  {
  m.RotationZ(angle);  
  v = 0;               
  return *this;
  }


















template <class T>
TMatrix43<T> &TMatrix43<T>::RotationAxis(const TVect3<T> &u, double angle)
  {
  m.RotationAxis(u, angle);  
  v = 0;                     
  return *this;
  }

















template <class T>
TMatrix43<T> &TMatrix43<T>::GenRotation(
    const TVect3<T> &ux, const TVect3<T> &uy, const TVect3<T> &uz)
  {
  m.GenRotation(ux, uy, uz);  
  v = 0;                      
  return *this;
  }










template <class T>
TMatrix43<T> &TMatrix43<T>::Translation(const TVect3<T> &u)
  {
  m.Identity();
  v = u;  
  return *this;
  }















template <class T>
TMatrix43<T> &TMatrix43<T>::Scale(const double x, const double y, const double z)
  {
  m.Scale(x, y, z);  
  v = 0;             
  return *this;
  }














template <class T>
inline TMatrix43<T> operator * (const double d, const TMatrix43<T> &u)
  {
  return u * d;
  }

















template <class T>
inline TPoint3<T> operator * (const TPoint3<T> &u, const TMatrix43<T> &a)
  {
  return (u.Vector() * a.Matrix3() + a.GetTrans()).Point();
  }







template <class T>
inline TMatrix43<float> ConvF(const TMatrix43<T> &v)
  {
  TMatrix43<float> res;

  
  res[0] = ConvF(v[0]);
  res[1] = ConvF(v[1]);
  res[2] = ConvF(v[2]);
  res[3] = ConvF(v[3]);
  return res;
  }








template <class T>
inline TMatrix43<double> ConvD(const TMatrix43<T> &v)
  {
  TMatrix43<double> res;

  
  res[0] = ConvD(v[0]);
  res[1] = ConvD(v[1]);
  res[2] = ConvD(v[2]);
  res[3] = ConvD(v[3]);
  return res;
  }

KIAM_NAMESPACE_END
#endif 
