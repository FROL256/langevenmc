








#ifndef _RGNB_MATRIX_HPP_
#define _RGNB_MATRIX_HPP_

#include <math/vect2.hpp>

#include "barrays.hpp"

KIAM_NAMESPACE_START


template <class T>
class TMatrix
  {
  public:
    
    
    
    inline explicit TMatrix();
    
    inline explicit TMatrix(int n_r, int n_c);
    
    inline TMatrix(const T *val, int n_r, int n_c);

    
    inline TMatrix(const TMatrix<T> &m);
    
    virtual ~TMatrix();
    

  public:
    
    
    
    inline OKAY Resize(int n_r, int n_c);
    
    inline OKAY Allocate(int n_r, int n_c);
    
    
    inline OKAY AllocateFast(int n, int m);
    
    inline OKAY Scale(int row_scale, int col_scale, TMatrix<T> &out) const;
    

  public:
    
    
    
    inline Vect2i GetRes() const;
    
    inline int NRows() const;
    
    inline int NColumns() const;
    
    inline SIZE_T Length() const;
    
    inline int Dimension(int i) const;
    

  public:
    
    
    
    inline OKAY InsertRows(int i, int n = 1, int m0 = -1);
    
    inline OKAY InsertColumns(int i, int n = 1, int n0 = -1);
    
    inline OKAY RemoveRows(int i, int n = 1);
    
    inline OKAY RemoveColumns(int i, int n = 1);
    

  public:
    
    
    
    inline TMatrix &operator =(const TMatrix<T> &src);
    
    inline TMatrix &operator =(const T &c);
    
    inline void Set(const T &val);
    

    
    
    
    inline TMatrix &operator *=(const double &c);
    
    inline TMatrix<T> &operator +=(const TMatrix<T> &m);
    

    
    
    
    bool operator ==(const TMatrix<T> &src) const;
    
    bool operator !=(const TMatrix<T> &src) const;
    

  public:
    
    
    
    inline operator T *();
    
    inline operator const T *() const;
    
    inline T *Data();
    
    inline const T *Data() const;
    
    inline SArray<T> operator [](int i);
    
    inline const SArray<T> operator [](int i) const;
    
    inline T *Slice(int i);
    
    inline const T *Slice(int i) const;
    
    inline void SetRow(int row, const T *val_ptr);
    
    inline T &operator ()(int i, int j);
    
    inline const T &operator ()(int i, int j) const;
    
    inline T &operator ()(SIZE_T i);
    
    inline const T &operator ()(SIZE_T i) const;
    

  public:
    
    
    
    inline T MaxValue() const;
    
    inline T MinValue() const;
    
    inline bool IsEmpty() const;
    
    static void SwapMatrix(TMatrix<T> &m1, TMatrix<T> &m2);
    
    inline void VertFlip();
    
    inline void HorFlip();
    
    inline OKAY Crop(const Point2i &beg, const Vect2i &size);
    
    inline void CopyFrom(const TMatrix<T> &src, const Point2i &dst_beg, const Point2i &src_beg, const Vect2i &size);
    

  public:

  public:
    
    
    
    inline OKAY ResizeBilinear(int n_rows, int n_cols, TMatrix<T> &out) const;
    
    inline OKAY ResizeBilinearCycled(int n_rows, int n_cols, TMatrix<T> &out, 
      bool cycle_rows, bool cycle_cols) const;
    
    inline OKAY ResizeBilinearCycledWithMask(int n_rows, int n_cols, TMatrix<T> &out, 
      bool cycle_rows, bool cycle_cols, const TMatrix<bool> &mask) const;
    
    inline OKAY ScaleToHalf(TMatrix<T> &out) const;
    
    inline OKAY ZoomOut(int row_n, int col_n, TMatrix<T> &out) const;
    
    
    inline void GetInterpPixCycled(const Vect2d &pnt, T &out) const;

  private:
    
    T *m_data;

  private:
    
    
    
    
    
    int m_n_rows;
    
    int m_n_cols;
    
  };  








template <class T>
TMatrix<T>::TMatrix()
  {
  m_n_rows = m_n_cols = 0;
  m_data = NULL;
  }








template <class T>
TMatrix<T>::TMatrix(int n_r, int n_c)
  {
  m_n_rows = m_n_cols = 0;
  m_data = NULL;
  Allocate(n_r, n_c);
  }








template <class T>
TMatrix<T>::TMatrix(const T *val, int n_r, int n_c)
  {
  m_n_rows = m_n_cols = 0;
  m_data = NULL;
  if (Allocate(n_r, n_c) != SUCCESS)
    return;
  SIZE_T len = (SIZE_T)n_r * (SIZE_T)n_c;
  for (SIZE_T i = 0; i < len; i++)
    m_data[i] = val[i];
  }



template <class T>
TMatrix<T>::~TMatrix()
  {
  Allocate(0, 0);
  }




template <class T>
TMatrix<T>::TMatrix(TMatrix<T> const &m)
  {
  m_n_rows = m_n_cols = 0;
  m_data = NULL;
  *this = m;
  }









template <class T>
TMatrix<T> &TMatrix<T>::operator =(TMatrix<T> const &src)
  {
  if (this != &src)  
    {
    if (Allocate(src.m_n_rows, src.m_n_cols) == SUCCESS)
      {
      
      SIZE_T n = (SIZE_T)m_n_rows * (SIZE_T)m_n_cols;
      for (SIZE_T i = 0; i < n; i++)
        m_data[i] = src.m_data[i];
      }
    }
  return *this;
  }  





template <class T>
TMatrix<T> &TMatrix<T>::operator =(T const &c)
  {
  
  SIZE_T n = (SIZE_T)m_n_rows * (SIZE_T)m_n_cols;
  for (SIZE_T i = 0; i < n; i++)
    m_data[i] = c;
  return *this;
  }  





template <class T>
void TMatrix<T>::Set(const T &val)
  {
  
  SIZE_T n = (SIZE_T)m_n_rows * (SIZE_T)m_n_cols;
  for (SIZE_T i = 0; i < n; i++)
    m_data[i] = val;
  }   








template <class T>
TMatrix<T> &TMatrix<T>::operator *=(const double &c)
  {
  SIZE_T n = (SIZE_T)m_n_rows * (SIZE_T)m_n_cols;
  for (SIZE_T i = 0; i < n; i++)
    m_data[i] = (T)(m_data[i] * c);
  return *this;
  }  








template <class T>
TMatrix<T> &TMatrix<T>::operator +=(const TMatrix<T> &m)
  {
  Assert(GetRes() == m.GetRes());
  
  SIZE_T n = (SIZE_T)m_n_rows * (SIZE_T)m_n_cols;
  for (SIZE_T i = 0; i < n; i++)
    m_data[i] += m.m_data[i];

  return *this;
  }  








template <class T>
bool TMatrix<T>::operator ==(const TMatrix<T> &src) const
  {
  if (m_n_rows != src.m_n_rows || m_n_cols != src.m_n_cols)
    return false;
  SIZE_T n = (SIZE_T)m_n_rows * (SIZE_T)m_n_cols;
  for (SIZE_T i = 0; i < n; i++)
    {
    if (!(m_data[i] == src.m_data[i]))
      return false;
    }
  return true;
  }








template <class T>
bool TMatrix<T>::operator !=(const TMatrix<T> &src) const
  {
  return !(*this == src);
  }












template <class T>
OKAY TMatrix<T>::Allocate(int n_r, int n_c)
  {
  if (n_r < 0 || n_c < 0)
    {
    Assert(false);
    return FAILURE;
    }

  if (n_r > 0 && n_c > 0)
    {
    
    
    if ((MAX_SIZE_T / n_r) / n_c < sizeof(T))
      {
      m_n_rows = m_n_cols = 0;
      if (m_data != NULL)
        delete m_data;
      m_data = NULL;
      return FAILURE;
      }
    }

  SIZE_T n_el = (SIZE_T)n_r * (SIZE_T)n_c;
  SIZE_T av_n_el = (SIZE_T)m_n_rows * (SIZE_T)m_n_cols;
  if (av_n_el != n_el || (n_el > 0 && m_data == NULL))
    {
    
    if (av_n_el > 0 && m_data != NULL)
      delete [] m_data;
    m_data = NULL;
    
    if (n_el > 0)
      {
      m_data = new T[n_el];
      if (m_data == NULL)
        {
        m_n_rows = m_n_cols = 0;
        return FAILURE;
        }
      }
    }
  m_n_rows = n_r;
  m_n_cols = n_c;

  return SUCCESS;
  }  













template <class T>
OKAY TMatrix<T>::AllocateFast(int n_r, int n_c)
  {
  SIZE_T n_el = (SIZE_T)n_r * (SIZE_T)n_c;
  SIZE_T av_n_el = (SIZE_T)m_n_rows * (SIZE_T)m_n_cols;

  if ((m_n_rows > 0) && (m_n_cols > 0) && (m_data != NULL) &&
      (n_r > 0) && (n_c > 0) && (n_el <= av_n_el))
    {
    m_n_rows = n_r;
    m_n_cols = n_c;
    return SUCCESS;
    }
  return Allocate(n_r, n_c);
  }  















template <class T>
OKAY TMatrix<T>::Resize(int n_r, int n_c)
  {
  if (m_n_rows == n_r && m_n_cols == n_c)
    return SUCCESS;  

  if (n_r < 0 || n_c < 0)
    {
    Assert(false);
    return FAILURE;
    }

  if (n_r > 0 && n_c > 0)
    {
    
    
    if ((MAX_SIZE_T / n_r) / n_c < sizeof(T))
      {
      m_n_rows = m_n_cols = 0;
      if (m_data != NULL)
        delete m_data;
      m_data = NULL;
      return FAILURE;
      }
    }

  SIZE_T av_n_el = (SIZE_T)m_n_rows * (SIZE_T)m_n_cols;

  if (m_data == NULL || av_n_el == 0)  
    return Allocate(n_r, n_c);
  else 
    {
    
    TMatrix<T> b(n_r, n_c);
    if (b.m_data == NULL && n_r !=0 && n_c != 0)
      return FAILURE;

    
    int min_n1 = Min(m_n_rows, n_r);
    int min_n2 = Min(m_n_cols, n_c);
    for (int i = 0; i < min_n1; i++)
      {
      for (int j = 0; j < min_n2; j++)
        b(i, j) = (*this)(i, j);
      }
    
    SwapMatrix(b, *this);
    }

  return SUCCESS;
  }  




template <class T>
Vect2i TMatrix<T>::GetRes() const
  {
  return Vect2i(m_n_cols, m_n_rows);
  }




template <class T>
int TMatrix<T>::NRows() const
  {
  return m_n_rows;
  }




template <class T>
int TMatrix<T>::NColumns() const
  {
  return m_n_cols;
  }




template <class T>
SIZE_T TMatrix<T>::Length() const
  {
  SIZE_T length = (SIZE_T)m_n_cols * (SIZE_T)m_n_rows;
  Assert(length <= MAX_SIZE_T);
  return length;
  }





template <class T>
int TMatrix<T>::Dimension(int i) const
  {
  Assert(i == 0 || i == 1);
  return *(&m_n_rows + i);
  }




















template <class T>
OKAY TMatrix<T>::InsertRows(int i0, int n, int m0)
  {
  int i, j;
  if ((m_n_rows == 0) && (m0 >= 0))
    m_n_cols = m0;

  if (m_n_cols == 0)
    {
    
    
    m_n_rows += n;
    return SUCCESS;
    }

  if (i0 > m_n_rows)  
    return FAILURE;

  
  TMatrix<T> b(m_n_rows + n, m_n_cols);
  if (!b.m_data)
    return FAILURE;

  
  if (m_data != NULL)  
    {
    for (i = 0; i < i0; i++)
      {
      for (j = 0; j < m_n_cols; j++)
        b(i, j) = (*this)(i, j);
      }
    for (i = i0; i < m_n_rows; i++)
      {
      for (j = 0; j < m_n_cols; j++)
        b(i + n, j) = (*this)(i, j);
      }
    }
  
  SwapMatrix(b, *this);
  return SUCCESS;
  }  





















template <class T>
OKAY TMatrix<T>::InsertColumns(int j0, int n, int n0)
  {
  int i, j;
  if ((m_n_cols == 0) && (n0 >= 0))
    m_n_rows = n0;

  if (m_n_rows == 0)
    {
    
    
    m_n_cols += n;
    return SUCCESS;
    }

  if (j0 > m_n_cols)  
    return FAILURE;

  
  TMatrix<T> b(m_n_rows, m_n_cols + n);
  if (!b.m_data)
    return FAILURE;

  
  if (m_data != NULL)  
    {
    for (i = 0; i < m_n_rows; i++)
      {
      for (j = 0; j < j0; j++)
        b(i, j) = (*this)(i, j);
      for (j = j0; j < m_n_cols; j++)
        b(i, j + n) = (*this)(i, j);
      }
    }
  
  SwapMatrix(b, *this);
  return SUCCESS;
  }  








template <class T>
T &TMatrix<T>::operator ()(int i, int j)
  {
  Assert(i >= 0 && i < m_n_rows && j >= 0 && j < m_n_cols);;
  return m_data[(SIZE_T)i * (SIZE_T)m_n_cols + j];
  }








template <class T>
const T &TMatrix<T>::operator ()(int i, int j) const
  {
  Assert(i >= 0 && i < m_n_rows && j >= 0 && j < m_n_cols);;
  return m_data[(SIZE_T)i * (SIZE_T)m_n_cols + j];
  }


























template <class T>
SArray<T> TMatrix<T>::operator [](int i)
  {
  Assert(i >= 0 && i < m_n_rows);;
  return SArray<T>(m_data + (SIZE_T)i * (SIZE_T)m_n_cols, m_n_cols);
  }


























template <class T>
const SArray<T> TMatrix<T>::operator [](int i) const
  {
  Assert(i >= 0 && i < m_n_rows);;
  return SArray<T>(m_data + (SIZE_T)i * (SIZE_T)m_n_cols, m_n_cols);
  }








template <class T>
void TMatrix<T>::SwapMatrix(TMatrix<T> &m1, TMatrix<T> &m2)
  {
  int nrows_tmp, ncols_tmp;
  T *a_tmp;
  nrows_tmp = m1.m_n_rows;
  ncols_tmp = m1.m_n_cols;
  a_tmp  = m1.m_data;

  m1.m_n_rows = m2.m_n_rows;
  m1.m_n_cols = m2.m_n_cols;
  m1.m_data = m2.m_data;

  m2.m_n_rows = nrows_tmp;
  m2.m_n_cols = ncols_tmp;
  m2.m_data = a_tmp;
  return;
  }



template <class T>
void TMatrix<T>::VertFlip()
  {
  for (int r = 0; r < m_n_rows / 2; r++)
    {
    for (int c = 0; c < m_n_cols; c++)
      Swap(*(m_data + (SIZE_T)m_n_cols * r + c), *(m_data + (SIZE_T)m_n_cols * (m_n_rows - 1 - r) + c));
    }
  }



template <class T>
void TMatrix<T>::HorFlip()
  {
  for (int r = 0; r < m_n_rows; r++)
    {
    for (int c = 0; c < m_n_cols / 2; c++)
      Swap(*(m_data + (SIZE_T)m_n_cols * r + c), *(m_data + (SIZE_T)m_n_cols * r + m_n_cols - 1 - c));
    }
  }






template <class T>
OKAY TMatrix<T>::Crop(const Point2i &beg, const Vect2i &size)
  {
  Vect2i cur_res = GetRes();
  Assert(beg.x < cur_res.x && beg.y < cur_res.y && beg.x + size.x <= cur_res.x && beg.y + size.y <= cur_res.y);
  for (int y = 0; y < size.y; y++)
    {
    for (int x = 0; x < size.x; x++)
      m_data[(SIZE_T)cur_res.x * y + x] = m_data[(SIZE_T)cur_res.x * (beg.y + y) + beg.x + x];
    }
  return Resize(size.y, size.x);
  }









template <class T>
void TMatrix<T>::CopyFrom(const TMatrix<T> &src, const Point2i &dst_beg, const Point2i &src_beg, const Vect2i &size)
  {
  const Vect2i src_res = src.GetRes();
  const Vect2i dst_res = GetRes();
  Assert(src_beg.x + size.x <= src_res.x);
  Assert(src_beg.y + size.y <= src_res.y);
  Assert(dst_beg.x + size.x <= dst_res.x);
  Assert(dst_beg.y + size.y <= dst_res.y);
  for (int i = 0; i < size.y; i++)
    {
    T *src_ptr = src.m_data + (SIZE_T)src_res.x * (src_beg.y + i) + src_beg.x;
    T *dst_ptr = m_data + (SIZE_T)dst_res.x * (dst_beg.y + i) + dst_beg.x;
    for (int j = 0; j < size.x; j++)
      *dst_ptr++ = *src_ptr++;
    }
  }













template <class T>
OKAY TMatrix<T>::RemoveRows(int row, int n)
  {
  if (row < 0 || row >= m_n_rows)
    return FAILURE;

  if (n == 0)
    return SUCCESS;  

  
  if (row + n > m_n_rows)
    n = m_n_rows - row;

  
  int new_nrows = m_n_rows - n;

  if (m_data == NULL)
    {
    m_n_rows = new_nrows;
    return SUCCESS;
    }

  
  SIZE_T size = (SIZE_T)new_nrows * (SIZE_T)m_n_cols;

  
  if (size == 0)
    {
    delete[] m_data;
    m_data = NULL;
    m_n_rows = new_nrows;
    return SUCCESS;
    }

  
  T *new_data = new T[size];
  if (new_data == NULL)
    return FAILURE;

  
  int r = 0;
  SIZE_T p = 0;
  SIZE_T p0 = 0;
  for (r = 0; r < row; r++)
    for (int c = 0; c < m_n_cols; c++)
      new_data[p++] = m_data[p0++];

  
  p0 = (SIZE_T)(row + n) * m_n_cols;
  for (r = row + n; r < m_n_rows; r++)
    for (int c = 0; c < m_n_cols; c++)
      new_data[p++] = m_data[p0++];

  delete[] m_data;
  m_data = new_data;
  m_n_rows = new_nrows;
  return SUCCESS;
  }  












template <class T>
OKAY TMatrix<T>::RemoveColumns(int col, int n)
  {
  if (col < 0 || col >= m_n_cols)
    return FAILURE;

  if (n == 0)
    return SUCCESS;  

  
  if (col + n > m_n_cols)
    n = m_n_cols - col;

  
  int new_ncols = m_n_cols - n;

  if (m_data == NULL)
    {
    m_n_cols = new_ncols;
    return SUCCESS;
    }

  
  SIZE_T size = (SIZE_T)m_n_rows * (SIZE_T)new_ncols;

  
  if (size == 0)
    {
    delete[] m_data;
    m_data = NULL;
    m_n_cols = new_ncols;
    return SUCCESS;
    }

  
  T *new_data = new T[size];
  if (new_data == NULL)
    return FAILURE;

  SIZE_T p0 = 0;  
  SIZE_T p  = 0;  
  for (int r = 0; r < m_n_rows; r++)
    {
    int c = 0;

    
    for (c = 0; c < col; c++)
      new_data[p++] = m_data[p0 + c];

    
    for (c = col + n; c < m_n_cols; c++)
      new_data[p++] = m_data[p0 + c];

    p0 += m_n_cols;
    }

  delete[] m_data;
  m_data = new_data;
  m_n_cols = new_ncols;
  return SUCCESS;
  }  





template <class T>
TMatrix<T>::operator T*()
  {
  return m_data;
  }





template <class T>
TMatrix<T>::operator const T*() const
  {
  return m_data;
  }





template <class T>
T *TMatrix<T>::Data()
  {
  return m_data;
  }





template <class T>
const T *TMatrix<T>::Data() const
  {
  return m_data;
  }









template <class T>
T *TMatrix<T>::Slice(int i)
  {
  Assert(i >= 0 && i < m_n_rows);
  return m_data + (SIZE_T)m_n_cols * i;
  }









template <class T>
const T *TMatrix<T>::Slice(int i) const
  {
  Assert(i >= 0 && i < m_n_rows);
  return m_data + (SIZE_T)m_n_cols * i;
  }





template <class T>
void TMatrix<T>::SetRow(int row, const T *val_ptr)
  {
  Assert(row < m_n_rows);
  for (int i = 0; i < m_n_cols; i++)
    m_data[(SIZE_T)m_n_cols * row + i] = val_ptr[i];
  }






template <class T>
T &TMatrix<T>::operator ()(SIZE_T i)
  {
  Assert(i >= 0 && (SIZE_T)i < (SIZE_T)m_n_rows * m_n_cols);
  return m_data[i];
  }






template <class T>
const T &TMatrix<T>::operator ()(SIZE_T i) const
  {
  Assert(i >= 0 && (SIZE_T)i < (SIZE_T)m_n_rows * m_n_cols);
  return m_data[i];
  }









template <class T>
OKAY TMatrix<T>::ResizeBilinear(int n_rows, int n_cols, TMatrix<T> &out) const
  {
  Assert(n_rows >= 1 && n_cols >= 1);
  if (n_rows == m_n_rows && n_cols == m_n_cols)
    {
    out = *this;
    return SUCCESS;
    }

  if (out.Allocate(n_rows, n_cols) != SUCCESS)
    return FAILURE;
  double row_scale = n_rows > 1 ? (m_n_rows - 1) / double(n_rows - 1) : 0;
  double col_scale = n_cols > 1 ? (m_n_cols - 1) / double(n_cols - 1) : 0;

  for (int i = 0; i < n_rows; i++)
    {
    double row = double(i) * row_scale;
    int r = (int)floor(row);
    int rn = r + 1;
    if (rn > m_n_rows - 1)
      rn = m_n_rows - 1;
    double u = row - r;

    for (int j = 0; j < n_cols; j++)
      {
      double col = double(j) * col_scale;
      int c = (int)floor(col);
      int cn = c + 1;
      if (cn > m_n_cols - 1)
        cn = m_n_cols - 1;
      double t = col - c;

      out(i, j) = (T)((*this)(r, c)   * ((1.0 - t) * (1.0 - u)) +
                      (*this)(r, cn)  * (       t  * (1.0 - u)) +
                      (*this)(rn, c)  * ((1.0 - t) *        u)  +
                      (*this)(rn, cn) * (       t  *        u));
      }  
    }  
  return SUCCESS;
  }





template <class T>
void TMatrix<T>::GetInterpPixCycled(const Vect2d &pnt, T &out) const
  {
  int r = (int)floor(pnt.y);
  int rn = r + 1;
  if (rn > m_n_rows - 1)
    rn = 0;
  double u = pnt.y - r;

  int c = (int)floor(pnt.x);
  int cn = c + 1;
  if (cn > m_n_cols - 1)
    cn = 0;
  double t = pnt.x - c;

  out = (T)((*this)(r, c)   * ((1.0 - t) * (1.0 - u)) +
            (*this)(r, cn)  * (       t  * (1.0 - u)) +
            (*this)(rn, c)  * ((1.0 - t) *        u)  +
            (*this)(rn, cn) * (       t  *        u));
  }











template <class T>
OKAY TMatrix<T>::ResizeBilinearCycled(int n_rows, int n_cols, TMatrix<T> &out, 
  bool cycle_rows, bool cycle_cols) const
  {
  Assert(n_rows >= 1 && n_cols >= 1);
  if (n_rows == m_n_rows && n_cols == m_n_cols)
    {
    out = *this;
    return SUCCESS;
    }

  if (out.Allocate(n_rows, n_cols) != SUCCESS)
    return FAILURE;
  double row_scale = cycle_rows ? (double)m_n_rows / n_rows : (n_rows > 1 ? (m_n_rows - 1) / double(n_rows - 1) : 0);
  double col_scale = cycle_cols ? (double)m_n_cols / n_cols : (n_cols > 1 ? (m_n_cols - 1) / double(n_cols - 1) : 0);

  for (int i = 0; i < n_rows; i++)
    {
    double row = cycle_rows ? (double(i + 0.5) * row_scale - 0.5) : (double(i) * row_scale);
    if (row < 0)
      row += m_n_rows;
    int r = (int)floor(row);
    int rn = r + 1;
    if (rn > m_n_rows - 1)
      {
      if (cycle_rows)
        rn = 0;
      else  
        rn = m_n_rows - 1;
      }  
    double u = row - r;

    for (int j = 0; j < n_cols; j++)
      {
      double col = cycle_cols ? (double(j + 0.5) * col_scale - 0.5) : (double(j) * col_scale);
      if (col < 0)
        col += m_n_cols;
      int c = (int)floor(col);
      int cn = c + 1;
      if (cn > m_n_cols - 1)
        {
        if (cycle_cols)
          cn = 0;
        else  
          cn = m_n_cols - 1;
        }  
      double t = col - c;

      out(i, j) = (T)((*this)(r, c)   * ((1.0 - t) * (1.0 - u)) +
                      (*this)(r, cn)  * (       t  * (1.0 - u)) +
                      (*this)(rn, c)  * ((1.0 - t) *        u)  +
                      (*this)(rn, cn) * (       t  *        u));
      }  
    }  
  return SUCCESS;
  }













template <class T>
OKAY TMatrix<T>::ResizeBilinearCycledWithMask(int n_rows, int n_cols, TMatrix<T> &out, 
  bool cycle_rows, bool cycle_cols, const TMatrix<bool> &mask) const
  {
  Assert(n_rows >= 1 && n_cols >= 1);
  if (n_rows == m_n_rows && n_cols == m_n_cols)
    {
    out = *this;
    return SUCCESS;
    }

  Assert((mask.NRows() == m_n_rows) && (mask.NColumns() == m_n_cols));
  if ((mask.NRows() != m_n_rows) || (mask.NColumns() != m_n_cols))
    return FAILURE;

  if (out.Allocate(n_rows, n_cols) != SUCCESS)
    return FAILURE;
  double row_scale = cycle_rows ? (double)m_n_rows / n_rows : (n_rows > 1 ? (m_n_rows - 1) / double(n_rows - 1) : 0);
  double col_scale = cycle_cols ? (double)m_n_cols / n_cols : (n_cols > 1 ? (m_n_cols - 1) / double(n_cols - 1) : 0);

  T elem_arr[4];
  bool mask_arr[4];

  for (int i = 0; i < n_rows; i++)
    {
    double row = cycle_rows ? (double(i + 0.5) * row_scale - 0.5) : (double(i) * row_scale);
    if (row < 0)
      row += m_n_rows;
    int r = (int)floor(row);
    int rn = r + 1;
    if (rn > m_n_rows - 1)
      {
      if (cycle_rows)
        rn = 0;
      else
        rn = m_n_rows - 1;
      }
    double u = row - r;

    for (int j = 0; j < n_cols; j++)
      {
      double col = cycle_cols ? (double(j + 0.5) * col_scale - 0.5) : (double(j) * col_scale);
      if (col < 0)
        col += m_n_cols;
      int c = (int)floor(col);
      int cn = c + 1;
      if (cn > m_n_cols - 1)
        {
        if (cycle_cols)
          cn = 0;
        else
          cn = m_n_cols - 1;
        }
      double t = col - c;

      mask_arr[0] = mask(r, c);
      mask_arr[1] = mask(r, cn);
      mask_arr[2] = mask(rn, c);
      mask_arr[3] = mask(rn, cn);
      elem_arr[0] = (T)(*this)(r, c);
      elem_arr[1] = (T)(*this)(r, cn);
      elem_arr[2] = (T)(*this)(rn, c);
      elem_arr[3] = (T)(*this)(rn, cn);
      
      int total = 0;
      T sum = 0;
      for (int i = 0; i < 4; i++)
        {
        if (mask_arr[i])
          {
          total++;
          sum += elem_arr[i];
          }
        }

      if ((total > 0) && (total < 4))
        {
        sum = (T)(sum / total);
        for (int i = 0; i < 4; i++)
          {
          if (!mask_arr[i])
            elem_arr[i] = sum;
          }
        }

      out(i, j) = (T)(elem_arr[0] * ((1.0 - t) * (1.0 - u)) +
                      elem_arr[1] * (t * (1.0 - u)) +
                      elem_arr[2] * ((1.0 - t) * u) +
                      elem_arr[3] * (t  * u));
      }  
    }  
  return SUCCESS;
  }








template <class T>
OKAY TMatrix<T>::Scale(int row_scale, int col_scale, TMatrix<T> &out) const
  {
  Assert(row_scale > 0 && col_scale > 0);
  if (row_scale < 1 || col_scale < 1)
    return FAILURE;
  if (row_scale == 1 && col_scale == 1)
    {
    out = *this;
    return SUCCESS;
    }

  if (out.Allocate(m_n_rows * row_scale, m_n_cols * col_scale) != SUCCESS)
    return FAILURE;

  for (int i = 0; i < m_n_rows * row_scale; i++)
    {
    double row = double(i) / row_scale;
    int r = (int)floor(row);
    int rn = r + 1;
    if (rn > m_n_rows - 1)
      rn = m_n_rows - 1;
    

    for (int j = 0; j < m_n_cols * col_scale; j++)
      {
      double col = double(j) / col_scale;
      int c = (int)floor(col);
      int cn = c + 1;
      if (cn > m_n_cols - 1)
        cn = m_n_cols - 1;
      

      out(i, j) = (T)((*this)(r, c));
      }  
    }  
  return SUCCESS;
  }





template <class T>
OKAY TMatrix<T>::ScaleToHalf(TMatrix<T> &out) const
  {
  Vect2i res = GetRes();
  Vect2i new_res = res / 2;

  if (out.Allocate(new_res.y, new_res.x) != SUCCESS)
    return FAILURE;

  T *dst = out.Data();
  for (int y = 0; y < new_res.y; y++)
    {
    const T *src = m_data + (SIZE_T)res.x * 2 * y;
    for (int x = 0; x < new_res.x; x++)
      {
      *dst++ = (T)((*src + src[1] + src[res.x] + src[res.x + 1]) * 0.25);
      src += 2;
      }
    }

  return SUCCESS;
  } 







template <class T>
OKAY TMatrix<T>::ZoomOut(int row_n, int col_n, TMatrix<T> &out) const
  {
  Vect2i res = GetRes();
  Vect2i new_res(res.x / col_n, res.y / row_n);

  if (out.Allocate(new_res.y, new_res.x) != SUCCESS)
    return FAILURE;

  T *dst = out.Data();
  double dvd = (double)row_n * col_n;
  for (int y = 0; y < new_res.y; y++)
    {
    for (int x = 0; x < new_res.x; x++)
      {
      T sum = 0;
      for (int yb = 0 ; yb < row_n; yb++)
        {
        const T *src = m_data + (SIZE_T)res.x * ((SIZE_T)row_n * y + yb) + (SIZE_T)col_n * x;
        for (int xb = 0 ; xb < col_n; xb++)
          sum += *src++;
        }
      
      *dst++ = (T)(sum / dvd);
      }
    }

  return SUCCESS;
  } 





template <class T>
T TMatrix<T>::MaxValue() const
  {
  T max_value(0);
  SIZE_T length = (SIZE_T)m_n_rows * (SIZE_T)m_n_cols;
  if (length < 1)
    return max_value;
  max_value = m_data[0];
  for (SIZE_T i = 1; i < length; i++)
    {
    if (max_value < m_data[i])
      max_value = m_data[i];
    }
  return max_value;
  }





template <class T>
T TMatrix<T>::MinValue() const
  {
  T min_value(0);
  SIZE_T length = (SIZE_T)m_n_rows * (SIZE_T)m_n_cols;

  if (length < 1)
    return min_value;
  min_value = m_data[0];
  for (SIZE_T i = 1; i < length; i++)
    {
    if (m_data[i] < min_value)
      min_value = m_data[i];
    }
  return min_value;
  }




template <class T>
bool TMatrix<T>::IsEmpty() const
  {
  return m_n_rows == 0 || m_n_cols == 0;
  }

KIAM_NAMESPACE_END

#endif

