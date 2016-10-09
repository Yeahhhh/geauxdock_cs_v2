#include <cstdio>
#include <cstdlib>

#include <yeah/c/sleep.h>
#include <yeah/measuring/sampling/base.hpp>


int main(int argc, char **argv)
{
    {
        yeah::measuring::sampling::BaseAuto<float> m(9);
        SleepS(1);
    }

    return 0;
}
