#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <cstdlib>
#include <cstdio>


#include <frontend.h>
#include <load.h>

#if TARGET_DEVICE == TARGET_CPU || TARGET_DEVICE == TARGET_MIC
#include <backend_cpu_mic.h>
#elif TARGET_DEVICE == TARGET_GPU
#include <backend_gpu.h>
#endif

//#include <yeah/cpp/timer.hpp>

using namespace std;


void process_lines(vector<string> & lines)
{
    if (lines.size() < 2) {
        cout << "number of lines is wrong" << endl;
        exit(EXIT_FAILURE);
    }

    Loader loader; // frontend
    Docker docker; // backend

    for (auto line = lines.begin() + 1; line < lines.end(); line++) {
        //cout << *line << endl;
        loader.load(*line);
        loader.check();

#if 1
        vector<string> tokens = loader.get_tokens();
        for (unsigned int i = 0; i < tokens.size() - 1; ++i)
            cout << tokens[i] << ",";
        cout << tokens[tokens.size() - 1];
#endif
        cout << endl;

        loader.build_complex(docker.complex);
        docker.run();
    }
}


int main(int argc, char **argv)
{
    string fn;
    if (argc == 1) {
        fn = "a1.csv";
    }
    if (argc == 2) {
        fn = argv[1];
    }
    if (argc > 2) {
        printf("%s <FILE(*.csv)>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    vector<string> lines;
    LoadFnToVecstr(fn, lines);
    process_lines(lines);

    return 0;
}

