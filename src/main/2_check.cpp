#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <cstdlib>
#include <cstdio>


#include <geauxdock.h>
#include <frontend.h>
#include <load.h>

#include <yeah/cpp/timer.hpp>

using namespace std;


void process_lines(vector<string> & lines)
{
    if (lines.size() < 2) {
        cout << "number of lines is wrong" << endl;
        exit(EXIT_FAILURE);
    }

    // prints modified CSV title
    vector<string> tokens;
    tokens = tokenlize(lines[0]);

    tokens[18] = "steps_total";
    tokens[20] = "sz.n_prt";
    tokens[21] = "sz.n_lig";
    tokens[22] = "sz.n_tmp";
    tokens[23] = "sz.n_rep";
    tokens[24] = "sz.prt_npoint";
    tokens[25] = "sz.lig_natom";
    tokens[26] = "sz.kde_npoint";
    tokens[27] = "sz.mcs_nrow";

    for (unsigned int i = 0; i < tokens.size() - 1; ++i)
        cout << tokens[i] << ",";
    cout << tokens[tokens.size() - 1];
    cout << endl;


    // CSV contents
    Loader loader;
    for (auto line = lines.begin() + 1; line < lines.end(); line++) {
        //cout << *line << endl;
        loader.load(*line);
        loader.check();

#if 1
        tokens = loader.get_tokens();
        McPara mcpara = loader.get_mcpara();
        ComplexSize sz = loader.get_sz();

        tokens[18] = num2string(mcpara.steps_total);
        tokens[20] = num2string(sz.n_prt);
        tokens[21] = num2string(sz.n_lig);
        tokens[22] = num2string(sz.n_tmp);
        tokens[23] = num2string(sz.n_rep);
        tokens[24] = num2string(sz.prt_npoint);
        tokens[25] = num2string(sz.lig_natom);
        tokens[26] = num2string(sz.kde_npoint);
        tokens[27] = num2string(sz.mcs_nrow);
        for (unsigned int i = 0; i < tokens.size() - 1; ++i)
            cout << tokens[i] << ",";
        cout << tokens[tokens.size() - 1];
#endif
        cout << endl;

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

