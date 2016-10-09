
#include <stdlib.h>
#include <stdio.h>
#include <papi.h>

#include <yeah/cpp/array_2d.hpp>
#include <yeah/measuring/papi/wrapper.h>
#include <yeah/measuring/papi/struct.h>
#include <yeah/measuring/counting/papi_h1.hpp>

#include "includes/main1.c"

Papi_event_struct papi_event_struct1[] = {
    //{,       ""},
    //{PAPI_L1_TCM,       "PAPI_L1_TCM"},
    //{PAPI_L2_TCM,       "PAPI_L2_TCM"},
    //{PAPI_L1_DCM,       "PAPI_L1_DCM"},
    {PAPI_L2_DCM,       "PAPI_L2_DCM"},
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


    //{PAPI_TOT_INS,        "PAPI_TOT_INS"},
    //{PAPI_TOT_CYC,        "PAPI_TOT_CYC"},
    {PAPI_NULL_YEAH,      "PAPI_NULL_YEAH"}
};




static void
launcher1 (float **a, float **b, float **c)
{
    yeah::papi::Measurer m0(papi_event_struct1);
    m0.Start ();

    mmm(a, b, c);

    m0.Stop ();
    m0.Print ();
    m0.Shutdown ();
}


static void
launcher2 (float **a, float **b, float **c)
{
    yeah::papi::MeasurerAuto m0(papi_event_struct1);
    mmm(a, b, c);
}

static void
launcher (float **a, float **b, float **c)
{
    launcher2(a, b, c);
}



#include "includes/main2.c"

