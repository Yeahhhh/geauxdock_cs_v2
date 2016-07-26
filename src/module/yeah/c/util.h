
#ifndef _YEAH_C_UTIL_H_
#define _YEAH_C_UTIL_H_

#include <stdio.h>
#include <stdlib.h>


// usage:
// NULLPTR (a = malloc (xxx));
#define NULLPTR(prt) __GetNullPointerError1 (prt, __FILE__, __LINE__)


inline void
__GetNullPointerError1 (void * prt, char *file, int line)
{
    if (prt == NULL) {
        printf ("%s: line %d: null ptr failure\n", file, line);
        exit (EXIT_FAILURE);
    }
}



// NetBSD
//   #include <sys/cdefs.h>
//   man 3 attribute







// memory alignment guidelines:
//     processor with 128 bit SIMD:             16 bytes alignment
//     processor with 256 bit SIMD:             32 bytes alignment
//     processor with 512 bit SIMD:             64 bytes alignment
//     Intel Xeon Phi co-processor offloading:  4K bytes alignment


// alignmed heap memory management
//
// C11 standard
// void * aligned_alloc (size_t alignment, size_t size);
// void free (void *p)
//
// POSIX standard
// int posix_memalign (void **memptr, size_t alignment, size_t size);
// void free (void *p)
//
// Windows
// void * _aligned_malloc(size_t size, size_t alignment);
// void _aligned_free (void $p);
//
// Intel C/C++ compiler
// void* _mm_malloc (int size, int align)
// void _mm_free (void *p)



// usage:
// ALIGN(n) // memory alignment at "n" bytes bondary

#if defined(__CUDACC__) // NVCC
#define ALIGN(n) __align__(n)
#elif defined(__GNUC__) // GCC
#define ALIGN(n) __attribute__((aligned (n)))
#elif defined(__INTEL_COMPILER) // INTEL
#define ALIGN(n) __attribute__((aligned (n)))
#elif defined(_MSC_VER) // MSVC
#define ALIGN(n) __declspec(align (n))
#else
  #error "Missing the definition of "ALIGN macro" for this compiler."
#endif




#define RESTRICT __restrict__



#endif
