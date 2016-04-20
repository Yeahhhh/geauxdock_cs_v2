
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

#include "kernel_cuda_l2_reduce_notemplate.cu"
#include "kernel_cuda_l2_util.cu"
#include "kernel_cuda_l1_initcurand.cu"
#include "kernel_cuda_l1_montecarlo.cu"



// GPU timer can't measure memory copy
// CPU timer can't measure mc kernel



void
InitCurand (curandState *s)
{
    srand (time (0));
    InitCurand_d <<< GD, BD >>> (s, rand ());
}



void
Dock (Complex *ch,
    Record *rh,
    Complex *cd,
    Record *rd,
    curandState *curandstate_d)
{
    const int steps_total = ch->mcpara.steps_total;
    const int steps_per_dump = ch->mcpara.steps_per_dump;
    const size_t record_sz = sizeof (Record) * ch->size.n_rep;


    yeah::Timer e[11];
    //yeah::cuda::EventSD e[11];

    CUDA_ERR (cudaMemcpyAsync (cd, ch, sizeof (Complex), cudaMemcpyHostToDevice));

    //GetPrintCudaFuncArributes ((void (*)) MonteCarlo_d, "MonteCarlo_d");
    //GetPrintCudaFuncArributes2 ((void (*)) MonteCarlo_d, "MonteCarlo_d", GD, BD, 0);


    e[10].Start ();


    e[3].Start ();
    MonteCarlo_d <<< GD, BD >>> (cd, rd, 0, 1, curandstate_d);
    CUDA_LAST_ERR ();
    e[3].Stop ();



    for (int s1 = 0; s1 < steps_total; s1 += steps_per_dump) {
        printf ("\t%d / %d \n", s1, steps_total);

        e[4].Start ();
        MonteCarlo_d <<< GD, BD >>> (cd, rd, s1, steps_per_dump, curandstate_d);
        CUDA_LAST_ERR ();
        //cudaDeviceSynchronize();

        //yeah::Timer eeee;
        //eeee.Start ();
        CUDA_ERR (cudaMemcpy (rh, rd, record_sz, cudaMemcpyDeviceToHost));
        // eeee.Stop ();
        // printf ("launcher: time of memory copy D2H %f\n", eeee.Span());
        e[4].Stop ();
//#include <kernel_dump.C>
    }

    Record *record = rh;
#include <kernel_print.C>


    e[10].Stop ();


#include <kernel_print_timer.C>
    //PrintSummary (ch);
#include <kernel_print_benchmark.C>

}



