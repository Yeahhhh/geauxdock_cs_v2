// http://icl.cs.utk.edu/projects/papi/files/documentation/PAPI_USER_GUIDE_23.htm

#include <papi.h>
#include <yeah/measuring/papi/wrapper.h>

#include "includes/main1.c"

static void
launcher (float **a, float **b, float **c)
{
#define NUM_EVENTS 1

    int papi_event_n = NUM_EVENTS;
    int papi_event[NUM_EVENTS] = {PAPI_TOT_INS};
    long long papi_event_val[NUM_EVENTS];

    PAPI_ERR (PAPI_start_counters (papi_event, papi_event_n));

    mmm (a, b, c);

    PAPI_ERR (PAPI_read_counters (papi_event_val, papi_event_n));
    printf ("after PAPI_read_counters:  %10.3f M\n", (float) papi_event_val[0] * 1e-6);

    mmm (a, b, c);

    PAPI_ERR (PAPI_accum_counters (papi_event_val, papi_event_n));
    printf ("after PAPI_accum_counters: %10.3f M\n", (float) papi_event_val[0] * 1e-6);

    mmm (a, b, c);

    PAPI_ERR (PAPI_accum_counters (papi_event_val, papi_event_n));
    printf ("after PAPI_accum_counters: %10.3f M\n", (float) papi_event_val[0] * 1e-6);

    mmm (a, b, c);



    PAPI_ERR (PAPI_stop_counters (papi_event_val, papi_event_n));
    printf ("after PAPI_stop_counters:  %10.3f M\n", (float) papi_event_val[0] * 1e-6);

    PAPI_shutdown ();
}


#include "includes/main2.c"
