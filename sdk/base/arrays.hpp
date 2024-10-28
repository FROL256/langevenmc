









#ifndef _KLBC_ARRAYS_HPP_
#define _KLBC_ARRAYS_HPP_

#include "base.hpp"
#include "iarray.hpp"
#include "user.hpp"

KIAM_NAMESPACE_START


template <class T>
class TArray : public IArray
  {
  public:
    
    
    
    enum
      {
      
      DEF_BLOCK_SIZE = 10
      };
    

  public:
    
    
    
    explicit TArray(int the_block_size = DEF_BLOCK_SIZE);
    
    inline TArray(const T *val, int length, int the_block_size = DEF_BLOCK_SIZE);
    
    TArray(const TArray<T> &sour);
    
    inline virtual ~TArray();
    

  public:
    
    
    
    inline T &operator [](int pos);
    
    inline const T &operator [](int pos) const;
    
    inline const T *Data() const;
    
    inline T *Data();
    

  public:
    
    
    
    inline int Length() const;
    
    inline int Size() const;
    
    inline int BlockSize() const;
    
    inline void SetBlockSize(int blsize);
    

  public:
    
    
    
    OKAY Add(const T &elem);
    
    OKAY Append(const T *pelem, int len = 1);
    
    OKAY Insert(const T *pelem, int pos, int len = 1);
    
    OKAY Put(const T &elem, int pos);
    

  public:
    
    
    
    void Exclude(int pos, int len = 1);
    
    void Remove(int pos);
    

  public:
    
    
    
    inline void Truncate(int new_count = 0);
    
    OKAY Resize(int new_size = 0);
    
    OKAY Allocate(int new_len);
    
    OKAY SetLength(int new_len);
    
    OKAY Grow(int new_len);
    

  public:
    
    
    
    static void SwapArrays(TArray<T> &a, TArray<T> &b);
    

  public:
    
    
    
    OKAY Copy(const TArray<T> &sour);
    
    OKAY Permute(const int *perm);
    
    TArray<T> &operator =(const TArray<T> &sour);
    
    OKAY SetArray(const TArray<T> &sour);
    
    TArray<T> &operator =(const T &val);
    
    void Set(const T &val);
    
    void Set(const T &val, int pos, int n);
    
    inline TArray<T> &Append(const TArray<T> &sour);
    

  public:

  private:
    
    
    
    OKAY Expand(int needed_size);
    

  protected:
    
    
    
    T *data;
    
    int count;
    

  private:
    
    
    
    int size;
    
    int block_size;
    
  };  












template <class T>
TArray<T>::TArray(int the_block_size)
  {
  Assert(the_block_size > 0);
  size = 0;
  count = 0;
  block_size = the_block_size;
  data = NULL;
  }








template <class T>
TArray<T>::TArray(const T *val, int length, int the_block_size)
  {
  Assert(the_block_size > 0);
  size = 0;
  count = 0;
  data = NULL;
  block_size = the_block_size;

  
  if (Resize(length) != SUCCESS)
    return;

  
  count = length;
  for (int i = 0; i < count; i++)
    data[i] = val[i];
  }




template <class T>
TArray<T>::TArray(const TArray<T> &sour)
  {
  size = 0;
  count = 0;
  data = NULL;
  block_size = sour.block_size;  
  (void)this->Copy(sour);
  }





template <class T>
TArray<T>::~TArray()
  {
  delete[] data;
  if (data != NULL)
    DelMemStat(size * sizeof(T), data, "TArray");
  }









template <class T>
T &TArray<T>::operator [](int pos)
  {
  Assert(pos >= 0 && pos < count);
  return data[pos];
  }









template <class T>
const T &TArray<T>::operator [](int pos) const
  {
  Assert(pos >= 0 && pos < count);
  return data[pos];
  }




template <class T>
const T *TArray<T>::Data() const
  {
  return data;
  }




template <class T>
T *TArray<T>::Data()
  {
  return data;
  }




template <class T>
int TArray<T>::Length() const
  {
  return count;
  }




template <class T>
int TArray<T>::Size() const
  {
  return size;
  }




template <class T>
int TArray<T>::BlockSize() const
  {
  return block_size;
  }





template <class T>
void TArray<T>::SetBlockSize(int blsize)
  {
  Assert(blsize > 0);
  block_size = blsize;
  }





template <class T>
OKAY TArray<T>::Add(const T &elem)
  {
  if (this->Expand(count + 1) != SUCCESS)
    return FAILURE;
  data[count++] = elem;
  Assert(count <= size);

  return SUCCESS;
  }










template <class T>
OKAY TArray<T>::Append(const T *elem, int len)
  {
  Assert(len >= 0);  

  if (this->Expand(count + len) != SUCCESS)
    return FAILURE;

  for (int i = 0; i < len; i++)
    data[count++] = elem[i];

  Assert(count <= size);

  return SUCCESS;
  }













template <class T>
OKAY TArray<T>::Insert(const T *elem, int pos, int len)
  {
  Assert(len >= 0 && pos >= 0);

  
  int new_len = (pos > count) ? (pos + len) : (count + len);
  if (this->Expand(new_len) != SUCCESS)
    return FAILURE;

  
  int i;
  for (i = count; i > pos; )
    {
    i--;
    data[i + len] = data[i];
    }

  
  for (i = 0;  i < len; i++)
    data[pos + i] = elem[i];

  count = new_len;
  Assert(count <= size);

  return SUCCESS;
  }  










template <class T>
OKAY TArray<T>::Put(const T &elem, int pos)
  {
  Assert(pos >= 0);

  if (this->Expand(pos + 1) != SUCCESS)
    return FAILURE;

  data[pos++] = elem;
  if (count < pos)
    count = pos;

  Assert(count <= size);

  return SUCCESS;
  }  














template <class T>
void TArray<T>::Exclude(int pos, int len)
  {
  Assert(len >= 0 && pos >= 0 && pos < count);

  if (pos + len < count)     
    {
    for (int i = pos; i + len < count; i++)
      data[i] = data[len + i];

    count -= len;
    }
  else
    {
    count = pos;
    }

  return;
  }  









template <class T>
void TArray<T>::Remove(int pos)
  {
  Assert(pos >= 0 && pos < count);

  count--;
  if (pos < count)
    data[pos] = data[count];
  }












template <class T>
OKAY TArray<T>::Resize(int new_size)
  {
  if (new_size < 0)
    {
    
    return User()->InternalError("TArray: new_size=%d < 0 (32 bit overflow?)",
      new_size);
    }
  Assert(new_size >= 0);
  if (new_size == size)
    return SUCCESS;

  
  if (new_size == 0)
    {
    delete[] data;
    if (data != NULL)
      DelMemStat(size * sizeof(T), data, "TArray");
    data = NULL;
    count = size = 0;
    return SUCCESS;
    }

  
  if (MAX_SIZE_T / new_size < sizeof(T))
    {
    
    return User()->InternalError("TArray: new_size=%d * %d (32 bit overflow?)",
      new_size, (int)sizeof(T));
    }
  T *new_data = new T[new_size];
  AddMemStat(new_size * sizeof(T), new_data, "TArray");
  if (new_data == NULL)
    return FAILURE;
  if (data != NULL)
    DelMemStat(size * sizeof(T), data, "TArray");
  
  size = new_size;
  if (count > size)
    count = size;

  
  for (int i = 0; i < count; i++)
    new_data[i] = data[i];

  
  delete[] data;
  data = new_data;
  return SUCCESS;
  }  









template <class T>
void TArray<T>::Truncate(int new_count)
  {
  Assert(new_count >= 0 && new_count <= count);
  count = new_count;
  }










template <class T>
OKAY TArray<T>::Allocate(int new_len)
  {
  Assert(new_len >= 0);
  if (new_len < 0)
    {
    
    return User()->InternalError("TArray::Alloc(): 32 bit overflow?", new_len);
    }
  if (new_len <= size)
    {
    
    count = new_len;
    return SUCCESS;
    }
  
  if (Resize(new_len) != SUCCESS)
    return FAILURE;

  count = new_len;
  return SUCCESS;
  }  








template <class T>
OKAY TArray<T>::SetLength(int new_len)
  {
  Assert(new_len >= 0);
  
  if (Resize(new_len) != SUCCESS)
    return FAILURE;
  count = new_len;
  return SUCCESS;
  }









template <class T>
OKAY TArray<T>::Grow(int new_len)
  {
  Assert(new_len >= 0);
  if (new_len < 0)
    return User()->InternalError("TArray::Grow(): 32 bit overflow?", new_len);
  
  if (new_len <= count)
    return SUCCESS;  
  
  
  if (Expand(new_len) != SUCCESS)
    return FAILURE;
  count = new_len;
  return SUCCESS;
  }








template <class T>
void TArray<T>::SwapArrays(TArray<T> &a, TArray<T> &b)
  {
  Swap(a.data, b.data);
  Swap(a.size, b.size);
  Swap(a.count, b.count);
  Swap(a.block_size, b.block_size);
  }







template <class T>
OKAY TArray<T>::Copy(const TArray<T> &sour)
  {
  
  if (this->Resize(sour.size) != SUCCESS)
    return FAILURE;

  
  count = sour.count;
  for (int i = 0; i < count; i++)
    data[i] = sour[i];

  return SUCCESS;
  }







template <class T>
TArray<T> &TArray<T>::operator =(const TArray<T> &sour)
  {
  (void)(this->Copy(sour));
  return(*this);
  }







template <class T>
TArray<T> &TArray<T>::operator =(const T &val)
  {
  Set(val);
  return(*this);
  }






template <class T>
void TArray<T>::Set(const T &val)
  {
  for (int i = 0; i < count; i++)
    data[i] = val;
  }










template <class T>
void TArray<T>::Set(const T &val, int pos, int n)
  {
  for (int i = 0; i < n; i++)
    data[pos + i] = val;
  }








template <class T>
OKAY TArray<T>::Expand(int needed_size)
  {
  if (needed_size < 0)
    return User()->InternalError("TArray::Expand(): 32 bit overflow?", needed_size);

  if (needed_size <= size)
    return SUCCESS;

  
  if (block_size <= 0)
    block_size = 8; 
  
  while (needed_size > block_size)
    block_size += block_size;
  
  return this->Resize(block_size);
#if 0
  int new_size = block_size;
  if (needed_size > block_size)
    {
    const int large_blk_size = MAX_INT / 8;
    if (needed_size < large_blk_size)
      {
      
      new_size = size + (((needed_size - size) + (block_size - 1)) / block_size) * block_size;
      }
    else
      {
      
      int n_free_blocks = (MAX_INT - needed_size) / large_blk_size;
      new_size = MAX_INT - n_free_blocks * large_blk_size;
      }
    }

  return this->Resize(new_size);
#endif  
  }







template <class T>
OKAY TArray<T>::Permute(const int *perm)
  {
  if (count <= 1)
    {
    return SUCCESS;
    }

  
  T *new_data = new T[count];
  AddMemStat(count * sizeof(T), new_data, "TArray");
  if (new_data == NULL)
    return FAILURE;
  Assert(data != NULL);
  DelMemStat(size * sizeof(T), data, "TArray");

  
  size = count;

  
  for (int i = 0; i < count; i++)
    new_data[i] = data[perm[i]];


  
  delete[] data;
  data = new_data;

  return SUCCESS;
  }  





template <class T>
TArray<T> &TArray<T>::Append(const TArray<T> &sour)
  {
  Append(sour.Data(), sour.Length());
  return *this;
  }






template <class T>
OKAY TArray<T>::SetArray(const TArray<T> &sour)
  {
  
  if (Resize(sour.count) != SUCCESS)
    return FAILURE;

  size = sour.count;
  count = size;
  
  for (int i = 0; i < count; i++)
    data[i] = sour[i];
  return SUCCESS;
  }

KIAM_NAMESPACE_END

#endif

