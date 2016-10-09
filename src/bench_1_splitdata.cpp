#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <cstdlib>
#include <cstdio>

#include <yeah/cpp/text_io.hpp>


using namespace std;

#define NPICES 100



void process_lines(vector<string> & lines)
{
    nlines = lines.size();
    if (nlines < 2) {
        cout << "number of lines is wrong" << endl;
        exit(EXIT_FAILURE);
    }
    const int nlines_per_piece = nlines.size() / NPICES;


    int fn_idx = 0;
    int line_idx = 0;
    int idx_begin[NPICES];
    int idx_end[NPICES];
    for (int i = 0; i < NPICES; i++) {
        idx_begin[i] = nlines_per_piece * i;
        idx_end[i] = idx_begin[i] + NPICES;
        cout << idx_begin[i] << " " << idx_end[i] << endl;
    }



    /*
    ofstream myfile;
    myfile.open ("example.txt");


    for (auto line = lines.begin() + 1; line < lines.end(); line++) {
        line_idx++;
        if (line_idx > nlines_per_piece) {
            line_idx = 0;
            fn_idx++;
            cout << lines[1] << endl;
            printf("%d\n", fn_idx);
        }
    }
    */
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
    load_fn_to_vecstr(fn, lines);
    process_lines(lines);

    return 0;
}

