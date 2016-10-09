#include <cstdio>
#include <cstdlib>

#include <yeah/c/sleep.h>
#include <yeah/measuring/sampling/nvml.hpp>


int main(int argc, char **argv)
{
    {
        yeah::measuring::sampling::NvmlPowerAuto m(98);
        SleepS(1);
    }

    return EXIT_SUCCESS;
}
