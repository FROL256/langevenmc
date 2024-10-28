










#ifndef _KLBC_MARRAY_HPP_
#define _KLBC_MARRAY_HPP_

#include <base/garray.hpp>

KIAM_NAMESPACE_START




template <class T>
class MArray : public GArray<T>
  {
  public:
    
    
    
    explicit MArray(int the_block_size = 10);
    
    inline MArray(const T *val, int length,
                  int the_block_size = TArray<T>::DEF_BLOCK_SIZE);
    
    inline MArray(const MArray<T> &sour);
    

    
    bool operator == (const MArray<T> &another) const;
    
    inline bool operator != (const MArray<T> &another) const;
    
    inline MArray &operator *=(const double &c);
    
    inline MArray<T> &operator += (const TArray<T> &sour);

    
    
    
    static void QSort(T *data, int count);

    
    static void QSort(T *data, int count, bool (*less)(const T &a, const T &b));

    
    static void QSort(const T *data, int count, TArray<int> &perm);

    
    
    static void StableSort(T *data, int count);
    
    
    static void StableSort(const T *data, int count, TArray<int> &perm);
    
    
    static void StableSortLessEqual(T *data, int count);
    

    
    
    
    inline void QSort();

    
    inline void QSort(TArray<int> &perm) const;

    
    inline void QSort(int len);

    
    inline void QSort(bool (*less)(const T &a, const T &b));

    
    inline void QSort(int len, bool (*less)(const T &a, const T &b));

    
    
    inline void StableSort();
    

    
    
    
    
    
    inline int BinarySearch(const T &x) const;

    
    inline static int BinarySearch(const T &x, const T *data, int n);
    

    
    
    
    
    
    inline int BinarySearchRev(const T &x) const;
    

    
    
    
    
    
    inline static int BinarySearchRev(const T &x, const T *data, int n);
    

    
    inline T MaxValue() const;
    
    inline T MinValue() const;
    
    inline int MaxValueIndex() const;
    
    inline T Sum() const;

    
    inline OKAY ResizeLinear(int n, MArray<T> &out) const;
    
    inline void Pack();
  };  














template <class T>
MArray<T>::MArray(int the_block_size) : GArray<T>(the_block_size)
  {
  }








template <class T>
MArray<T>::MArray(const T *val, int length, int the_block_size)
  : GArray<T>(val, length, the_block_size)
  {
  }





template <class T>
MArray<T>::MArray(const MArray<T> &sour) : GArray<T>(sour)
  {
  }








template <class T>
bool MArray<T>::operator == (const MArray<T> &another) const
  {
  int len = this->Length();
  if (another.Length() != len)
    return false;
  for (int i = 0; i < len; i++)
    {
    if (this->data[i] != another.data[i])
      return false;
    }
  return true;
  }








template <class T>
bool MArray<T>::operator != (const MArray<T> &another) const
  {
  return !(this->operator == (another));
  }







template <class T>
MArray<T> &MArray<T>::operator *=(const double &c)
  {
  for (int i = 0; i < this->count; i++)
    this->data[i] = (T)(this->data[i] * c);
  return *this;
  }  







template <class T>
MArray<T> &MArray<T>::operator += (const TArray<T> &sour)
  {
  Assert(this->count == sour.count);
  for (int i = 0; i < this->count; i++)
    this->data[i] += sour.data[i];
  return *this;
  }







template <class T>
void MArray<T>::QSort(T *data, int count)
  {
  
  Assert(this->count <= 2147483647);  
  const int QS_STACK_SIZE = 130;  
  int stack[QS_STACK_SIZE];
  int stck_top = 0; 

  
  int i, j, k;
  int ir = count - 1; 
  int il = 0; 

  
  T a;

  for ( ; ; )
    {
    
    if (ir - il <= 6)
      {
      for (j = il + 1; j <= ir; j++)
        {
        a = data[j];
        for (i = j - 1; i >= il; i--)
          {
          if (data[i] < a || data[i] == a) 
            break;
          data[i + 1] = data[i];
          }
        data[i + 1] = a;
        }
      if (stck_top == 0) 
        break;

      
      ir = stack[stck_top--];
      il = stack[stck_top--];
      }
    else
      {
      k = (il + ir) >> 1; 
                          
                          

      Swap(data[k], data[il + 1]);
      if (data[ir] < data[il])
        Swap(data[il], data[ir]);
      if (data[ir] < data[il + 1])
        Swap(data[il + 1], data[ir]);
      if (data[il + 1] < data[il])
        Swap(data[il], data[il + 1]);

      i = il + 1; 
      j = ir;
      a = data[il + 1]; 

      for ( ; ; )
        {
        do
          i++;
        while (data[i] < a); 
        do
          j--;
        while (a < data[j]); 
        if (j < i)
          break; 
        Swap(data[i], data[j]); 
        }

      data[il + 1] = data[j]; 
      data[j] = a;
      stck_top += 2;
      Assert(stck_top < QS_STACK_SIZE);

      if (ir - i + 1 >= j - il)
        {
        stack[stck_top] = ir;
        stack[stck_top - 1] = i;
        ir = j - 1;
        }
      else
        {
        stack[stck_top] = j - 1;
        stack[stck_top - 1] = il;
        il = i;
        }
      }
    }
  } 













template <class T>
void MArray<T>::QSort(const T *data, int count, TArray<int> &perm)
  {
  
  Assert(count <= 2147483647);  
  const int QS_STACK_SIZE = 130;  
  int stack[QS_STACK_SIZE];
  int stck_top = 0; 
  Assert(count <= perm.Length());

  
  int i, j, k;
  int ir = count - 1; 
  int il = 0; 

  
  T a;
  int b;

  for ( ; ; )
    {
    
    if (ir - il <= 6)
      {
      for (j = il + 1; j <= ir; j++)
        {
        a = data[perm[j]];
        b = perm[j];
        for (i = j - 1; i >= il; i--)
          {
          if (data[perm[i]] < a || data[perm[i]] == a) 
            break;
          perm[i + 1] = perm[i];
          }
        perm[i + 1] = b;
        }
      if (stck_top == 0) 
        break;

      
      ir = stack[stck_top--];
      il = stack[stck_top--];
      }
    else
      {
      k = (il + ir) >> 1; 
                          
                          

      Swap(perm[k], perm[il + 1]);
      if (data[perm[ir]] < data[perm[il]])
        Swap(perm[il], perm[ir]);
      if (data[perm[ir]] < data[perm[il + 1]])
        Swap(perm[il + 1], perm[ir]);
      if (data[perm[il + 1]] < data[perm[il]])
        Swap(perm[il], perm[il + 1]);

      i = il + 1; 
      j = ir;
      a = data[perm[il + 1]]; 
      b = perm[il + 1];

      for ( ; ; )
        {
        do
          i++;
        while (data[perm[i]] < a); 
        do
          j--;
        while (a < data[perm[j]]); 
        if (j < i)
          break; 
        Swap(perm[i], perm[j]); 
        }

      perm[il + 1] = perm[j]; 
      perm[j] = b;
      stck_top += 2;
      Assert(stck_top < QS_STACK_SIZE);

      if (ir - i + 1 >= j - il)
        {
        stack[stck_top] = ir;
        stack[stck_top - 1] = i;
        ir = j - 1;
        }
      else
        {
        stack[stck_top] = j - 1;
        stack[stck_top - 1] = il;
        il = i;
        }
      }
    }
  } 














template <class T>
void MArray<T>::QSort(T *data, int count, bool (*less)(const T &a, const T&b))
  {
  
  Assert(count <= 2147483647);  
  const int QS_STACK_SIZE = 130;  
  int stack[QS_STACK_SIZE];
  int stck_top = 0; 

  
  int i, j, k;
  int ir = count - 1; 
  int il = 0; 

  
  T a;

  for ( ; ; )
    {
    
    if (ir - il <= 6)
      {
      for (j = il + 1; j <= ir; j++)
        {
        a = data[j];
        for (i = j - 1; i >= il; i--)
          {
          if (less(data[i],a) || (!less(data[i], a) && !less(a, data[i])))
            break;
          data[i + 1] = data[i];
          }
        data[i + 1] = a;
        }
      if (stck_top == 0) break;

      
      ir = stack[stck_top--];
      il = stack[stck_top--];
      }
    else
      {
      k = (il + ir) >> 1; 
                          
                          

      Swap(data[k], data[il + 1]);
      if (less(data[ir], data[il]))
        Swap(data[il], data[ir]);
      if (less(data[ir], data[il + 1]))
        Swap(data[il + 1], data[ir]);
      if (less(data[il + 1], data[il]))
        Swap(data[il], data[il + 1]);

      i = il + 1; 
      j = ir;
      a = data[il + 1]; 

      for ( ; ; )
        {
        do i++; while (less(data[i], a)); 
        do j--; while (less(a, data[j])); 
        if (j < i) break; 
        Swap(data[i], data[j]); 
        }

      data[il + 1] = data[j]; 
      data[j] = a;
      stck_top += 2;
      Assert(stck_top < QS_STACK_SIZE);

      if (ir - i + 1 >= j - il)
        {
        stack[stck_top] = ir;
        stack[stck_top - 1] = i;
        ir = j - 1;
        }
      else
        {
        stack[stck_top] = j - 1;
        stack[stck_top - 1] = il;
        il = i;
        }
      }
    }
  }



template <class T>
void MArray<T>::QSort()
  {
  QSort(this->data, this->count);
  }





template <class T>
void MArray<T>::Pack()
  {
  QSort();
  int prev = 0;
  for (int i = 1; i < this->count; i++)
    {
    if (this->data[i] == this->data[prev])
      continue;
    this->data[++prev] = this->data[i];
    }
  this->Resize(prev + 1);
  }












template <class T>
void MArray<T>::QSort(TArray<int> &perm) const
  {
  QSort(this->data, this->count, perm);
  }





template <class T>
void MArray<T>::QSort(int len)
  {
  QSort(this->data, len);
  }












template <class T>
void MArray<T>::QSort(bool (*less)(const T &a, const T &b))
  {
  QSort(this->data, this->count, less);
  }














template <class T>
void MArray<T>::QSort(int len, bool (*less)(const T &a, const T &b))
  {
  QSort(this->data, len, less);
  }















template <class T>
int MArray<T>::BinarySearch(const T &x, const T *data, int n)
  {
  int mid, low, high;
  low = 0;
  high = n - 1;



  
  while (low <= high)
    {
    mid = (low + high) >> 1;
    if (x < data[mid])
      high = mid - 1;
    else
      low = mid + 1;
    }
  Assert((0 <= low) && (low <= n));;
  return low;
  }  













template <class T>
int MArray<T>::BinarySearch(const T &x) const
  {
  return BinarySearch(x, this->data, this->count);
  }















template <class T>
int MArray<T>::BinarySearchRev(const T &x, const T* data, int n)
  {
  int mid, low, high;
  low = 0;
  high = n - 1;




  
  while (low <= high)
    {
    mid = (low + high) >> 1;
    if (data[mid] < x)
      high = mid - 1;
    else
      low = mid + 1;
    }
  Assert((0 <= low) && (low <= n));;
  return low;
  }  













template <class T>
int MArray<T>::BinarySearchRev(const T &x) const
  {
  return BinarySearchRev(x, this->data, this->count);
  }



template <class T>
class ValOrd
  {
  public:
    
    inline ValOrd();
    
    inline ValOrd(T val, int ord);
    
    inline bool operator == (const ValOrd<T> &u) const;
    
    inline bool operator < (const ValOrd<T> &u) const;
  public:
    
    T m_val;
    
    int m_ord;
  };



template <class T>
ValOrd<T>::ValOrd()
  {
  }






template <class T>
ValOrd<T>::ValOrd(T val, int ord)
  {
  m_val = val;
  m_ord = ord;
  }






template <class T>
bool ValOrd<T>::operator == (const ValOrd<T> &u) const
  {
  return (m_val == u.m_val && m_ord == u.m_ord);
  }






template <class T>
bool ValOrd<T>::operator < (const ValOrd<T> &u) const
  {
  return (m_val == u.m_val ? (m_ord < u.m_ord) : (m_val < u.m_val));
  }














template <class T>
void MArray<T>::StableSort(const T *data, int count, TArray<int> &perm)
  {
  
  MArray<ValOrd<T> > sort_arr;
  sort_arr.Allocate(count);

  for (int i = 0; i < count; i++)
    sort_arr[i] = ValOrd<T>(data[i], i);

  MArray<ValOrd<T> >::QSort(sort_arr.Data(), count, perm);
  }







template <class T>
void MArray<T>::StableSort(T *data, int count)
  {
  
  MArray<ValOrd<T> > sort_arr;
  sort_arr.Allocate(count);

  for (int i = 0; i < count; i++)
    sort_arr[i] = ValOrd<T>(data[i], i);

  MArray<ValOrd<T> >::QSort(sort_arr.Data(), count);

  for (int i = 0; i < count; i++)
    data[i] = sort_arr[i].m_val;
  }







template <class T>
class ValOrdLessEqual
  {
  public:
    
    inline ValOrdLessEqual();
    
    inline ValOrdLessEqual(T val, int ord);
    
    inline bool operator == (const ValOrdLessEqual<T> &u) const;
    
    inline bool operator < (const ValOrdLessEqual<T> &u) const;
  public:
    
    T m_val;
    
    int m_ord;
  };



template <class T>
ValOrdLessEqual<T>::ValOrdLessEqual()
  {
  }






template <class T>
ValOrdLessEqual<T>::ValOrdLessEqual(T val, int ord)
: m_val(val), m_ord(ord)
  {
  }






template <class T>
bool ValOrdLessEqual<T>::operator == (const ValOrdLessEqual<T> &u) const
  {
  return (m_val.Equal(u.m_val) && m_ord == u.m_ord);
  }






template <class T>
bool ValOrdLessEqual<T>::operator < (const ValOrdLessEqual<T> &u) const
  {
  return (m_val.Equal(u.m_val) ? (m_ord < u.m_ord) : (m_val.Less(u.m_val)));
  }









template <class T>
void MArray<T>::StableSortLessEqual(T *data, int count)
  {
  
  MArray<ValOrdLessEqual<T> > sort_arr;
  sort_arr.Allocate(count);

  for (int i = 0; i < count; i++)
    sort_arr[i] = ValOrdLessEqual<T>(data[i], i);

  MArray<ValOrdLessEqual<T> >::QSort(sort_arr.Data(), count);

  for (int i = 0; i < count; i++)
    data[i] = sort_arr[i].m_val;
  }




template <class T>
void MArray<T>::StableSort()
  {
  StableSort(this->data, this->count);
  }





template <class T>
T MArray<T>::MaxValue() const
  {
  T max_value(0);
  if (this->count < 1)
    return max_value;
  max_value = this->data[0];
  for (int i = 1; i < this->count; i++)
    {
    if (max_value < this->data[i])
      max_value = this->data[i];
    }
  return max_value;
  }





template <class T>
T MArray<T>::MinValue() const
  {
  T min_value(0);
  if (this->count < 1)
    return min_value;
  min_value = this->data[0];
  for (int i = 1; i < this->count; i++)
    {
    if (this->data[i] < min_value)
      min_value = this->data[i];
    }
  return min_value;
  }






template <class T>
int MArray<T>::MaxValueIndex() const
  {
  T max_value(0);
  this->ind = 0;
  if (this->count < 1)
    return -1;
  this->ind = 0;
  max_value = this->data[0];
  for (int i = 1; i < this->count; i++)
    {
    if (max_value < this->data[i])
      {
      max_value = this->data[i];
      this->ind = i;
      }
    }
  return this->ind;
  }




template <class T>
T MArray<T>::Sum() const
  {
  T sum(0);
  for (int i = 0; i < this->count; i++)
    sum += this->data[i];
  return sum;
  }







template <class T>
OKAY MArray<T>::ResizeLinear(int n, MArray<T> &out) const
  {
  Assert(n > 0 && this->count > 0);
  if (n == this->count)
    {
    out = *this;
    return SUCCESS;
    }

  if (out.Allocate(n) != SUCCESS)
    return FAILURE;

  if (n == 1)
    {
    out[0] = (*this)[0];
    return SUCCESS;
    }

  for (int i = 0; i < n; i++)
    {
    double row = double(i) * (this->count - 1) / double(n - 1);
    int r = (int)this->floor(row);
    int rn = r + 1;
    if (rn > this->count - 1)
      rn = this->count - 1;
    double u = row - r;

    out[i] = (*this)[r]  * (1.0 - u) + (*this)[rn] * u;
    }  

  return SUCCESS;
  }


KIAM_NAMESPACE_END
#endif
