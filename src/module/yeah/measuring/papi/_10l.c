// http://icl.cs.utk.edu/projects/papi/files/documentation/PAPI_USER_GUIDE_23.htm

#include <papi.h>
#include <yeah/measuring/papi/wrapper.h>

#include "includes/main1.c"

static void
launcher (float **a, float **b, float **c)
{
#define NUM_EVENTS 1

    int papi_event = PAPI_NULL;
    long long papi_event_val[NUM_EVENTS];


    PAPI_ERR_INIT (PAPI_library_init (PAPI_VER_CURRENT));
    PAPI_ERR (PAPI_create_eventset (&papi_event));
    PAPI_ERR (PAPI_add_event (papi_event, PAPI_TOT_INS));
    //PAPI_ERR (PAPI_add_event (papi_event, PAPI_TOT_CYC));

    PAPI_ERR (PAPI_start (papi_event));
    mmm (a, b, c);

    PAPI_ERR (PAPI_read (papi_event, papi_event_val));
    printf ("after PAPI_read:  %10.3f M\n", (float) papi_event_val[0] * 1e-6);

    mmm (a, b, c);

    PAPI_ERR (PAPI_reset (papi_event));
    printf ("after PAPI_reset: %10.3f M\n", (float) papi_event_val[0] * 1e-6);

    mmm (a, b, c);

    PAPI_ERR (PAPI_accum (papi_event, papi_event_val));
    printf ("after PAPI_accum: %10.3f M\n", (float) papi_event_val[0] * 1e-6);

    mmm (a, b, c);

    PAPI_ERR (PAPI_stop (papi_event, papi_event_val));
    printf ("after PAPI_stop:  %10.3f M\n", (float) papi_event_val[0] * 1e-6);

}


#include "includes/main2.c"
