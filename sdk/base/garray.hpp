








#ifndef _KLBC_GARRAY_HPP_
#define _KLBC_GARRAY_HPP_

#include "arrays.hpp"

KIAM_NAMESPACE_START



template <class T>
class GArray : public TArray<T>
  {
  public:
    
    
    
    explicit GArray(int the_block_size = TArray<T>::DEF_BLOCK_SIZE);
    
    inline GArray(const T *val, int length,
                  int the_block_size = TArray<T>::DEF_BLOCK_SIZE);
    
    GArray(const GArray<T> &sour);
    

  public:
    
    
    
    bool operator ==(const GArray<T> &src) const;
    

  public:
    
    
    
    bool Find(const T &elem, int *pos = NULL) const;
    
  };  












template <class T>
GArray<T>::GArray(int the_block_size) : TArray<T>(the_block_size)
  {
  }








template <class T>
GArray<T>::GArray(const T *val, int length, int the_block_size)
  : TArray<T>(val, length, the_block_size)
  {
  }




template <class T>
GArray<T>::GArray(const GArray<T> &sour) : TArray<T>(sour)
  {
  }








template <class T>
bool GArray<T>::operator ==(const GArray<T> &src) const
  {
  if (this->count != src.count)
    return false;
  for (int i = 0; i < this->count; i++)
    if (!(this->data[i] == src.data[i]))
      return false;
  return true;
  }











template <class T>
bool GArray<T>::Find(const T &elem, int *pos) const
  {
  int len = this->Length();
  for (int i = 0; i < len; i++)
    {
    if (elem == this->operator[](i))
      {
      if (pos != NULL)
        *pos = i;
      return YES;
      }
    }
  return NO;
  }

KIAM_NAMESPACE_END
#endif
