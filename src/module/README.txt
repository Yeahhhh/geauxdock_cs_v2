libraries that I frequently use in Linux X86_64





Build this library package:
    cd module/yeah
    vi GNUmakefile
    gmake clean
    gmake





Use this library package:

Method 1 (prefered): using environment-modules to import env            !!! BUGGY, to be done
    module use PATH/TO/module/env
    module add yeahmodule
    cc -c a.c
    cc a.o -lyeahc

Method 2: using BASH script to import env
    . PATH/TO/module/env/sourceme.bash
    cc -c a.c
    cc a.o -lyeahc

Method 3:
    put the entire package ("module") under your project
    cc -I./module -c a.c
    cc a.o -L./module/lib -lyeahc


