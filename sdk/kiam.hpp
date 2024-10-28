
















#ifndef _KIAM_H_
#define _KIAM_H_

#include <rep_version.hpp>


#ifndef OS_MARK

#if defined(_WIN32)          
#define OS_MARK  'I'
#elif defined(__sgi)        
#define OS_MARK  'U'
#elif defined(__linux)      
#define OS_MARK  'L'
#endif

#endif



#if defined(DEBUG) || defined (_DEBUG)


#ifndef DEBUG
#define DEBUG
#endif
#ifndef _DEBUG
#define _DEBUG
#endif
#ifdef NDEBUG
#undef NDEBUG
#endif

#else


#ifdef DEBUG
#undef DEBUG
#endif
#ifdef _DEBUG
#undef _DEBUG
#endif
#ifndef NDEBUG
#define NDEBUG
#endif
#ifndef QT_NO_DEBUG
#define QT_NO_DEBUG
#endif

#endif

#ifdef KIAM_CATIA_DEBUG
#undef NDEBUG
#endif


#ifdef INLINE
#undef INLINE
#endif

#ifdef VIRTUAL
#undef VIRTUAL
#endif

#ifdef STATIC
#undef STATIC
#endif

#ifdef BOOL
#undef BOOL
#endif



#include <ctype.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _WIN32
#include <stdint.h>
#endif



#define START_C_DECLS extern "C" {
#define END_C_DECLS   }


#define KIAM_NAMESPACE_START namespace Kiam {
#define KIAM_NAMESPACE_END }
KIAM_NAMESPACE_START
KIAM_NAMESPACE_END


#ifdef _WIN32
#define INLINE __forceinline
#else
#define INLINE inline
#endif



#define VIRTUAL
#define STATIC


#define FVIRTUAL virtual



#define IN
#define INOUT
#define OUT


#define PROT(x) x


#ifndef VOID
#define VOID void
typedef char CHAR;
typedef short SHORT;
typedef long LONG;
#endif



typedef void *VPTR;


typedef unsigned char      BYTE;   
typedef unsigned short     WORD;   


#define  MAX_BYTE   255
#define  MIN_SHORT  (-32767)       
#define  MAX_SHORT  32767          
#define  MIN_INT    (-2147483647)  
#define  MAX_INT    2147483647     


#define  MAX_USHORT 0xffff         
#define  MAX_UINT   0xffffffff     


#define  MIN_INT64  0x8000000000000000
#define  MAX_INT64  0x7fffffffffffffff


#define  MAX_UINT64 0xffffffffffffffff


#ifdef _WIN32
  typedef unsigned long       DWORD;  
  typedef __int64             INT64;  
  typedef unsigned __int64   UINT64;  
  #ifdef _WIN64
    typedef unsigned __int64    SIZE_T;
    const SIZE_T MAX_SIZE_T = MAX_INT64;  
  #else
    #if _MSC_VER >= 1300
      typedef __w64 unsigned long SIZE_T;
    #else
      typedef unsigned long       SIZE_T;
    #endif
    const SIZE_T MAX_SIZE_T = MAX_INT;    
  #endif
#endif


typedef void *HANDLE;


#ifdef __sgi
typedef unsigned int       DWORD;  
typedef __int64_t          INT64;  
#endif


#ifdef __linux
typedef unsigned int       DWORD;  
typedef int64_t            INT64;  
typedef uint64_t           UINT64; 
typedef size_t             SIZE_T;
#ifdef __x86_64
const SIZE_T MAX_SIZE_T = MAX_INT64;  
#else
const SIZE_T MAX_SIZE_T = MAX_INT;    
#endif
#endif



#ifdef _WIN32
typedef int BOOL;
#else
typedef unsigned int BOOL;
#endif

#define TRUE    1
#define FALSE   0
#define YES     TRUE
#define NO      FALSE
#define ON      TRUE
#define OFF     FALSE



typedef int OKAY;
#define SUCCESS   0
#define FAILURE (-1)


#ifdef ASSERT
#undef ASSERT
#endif
#define ASSERT(expr) Assert(expr);  

#if _MSC_VER >= 1400
#if defined(DEBUG) || defined(INT_ASSERT)
START_C_DECLS
void __cdecl int_assert(const char *_Message,
                        const char *_File,
                        unsigned _Line);
END_C_DECLS
#define Assert(_Expression) (void)( (!!(_Expression)) || \
  (int_assert(#_Expression, __FILE__, __LINE__), 0) )
#else 
#define Assert(_Expression) ((void)0)
#endif  
#else  
#include <assert.h>
#define Assert(expr) assert(expr)
#endif  


#define PLUG_EXPORT


#ifdef _WIN32  

#pragma warning(disable : 4100)

#pragma warning(disable : 4456)

#pragma warning(disable : 4457)

#pragma warning(disable : 4458)

#pragma warning(disable : 4459)

#pragma warning(disable : 4514)

#pragma warning(disable : 4710)

#pragma warning(disable : 4714)

#pragma warning(disable : 4840)
#if _MSC_VER >= 1900

#pragma warning(disable : 5037)
#endif
#endif


#ifdef _WIN32

#define itoa _itoa
#define chdir _chdir
#define mkdir _mkdir
#define rmdir _rmdir
#define unlink _unlink
#define getcwd _getcwd
#define putenv _putenv
#define spawnvp _spawnvp
#define stricmp _stricmp
#define strnicmp _strnicmp
#else  
#define  _isnan    isnan
#define  _finite   finite
#define  stricmp   strcasecmp
#define  strnicmp  strncasecmp
#define _vsnprintf vsnprintf
#endif


#ifdef _WIN32
#define OS_BYTE_ORDER        0          
#define LIB_TEMPLATE_INSTANCE(Class, Type) template class Class<Type>;
#endif

#ifdef __sgi
#define OS_BYTE_ORDER        1          

#define LIB_TEMPLATE_INSTANCE(Class, Type) \
Class<Type> *Generate_##Class##_##Type()   \
  {                                        \
  return (Class<Type> *) new Class<Type>;  \
  }
#endif

#ifdef __linux
#define OS_BYTE_ORDER        0          
#define LIB_TEMPLATE_INSTANCE(Class, Type) template class Class<Type>;
#endif


#if (OS_MARK == 'I')
#if defined(MEMORY_LEAK_DEBUG) && defined(DEBUG)


#define IMAL_NO_C_RTL_MACRO
#undef RTL_MEMORY_TO_IMAL
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif 

#endif 

#endif 
