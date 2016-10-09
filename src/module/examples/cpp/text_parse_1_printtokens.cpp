#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#include <yeah/cpp/text_io.hpp>
#include <yeah/cpp/text_parse.hpp>


#define DELIM ','
//#define DELIM ' '


void func2(std::vector<std::string> lines)
{
    const int n = lines.size();  // number of lines
    for (int i = 0; i < n; ++i) {
        std::vector<std::string> tokens = yeah::tokenlize(lines[i], DELIM);
        yeah::print_tokens_csv(tokens);
        yeah::print_tokens_table1(tokens);
    }
}



int main(int argc, char **argv)
{
    if (argc == 1) {
        printf("%s <INPUTFILE>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    std::vector<std::string> lines;
    yeah::load_fn_to_vecstr(argv[1], lines);
    func2(lines);

    return EXIT_SUCCESS;
}
