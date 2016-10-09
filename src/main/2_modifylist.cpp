#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <cstdlib>
#include <cstdio>

#include <yeah/cpp/text_io.hpp>
#include <yeah/cpp/text_parse.hpp>
#include <yeah/cpp/string.hpp>

#include <size.h>


using namespace std;


void process_lines(vector<string> & lines)
{
    const int nlines = lines.size();
    if (nlines < 2) {
        cout << "number of lines is wrong" << endl;
        exit(EXIT_FAILURE);
    }

    // prints modified CSV title
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


    int i = 0;
    for (auto line = lines.begin() + 1; line < lines.end(); line++) {
        tokens = yeah::tokenlize(*line, ',');

        int data_id = i;
        tokens[CSVTAG_DATA_ID] = yeah::num2string(data_id);
        //int steps_total = 1000;
        //tokens[CSVTAG_STEPS_TOTAL] = yeah::num2string(steps_total);

        yeah::print_tokens_csv(tokens);
        i++;
    }

}


int main(int argc, char **argv)
{
    string fn;
    if (argc == 1) {
        fn = "a2.csv";
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

