Build this library package:
    cd PATH/TO/module/yeah
    make -B



Use this library package:

Method 1:
    put the entire package ("module") under "src_root" of your project
    cc -I./module -c a.c
    cc a.o -L./module/lib -lyeahc

Method 2:
    source PATH/TO/module/sourceme.bash   # Import environment variables using Bash
    cc -c a.c
    cc a.o -lyeahc




COPYRIGHT

Please read the copyright of each components before distributing the code.
For what I understand, you should announce the following statement(s):

This software contains source code provided by NVIDIA Corporation.
This software contains source code (Random123) developed by D. E. Shaw Research.
This software contains source code (Catch) developed by Phil Nash

