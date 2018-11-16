
//#include <vector>
//#include <map>
#include <cstdlib>
#include <cstdio>
#include <cmath>

#include <geauxdock.h>
#include <size.h>
#include <toggle.h>
#include <util_print.h>
#include <complex.h>

#include <yeah/measuring/counting/timer.hpp>


#if IS_PAPI == 1
#include <papi.h>
#include <yeah/papi/wrapper.h>
#include <yeah/papi/struct.h>
#include <yeah/papi/measurer.hpp>
#endif




#include <backend_cpu_mic.h>
#include "kernel_cpp_montecarlo_soa.cpp"






static void
Dock (Complex *ch, Record *rh)
{
    yeah::measuring::counting::Timer e[16];

    // data for analysis
    //std::map < int, std::vector < LigRecordSingleStep > > multi_reps_records;



    e[10].Start ();

    // sizes
    const int steps_total = ch->mcpara.steps_total;
    const int steps_per_dump = ch->mcpara.steps_per_dump;

    printf ("steps_per_dump = %d\n", steps_per_dump);
    printf ("steps_total = %d\n", steps_total);

    e[3].Start ();
    // calculate initial energy
    MonteCarlo_d (ch, rh, 0, 1);
    e[3].Stop ();


#if IS_PAPI == 1
    Papi_event_struct papi_event_struct1[] = {
        //{,       ""},
        //{PAPI_L1_TCM,       "PAPI_L1_TCM"},
        //{PAPI_L2_TCM,       "PAPI_L2_TCM"},
        {PAPI_L1_DCM,       "PAPI_L1_DCM"},
        //{PAPI_L2_DCM,       "PAPI_L2_DCM"},
        //{PAPI_L1_ICM,       "PAPI_L1_ICM"},
        //{PAPI_L2_ICM,       "PAPI_L2_ICM"},

        //{PAPI_LD_INS,       "PAPI_LD_INS"},
        //{PAPI_SR_INS,       "PAPI_SR_INS"},

        {PAPI_BR_MSP,       "PAPI_BR_MSP"},
        //{PAPI_BR_PRC,       "PAPI_BR_PRC"},
        //{PAPI_BR_INS,       "PAPI_BR_INS"},

        {PAPI_SP_OPS,       "PAPI_SP_OPS"},
        {PAPI_DP_OPS,       "PAPI_DP_OPS"},
        //{PAPI_FP_OPS,       "PAPI_FP_OPS"},
        {PAPI_VEC_SP,       "PAPI_VEC_SP"},
        {PAPI_VEC_DP,       "PAPI_VEC_DP"},


        {PAPI_TOT_INS,      "PAPI_TOT_INS"},
        {PAPI_TOT_CYC,      "PAPI_TOT_CYC"},
        {PAPI_NULL_YEAH,    "PAPI_NULL_YEAH"}
    };
    yeah::papi::Measurer m0 (papi_event_struct1);
    m0.Start ();
#endif

    e[4].Start ();
    for (int s1 = 0; s1 < steps_total; s1 += steps_per_dump) {
        printf ("\t%d / %d \n", s1, steps_total);
        // fflush (stdout);
        MonteCarlo_d (ch, rh, s1, steps_per_dump);
#include <kernel_dump.cpp>
    }
    e[4].Stop ();

#if IS_PAPI == 1
    m0.Stop ();
    m0.Print ();
#endif

    /*
       for (int s = 0; s < ligrecord[rep].next_ptr; ++s) {
       LigRecordSingleStep my_step = ligrecord[rep].step[s];
       multi_reps_records[rep].push_back(my_step);
       }
       */


    e[10].Stop ();


#include "kernel_print_performance.cpp"
PrintResult (ch, rh);
//PrintSummary (ch);


#if IS_PAPI == 1
    m0.Shutdown ();
#endif

}






Docker::Docker()
{
    complex = new Complex;
    record = new Record[MAX_REP];
}



Docker::~Docker()
{
    delete complex;
    delete[] record;
}



void Docker::run()
{
    Dock (complex, record);
}

