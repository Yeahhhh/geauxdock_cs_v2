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



#include <sstream>

template <typename T>
string num2string (T n)
{
    ostringstream oss;
    oss << n;
    return oss.str();
}





void process_lines(vector<string> & lines)
{
    const int nlines = lines.size();
    if (nlines < 2) {
        cout << "number of lines is wrong" << endl;
        exit(EXIT_FAILURE);
    }


    vector<string> tokens;
    tokens = yeah::tokenlize(lines[0], ',');
    yeah::print_tokens_csv(tokens);
    cout << endl;

    int i = 0;
    for (auto line = lines.begin() + 1; line < lines.end(); line++) {
        tokens = yeah::tokenlize(*line, ',');

        int data_id = i;
        tokens[CSVTAG_DATA_ID] = yeah::num2string(data_id);
        //int steps_total = 1000;
        //tokens[CSVTAG_STEPS_TOTAL] = yeah::num2string(steps_total);

        yeah::print_tokens_csv(tokens);
        i++;
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

