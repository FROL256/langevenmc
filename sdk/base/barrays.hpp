








#ifndef _KLBM_BARRAYS_HPP_
#define _KLBM_BARRAYS_HPP_

#include "arrays.hpp"

KIAM_NAMESPACE_START


template <class T> class BArray;


template <class T>
class BArray
  {
  public:
    
    inline virtual ~BArray();

    
    inline int Length() const;

  public:
    
    
    
    inline T &operator [](int i);
    
    inline const T &operator [](int i) const;
    
    inline T *Data();
    
    inline const T *Data() const;
    

  public:
    
    
    
    inline BArray<T> &operator =(const BArray<T> &src);
    
    inline BArray<T> &operator =(const T &src);
    
    inline void SetVal(const T &val);
    
    inline void Set(const T *ptr);
    
    inline void Add(const T *ptr);
    
    
    inline BArray &operator *=(const double &c);
    
    inline BArray &operator *=(const float &c);
    
    inline void Scale(const T &v);

  protected:
    
    
    
    inline BArray(T *memblock, int size);
    
    inline BArray(const BArray &from);
    

  protected:
    
    
    
    inline void Create(T *memblock, int size);
    
    inline virtual void Copy(const BArray &src);
    

    
    inline T *XData() const;

  private:
    
    T *data;
    
    int count;
  };  


template <class T>
class SArray : public BArray<T>
  {
  public:
    
    
    
    inline SArray(T *memblock, int size);
    
    inline SArray(const BArray<T> &src);
    
    inline virtual ~SArray();
    

  public:
    
    
    
    inline SArray<T> &operator =(const BArray<T> &src);
    
    inline SArray<T> &operator =(const T &src);
  };  



template <class T>
class WArray : public BArray<T>
  {
  public:
    
    
    
    inline WArray();
    
    inline WArray(T *memblock, int size);
    
    inline WArray(const BArray<T> &src);
    
    inline WArray(const WArray<T> &src);
    

  public:
    
    
    
    inline WArray<T> &operator =(const WArray<T> &src);
    
    inline WArray<T> &operator =(const BArray<T> &src);
  };  


template <class T>
class Array : public BArray<T>
  {
  public:
    
    
    
    inline Array();
    
    inline Array(int n);
    
    inline Array(const Array<T> &from);
    
    inline virtual ~Array();
    

  public:
    
    
    
    inline Array<T> &operator =(const BArray<T> &src);
    
    inline Array<T> &operator =(const T &src);
    

  public:

  protected:
    
    inline void Free();
    
    inline OKAY Allocate(int nc);
    
    inline virtual void Copy(const BArray<T> &src);
  };  










template <class T>
BArray<T>::~BArray()
  {
  }




template <class T>
int BArray<T>::Length() const
  {
  return count;
  }





template <class T>
T &BArray<T>::operator [](int i)
  {
  Assert (i >=0 && i < count);
  return data[i];
  }





template <class T>
const T &BArray<T>::operator [](int i) const
  {
  Assert (i >=0 && i < count);
  return data[i];
  }








template <class T>
BArray<T> &BArray<T>::operator =(const BArray<T> &src)
  {
  Copy(src); 
  return *this;
  }







template <class T>
BArray<T> &BArray<T>::operator =(const T &src)
  {
  if (data != NULL)
    {
    for (int i = 0; i < count; i++)
      data[i] = src;
    }
  else
    Assert(false);
  return *this;
  }




template <class T>
void BArray<T>::SetVal(const T &val)
  {
  for (int i = 0; i < count; i++)
    data[i] = val;
  }




template <class T>
void BArray<T>::Set(const T *ptr)
  {
  for (int i = 0; i < count; i++)
    data[i] = ptr[i];
  }




template <class T>
void BArray<T>::Add(const T *ptr)
  {
  for (int i = 0; i < count; i++)
    data[i] += ptr[i];
  }







template <class T>
BArray<T> &BArray<T>::operator *=(const double &c)
  {
  for (int i = 0; i < count; i++)
    data[i] *= c;
  return *this;
  }  







template <class T>
BArray<T> &BArray<T>::operator *=(const float &c)
  {
  for (int i = 0; i < count; i++)
    data[i] *= c;
  return *this;
  }  






template <class T>
T *BArray<T>::Data()
  {
  return data;
  }






template <class T>
const T *BArray<T>::Data() const
  {
  return data;
  }






template <class T>
T *BArray<T>::XData() const
  {
  return data;
  }








template <class T>
BArray<T>::BArray(T *memblock, int size)
  {
  data = memblock;
  count = size;
  }






template <class T>
BArray<T>::BArray(const BArray &from)
  {
  data = from.data;
  count = from.count;
  }











template <class T>
void BArray<T>::Create(T *memblock, int size)
  {
  data = memblock; 
  count = size;
  }












template <class T>
void BArray<T>::Copy(const BArray &src)
  {
  if (&src != this)
    {
    if (data != NULL && src.data != NULL)
      {
      int i, n = Min(Length(), src.Length());
      for (i = 0; i < n; i++)
        data[i] = src.data[i];
      }
    else
      Assert(false);
    }
  }  





template <class T>
inline void BArray<T>::Scale(const T &v)
  {
  for (int i = 0; i < Length(); i++)
    data[i] *= v;
  }






template <class T>
inline void Set(BArray<T> &a, const BArray<T> &b)
  {
  Assert(a.Length() == b.Length());
  for (int i = 0; i < a.Length(); i++)
    a[i] = b[i];
  }






template <class T>
inline void Add(BArray<T> &a, const BArray<T> &b)
  {
  Assert(a.Length() == b.Length());
  for (int i = 0; i < a.Length(); i++)
    a[i] += b[i];
  }






template <class T>
WArray<T>::WArray() : BArray<T>(NULL, 0)
  {
  }







template <class T>
WArray<T>::WArray(T *memblock, int size)
  : BArray<T>(memblock, size)
  {
  }




template <class T>
WArray<T>::WArray(const WArray<T> &src)
  : BArray<T>(src)
  {
  }




template <class T>
WArray<T>::WArray(const BArray<T> &src)
  : BArray<T>(src)
  {
  }







template <class T>
WArray<T> &WArray<T>::operator =(const BArray<T> &src)
  {
  Create(src.Data(), src.Length());
  return *this;
  }







template <class T>
WArray<T> &WArray<T>::operator =(const WArray<T> &src)
  {
  Create(src.XData(), src.Length());
  return *this;
  }











template <class T>
SArray<T>::SArray(T *memblock, int size) : 
  BArray<T>(memblock, size)
  {
  }




template <class T>
SArray<T>::SArray(const BArray<T> &src) : 
  BArray<T>(src)
  {
  }





template <class T>
SArray<T>::~SArray()
  {
  }








template <class T>
SArray<T> &SArray<T>::operator =(const BArray<T> &src)
  {
  Copy(src);
  return *this;
  }







template <class T>
SArray<T> &SArray<T>::operator =(const T &src)
  {
  BArray<T>::operator=(src);
  return *this;
  }






template <class T>
Array<T>::~Array()
  {
  Free();
  }





template <class T>
Array<T>::Array()
  : BArray<T>(NULL, 0)
  {
  }






template <class T>
Array<T>::Array(int n)
  : BArray<T>(n > 0 ? new T[n] : NULL, n)
  {
  Assert(n >= 0);
  };







template <class T>
Array<T>::Array(const Array<T> &from)
  : BArray<T>(new T[from.Length()],
  from.Length())
  {
  BArray<T>::operator=(from);
  }








template <class T>
Array<T> &Array<T>::operator =(const BArray<T> &src)
  {
  Copy(src);
  return *this;
  }





template <class T>
Array<T> &Array<T>::operator =(const T &src)
  {
  BArray<T>::operator =(src);
  return *this;
  }









template <class T> void
Array<T>::Copy(const BArray<T> &src)
  {
  
  Allocate(src.Length());

  
  BArray<T>::Copy(src);
  }




template <class T>
void Array<T>::Free()
  {
  if (this->Length() > 0 && this->Data())
    {
    T* data = this->Data();
    delete [] data;

    
    this->Create(NULL, 0);
    }
  }









template <class T> OKAY Array<T>::Allocate(int nc)
  {
  if (nc < 0)
    {
    
    Assert(false);
    return FAILURE;
    }
  if (nc == this->Length())
    return SUCCESS;

  
  Free();
  T *memblock = new T[nc];
  if (!memblock)
    {
    this->Create(NULL, 0);
    return FAILURE;
    }

  
  Create(memblock, nc);
  return SUCCESS;
  }  

KIAM_NAMESPACE_END
#endif 
