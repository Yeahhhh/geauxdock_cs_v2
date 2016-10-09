
#include <papi.h>
#include <yeah/measuring/papi/wrapper.h>
#include <yeah/measuring/papi/struct.h>

#include "includes/main1.c"

Papi_event_struct papi_event_struct1[] = {
    //{,       ""},
    //{PAPI_L1_TCM,       "PAPI_L1_TCM"},
    //{PAPI_L2_TCM,       "PAPI_L2_TCM"},
    {PAPI_L1_DCM,        "PAPI_L1_DCM"},
    //{PAPI_L2_DCM,       "PAPI_L2_DCM"},
    //{PAPI_L1_ICM,       "PAPI_L1_ICM"},
    //{PAPI_L2_ICM,       "PAPI_L2_ICM"},

    //{PAPI_LD_INS,       "PAPI_LD_INS"},
    //{PAPI_SR_INS,       "PAPI_SR_INS"},


    //{PAPI_BR_MSP,       "PAPI_BR_MSP"},
    //{PAPI_BR_PRC,       "PAPI_BR_PRC"},
    //{PAPI_BR_INS,       "PAPI_BR_INS"},


    //{PAPI_SP_OPS,       "PAPI_SP_OPS"},
    //{PAPI_DP_OPS,       "PAPI_DP_OPS"},
    //{PAPI_FP_OPS,       "PAPI_FP_OPS"},
    //{PAPI_VEC_SP,       "PAPI_VEC_SP"},
    //{PAPI_VEC_DP,       "PAPI_VEC_DP"},


    {PAPI_TOT_INS,        "PAPI_TOT_INS"},
    {PAPI_TOT_CYC,        "PAPI_TOT_CYC"},
    {PAPI_NULL_YEAH,      "PAPI_NULL_YEAH"}
};



static void
launcher (float **a, float **b, float **c)
{
    int i;
    float t0, t1;

    Papi_event_struct * papi_event_struct = papi_event_struct1;
    const int papi_event_n = Papi_event_struct_n (papi_event_struct);
    long long *papi_event_val = (long long *) malloc (sizeof (long long) * papi_event_n);
    int *papi_event = (int *) malloc (sizeof (int) * papi_event_n);
    for (i = 0; i < papi_event_n; ++i) {
        papi_event[i] = papi_event_struct[i].event;
    }

    t0 = (float) PAPI_get_virt_usec () * 1e-6;
    PAPI_ERR (PAPI_start_counters (papi_event, papi_event_n));

    mmm (a, b, c);

    PAPI_ERR (PAPI_read_counters (papi_event_val, papi_event_n));
    t1 = (float) PAPI_get_virt_usec () * 1e-6;

    printf ("time\t\t%10.3f s\n", t1 - t0);
    for (i = 0; i < papi_event_n; ++i) {
        printf ("%s\t%10.3f M\n",
            papi_event_struct[i].str,
            (float) papi_event_val[i] * 1e-6);
    }


    PAPI_shutdown ();

    free (papi_event);
    free (papi_event_val);
}

#include "includes/main2.c"
