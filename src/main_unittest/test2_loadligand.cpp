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
    inputfiles.lig_file.path = "../../data/astex/ligands/1a07C1.sdf";
    //inputfiles.lig_file.path = "../../data/edud_1b9vA/ouput_sdf/ZINC16996483.sdf";
    inputfiles.lig_file.molid = "MOLID"; // this is a constant

    Ligand0 *lig0;
    lig0 = new Ligand0[MAX_CONF_LIG];

    loadLigand(&inputfiles.lig_file, lig0);

    delete[] lig0;

    printf("done\n");
    return 0;
}

