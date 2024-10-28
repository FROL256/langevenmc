










#ifndef _KLBC_STR_HPP_
#define _KLBC_STR_HPP_

#include <kiam.hpp>

#include "export.h"

KIAM_NAMESPACE_START

#ifdef PATH_SEPARATOR
#undef PATH_SEPARATOR
#endif
#ifdef PATH_SEPARATOR_STR
#undef PATH_SEPARATOR_STR
#endif

class Time;
template <class T> class TArray;


class Str
  {
  public:
    
    
    
    
    
    
    
    
    
    enum { MAX_LENGTH = 4096 };
    

  public:
    
    
    
    inline Str();
    
    INTAPI_BASE Str(const char *ch);
    
    INTAPI_BASE Str(const char *ch, int n);
    
    INTAPI_BASE Str(const Str &s);
    
    INTAPI_BASE ~Str();
    

    
    INTAPI_BASE OKAY Allocate(int n);

  public:
    
    
    
    inline char &operator [](int ind);
    
    inline char operator [](int ind) const;
    
    inline operator const char *() const;
    
    inline const char *Data() const;
    
    INTAPI_BASE const char *PData() const;
    
    inline char *XData() const;
    

  public:
    
    
    
    INTAPI_BASE void operator =(const char *s);
    
    inline void operator =(const Str &s);
    
    INTAPI_BASE void Set(const char *ch, int n);
    
    INTAPI_BASE void operator +=(const char *s);
    
    INTAPI_BASE Str operator +(const Str &s) const;
    

  public:
    
    
    
    inline bool operator ==(const char *s) const;
    
    inline bool operator !=(const char *s) const;
    
    inline bool operator <(const char *s) const;
    
    inline bool operator <=(const char *s) const;
    
    inline bool operator >(const char *s) const;
    
    inline bool operator >=(const char *s) const;
    
    inline int ICmp(const char *s) const;
    
    INTAPI_BASE int NCmp(const char *s, int n) const;
    
    INTAPI_BASE int NICmp(const char *s, int n) const;
    

  public:
    
    
    
    inline bool IsNull() const;
    
    inline bool IsEmpty() const;
    
    inline int Length() const;
    

  public:
    
    
    
    INTAPI_BASE void RemoveBlanks();
    
    INTAPI_BASE void Clip();
    
    INTAPI_BASE void RemoveTrailZeros();
    
    INTAPI_BASE void ToUpper();
    
    INTAPI_BASE void ToLower();
    
    INTAPI_BASE OKAY CheckAndConvert2Real();
    
    INTAPI_BASE void Printf(const char *format, ...);
    
    INTAPI_BASE int Scanf(const char *format, ...) const;
    
    INTAPI_BASE void Catf(const char *format, ...);
    
    INTAPI_BASE int IntegerNum(bool &ok) const;
    
    INTAPI_BASE double DoubleNum(bool &ok) const;
    
    INTAPI_BASE void TruncateReal(double num, int prec, int digits);
    

  public:
    
    
    
    INTAPI_BASE Str SubStr(int start, int nchars) const;
    
    INTAPI_BASE int SubStrCmp(const char *str, int start = 0) const;
    
    INTAPI_BASE void Exclude(int pos, int n);
    
    INTAPI_BASE OKAY Resize(int nchars);
    
    INTAPI_BASE void Clear();
    

  public:
    
    
    
    INTAPI_BASE bool FindFirst(char c, int *out_pos = NULL) const;
    
    INTAPI_BASE bool FindLast(char c, int *out_pos = NULL) const;
    
    INTAPI_BASE bool Find(char c, int in_pos, int *out_pos = NULL) const;
    
    INTAPI_BASE bool Find(const Str &s, int *out_pos = NULL, int start = 0) const;
    
    INTAPI_BASE bool IFind(const Str &s, int *out_pos = NULL, int start = 0) const;
    

  public:

  private:
    
    
    
    char *buf;
    
  };  

KIAM_NAMESPACE_END


typedef char CHAR;


#define KIAM_T(x) x

#if (_MSC_VER >= 1400) || defined(__linux)

#define Tr(str, ...) GlobTr(__FUNCTION__, str, ##__VA_ARGS__)
#else 
#endif

#ifndef QT_TR_NOOP

#define QT_TR_NOOP(x) (x)
#endif
#ifndef QT_TRANSLATE_NOOP

#define QT_TRANSLATE_NOOP(scope, x) (x)
#endif

KIAM_NAMESPACE_START











Str::Str()
  {
  buf = NULL;
  }







char &Str::operator [](int ind)
  {
  Assert(buf != NULL);
  Assert(0 <= ind && ind <= Length());
  return buf[ind];
  }







char Str::operator [](int ind) const
  {
  Assert(buf != NULL);
  Assert(0 <= ind && ind <= Length());
  return buf[ind];
  }




Str::operator const char *() const
  {
  return buf;
  }





const char *Str::Data() const
  {
  return buf;
  }








char *Str::XData() const
  {
  return buf;
  }





void Str::operator =(const Str &s)
  {
  *this = s.buf;
  }









bool Str::operator ==(const char *s) const
  {
  if (buf == NULL || s == NULL)
    return buf == s;
  return strcmp(buf, s) == 0;
  }









bool Str::operator !=(const char *s) const
  {
  if (buf == NULL || s == NULL)
    return buf != s;
  return strcmp(buf, s) != 0;
  }











bool Str::operator <(const char *s) const
  {
  if (buf == NULL || s == NULL)
    return (s != NULL);
  return strcmp(buf, s) < 0;
  }











bool Str::operator <=(const char *s) const
  {
  if (buf == NULL || s == NULL)
    return (buf == NULL ? s == NULL : false);
  return strcmp(buf, s) <= 0;
  }











bool Str::operator >(const char *s) const
  {
  if (buf == NULL || s == NULL)
    return buf != NULL;
  return strcmp(buf, s) > 0;
  }











bool Str::operator >=(const char *s) const
  {
  if (buf == NULL || s == NULL)
    return (buf == NULL ? s == NULL : true);
  return strcmp(buf, s) >= 0;
  }








int Str::ICmp(const char *s) const
  {
  if (buf == NULL)
    {
    if (s == NULL)
      return 0;
    return -1;
    }
  if (s == NULL)
    return 1;

  return stricmp(buf, s);
  }




bool Str::IsNull() const
  {
  return (buf == NULL);
  }




bool Str::IsEmpty() const
  {
  return (buf == NULL) || (buf[0] == '\0');
  }




int Str::Length() const
  {
  if (IsNull())
    return 0;
  return (int)strlen(buf);
  }


KIAM_NAMESPACE_END
#endif
