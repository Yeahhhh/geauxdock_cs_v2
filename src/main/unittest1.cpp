#include <string>
#include <iostream>

#include <cstdlib>
#include <cstdio>

#include <frontend.h>


using namespace std;



int main(int argc, char **argv)
{
    Loader loader;


    string input1 = "magicnumber_a4a6b25c,0,1a07C,/home/yfang11/work2/geauxdock_cs_v2/data/astex/proteins/1a07C.pdb,1a07C1,/home/yfang11/work2/geauxdock_cs_v2/data/astex/ligands/1a07C1.sdf,/home/yfang11/work2/geauxdock_cs_v2/data/astex/ligands/1a07C1-0.8.ff,/home/yfang11/work2/geauxdock_cs_v2/data/parameters/08ff_opt,/home/yfang11/work2/geauxdock_cs_v2/data/parameters/paras,/home/yfang11/work2/geauxdock_cs_v2/data/parameters/08_nor_a,/home/yfang11/work2/geauxdock_cs_v2/data/parameters/08_nor_b,1,0.044,0.036,0.02,0.08,2,0,200,0,11,51,1,561,344,34,454,11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";

    //string input2 = "magicnumber_a4a6b25c,1,1a07C,/home/yfang11/work2/geauxdock_cs_v2/data/astex/proteins/1a07C.pdb,1a0qB1,/home/yfang11/work2/geauxdock_cs_v2/data/astex/ligands/1a0qB1.sdf,/home/yfang11/work2/geauxdock_cs_v2/data/astex/ligands/1a0qB1-0.8.ff,/home/yfang11/work2/geauxdock_cs_v2/data/parameters/08ff_opt,/home/yfang11/work2/geauxdock_cs_v2/data/parameters/paras,/home/yfang11/work2/geauxdock_cs_v2/data/parameters/08_nor_a,/home/yfang11/work2/geauxdock_cs_v2/data/parameters/08_nor_b,1,0.044,0.036,0.02,0.08,2,0,200,0,11,51,1,561,344,23,1034,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0";



    loader.load(input1);
    loader.print_sz();
    loader.load(input1);
    loader.print_sz();
    loader.load(input1);
    loader.print_sz();

    //loader.load(input2);
    //loader.check();
    cout << endl;

    return 0;
}

