#include <string>
#include <iostream>

#include <cstdlib>
#include <cstdio>

#include <frontend.h>
//#include <backend_cpu_mic.h>
#include <backend_gpu.h>


using namespace std;


int main(int argc, char **argv)
{
    string input1 =
        "magicnumber_a4a6b25c,0,1a07C,/worka/work/yfang11/geauxdock_cs_v2/data/astex/proteins/1a07C.pdb,1a07C1,/worka/work/yfang11/geauxdock_cs_v2/data/astex/ligands/1a07C1.sdf,/worka/work/yfang11/geauxdock_cs_v2/data/astex/ligands/1a07C1-0.8.ff,/worka/work/yfang11/geauxdock_cs_v2/data/parameters/08ff_opt,/worka/work/yfang11/geauxdock_cs_v2/data/parameters/paras,/worka/work/yfang11/geauxdock_cs_v2/data/parameters/08_nor_a,/worka/work/yfang11/geauxdock_cs_v2/data/parameters/08_nor_b,1,0.044,0.036,0.02,0.08,1,0,1000,0,11,51,1,561,344,34,454,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";

    Loader loader;
    Docker docker;

    loader.load(input1);
    loader.check();

    loader.build_complex(docker.complex);
    docker.run();

    return 0;
}

