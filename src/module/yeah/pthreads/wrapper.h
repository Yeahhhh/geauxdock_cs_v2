#ifndef _YEAH_PTHREADS_WRAPPER_H_
#define _YEAH_PTHREADS_WRAPPER_H_

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

//#ifdef __cplusplus
// extern "C" {
//#endif

#define PTHREADS_ERR(err) __GetErrPT(err, __FILE__, __LINE__)

// inline void
void __GetErrPT(const int err, const char *const file, const int line)
{
    if (err != 0) {
        const char *s = "this is the error string";
        printf("%s(%d) : PThreads error : (%d) : %s.\n", file, line, (int)err,
               s);
        exit(EXIT_FAILURE);
    }
}

//#ifdef __cplusplus
//}
//#endif

#endif
