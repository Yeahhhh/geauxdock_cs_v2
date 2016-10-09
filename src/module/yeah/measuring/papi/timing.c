#include <papi.h>


/* Return current time (number of seconds since the Epoch). */
double
HostTimeNow ()
{
    return (double) PAPI_get_virt_usec () * 1e-6;
}


