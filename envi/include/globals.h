


#ifdef  GLOBAL
#undef  GLOBAL
#endif 
#ifdef  INITIALIZE
#undef  INITIALIZE
#endif
#ifdef  DEFINE_GLOBALS
#define GLOBAL
#define INITIALIZE
#else
#define GLOBAL extern
#endif



