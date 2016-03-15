
#include <vector>
#include <map>
#include <cstdlib>
#include <cstdio>
#include <cmath>

#include <dock.h>
#include <size.h>
#include <toggle.h>
#include <util_print.h>
#include <record.h>

#include <yeah/cpp/timer.hpp>

#if IS_PAPI == 1
#include <papi.h>
#include <yeah/papi/wrapper.h>

typedef struct {
  const int event;
  const char * str;
} Papi_event_struct;

#endif




#include "kernel_cpp_montecarlo_soa.C"


void
Dock (Complex *complex, Record *record)
{
  yeah::Timer e[16];

  // data for analysis
  std::map < int, std::vector < LigRecordSingleStep > > multi_reps_records;




#if IS_PAPI == 1
    const Papi_event_struct papi_info_struct[] = {
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
        {PAPI_TOT_CYC,      "PAPI_TOT_CYC"}
    };


    const int papi_event_n = sizeof (papi_info_struct) / sizeof (Papi_event_struct);
    int *papi_event = (int *) malloc (sizeof (int) * papi_event_n);
    long long *papi_event_val = (long long *) malloc (sizeof (long long) * papi_event_n);
    for (int i = 0; i < papi_event_n; ++i) {
        papi_event[i] = papi_info_struct[i].event;
    }
#endif


  e[10].Start ();

  // sizes
  const int steps_total = complex->mcpara.steps_total;
  const int steps_per_dump = complex->mcpara.steps_per_dump;

  printf ("Start kernels on msg %02d\n", complex->signal);
  printf ("steps_per_dump = %d\n", steps_per_dump);
  printf ("steps_total = %d\n", steps_total);

  e[3].Start ();
  // calculate initial energy
  MonteCarlo_d (complex, record, 0, 1);
  e[3].Stop ();

#if IS_PAPI == 1
  PAPI_ERR (PAPI_start_counters (papi_event, papi_event_n));
#endif

  e[4].Start ();
  for (int s1 = 0; s1 < steps_total; s1 += steps_per_dump) {
    printf ("\t%d / %d \n", s1, steps_total);
    // fflush (stdout);
    MonteCarlo_d (complex, record, s1, steps_per_dump);
    #include <kernel_dump.C>
  }
  e[4].Stop ();



/*
	for (int s = 0; s < ligrecord[rep].next_ptr; ++s) {
		LigRecordSingleStep my_step = ligrecord[rep].step[s];
		multi_reps_records[rep].push_back(my_step);
	}
*/


#if IS_PAPI == 1
  PAPI_ERR (PAPI_read_counters (papi_event_val, papi_event_n));
#endif


  e[10].Stop ();


  Complex *ch = complex;
#include "kernel_print.C"
#include "kernel_print_timer.C"
#include "kernel_print_benchmark.C"

  //PrintSummary (complex);


#if IS_PAPI == 1
  PAPI_shutdown ();
  free (papi_event);
  free (papi_event_val);
#endif

}

