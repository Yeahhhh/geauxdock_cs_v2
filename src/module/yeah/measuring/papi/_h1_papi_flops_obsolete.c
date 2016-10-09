#include <papi.h>
#include <yeah/measuring/papi/wrapper.h>

#include "includes/main1.c"

static void
launcher (float **a, float **b, float **c)
{
    float real_time, proc_time, mflops;
    long long flpins; // fp instructions

    /* Setup PAPI library and begin collecting data from the counters */
    PAPI_ERR (PAPI_flops (&real_time, &proc_time, &flpins, &mflops));

    mmm (a, b, c);

    /* Collect the data into the variables passed in */
    PAPI_ERR (PAPI_flops (&real_time, &proc_time, &flpins, &mflops));


    printf ("real time\t%.3f\n", real_time);
    printf ("proc time\t%.3f\n", proc_time);
    printf ("M fp ins\t%.3f\n", flpins * 1e-6);
    printf ("MFLOPS\t\t%.3f\n", mflops);
    PAPI_shutdown ();
}


#include "includes/main2.c"
