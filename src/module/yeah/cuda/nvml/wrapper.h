
#ifndef _YEAH_CUDA_NVML_WRAPPER_H_
#define _YEAH_CUDA_NVML_WRAPPER_H_


#include <nvidia/nvml.h>
#include <stdlib.h>
#include <stdio.h>




#define NVML_ERR(err) __GetErrorNVML (err, __FILE__, __LINE__)

inline void
__GetErrorNVML (const nvmlReturn_t err, const char *file, const int line)
{
    if (err != NVML_SUCCESS) {
        const char* s = nvmlErrorString (err);
        printf ("%s(%d) : CUDA error : (%d) : %s.\n", file, line, (int) err, s);
        exit (EXIT_FAILURE);
    }
}




#endif
