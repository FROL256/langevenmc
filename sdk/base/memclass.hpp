








#ifndef _AT58_MEMORYCLASS_HPP_
#define _AT58_MEMORYCLASS_HPP_

#include "arrays.hpp"
#include "export.h"
#include "str.hpp"

KIAM_NAMESPACE_START


class MemoryClass
  {
  public:
    
    
    
    inline const Str &GetName() const;
    

  public:
    
    
    
    inline void Add(SIZE_T size);
    
    inline void Del(SIZE_T size);
    

  public:
    
    
    
    INTAPI_BASE SIZE_T CurSize();
    
    INTAPI_BASE SIZE_T MaxSize();
    

  public:
    
    
    
    INTAPI_BASE static MemoryClass *FirstClass();
    

  public:
    
    
    
    INTAPI_BASE MemoryClass *NextClass();
    

  public:
    
    
    
    INTAPI_BASE static MemoryClass *GetClass(const char *class_name);
    

  public:
    
    
    
    INTAPI_BASE static SIZE_T AllocatedByClass(const char *class_name);
    
    INTAPI_BASE static SIZE_T AllocatedByAll();
    
    INTAPI_BASE static void PrintMapForClass(const char *class_name, TArray<Str> &out);
    
    INTAPI_BASE static void PrintMapForAll(TArray<Str> &out);
    

  public:
    
    
    
    inline static bool ToTrace(SIZE_T size);
    

  private:
    
    MemoryClass(const char *class_name);

  private:
    
    
    
    enum TraceMode
      {
      
      UNDEFINED,
      
      TRACE,
      
      NO_TRACE
      };

  private:
    
    
    
    INTAPI_BASE static TraceMode trace_mode;
    
    INTAPI_BASE static SIZE_T trace_size;
    

  private:
    
    
    
    Str name;
    
    SIZE_T cur_size;
    
    SIZE_T max_size;
    

  private:
    
    
    
    static MemoryClass *top;
    

  private:
    
    
    
    MemoryClass *next;
    
  };  









const Str &MemoryClass::GetName() const
  {
  return name;
  }






void MemoryClass::Add(SIZE_T size)
  {
  cur_size += size;
  if (cur_size > max_size)
    max_size = cur_size;
  }






void MemoryClass::Del(SIZE_T size)
  {
  cur_size -= size;
  }







bool MemoryClass::ToTrace(SIZE_T size)
  {
  return (trace_mode == TRACE && trace_size <= size);
  }



KIAM_NAMESPACE_END
#endif
