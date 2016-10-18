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

    vector<string> tokens;
    tokens = yeah::tokenlize(lines[1], ',');
    int ntemp = atoi(tokens[CSVTAG_NTEMP].c_str());
    int sz_n_tmp = atoi(tokens[CSVTAG_SZ_N_TMP].c_str());
    int sz_n_rep = atoi(tokens[CSVTAG_SZ_N_REP].c_str());

    vector<string> t2 = tokens;
    for (int i = 1; i <= 240 * 3; i++) {
        std::stringstream b0, b1, b2, b3;
        b0 << i - 1;
        b1 << ntemp * i;
        b2 << sz_n_tmp * i;
        b3 << sz_n_rep * i;
        t2[CSVTAG_DATA_ID] = b0.str();
        t2[CSVTAG_NTEMP] = b1.str();
        t2[CSVTAG_SZ_N_TMP] = b2.str();
        t2[CSVTAG_SZ_N_REP] = b3.str();
        yeah::print_tokens_csv(t2);
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

