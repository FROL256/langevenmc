


#ifndef _KIAM_H_
#define _KIAM_H_

#include "../../sdk/rep_version.hpp"



#ifndef OS_MARK

#if defined(_WIN32)          
#define OS_MARK  'I'
#elif defined(__sgi)        
#define OS_MARK  'U'
#elif defined(__linux)      
#define OS_MARK  'L'
#endif

#if !defined(TIPE) && !defined(NO_TIPE)
#define TIPE
#endif

#endif


#ifdef __cplusplus

#define START_C_DECLS  extern "C" {
#define END_C_DECLS      }

#ifdef VIRTUAL
#undef VIRTUAL
#endif
#define VIRTUAL

#ifdef STATIC
#undef STATIC
#endif
#define STATIC

#ifdef INLINE
#undef INLINE
#endif
#define INLINE inline


#define FVIRTUAL virtual



#define KIAM_NAMESPACE_START namespace Kiam {
#define KIAM_NAMESPACE_END }
KIAM_NAMESPACE_START
KIAM_NAMESPACE_END

#else

#define START_C_DECLS
#define END_C_DECLS

#endif


typedef unsigned short USHORT;
typedef unsigned long  ULONG;
typedef unsigned char  BYTE;


#define MAX_BYTE 255




#define TRUE    1
#define FALSE   0

#define YES     TRUE
#define NO      FALSE

#define ON      TRUE
#define OFF     FALSE



typedef int OKAY;

#define SUCCESS   0
#define FAILURE (-1)



#define MAX_IDENTIFIER_LENGTH   128





#include "int_env.h"




#define X 0   
#define Y 1
#define Z 2

#define XY  2 
#define XYZ 3 

#define R 0   
#define G 1
#define B 2

#ifdef RGB
#undef RGB
#endif
#define RGB 3 



START_C_DECLS


#ifdef OS_MARK

#include "globals.h"


#endif


#define DL 0x000F     
#define DM 0x00FF     
#define DH 0xFFFF     



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

#define DB(expr) (expr);


#define DBM(mask, expr) \
  { \
  if ((mask) & DB_MASK) \
    (expr); \
  }

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


#define  DB(expr)         ;
#define  DBM(mask, expr)  ;

#endif 


#ifdef ASSERT
#undef ASSERT
#endif
#define ASSERT(expr) Assert(expr);  

#if _MSC_VER >= 1400
#if defined(DEBUG) || defined(INT_ASSERT)
void __cdecl int_assert(const char *_Message,
                        const char *_File,
                        unsigned _Line);
#define Assert(_Expression) (void)( (!!(_Expression)) || \
  (int_assert(#_Expression, __FILE__, __LINE__), 0) )
#else  
#define Assert(_Expression) ((void)0)
#endif  
#else  
#include <assert.h>
#define Assert(expr) assert(expr)
#endif  

END_C_DECLS


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


