#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <cstdlib>
#include <cstdio>

using namespace std;

#include <yeah/cpp/text_io.hpp>
#include <yeah/cpp/text_parse.hpp>


void func2(std::vector<std::string> lines)
{
    const int n = lines.size (); // number of lines
    int mcs_nrow = 0;

    for (int i = 0; i < n; ++i) {
        std::string line = lines[i];

        // cout << line.length () << endl;
        // if (line.substr (0, 3) == "KDE") ...


        std::vector<std::string> tokens = yeah::tokenlize(line, ' ');

        if (tokens.size() <= 1)
            continue;

        if (tokens[0] == "KDE") {
            printf("KDE ");
            float x = atof(tokens[2].c_str());
            float y = atof(tokens[3].c_str());
            float z = atof(tokens[4].c_str());
            printf("%f %f %f\n", x, y, z);
        }
        if (tokens[0] == "PSP") {
            printf("PSP ");
            cout << tokens[1] << " ";
            cout << tokens[2] << " ";
            cout << tokens[3] << " ";
            cout << endl;
        }
        if (tokens[0] == "MCS") {
            // float tcc = atof (tokens[2].c_str ());
            mcs_nrow++;
            int mcs_ncol = atoi(tokens[3].c_str());

#if 0
            cout << line << endl;
            for (int i = 0; i < mcs_ncol; ++i) {
                const int offset = 4;
                int loc = atoi (tokens[4 * i + 0 + offset].c_str ());
                float x = atof (tokens[4 * i + 1 + offset].c_str ());
                float y = atof (tokens[4 * i + 2 + offset].c_str ());
                float z = atof (tokens[4 * i + 3 + offset].c_str ());
                printf ("%3d:    %2d    %f %f %f\n", i, loc, x, y, z);
            }
#endif

#if 1
            printf("MCS row %3d has %3d valid points:   ", mcs_nrow, mcs_ncol);
            for (int i = 0; i < mcs_ncol; ++i) {
                const int offset = 4;
                int loc = atoi(tokens[4 * i + 0 + offset].c_str());
                printf("%2d ", loc);
            }
            printf("\n");
#endif
        }
    }
}


int main(int argc, char **argv)
{
    if (argc == 1) {
        printf("%s <LHMFILE(*.ff)>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    std::vector<std::string> lines;
    yeah::load_fn_to_vecstr(argv[1], lines);
    func2(lines);

    return 0;
}



