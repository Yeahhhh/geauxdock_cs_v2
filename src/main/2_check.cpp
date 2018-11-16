#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <cstdlib>
#include <cstdio>


#include <geauxdock.h>
#include <frontend.h>
#include <size.h>

#include <yeah/cpp/text_io.hpp>
#include <yeah/cpp/text_parse.hpp>
#include <yeah/cpp/string.hpp>



using namespace std;


void process_lines(vector<string> & lines)
{
    if (lines.size() < 2) {
        cout << "number of lines is wrong" << endl;
        exit(EXIT_FAILURE);
    }


    // load and modify the CSV title
    vector<string> tokens;
    tokens = yeah::tokenlize(lines[0], ',');

    tokens[CSVTAG_STEPS_TOTAL] = "steps_total";
    tokens[CSVTAG_SZ_N_PRT] = "sz_n_prt";
    tokens[CSVTAG_SZ_N_LIG] = "sz_n_lig";
    tokens[CSVTAG_SZ_N_TMP] = "sz_n_tmp";
    tokens[CSVTAG_SZ_N_REP] = "sz_n_rep";
    tokens[CSVTAG_SZ_PRT_NPOINT] = "sz_prt_npoint";
    tokens[CSVTAG_SZ_LIG_NATOM] = "sz_lig_natom";
    tokens[CSVTAG_SZ_KDE_NPOINT] = "sz_kde_npoint";
    tokens[CSVTAG_SZ_MCS_NROW] = "sz_mcs_nrow";
    tokens[CSVTAG_TIME_RL_CPU] = "time_rl_cpu";
    tokens[CSVTAG_TIME_EST_CPU] = "time_est_cpu";
    tokens[CSVTAG_TIME_RL_MIC] = "time_rl_mic";
    tokens[CSVTAG_TIME_EST_MIC] = "time_est_mic";
    tokens[CSVTAG_TIME_RL_GPU] = "time_rl_gpu";
    tokens[CSVTAG_TIME_EST_GPU] = "time_est_gpu";
 
    yeah::print_tokens_csv(tokens);








    // load the data, validate, and print the sizes of input files
    Loader loader;
#if 0
    int i = 0;
#endif
    for (auto line = lines.begin() + 1; line < lines.end(); line++) {
        //cout << *line << endl;
        loader.load(*line);     // the loader will validate the data size
#if 0
        int data_id = i;
        tokens[CSVTAG_DATA_ID] = yeah::num2string(data_id);
        i++
#endif

// this is optional
// help figure out the size of data, and assist performance analysis
#if 1
        tokens = loader.get_tokens();
        McPara mcpara = loader.get_mcpara();
        ComplexSize sz = loader.get_sz();

        tokens[CSVTAG_STEPS_TOTAL] = num2string(mcpara.steps_total);
        tokens[CSVTAG_SZ_N_PRT] = num2string(sz.n_prt);
        tokens[CSVTAG_SZ_N_LIG] = num2string(sz.n_lig);
        tokens[CSVTAG_SZ_N_TMP] = num2string(sz.n_tmp);
        tokens[CSVTAG_SZ_N_REP] = num2string(sz.n_rep);
        tokens[CSVTAG_SZ_PRT_NPOINT] = num2string(sz.prt_npoint);
        tokens[CSVTAG_SZ_LIG_NATOM] = num2string(sz.lig_natom);
        tokens[CSVTAG_SZ_KDE_NPOINT] = num2string(sz.kde_npoint);
        tokens[CSVTAG_SZ_MCS_NROW] = num2string(sz.mcs_nrow);
        yeah::print_tokens_csv(tokens);
#endif
        cout << endl;

    }
}





int main(int argc, char **argv)
{
    string fn;
    if (argc == 1) {
        fn = "data1.csv";
    }
    if (argc == 2) {
        fn = argv[1];
    }
    if (argc > 2) {
        printf("%s <FILE(*.csv)>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    vector<string> lines;
    yeah::load_fn_to_vecstr(fn, lines);
    process_lines(lines);

    return 0;
}

