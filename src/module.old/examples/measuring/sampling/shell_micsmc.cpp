#include <cstdio>
#include <cstdlib>

#include <yeah/c/sleep.h>
#include <yeah/measuring/sampling/shell_micsmc.hpp>


int main(int argc, char **argv)
{
    {
        yeah::measuring::sampling::ShellMicsmcPowerAuto m(7);
        SleepS(1);
    }

    return EXIT_SUCCESS;
}
