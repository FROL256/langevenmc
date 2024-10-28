








#ifndef _AT58_ENVI_HPP_
#define _AT58_ENVI_HPP_

#include "export.h"
#include "str.hpp"

KIAM_NAMESPACE_START


class IntMemoryException
  {
  public:
  private:
    
    INT64 size;
  };  


class Envi
  {
  public:
    
    
    
    INTAPI_BASE static void GetMemSize(int *used, int *limit,
      int *phys_free, int *phys_limit, int *peak_ws, int *peak_pf);
    
    INTAPI_BASE static SIZE_T AvailMemBlockSize();
    
    INTAPI_BASE static int Bytes2MBytes(SIZE_T bytes);
    

  public:
    
    
    
    INTAPI_BASE static Str GetEnv(const char *name);
    
    INTAPI_BASE static OKAY PutEnv(const char *name, const char *value);
    
    INTAPI_BASE static Str GetFrom(const Str &env, const Str &name);
    
    INTAPI_BASE static int GetInt(const Str &env, const Str &name, 
      int def_val);
    

  public:
    
    
    
    INTAPI_BASE static void *AlignedMalloc(SIZE_T size, int align);
    
    INTAPI_BASE static void AlignedFree(void *ptr);
    
    INTAPI_BASE static void *AlignedMemBlockPtr(void *ptr);
    

  public:
    
    
    
    INTAPI_BASE static Str FormatErrorMsg(unsigned error);
    

  public:

    
    INTAPI_BASE static void Beep();
  };  

KIAM_NAMESPACE_END

#endif

