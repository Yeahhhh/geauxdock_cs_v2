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
    inputfiles.lhm_file.ligand_id = "1a07C1";
    inputfiles.lig_file.path = "../../data/astex/ligands/1a07C1.sdf";
    inputfiles.lhm_file.path = "../../data/astex/ligands/1a07C1-0.8.ff";
    inputfiles.lig_file.molid = "MOLID"; // this is a constant


    Ligand0 *lig0;
    Psp0 *psp0;
    Kde0 *kde0;
    Mcs0 *mcs0;
    Ligand *lig;
    Psp *psp;
    Kde *kde;
    Mcs *mcs;
    Mcs_R *mcs_r;
    Mcs_ELL *mcs_ell;
    Mcs_CSR *mcs_csr;

    lig0 = new Ligand0[MAX_CONF_LIG];
    psp0 = new Psp0;
    kde0 = new Kde0;
    mcs0 = new Mcs0[MAX_MCS_ROW];
    lig = new Ligand[MAX_CONF_LIG];
    psp = new Psp;
    kde = new Kde;
    mcs = new Mcs[MAX_MCS_ROW];
    mcs_r = new Mcs_R;
    mcs_ell = new Mcs_ELL;
    mcs_csr = new Mcs_CSR;


    loadLigand(&inputfiles.lig_file, lig0);
    loadLHM(&inputfiles.lhm_file, psp0, kde0, mcs0);

    OptimizeKde(kde0, kde);
    OptimizeLigand(lig0, kde, lig, inputfiles.lig_file.conf_total);
    OptimizePsp(psp0, psp);
    OptimizeMcs(mcs0, mcs, mcs_r, mcs_ell, mcs_csr, inputfiles.lhm_file.mcs_nrow);

    delete[] lig0;
    delete psp0;
    delete kde0;
    delete[] mcs0;
    delete[] lig;
    delete psp;
    delete kde;
    delete[] mcs;
    delete mcs_r;
    delete mcs_ell;
    delete mcs_csr;

    printf("done\n");
    return 0;
}

