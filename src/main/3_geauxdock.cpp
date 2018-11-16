#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <cstdlib>
#include <cstdio>


#include <size.h>
#include <frontend.h>

#if TARGET_DEVICE == TARGET_CPU || TARGET_DEVICE == TARGET_MIC
#include <backend_cpu_mic.h>
#elif TARGET_DEVICE == TARGET_GPU
#include <backend_gpu.h>
#endif

#include <yeah/cpp/text_io.hpp>
#include <yeah/cpp/text_parse.hpp>
#include <yeah/measuring/counting/timer.hpp>


using namespace std;


void process_lines(vector<string> & lines)
{
    if (lines.size() < 2) {
        cout << "number of lines is wrong" << endl;
        exit(EXIT_FAILURE);
    }

    vector<string> tokens;
    Loader loader; // frontend
    Docker docker; // backend
    yeah::measuring::counting::Timer t;

    for (auto line = lines.begin() + 1; line < lines.end(); line++) {
        //cout << *line << endl;
        loader.load(*line);
        loader.build_complex(docker.complex);

        t.Reset();
        t.Start();
        docker.run();
        t.Stop();
        //t.Print();




// this is optional
// help figure out the size of data, and assist performance analysis
#if 0
        tokens = loader.get_tokens();
        McPara mcpara = loader.get_mcpara();
        ComplexSize sz = loader.get_sz();

#if TARGET_DEVICE == TARGET_CPU
        tokens[CSVTAG_TIME_RL_CPU] = num2string(t.ts);
#endif
#if TARGET_DEVICE == TARGET_MIC
        tokens[CSVTAG_TIME_RL_MIC] = num2string(t.ts);
#endif
#if TARGET_DEVICE == TARGET_GPU
        tokens[CSVTAG_TIME_RL_GPU] = num2string(t.ts);
#endif

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
        cout << endl;
#endif


    }
}


int main(int argc, char **argv)
{
    string fn;
    if (argc == 1) {
        fn = "data2.csv";
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

