//#include <mpi.h>

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstdio>


#include <size.h>
#include <geauxdock.h>
#include <util.h>
#include <util_optimize.h>
#include <util_print.h>
#include <toggle.h>
#include <load.h>
//#include <sys/resource.h>

#include <cuda_runtime.h>
#include <curand.h>
#include <curand_kernel.h>


#include "../backend_gpu/backend_gpu.h"
#include <yeah/c/timing.h>
#include <yeah/cpp/timer.hpp>
#include <yeah/cuda/runtime/wrapper.h>





int main (int argc, char **argv)
{


#include "../frontend/server1.C"

    yeah::Timer tc[8];

    tc[0].Start ();

    printf ("Initilizing GPU\n");
    printf ("sizeof record = %f MB\n", (float) sizeof (Record) * MAX_REP / 1024 / 1024);


    Complex *ch; // complex on host
    Record *rh; // record on host
    CUDA_ERR (cudaMallocHost ((void **) &ch, sizeof (Complex)));
    CUDA_ERR (cudaMallocHost ((void **) &rh, sizeof (Record) * MAX_REP));


    Complex *cd; // complex on device
    Record *rd; // record on device
    curandState *sd; // curand seed on device
    CUDA_ERR (cudaMalloc ((void **) &cd, sizeof (Complex)));
    CUDA_ERR (cudaMalloc ((void **) &rd, sizeof (Record) * MAX_REP));
    CUDA_ERR (cudaMalloc ((void **) &sd, sizeof (curandState) * BD * GD));


    cudaDeviceSetCacheConfig (cudaFuncCachePreferShared);
    InitCurand (sd);

    tc[0].Stop ();


    tc[1].Start ();

    for (int i = 0; i < ncomplex; ++i) {
        *ch = complex[i];
        printf ("\n");
        printf ("complex %d: %s\n", i, argv[0]);
        //PrintComplexInfo (ch);

        t[3].Reset ();
        t[3].Start ();
        Dock (ch, rh, cd, rd, sd);
        t[3].Stop ();
        printf ("Dock time\t\t\t%8.3f\n", t[15].Span ());
    }

    tc[1].Stop ();

    tc[3].Start ();

    CUDA_ERR (cudaFree (cd));
    CUDA_ERR (cudaFree (rd));
    CUDA_ERR (cudaFree (sd));
    CUDA_ERR (cudaFreeHost (rh));
    CUDA_ERR (cudaFreeHost (ch));

    tc[3].Stop ();

    cudaDeviceReset ();



#include "../frontend/server2.C"


    printf ("client mem alloc time\t\t%8.3f\n", tc[0].Span ());
    printf ("client compute time\t\t%8.3f\n", tc[1].Span ());
    printf ("client mem free time\t\t%8.3f\n", tc[3].Span ());


    return 0;
}


