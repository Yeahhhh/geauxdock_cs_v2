#ifndef _YEAH_CUDA_CUPTI_WRAPPER_H_
#define _YEAH_CUDA_CUPTI_WRAPPER_H_


#include <cuda_runtime.h>
#include <cupti.h>
#include <stdlib.h>
#include <stdio.h>




#define CUPTI_ERR(err) __GetError_cupti (err, __FILE__, __LINE__)

inline void
__GetError_cupti (const CUptiResult err, const char * const file, const int line)
{
    if (err != CUPTI_SUCCESS) {
        const char *s;
        cuptiGetResultString(err, &s);
        printf ("%s(%d) : CUPTI error : (%d) : %s.\n", file, line, (int) err, s);
        exit (EXIT_FAILURE);
    }
}


#endif
