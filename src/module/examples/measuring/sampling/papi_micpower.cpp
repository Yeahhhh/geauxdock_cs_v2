#include <cstdio>
#include <cstdlib>

#include <yeah/c/sleep.h>
#include <yeah/measuring/sampling/papi_micpower.hpp>


int main(int argc, char **argv)
{
    {
        yeah::measuring::sampling::PapiMicpowerAuto m(7);
        SleepS(1);
    }

    return EXIT_SUCCESS;
}
