#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

#include <cstdlib>
#include <cstdio>

#include <yeah/cpp/text_io.hpp>
#include <yeah/cpp/text_parse.hpp>
#include <yeah/cpp/string.hpp>

#include <size.h>


using namespace std;


void process_lines(
    vector<string> & i0,
    vector<string> & f1,
    vector<string> & f2,
    vector<string> & f3
    )
{
    vector<string> t1, t2, t3; // tokens
    int n = f1.size();

    for (int i = 0; i < n; i++) {
        t1 = yeah::tokenlize(f1[i], ','); // cpu data
        t2 = yeah::tokenlize(f2[i], ','); // mic data
        t3 = yeah::tokenlize(f3[i], ','); // gpu data

        t1[CSVTAG_TIME_RL_MIC] = t2[CSVTAG_TIME_RL_MIC];
        t1[CSVTAG_TIME_RL_GPU] = t3[CSVTAG_TIME_RL_GPU];
        yeah::print_tokens_csv(t1);
    }

}


int main(int argc, char **argv)
{
    if (argc != 4) {
        printf("%s fn1, fn2, fn3\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    vector<string> i0, f1, f2, f3;
    yeah::load_fn_to_vecstr(argv[1], f1);
    yeah::load_fn_to_vecstr(argv[2], f2);
    yeah::load_fn_to_vecstr(argv[3], f3);
    process_lines(i0, f1, f2, f3);

    return 0;
}

