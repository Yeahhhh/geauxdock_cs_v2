#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstring>
#include <sys/stat.h>


#include <geauxdock.h>
#include <size.h>
#include <toggle.h>
#include <load.h>
#include <frontend.h>
#include <util_optimize.h>
#include <util_print.h>

//#include <yeah/c/mkdir.h>


using namespace std;

void Usage(char *bin)
{
    fprintf(stderr, "usage: %s [options]\n", bin);
    exit(1);
}

void Banner()
{
    cout << "------------------------------------------------------------"
        << endl
        << "                         GeauxDock                          "
        << endl
        << "                        version 0.1                         "
        << endl
        << endl
        << "   GPU-accelerated mixed-resolution ligand docking using    "
        << endl
        << "                ReplicaMC Exchange Monte Carlo                "
        << endl
        << "------------------------------------------------------------"
        << endl
        << endl;
}



void SetMcLog(McLog *mclog)
{
    mclog->ac_mc = 0;  // MC acceptance counter
    for (int i = 0; i < MAX_REP; ++i)
        mclog->acs_mc[i] = 0;  // MC acceptance counter for all replicas
}














static void trim(string & s)
{
    size_t p;
    p = s.find_first_not_of(" \t");
    s.erase(0, p);

    p = s.find_last_not_of(" \t");
    if (string::npos != p)
        s.erase(p + 1);
}


vector<string> tokenlize(string & line)
{
    vector<string> tokens;
    stringstream ss(line);
    string t;

    // cout << line << endl;

    while (getline(ss, t, ',')) {
        trim(t);
        tokens.push_back(t);
    }

#if 0
#define NTOKEN 16
    const int n = tokens.size();
    if (n != NTOKEN) {
        cout << "number of tokens is wrong" << endl;
        exit(EXIT_FAILURE);
    }
#endif

    return tokens;
}




void ParaParser::parse(std::string str)
{
    tokens = tokenlize(str);

#if 0
    for (int i = 0; i < tokens.size(); ++i) {
        cout << "token" << "\t" << i << "\t";
        cout << tokens[i] << endl;
    }
#endif

#if 0
    cout << tokens[4] << endl; // .sdf
    cout << tokens[5] << endl; // .ff
#endif

    int argn = 0;

    argn++; // skip magic number
    inputfiles.id = atoi(tokens[argn++].c_str());

    inputfiles.prt_file.id = tokens[argn++];
    inputfiles.prt_file.path = tokens[argn++];

    inputfiles.lhm_file.ligand_id = tokens[argn++];
    inputfiles.lig_file.path = tokens[argn++];
    inputfiles.lhm_file.path = tokens[argn++];
    inputfiles.lig_file.molid = "MOLID";         // this is a constant

    inputfiles.weight_file.path = tokens[argn++];
    inputfiles.enepara_file.path = tokens[argn++];
    inputfiles.norpara_file.path_a = tokens[argn++];
    inputfiles.norpara_file.path_b = tokens[argn++];

    exchgpara.num_temp = atoi(tokens[argn++].c_str());
    exchgpara.ceiling_temp = atof(tokens[argn++].c_str());
    exchgpara.floor_temp = atof(tokens[argn++].c_str());
    const float tras_scale = atof(tokens[argn++].c_str());
    const float rot_scale = atof(tokens[argn++].c_str());
    mcpara.move_scale[0] = tras_scale;
    mcpara.move_scale[1] = tras_scale;
    mcpara.move_scale[2] = tras_scale;
    mcpara.move_scale[3] = rot_scale;
    mcpara.move_scale[4] = rot_scale;
    mcpara.move_scale[5] = rot_scale;


    mcpara.steps_per_dump = STEPS_PER_DUMP;        // constant, see size.h
    mcpara.steps_n_dump = atoi(tokens[argn++].c_str());
    mcpara.steps_total = mcpara.steps_n_dump * mcpara.steps_per_dump;

    strcpy(mcpara.outputdir, "NO_OUTPUTDIR");
    strcpy(mcpara.outputfile, "NO_OUTPUTFILE");
}









Loader::Loader()
{
    inputfiles.prt_file.path = "NOT_ASSIGNED";
    inputfiles.prt_file.id = "NOT_ASSIGNED";
    inputfiles.enepara_file.path = "NOT_ASSIGNED";
    inputfiles.weight_file.path = "NOT_ASSIGNED";
    inputfiles.norpara_file.path_a = "NOT_ASSIGNED";
    inputfiles.norpara_file.path_b = "NOT_ASSIGNED";


    prt0 = new Protein0[MAX_CONF_PRT];
    prt = new Protein[MAX_CONF_PRT];
    enepara0 = new EnePara0;
    enepara = new EnePara;


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

    temp = new Temp[MAX_TMP];
    replica = new ReplicaMC[MAX_REP];
}


Loader::~Loader()
{
    delete[] prt0;
    delete[] prt;
    delete enepara0;
    delete enepara;

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

    delete[] temp;
    delete[] replica;
}







bool Loader::is_identical_target()
{
    bool is_same_target =
        (this->inputfiles.prt_file.path == ParaParser::inputfiles.prt_file.path) &&
        (this->inputfiles.prt_file.id == ParaParser::inputfiles.prt_file.id) &&
        (this->inputfiles.enepara_file.path == ParaParser::inputfiles.enepara_file.path) &&
        (this->inputfiles.weight_file.path == ParaParser::inputfiles.weight_file.path) &&
        (this->inputfiles.norpara_file.path_a == ParaParser::inputfiles.norpara_file.path_a) &&
        (this->inputfiles.norpara_file.path_b == ParaParser::inputfiles.norpara_file.path_b);

    return is_same_target;
}


void Loader::assign_new_target()
{
    (this->inputfiles.prt_file.path = ParaParser::inputfiles.prt_file.path);
    (this->inputfiles.prt_file.id = ParaParser::inputfiles.prt_file.id);
    (this->inputfiles.enepara_file.path = ParaParser::inputfiles.enepara_file.path);
    (this->inputfiles.weight_file.path = ParaParser::inputfiles.weight_file.path);
    (this->inputfiles.norpara_file.path_a = ParaParser::inputfiles.norpara_file.path_a);
    (this->inputfiles.norpara_file.path_b = ParaParser::inputfiles.norpara_file.path_b);
}




void Loader::set_temperature()
{
    int num_temp = exchgpara.num_temp;
    float floor_temp = exchgpara.floor_temp;
    float ceiling_temp = exchgpara.ceiling_temp;


    if (num_temp == 1) {
        float my_temp = floor_temp;
        float beta = 1.0f / (BOLTZMANN_CONST * my_temp);

        for (int i = 0; i < num_temp; i++) {
            // printf ("temp # %d\t\t\t%f\n", i, my_temp);
            temp[i].order = i;
            temp[i].minus_beta = 0.0f - beta;
        }
    }
    else {
        const float temp_ratio =
            exp(log(ceiling_temp / floor_temp) / (float)(num_temp - 1));
        float a = floor_temp;
        for (int i = 0; i < num_temp; i++) {
            float my_temp = a;
            float my_beta = 1.0f / (BOLTZMANN_CONST * my_temp);
            // printf ("temp # %d\t\t\t%f\n", i, my_temp);

            temp[i].order = i;
            temp[i].minus_beta = 0.0f - my_beta;

            a *= temp_ratio;
        }
    }

    // for (int i = 0; i < num_temp; i++) {
    //   temp[i].t = floor_temp;
    //   temp[i].minus_beta = -1.0f / temp[i].t;
    //   temp[i].order = i;
    // }
}




// replica[n_rep]
// replica[n_prt][n_tmp][n_lig]
void Loader::set_replica()
{
    const int n_lig = sz.n_lig;
    const int n_prt = sz.n_prt;
    const int n_tmp = sz.n_tmp;

    for (int p = 0; p < n_prt; ++p) {
        for (int t = 0; t < n_tmp; ++t) {
            for (int l = 0; l < n_lig; ++l) {
                const int flatten_addr = n_tmp * n_lig * p + n_lig * t + l;
                replica[flatten_addr].idx_rep = flatten_addr;

                replica[flatten_addr].idx_prt = p;
                replica[flatten_addr].idx_tmp = t;
                replica[flatten_addr].idx_lig = l;

                /*
                // set identical replicas for test purpose
                replica[flatten_addr].idx_prt = 0;
                replica[flatten_addr].idx_tmp = 0;
                replica[flatten_addr].idx_lig = 0;
                */

                for (int aa = 0; aa < 6; ++aa)
                    replica[flatten_addr].movematrix[aa] = 0.0f;
                for (int aa = 0; aa < MAXWEI; ++aa)
                    replica[flatten_addr].energy[aa] = 0.0f;

                replica[flatten_addr].is_accept = 0;
            }
        }
    }
}





void Loader::load_target()
{
    // The data set is stored in one buffer.
    // It could be extended to multiple buffers,
    // so that multiple target couild be saved altogether
    if (is_identical_target() == false) {
        assign_new_target();

        loadProtein(&inputfiles.prt_file, prt0);
        loadEnePara(&inputfiles.enepara_file, enepara0);
        loadWeight(&inputfiles.weight_file, enepara0);
        loadNorPara(&inputfiles.norpara_file, enepara0);
        OptimizeProtein(prt0, prt, enepara0, inputfiles.prt_file.conf_total);
        OptimizeEnepara(enepara0, enepara);

        cout << "done loading target" << endl;
    }
    else {
        cout << "skip loading identical target" << endl;
    }
}


void Loader::load_ligand()
{
    loadLigand(&inputfiles.lig_file, lig0);
    loadLHM(&inputfiles.lhm_file, psp0, kde0, mcs0);

    // debug
    PrintLigand0(lig0);


    OptimizeKde(kde0, kde);
    OptimizeLigand(lig0, kde, lig, inputfiles.lig_file.conf_total);
    OptimizePsp(psp0, psp);
    OptimizeMcs(mcs0, mcs, mcs_r, mcs_ell, mcs_csr, inputfiles.lhm_file.mcs_nrow);

    cout << "done loading ligand" << endl;
}




void Loader::load(std::string str)
{
    ParaParser::parse(str);
    inputfiles.id = ParaParser::inputfiles.id;
    inputfiles.lig_file = ParaParser::inputfiles.lig_file;
    inputfiles.lhm_file = ParaParser::inputfiles.lhm_file;

    load_target();
    load_ligand();


    sz.n_prt = inputfiles.prt_file.conf_total; // protein conf
    sz.n_lig = inputfiles.lig_file.conf_total; // ligand conf
    sz.n_tmp = ParaParser::exchgpara.num_temp; // temperature
    sz.n_rep = sz.n_lig * sz.n_prt * sz.n_tmp;
    sz.prt_npoint = inputfiles.prt_file.prt_npoint;
    sz.lig_natom = inputfiles.lig_file.lig_natom;
    sz.kde_npoint = kde0->kde_npoint;
    sz.mcs_nrow = inputfiles.lhm_file.mcs_nrow;



    // set protein pocket center
    const float cx = lig0[0].pocket_center[0];
    const float cy = lig0[0].pocket_center[1];
    const float cz = lig0[0].pocket_center[2];
    for (int i = 0; i < sz.n_prt; i++) {
        Protein *dst = &prt[i];
        dst->pocket_center[0] = cx;
        dst->pocket_center[1] = cy;
        dst->pocket_center[2] = cz;
    }


    OptimizeProtein(prt0, prt, enepara0, sz.n_prt);
    set_temperature();
    set_replica();
}



void Loader::print_sz()
{
    cout << sz.n_prt << ",";
    cout << sz.n_lig << ",";
    cout << sz.n_tmp << ",";
    cout << sz.n_rep << ",";
    cout << sz.prt_npoint << ",";
    cout << sz.lig_natom << ",";
    cout << sz.kde_npoint << ",";
    cout << sz.mcs_nrow;

    cout << endl;
}


void Loader::check()
{
    //print_sz();

    if (sz.n_prt > MAX_CONF_PRT) {
        cout << inputfiles.prt_file.id << " ";
        cout << "protein conformation number exceeds the limit: ";
        cout << sz.n_prt << " > " << MAX_CONF_PRT << endl;
        exit(EXIT_FAILURE);
    }
    if (sz.n_lig > MAX_CONF_LIG) {
        cout << inputfiles.lig_file.id << " ";
        cout << "ligand conformation number exceeds the limit: ";
        cout << sz.n_lig << " > " << MAX_CONF_LIG << endl;
        exit(EXIT_FAILURE);
    }
    if (sz.n_tmp > MAX_TMP) {
        cout << "temperature number exceeds the limit: ";
        cout << sz.n_tmp << " > " << MAX_TMP << endl;
        exit(EXIT_FAILURE);
    }
    if (sz.n_rep > MAX_REP) {
        cout << "ensemble number execeeds the limit: ";
        cout << sz.n_rep << " > " << MAX_REP << endl;
        exit(EXIT_FAILURE);
    }
    if (sz.prt_npoint > MAXPRO) {
        cout << inputfiles.prt_file.id << " ";
        cout << "protein point number execeeds the limit: ";
        cout << sz.prt_npoint << " > " << MAXPRO << endl;
        exit(EXIT_FAILURE);
    }
    if (sz.lig_natom > MAXLIG) {
        cout << inputfiles.lig_file.id << " ";
        cout << "ligand point number execeeds the limit: ";
        cout << sz.lig_natom << " > " << MAXLIG << endl;
        exit(EXIT_FAILURE);
    }
    if (sz.kde_npoint > MAXKDE) {
        cout << "KDE point number execeeds the limit: ";
        cout << sz.kde_npoint << " > " << MAXKDE << endl;
        exit(EXIT_FAILURE);
    }
    if (sz.mcs_nrow > MAX_MCS_ROW) {
        cout << "MCS point number execeeds the limit: ";
        cout << sz.mcs_nrow << " > " << MAX_MCS_ROW << endl;
        exit(EXIT_FAILURE);
    }

    cout << "done checking" << endl;
}




void Loader::build_complex(Complex * complex)
{
    for (int i = 0; i < sz.n_lig; i++) complex->lig[i] = lig[i];
    for (int i = 0; i < sz.n_prt; i++) complex->prt[i] = prt[i];
    complex->psp = *psp;
    complex->kde = *kde;
    for (int i = 0; i < sz.mcs_nrow; i++) complex->mcs[i] = mcs[i];
    complex->mcs_r =  *mcs_r;
    complex->mcs_ell = *mcs_ell;
    complex->mcs_csr = *mcs_csr;
    complex->enepara = *enepara;
    for (int i = 0; i < sz.n_tmp; i++) complex->temp[i] = temp[i];


    for (int i = 0; i < sz.n_rep; i++) complex->replica[i] = replica[i];
    complex->size = sz;
    complex->mcpara = mcpara;


    //complex->inputfiles = ParaParser::inputfiles;



    // get the file name from a path
    /*
       std::string str;
       size_t p1;

       str = inputfiles.lig_file.path;
       p1 = str.find_last_of("/");
       if (std::string::npos != p1)
       str.erase(0, p1 + 1);
       strcpy(complex->lig_file, str.c_str());

       str = inputfiles.prt_file.path;
       p1 = str.find_last_of("/");
       if (std::string::npos != p1)
       str.erase(0, p1 + 1);
       strcpy(complex->prt_file, str.c_str());
       */

    strcpy(complex->lig_file, inputfiles.lig_file.path.c_str());
    strcpy(complex->prt_file, inputfiles.prt_file.path.c_str());
    strcpy(complex->lhm_file, inputfiles.lhm_file.path.c_str());
    strcpy(complex->enepara_file, inputfiles.enepara_file.path.c_str());
    strcpy(complex->weight_file, inputfiles.weight_file.path.c_str());
}


