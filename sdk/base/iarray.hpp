








#ifndef _AT58_IARRAY_HPP_
#define _AT58_IARRAY_HPP_

#include "export.h"
#include "str.hpp"

KIAM_NAMESPACE_START

class MemoryClass;


class IArray
  {
  public:
    
    INTAPI_BASE void SetName(const char *class_name, const char *array_name);
    
    INTAPI_BASE virtual ~IArray();
  protected:
    
    INTAPI_BASE IArray();
    
    INTAPI_BASE void AddMemStat(SIZE_T size, void *p, const char *str);
    
    INTAPI_BASE void DelMemStat(SIZE_T size, void *p, const char *str);
  protected:
    
    MemoryClass *mem_class;
    
    Str name;
  };  

KIAM_NAMESPACE_END
#endif
