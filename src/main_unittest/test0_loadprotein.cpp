#include <string>
#include <iostream>

#include <cstdlib>
#include <cstdio>

#include <load.h>
#include <util_optimize.h>


using namespace std;



int main(int argc, char **argv)
{
    InputFiles inputfiles;
    inputfiles.prt_file.id = "1a07C";
    inputfiles.prt_file.path = "../../data/astex/proteins/1a07C.pdb";
    inputfiles.enepara_file.path = "../../data/parameters/paras";

    Protein0 *prt0;
    Protein *prt;
    EnePara0 *enepara0;
    prt0 = new Protein0[MAX_CONF_PRT];
    prt = new Protein[MAX_CONF_PRT];
    enepara0 = new EnePara0;

    loadProtein(&inputfiles.prt_file, prt0);
    loadEnePara(&inputfiles.enepara_file, enepara0);
    OptimizeProtein(prt0, prt, enepara0, inputfiles.prt_file.conf_total);


    delete[] prt0;
    delete[] prt;
    delete enepara0;


    printf("done\n");
    return 0;
}

