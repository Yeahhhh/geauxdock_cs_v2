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

    for (auto line = lines.begin(); line < lines.end(); line++) {
        tokens = yeah::tokenlize(*line, ',');
        string s = tokens[CSVTAG_DATA_ID];
        int a = atoi(s.c_str());
        printf("%07d\n", a);
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

