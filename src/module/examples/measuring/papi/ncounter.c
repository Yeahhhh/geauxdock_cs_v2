#include <stdio.h>
#include <papi.h>


int
main (int argc, char **argv)
{
    const int ncounter = PAPI_num_counters();
    printf("PAPI_num_counters = %d\n", ncounter);

    return(0);
}
