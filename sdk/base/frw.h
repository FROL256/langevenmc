








#ifndef _AE32_FRW_H_
#define _AE32_FRW_H_

#include "export.h"

START_C_DECLS
#ifndef _WIN32
#define __cdecl
#endif


INTAPI_BASE size_t __cdecl kiam_fread(void *buffer, size_t size, size_t count, FILE *stream);


INTAPI_BASE size_t __cdecl kiam_fwrite(const void *buffer, size_t size, size_t count, FILE *stream);

#ifndef _WIN32
#define __cdecl
#endif
END_C_DECLS

#endif
