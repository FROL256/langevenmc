

#ifndef _INT_ENV_H_
#define _INT_ENV_H_



#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <malloc.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <signal.h>

START_C_DECLS

/***************************************************************************
   Prototypes definitions.
 ***************************************************************************/



#ifndef PROTOTYPES
#ifndef NO_PROTOTYPES

#define PROTOTYPES

#endif
#endif



#ifdef PROTOTYPES
#undef NO_PROTOTYPES
#endif

#ifdef NO_PROTOTYPES
#undef PROTOTYPES
#endif


#ifndef NO_PROTOTYPES
#define PROT(x) x
#else
#define PROT(x) ()
#endif


#define IN
#define INOUT
#define OUT


#ifdef  BOOL
#undef  BOOL
#endif
typedef unsigned int  BOOL;


#ifdef  REAL
#undef  REAL
#endif
#define REAL double





#ifdef  VOID
#undef  VOID
#endif

#if YES    
#define VOID  void
typedef void *VPTR;
#else  
typedef int   VOID;
typedef char *VPTR;
#endif



typedef unsigned short WORD;   
typedef unsigned int DWORD;    




typedef int64_t INT64;
typedef size_t SIZE_T;

#define  MIN_SHORT  (-32767)  
#define  MAX_SHORT  32767     

#define  MIN_INT    (-2147483647) 
#define  MAX_INT    2147483647    

#ifdef __x86_64
#define  MIN_LONG   (-9223372036854775807L) 
#define  MAX_LONG   9223372036854775807L    
#else
#define  MIN_LONG   (-2147483647L) 
#define  MAX_LONG   2147483647L    
#endif


#define  MAX_USHORT 0xFFFF        
#define  MAX_UINT   0xFFFFFFFFU   
#ifdef __x86_64
#define  MAX_ULONG  0xFFFFFFFFFFFFFFFFUL   
#else
#define  MAX_ULONG  0xFFFFFFFFUL   
#endif

#ifdef __x86_64

#define MAX_SIZE_T 8000000000000LL
#else

#define MAX_SIZE_T MAX_INT
#endif


#define  MAX_FLOAT  3.40e+38        
#define  MAX_DOUBLE 1.79e+308       


#define  MIN_FLOAT  1.18e-38      
#define  MIN_DOUBLE 2.23e-308     


#define  EPS_FLOAT  1.19209290e-07               
#define  EPS_DOUBLE 2.2204460492503131e-16     

#define PATH_SEPARATOR       '/'
#define PATH_SEPARATOR_STR   "/"
#define MAX_PATHNAME_LENGTH  1024
#define MAX_FILENAME_LENGTH  255
#define MAX_BASENAME_LENGTH  255
#define MAX_SUFFIX_LENGTH    254

#define ALIGN                8
#define NO_64KB_LIMIT        1
#define MAX_ARRAY_SIZE       0x7FFFFFFF

#define OS_NAME              "LINUX"
#define OS_BYTE_ORDER        0      
#define OS_FP_FORMAT         0      

#ifndef min
#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))
#endif

#define  stricmp   strcasecmp

#define OS_AVAILABLE_NAME       {' ', '!', '#', '$', '%', '&', '\'', '(', ')', \
                                 '-', '@', '^', '_', '`', '{', '}', '~', \
                                 '\x7F', '\x86', '\x87', '\x8D', '\x8E', \
                                 '\x8F', '\x94', '\x98', '\x9B', '\x9C', \
                                 '\x9F', '\xA0', '\xA1', '\xA2', '\xA3', \
                                 '\xA4', '\xA5', '\xA6', '\xA7', '\xA8', \
                                 '\xA9', '\xAA', '\xAB', '\xAC', '\xAD', \
                                 '\xAE', '\xAF', '\xB0', '\xB1', '\xB2', \
                                 '\xB3', '\xB4', '\xB5', '\xB6', '\xB7', \
                                 '\xB8', '\xB9', '\xBA', '\xBB', '\xBC', \
                                 '\xBD', '\xBE', '\xBF', '\xC0', '\xC1', \
                                 '\xC2', '\xC3', '\xC4', '\xC5', '\xC6', \
                                 '\xC7', '\xC8', '\xC9', '\xCA', '\xCB', \
                                 '\xCC', '\xCD', '\xCE', '\xCF', '\xD0', \
                                 '\xD1', '\xD2', '\xD3', '\xD4', '\xD5', \
                                 '\xD6', '\xD7', '\xD8', '\xD9', '\xDA', \
                                 '\xDB', '\xDC', '\xDD', '\xDE', '\xDF', \
                                 '\xE0', '\xE1', '\xE2', '\xE3', '\xE4', \
                                 '\xE5', '\xE6', '\xE7', '\xE8', '\xE9', \
                                 '\xEA', '\xEB', '\xEC', '\xED', '\xEE', \
                                 '\xEF', '\xF0', '\xF1', '\xF2', '\xF3', \
                                 '\xF4', '\xF5', '\xF6', '\xF7', '\xF8', \
                                 '\xF9', '\xFA', '\xFB', '\xFC', '\xFD', \
                                 '\xFE', '\xFF', '\x00'}


#define LIB_TEMPLATE_INSTANCE(Class, Type) template class Class<Type>;

END_C_DECLS


#endif



