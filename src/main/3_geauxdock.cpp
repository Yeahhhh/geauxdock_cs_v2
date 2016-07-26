#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <cstdlib>
#include <cstdio>


#include <frontend.h>

#if TARGET_DEVICE == TARGET_CPU || TARGET_DEVICE == TARGET_MIC
#include <backend_cpu_mic.h>
#elif TARGET_DEVICE == TARGET_GPU
#include <backend_gpu.h>
#endif

//#include <yeah/cpp/timer.hpp>

using namespace std;


void process_lines(vector<string> & lines)
{

    const int nlines = lines.size();  // number of lines
    const int n = nlines - 1; // number of input data
    if (nlines < 2) {
        cout << "number of lines is wrong" << endl;
        exit(EXIT_FAILURE);
    }


    Loader loader; // frontend
    Docker docker; // backend

    for (int i = 0; i < n; ++i) {
        string input = lines[i + 1];
        //cout << input << endl;

        loader.load(input);
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

void load(const string fnpath)
{
    ifstream ifn(fnpath.c_str());
    if (!ifn.is_open()) {
        cout << "Failed to open " << fnpath << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    vector<string> lines;

    while (getline(ifn, line)) {
        //cout << line << endl;
        lines.push_back(line);
    }

    ifn.close();

    process_lines(lines);
}


int main(int argc, char **argv)
{
    if (argc == 1) {
        load("a2.csv");
    }
    else if (argc == 2) {
        load(argv[1]);
    }
    else {
        printf("%s <FILE(*.csv)>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    return 0;
}

