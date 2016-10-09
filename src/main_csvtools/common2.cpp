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
    vector<string> & f1
    )
{
    vector<string> t1;
    int if1 = 0;
    int nf1;

    for (auto i = i0.begin(); i < i0.end(); i++) {
        string line = *i;
        int number = atoi(line.c_str());

        // cpu data
        while (1) {
            t1 = yeah::tokenlize(f1[if1], ',');
            nf1 = atoi(t1[CSVTAG_DATA_ID].c_str());
            if (nf1 == number)
                break;
            else {
                if1++;
                //std::cout << nf1 << "  miss1" << std::endl;
            }
            /*
            if (nf1 == number) {
                std::cout << nf1 << "   hit" << std::endl;
                break;
            }
            else {
                if1++;
                std::cout << nf1 << "  miss" << std::endl;
            }
            */
        }


        //std::cout << if1 << " " << number << std::endl;
        //std::cout << if2 << number << std::endl;
        //std::cout << if3 << number << std::endl;
        //std::cout << std::endl;

        //std::cout << f1[if1] << std::endl;
        //std::cout << f2[if2] << std::endl;
        //std::cout << f3[if3] << std::endl;

        //t1[CSVTAG_TIME_RL_MIC] = t2[CSVTAG_TIME_RL_MIC];
        //t1[CSVTAG_TIME_RL_GPU] = t3[CSVTAG_TIME_RL_GPU];
        yeah::print_tokens_csv(t1);
    }

}


int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("%s common_idx, fn1, fn2\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    vector<string> i0, f1, f2, f3;
    yeah::load_fn_to_vecstr(argv[1], i0);
    yeah::load_fn_to_vecstr(argv[2], f1);
    process_lines(i0, f1);

    return 0;
}

