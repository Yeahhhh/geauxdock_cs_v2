
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
        //printf ("\t%d / %d \n", s1, steps_total);
        MonteCarlo_d (ch, rh, s1, steps_per_dump);

        // insert your replica-exchange code here

        /*
        //
        // total monte carlo steps = steps_per_dump * n_dump
        // steps_per_dump:           A compiling time constant, see "src/common/size.h" STEPS_PER_DUMP
        // n_dump:                   Only "1" is valid, otherwise, the result data may overflow the "record" buffer, see "src/common/geauxdock.h" struct Record
        //
        // codes for periorically dump and clean the record buffer
        // prototype code, BUGGY !!!!!!!!!!!!!
        //
        const int n_rep = complex->size.n_rep;
        for (int r = 0; r < n_rep; ++r) {
            for (int s = 0; s < ligrecord[rep].next_ptr; ++s) {
                LigRecordSingleStep my_step = ligrecord[rep].step[s];
                multi_reps_records[rep].push_back(my_step);
            }
            ligrecord[rep].step[0] = ligrecord[rep].step[ligrecord[rep].next_ptr - 1]    // save record to entry "0"
            ligrecord[rep].next_ptr = 1
        }
        */

    }
    e[4].Stop ();


#if IS_PAPI == 1
    m0.Stop ();
    m0.Print ();
#endif

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

