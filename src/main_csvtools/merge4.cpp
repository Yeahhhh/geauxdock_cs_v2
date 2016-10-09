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
    int if1, if2, if3; // indices
    if1 = if2 = if3 = 0;
    int nf1, nf2, nf3; // number

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
                std::cout << nf1 << "  miss1" << std::endl;
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

        // mic data
        while (1) {
            t2 = yeah::tokenlize(f2[if2], ',');
            nf2 = atoi(t2[CSVTAG_DATA_ID].c_str());
            if (nf2 == number)
                break;
            else {
                if2++;
                std::cout << nf1 << "  miss2" << std::endl;
            }
        }

        // gpu data
        while (1) {
            t3 = yeah::tokenlize(f3[if3], ',');
            nf3 = atoi(t3[CSVTAG_DATA_ID].c_str());
            if (nf3 == number)
                break;
            else {
                if3++;
                std::cout << nf1 << "  miss3" << std::endl;
            }
        }




        //std::cout << if1 << " " << number << std::endl;
        //std::cout << if2 << number << std::endl;
        //std::cout << if3 << number << std::endl;
        //std::cout << std::endl;

        //std::cout << f1[if1] << std::endl;
        //std::cout << f2[if2] << std::endl;
        //std::cout << f3[if3] << std::endl;

        t1[CSVTAG_TIME_RL_MIC] = t2[CSVTAG_TIME_RL_MIC];
        t1[CSVTAG_TIME_RL_GPU] = t3[CSVTAG_TIME_RL_GPU];
        yeah::print_tokens_csv(t1);
    }

}


int main(int argc, char **argv)
{
    if (argc != 5) {
        printf("%s common_idx, fn1, fn2, fn3\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    vector<string> i0, f1, f2, f3;
    yeah::load_fn_to_vecstr(argv[1], i0);
    yeah::load_fn_to_vecstr(argv[2], f1);
    yeah::load_fn_to_vecstr(argv[3], f2);
    yeah::load_fn_to_vecstr(argv[4], f3);
    process_lines(i0, f1, f2, f3);

    return 0;
}

