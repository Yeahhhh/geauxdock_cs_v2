
#ifndef _YEAH_MEASURING_PAPI_STRUCT_H_
#define _YEAH_MEASURING_PAPI_STRUCT_H_

#define PAPI_NULL_YEAH 0x00000000

typedef struct {
  const int event;
  const char * str;
} Papi_event_struct;


int Papi_event_struct_n (Papi_event_struct * tt)
{
    int n = 0;
    while (1) {
        if (tt[n].event != PAPI_NULL_YEAH)
            n++;
        else
            break;
    }
    return n;
}


int Get_papi_events_n (int * tt)
{
    int n = 0;
    while (1) {
        if (tt[n] != PAPI_NULL_YEAH)
            n++;
        else
            break;
    }
    return n;
}






#endif
