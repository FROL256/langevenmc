








#ifndef KLBM_TMATRIX3D_HPP
#define KLBM_TMATRIX3D_HPP

#include <math/vect2.hpp>

#include "barrays.hpp"

KIAM_NAMESPACE_START


template <class T> class TMatrix3D
  {
  public:
    
    
    
    virtual ~TMatrix3D();
    
    inline explicit TMatrix3D();
    
    inline explicit TMatrix3D(int n1, int n2, int n3);
    
    inline TMatrix3D(const TMatrix3D<T> &m);
    

  public:
    
    
    
    inline TMatrix3D &operator =(const TMatrix3D<T> &src);
    
    inline TMatrix3D &operator =(const T &c);
    
    inline TMatrix3D &operator *=(const double &c);
    

  public:
    
    
    
    bool operator ==(const TMatrix3D<T> &src) const;
    

  public:
    
    
    
    inline OKAY Allocate(int n1, int n2, int n3);
    
    inline OKAY Resize(int n1, int n2, int n3);
    
    inline int Dimension(int i) const;
    
    int Length() const;
    

  public:
    
    
    
    inline const T &operator()(int i, int j, int k) const;
    
    inline T &operator()(int i, int j, int k);
    
    inline SArray<T> operator()(int i, int j);
    
    inline const SArray<T> operator()(int i, int j) const;
    
    inline T *Slice(int i, int j);
    
    inline const T *Slice(int i, int j) const;
    
    inline T *Data();
    
    inline const T *Data() const;
    
    inline SIZE_T Size() const;
    

  public:
    
    
    
    static void SwapMatrix(TMatrix3D<T> &m1, TMatrix3D<T> &m2);
    
    inline void VertFlip();
    
    inline void HorFlip();
    
    inline OKAY Crop(const Point2i &beg, const Vect2i &size);
    


  private:
    
    
    
    int m_n1;
    
    int m_n2;
    
    int m_n3;
    

    
    T *m_data;
  };  








template <class T>
TMatrix3D<T>::~TMatrix3D()
  {
  Allocate(0, 0, 0);
  }





template <class T>
TMatrix3D<T>::TMatrix3D() : 
  m_data(NULL), 
  m_n1(0), m_n2(0), m_n3(0)
  {
  }








template <class T>
TMatrix3D<T>::TMatrix3D(int n1, int n2, int n3)
  {
  m_n1 = m_n2 = m_n3 = 0;
  m_data = NULL;
  Allocate(n1, n2, n3);
  }




template <class T>
TMatrix3D<T>::TMatrix3D(TMatrix3D<T> const &m)
  {
  m_n1 = m_n2 = m_n3 = 0;
  m_data = NULL;
  *this = m;
  }








template <class T>
TMatrix3D<T> &TMatrix3D<T>::operator =(TMatrix3D<T> const &src)
  {
  if (this != &src) 
    {
    if (Allocate(src.m_n1, src.m_n2, src.m_n3) == SUCCESS)
      {
      
      SIZE_T i, n = (SIZE_T)m_n1 * m_n2 * m_n3;
      for (i = 0; i < n; i++)
        m_data[i] = src.m_data[i];
      }
    }
  return *this;
  }  






template <class T>
TMatrix3D<T> &TMatrix3D<T>::operator =(const T &c)
  {
  
  SIZE_T i, n = (SIZE_T)m_n1 * m_n2 * m_n3;
  for (i = 0; i < n; i++)
    m_data[i] = c;
  return *this;
  }  





template <class T>
TMatrix3D<T> &TMatrix3D<T>::operator *=(const double &c)
  {
  SIZE_T i, n = (SIZE_T)m_n1 * m_n2 * m_n3;
  for (i = 0; i < n; i++)
    m_data[i] *= c;
  return *this;
  }  








template <class T>
bool TMatrix3D<T>::operator ==(const TMatrix3D<T> &src) const
  {
  if (m_n1 != src.m_n1 || m_n2 != src.m_n2 || m_n3 != src.m_n3)
    return false;
  SIZE_T n = (SIZE_T)m_n1 * m_n2 * m_n3;
  for (SIZE_T i = 0; i < n; i++)
    if (!(m_data[i] == src.m_data[i]))
      return false;
  return true;
  }










template <class T>
OKAY TMatrix3D<T>::Allocate(int n1, int n2, int n3)
  {
  if (n1 < 0 || n2 < 0 || n3 < 0)
    {
    Assert(false);
    return FAILURE;
    }

  if (n1 > 0 && n2 > 0 && n3 > 0)
    {
    
    
    if ((((MAX_SIZE_T / n1) / n2) / n3) < sizeof(T))
      {
      m_n1 = m_n2 = m_n3 = 0;
      if (m_data != NULL)
        delete m_data;
      m_data = NULL;
      return FAILURE;
      }
    }


  SIZE_T new_len = (SIZE_T)n1 * n2 * n3;
  SIZE_T prev_len = (SIZE_T)m_n1  * m_n2  * m_n3;

  if (prev_len != new_len || (new_len > 0 && m_data == NULL))
    {
    
    if (prev_len > 0 && m_data != NULL)
      delete [] m_data;
    m_data = NULL;

    
    if (new_len > 0)
      {
      m_data = new T[new_len];
      if (m_data == NULL)
        {
        m_n1 = m_n2 = m_n3 = 0;
        return FAILURE;
        }
      }
    }
  m_n1 = n1;
  m_n2 = n2;
  m_n3 = n3;

  return SUCCESS;
  }  










template <class T>
OKAY TMatrix3D<T>::Resize(int n1, int n2, int n3)
  {
  if (n1 < 0 || n2 < 0 || n3 < 0)
    {
    Assert(false);
    return FAILURE;
    }

  if (n1 > 0 && n2 > 0 && n3 > 0)
    {
    
    
    if ((((MAX_SIZE_T / n1) / n2) / n3) < sizeof(T))
      {
      m_n1 = m_n2 = m_n3 = 0;
      if (m_data != NULL)
        delete m_data;
      m_data = NULL;
      return FAILURE;
      }
    }

  SIZE_T prev_len = (SIZE_T)m_n1  * m_n2  * m_n3;

  if (m_data == NULL || prev_len == 0)  
    return Allocate(n1, n2, n3);
  else 
    {
    
    TMatrix3D<T> b(n1, n2, n3);
    if (b.m_data == NULL && n1 !=0 && n2 != 0 && n3 != 0)
      return FAILURE;

    
    int min_n1 = Min(m_n1, n1);
    int min_n2 = Min(m_n2, n2);
    int min_n3 = Min(m_n3, n3);
    for (int i = 0; i < min_n1; i++)
      {
      for (int j = 0; j < min_n2; j++)
        {
        for (int k = 0; k < min_n3; k++)
          b(i, j, k) = (*this)(i, j, k);
        }
      }
    
    SwapMatrix(b, *this);
    }

  return SUCCESS;
  }  






template <class T>
int TMatrix3D<T>::Dimension(int i) const
  {
  Assert(i >= 0 && i < 3);
  return *(&m_n1 + i);
  }




template <class T>
int TMatrix3D<T>::Length() const
  {
  return m_n1 * m_n2 * m_n3;
  }








template <class T>
T &TMatrix3D<T>::operator ()(int i, int j, int k)
  {
  Assert(i >= 0 && i < m_n1 && j >= 0 && j < m_n2 && k >= 0 && k < m_n3);
  return m_data[(SIZE_T)k + m_n3 * (j + m_n2 * i)];
  }








template <class T>
const T &TMatrix3D<T>::operator ()(int i, int j, int k) const
  {
  Assert(i >= 0 && i < m_n1 && j >= 0 && j < m_n2 && k >= 0 && k < m_n3);
  return m_data[(SIZE_T)k + m_n3 * (j + m_n2 * i)];
  }


































template <class T>
SArray<T> TMatrix3D<T>::operator()(int i, int j)
  {
  Assert(i >= 0 && i < m_n1 && j >= 0 && j < m_n2);;
  return SArray<T>(m_data + (SIZE_T)m_n3 * (j + m_n2 * i), m_n3);
  }


































template <class T>
const SArray<T> TMatrix3D<T>::operator()(int i, int j) const
  {
  Assert(i >= 0 && i < m_n1 && j >= 0 && j < m_n2);;
  return SArray<T>(m_data + (SIZE_T)m_n3 * (j + m_n2 * i), m_n3);
  }











template <class T>
T *TMatrix3D<T>::Slice(int i, int j)
  {
  Assert(i >= 0 && i < m_n1 && j >= 0 && j < m_n2);;
  return m_data + (SIZE_T)m_n3 * (j + m_n2 * i);
  }











template <class T>
const T *TMatrix3D<T>::Slice(int i, int j) const
  {
  Assert(i >= 0 && i < m_n1 && j >= 0 && j < m_n2);;
  return m_data + (SIZE_T)m_n3 * (j + m_n2 * i);
  }








template <class T> void
TMatrix3D<T>::SwapMatrix(TMatrix3D<T> &m1, TMatrix3D<T> &m2)
  {
  Swap(m1.m_n1, m2.m_n1);
  Swap(m1.m_n2, m2.m_n2);
  Swap(m1.m_n3, m2.m_n3);
  Swap(m1.m_data, m2.m_data);
  }



template <class T>
void TMatrix3D<T>::HorFlip()
  {
  SIZE_T r_size = m_n2 * m_n3;
  for (int r = 0; r < m_n1; r++)
    {
    for (int c = 0; c < m_n2 / 2; c++)
      {
      for (int z = 0; z < m_n3; z++)
        Swap(*(m_data + r_size * r + c * m_n3 + z), *(m_data + r_size * r + (m_n2 - 1 - c) * m_n3 + z));
      }
    }
  }



template <class T>
void TMatrix3D<T>::VertFlip()
  {
  SIZE_T r_size = m_n2 * m_n3;
  for (int r = 0; r < m_n1 / 2; r++)
    {
    for (int c = 0; c < m_n2; c++)
      {
      for (int z = 0; z < m_n3; z++)
        Swap(*(m_data + r_size * r + c * m_n3 + z), *(m_data + r_size * (m_n1 - 1 - r) + m_n3 * c + z));
      }
    }
  }






template <class T>
OKAY TMatrix3D<T>::Crop(const Point2i &beg, const Vect2i &size)
  {
  Vect2i cur_res(m_n2, m_n1);
  Assert(beg.x < cur_res.x && beg.y < cur_res.y && beg.x + size.x <= cur_res.x && beg.y + size.y <= cur_res.y);
  for (int y = 0; y < size.y; y++)
    {
    for (int x = 0; x < size.x; x++)
      {
      for (int z = 0; z < m_n3; z++)
        m_data[((SIZE_T)cur_res.x * y + x) * m_n3 + z] = m_data[((SIZE_T)cur_res.x * (beg.y + y) + beg.x + x) * m_n3 + z];
      }
    }

  return Resize(size.y, size.x, m_n3);
  }




template <class T>
T *TMatrix3D<T>::Data()
  {
  return m_data;
  }




template <class T>
const T *TMatrix3D<T>::Data() const
  {
  return m_data;
  }




template <class T>
SIZE_T TMatrix3D<T>::Size() const
  {
  return (SIZE_T)m_n1 * m_n2 * m_n3;
  }

KIAM_NAMESPACE_END
#endif
