
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>

#include <geauxdock.h>
#include <size.h>
#include <toggle.h>

#include <cuda.h>
#include <curand.h>
#include <curand_kernel.h>

#include <geauxdock.h>
#include <toggle.h>
#include <util_print.h>

#include <yeah/cuda/runtime/wrapper.h>
#include <yeah/cuda/runtime/event.h>
#include <yeah/cuda/runtime/info.h>
#include <yeah/cuda/kernel/util.h>
#include <yeah/c/timing.h>
#include <yeah/cpp/timer.hpp>



#define CUDAASSERT(condition, code) \
    if (!(condition)) printf("Assertion failure. Code %s%n\n", code)

#include <backend_gpu.h>
#include "kernel_cuda_l2_reduce_notemplate.cu"
#include "kernel_cuda_l2_util.cu"
#include "kernel_cuda_l1_initcurand.cu"
#include "kernel_cuda_l1_montecarlo.cu"



// GPU timer can't measure memory copy
// CPU timer can't measure mc kernel



static void
InitCurand (curandState *s)
{
    const int mydevice = 0;
    cudaDeviceProp prop;
    CUDA_ERR (cudaGetDeviceProperties (&prop, mydevice));
    const int BperG = prop.multiProcessorCount * BperMP; // blocks per GPU


    srand (time (0));
    InitCurand_d <<< BperG, TperB >>> (s, rand ());
}



static void
Dock (Complex *ch,
    Record *rh,
    Complex *cd,
    Record *rd,
    curandState *curandstate_d)
{
    const int steps_total = ch->mcpara.steps_total;
    const int steps_per_dump = ch->mcpara.steps_per_dump;
    const size_t record_sz = sizeof (Record) * ch->size.n_rep;


    const int mydevice = 0;
    cudaDeviceProp prop;
    CUDA_ERR (cudaGetDeviceProperties (&prop, mydevice));
    const int BperG = prop.multiProcessorCount * BperMP; // blocks per GPU



    yeah::Timer e[11];
    //yeah::cuda::EventSD e[11];

    CUDA_ERR (cudaMemcpyAsync (cd, ch, sizeof (Complex), cudaMemcpyHostToDevice));

    //GetPrintCudaFuncArributes ((void (*)) MonteCarlo_d, "MonteCarlo_d");
    //GetPrintCudaFuncArributes2 ((void (*)) MonteCarlo_d, "MonteCarlo_d", BperG, TperB, 0);


    e[10].Start ();


    e[3].Start ();
    MonteCarlo_d <<< BperG, TperB >>> (cd, rd, 0, 1, curandstate_d);
    CUDA_LAST_ERR ();
    e[3].Stop ();



    for (int s1 = 0; s1 < steps_total; s1 += steps_per_dump) {
        printf ("\t%d / %d \n", s1, steps_total);

        e[4].Start ();
        MonteCarlo_d <<< BperG, TperB >>> (cd, rd, s1, steps_per_dump, curandstate_d);
        CUDA_LAST_ERR ();
        //cudaDeviceSynchronize();

        //yeah::Timer eeee;
        //eeee.Start ();
        CUDA_ERR (cudaMemcpy (rh, rd, record_sz, cudaMemcpyDeviceToHost));
        // eeee.Stop ();
        // printf ("launcher: time of memory copy D2H %f\n", eeee.Span());
        e[4].Stop ();
//#include <kernel_dump.cpp>
    }

    Record *record = rh;
#include <kernel_print.cpp>


    e[10].Stop ();


#include <kernel_print_timer.cpp>
    //PrintSummary (ch);
#include <kernel_print_benchmark.cpp>

}






Docker::Docker()
{
    const int mydevice = 0;
    cudaDeviceProp prop;
    CUDA_ERR (cudaGetDeviceProperties (&prop, mydevice));
    const int BperG = prop.multiProcessorCount * BperMP; // blocks per GPU
    printf ("BperG = %d\n", BperG);




    printf ("Initilizing GPU\n");
    printf ("sizeof record = %f MB\n", (float) sizeof (Record) * MAX_REP / 1024 / 1024);


    CUDA_ERR (cudaMallocHost ((void **) &complex, sizeof (Complex)));
    CUDA_ERR (cudaMallocHost ((void **) &record, sizeof (Record) * MAX_REP));

    CUDA_ERR (cudaMalloc ((void **) &cd, sizeof (Complex)));
    CUDA_ERR (cudaMalloc ((void **) &rd, sizeof (Record) * MAX_REP));
    CUDA_ERR (cudaMalloc ((void **) &sd, sizeof (curandState) * TperB * BperG));

    cudaDeviceSetCacheConfig (cudaFuncCachePreferShared);
    InitCurand (sd);
}



Docker::~Docker()
{
    CUDA_ERR (cudaFree (cd));
    CUDA_ERR (cudaFree (rd));
    CUDA_ERR (cudaFree (sd));
    CUDA_ERR (cudaFreeHost (record));
    CUDA_ERR (cudaFreeHost (complex));

    cudaDeviceReset ();
}



void Docker::run()
{
    Dock (complex, record, cd, rd, sd);
}


