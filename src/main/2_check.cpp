#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <cstdlib>
#include <cstdio>


#include <geauxdock.h>
#include <frontend.h>

#include <yeah/cpp/timer.hpp>

using namespace std;


void process_lines(vector<string> & lines)
{

    const int nlines = lines.size();  // number of lines
    const int n = nlines - 1; // number of input data
    if (nlines < 2) {
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
    for (int i = 0; i < n; ++i) {
        string input = lines[i + 1];
        //cout << input << endl;

        loader.load(input);
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
#if 0
    if (argc != 2) {
        printf("%s <FILE(*.csv)>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    load(argv[1]);
#endif
    load("a1.csv");

    return 0;
}

