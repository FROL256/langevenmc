








#ifndef _KLBC_BARRAY_HPP_
#define _KLBC_BARRAY_HPP_

#include "base.hpp"
#include "iarray.hpp"
#include "user.hpp"

KIAM_NAMESPACE_START


template <class T>
class TBArray : public IArray
  {
  public:
    
    
    
    static const int OPTIMAL_BLOCK_SIZE = (8 * 64 * 1024 - 32) / sizeof(T);
    
    
    
    

  public:
    
    
    
    explicit TBArray(int the_block_size = OPTIMAL_BLOCK_SIZE);
    
    TBArray(const TBArray<T> &sour);
    
    inline virtual ~TBArray();
    

  public:
    
    
    
    inline T &operator [](int pos);
    
    inline const T &operator [](int pos) const;
    
    inline T *BlockData(int block) const;
    
    inline int BlockIndex(int pos) const;
    
    inline int FirstInBlock(int block_index) const;
    

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
    
    
    OKAY ZeroAllocate(int new_len);
    
    OKAY Grow(int new_len);

  public:
    
    
    
    static void SwapArrays(TBArray<T> &a, TBArray<T> &b);
    

  public:
    
    
    
    OKAY Copy(const TBArray<T> &sour);
    
    TBArray<T> &operator =(const TBArray<T> &sour);
    

  public:

  private:
    
    
    
    OKAY Expand(int needed_size);
    

  private:
    
    
    
    T **data;
    
    int count;
    
    int size;
    
    int block_size;

  };  












template <class T>
TBArray<T>::TBArray(int the_block_size)
  {
  Assert(the_block_size > 0);
  size = 0;
  count = 0;
  block_size = the_block_size;
  data = NULL;
  }




template <class T>
TBArray<T>::TBArray(const TBArray<T> &sour)
  {
  size = 0;
  count = 0;
  data = NULL;
  block_size = sour.block_size;  
  (void)this->Copy(sour);
  }





template <class T>
TBArray<T>::~TBArray()
  {
  if (data == NULL)
    return;
  for (int ic = 0; ic < size; ic++)
    {
    delete[] data[ic];
    DelMemStat(block_size * sizeof(T), data[ic], "TBArray data block");
    }
  delete[] data;
  DelMemStat(size * sizeof(T *), data, "TBArray control block");
  data = NULL;
  }









template <class T>
T &TBArray<T>::operator [](int pos)
  {
  Assert(pos >= 0 && pos < count);
  return data[pos / block_size][pos % block_size];
  }









template <class T>
const T &TBArray<T>::operator [](int pos) const
  {
  Assert(pos >= 0 && pos < count);
  return data[pos / block_size][pos % block_size];
  }









template <class T>
T* TBArray<T>::BlockData(int block) const
  {
  return data[block];
  }









template <class T>
int TBArray<T>::BlockIndex(int pos) const
  {
  return pos / block_size;
  }







template <class T>
int TBArray<T>::FirstInBlock(int block_index) const
  {
  return block_index * block_size;
  }




template <class T>
int TBArray<T>::Length() const
  {
  return count;
  }




template <class T>
int TBArray<T>::Size() const
  {
  return size * block_size;
  }




template <class T>
int TBArray<T>::BlockSize() const
  {
  return block_size;
  }







template <class T>
void TBArray<T>::SetBlockSize(int blsize)
  {
  Assert(blsize > 0);
  block_size = blsize;
  }





template <class T>
OKAY TBArray<T>::Add(const T &elem)
  {
  if (this->Expand(count + 1) != SUCCESS)
    return FAILURE;
  (*this)[count++] = elem;
  Assert(count <= size * block_size);

  return SUCCESS;
  }










template <class T>
OKAY TBArray<T>::Append(const T *elem, int len)
  {
  Assert(len > 0);

  if (this->Expand(count + len) != SUCCESS)
    return FAILURE;

  for (int i = 0; i < len; i++)
    (*this)[count++] = elem[i];

  Assert(count <= size * block_size);

  return SUCCESS;
  }













template <class T>
OKAY TBArray<T>::Insert(const T *elem, int pos, int len)
  {
  Assert(len >= 0 && pos >= 0);

  
  int new_len = (pos > count) ? (pos + len) : (count + len);
  if (this->Expand(new_len) != SUCCESS)
    return FAILURE;

  
  int i;
  int old_count = count;
  count = new_len;
  for (i = old_count; i > pos; )
    {
    i--;
    (*this)[i + len] = (*this)[i];
    }

  
  for (i = 0;  i < len; i++)
    (*this)[pos + i] = elem[i];

  Assert(count <= size * block_size);

  return SUCCESS;
  }  










template <class T>
OKAY TBArray<T>::Put(const T &elem, int pos)
  {

  Assert(pos >= 0);

  if (this->Expand(pos + 1) != SUCCESS)
    return FAILURE;

  if (count <= pos)
    count = pos + 1;

  (*this)[pos++] = elem;
  Assert(count <= size * block_size);
  return SUCCESS;
  }















template <class T>
void TBArray<T>::Exclude(int pos, int len)
  {

  Assert(len > 0 && pos >= 0 && pos < count);

  if (pos + len < count)     
    {
    for (int i = pos; i + len < count; i++)
      (*this)[i] = (*this)[len + i];

    count -= len;
    }
  else
    {
    count = pos;
    }

  return;
  }









template <class T>
void TBArray<T>::Remove(int pos)
  {
  Assert(pos >= 0 && pos < count);

  if (pos < count)
    (*this)[pos] = (*this)[count - 1];
  count--;
  }









template <class T>
void TBArray<T>::Truncate(int new_count)
  {
  Assert(new_count >= 0 && new_count <= count);
  count = new_count;
  }












template <class T>
OKAY TBArray<T>::Resize(int new_count)
  {
  if ((new_count < 0) || (new_count + block_size - 1 < 0))
    {
    
    return User()->InternalError("TBArray: new_size=%d (32 bit overflow?)",
      new_count);
    }
  
  if (new_count == 0)
    {
    for (int ic = 0; ic < size; ic++)
      {
      delete[] data[ic];
      DelMemStat(block_size * sizeof(T), data[ic], "TBArray data block");
      }
    delete[] data;
    DelMemStat(size * sizeof(T *), data, "TBArray control block");
    data = NULL;
    count = size = 0;
    return SUCCESS;
    }

  int req_size = (new_count + block_size - 1) / block_size;
  if (req_size == size)
    return SUCCESS;

  
  T **new_data;
  int old_size = size;
  size = req_size;
  new_data = new T*[size];
  AddMemStat(size * sizeof(T *), new_data, "TBArray control block");
  if (new_data == NULL)
    return FAILURE;
  memset(new_data, 0, sizeof(T*) * size);
  int ret = SUCCESS;
  if (size < old_size)
    {
    for (int ic = 0; ic < old_size; ic++)
      {
      if (ic < size)
        new_data[ic] = data[ic];
      else
        {
        delete [] data[ic];
        DelMemStat(block_size * sizeof(T), data[ic], "TBArray data block");
        }
      }
    }
  else
    {
    for (int ic = 0; ic < size; ic++)
      {
      if (ic < old_size)
        new_data[ic] = data[ic];
      else
        {
        new_data[ic] = new T[block_size];
        AddMemStat(block_size * sizeof(T), new_data[ic], "TBArray data block");
        if (new_data[ic] == NULL)
          {
          ret = FAILURE;
          size = ic;
          break;
          }
        }
      }
    }


  if (count > new_count)
    count = new_count;

  
  delete[] data;
  DelMemStat(old_size * sizeof(T *), data, "TBArray control block");
  data = new_data;
  return ret;
  }  










template <class T>
OKAY TBArray<T>::Allocate(int new_len)
  {
  Assert(new_len >= 0);
  if (new_len <= size * block_size)
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
OKAY TBArray<T>::ZeroAllocate(int new_len)
  {
  int old_size = count / block_size;
  int old_len = count;
  old_len %= block_size;
  if (Allocate(new_len) != SUCCESS)
    return FAILURE;
  if (old_size >= size)
    return SUCCESS;
  memset(data[old_size] + old_len, 0, sizeof(T) * (block_size - old_len));
  for (++old_size ; old_size < size; ++old_size)
    memset(data[old_size], 0 , sizeof(T) * block_size);
  return SUCCESS;
  }










template <class T>
OKAY TBArray<T>::Grow(int new_len)
  {
  Assert(new_len >= 0);
  
  if (new_len <= count)
    return SUCCESS;  

  
  
  if (Expand(new_len) != SUCCESS)
    return FAILURE;

  count = new_len;
  return SUCCESS;
  }








template <class T>
void TBArray<T>::SwapArrays(TBArray<T> &a, TBArray<T> &b)
  {
  Swap(a.data, b.data);
  Swap(a.size, b.size);
  Swap(a.count, b.count);
  Swap(a.block_size, b.block_size);
  }







template <class T>
OKAY TBArray<T>::Copy(const TBArray<T> &sour)
  {
  
  if (block_size != sour.block_size)
    {
    
    Resize();
    this->block_size = sour.block_size;
    }
  
  if (sour.size > 0)
    {
    if (this->Resize(sour.size * block_size - 1) != SUCCESS)
      return FAILURE;
    }
  else
    size = sour.size;

  
  count = sour.count;
  for (int i = 0; i < count; i++)
    (*this)[i] = sour[i];
  return SUCCESS;
  }  







template <class T>
TBArray<T> &TBArray<T>::operator =(const TBArray<T> &sour)
  {
  (void)(this->Copy(sour));
  return(*this);
  }








template <class T>
OKAY TBArray<T>::Expand(int needed_size)
  {
  int new_size = (needed_size + block_size - 1) / block_size;

  if (new_size <= size)
    return SUCCESS;

  return this->Resize(needed_size);
  }


KIAM_NAMESPACE_END
#endif  
