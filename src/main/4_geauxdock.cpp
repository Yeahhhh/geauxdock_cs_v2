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

    // prints modified CSV title
    vector<string> tokens;
    tokens = yeah::tokenlize(lines[0], ',');
#if TARGET_DEVICE == TARGET_CPU
    tokens[CSVTAG_TIME_RL_CPU] = "time_rl_cpu";
    tokens[CSVTAG_TIME_EST_CPU] = "time_est_cpu";
#endif
#if TARGET_DEVICE == TARGET_MIC
    tokens[CSVTAG_TIME_RL_MIC] = "time_rl_mic";
    tokens[CSVTAG_TIME_EST_MIC] = "time_est_mic";
#endif
#if TARGET_DEVICE == TARGET_GPU
    tokens[CSVTAG_TIME_RL_GPU] = "time_rl_gpu";
    tokens[CSVTAG_TIME_EST_GPU] = "time_est_gpu";
#endif
    yeah::print_tokens_csv(tokens);



    Loader loader; // frontend
    Docker docker; // backend
    yeah::measuring::counting::Timer t;

    for (auto line = lines.begin() + 1; line < lines.end(); line++) {
        //cout << *line << endl;
        loader.load(*line);
        loader.check();
        loader.build_complex(docker.complex);

        t.Reset();
        t.Start();
        docker.run();
        t.Stop();
        //t.Print();

        tokens = loader.get_tokens();
#if TARGET_DEVICE == TARGET_CPU
        tokens[CSVTAG_TIME_RL_CPU] = num2string(t.ts);
#endif
#if TARGET_DEVICE == TARGET_MIC
        tokens[CSVTAG_TIME_RL_MIC] = num2string(t.ts);
#endif
#if TARGET_DEVICE == TARGET_GPU
        tokens[CSVTAG_TIME_RL_GPU] = num2string(t.ts);
#endif

        yeah::print_tokens_csv(tokens);
        cout << endl;

    }
}


int main(int argc, char **argv)
{
    string fn;
    if (argc == 1) {
        fn = "a4.csv";
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

