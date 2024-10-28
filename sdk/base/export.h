#ifdef _WIN32
#ifdef INTEXPORT_BASE
#define INTAPI_BASE __declspec(dllexport)
#elif defined INTEXPORT_LTKERNEL
#define INTAPI_BASE
#else
#define INTAPI_BASE __declspec(dllimport)
#endif
#else 
#define INTAPI_BASE
#endif
