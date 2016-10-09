#include <cstdio>
#include <cstdlib>

#include <yeah/c/sleep.h>
#include <yeah/measuring/sampling/papi_rapl.hpp>


int main(int argc, char **argv)
{
    {
        yeah::measuring::sampling::PapiRaplAuto m(7);
        SleepS(1);
    }

    return EXIT_SUCCESS;
}
