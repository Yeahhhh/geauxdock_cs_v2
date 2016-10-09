#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include <yeah/cpp/text_io.hpp>

int
main (int argc, char ** argv)
{
    if (argc == 1) {
        printf("%s <INPUTFILE>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    std::string ifn = argv[1];
    std::string ofn = "/tmp/_tmp_out_xcsadfsdaf";

    std::vector<std::string> lines;
    yeah::load_fn_to_vecstr(ifn, lines);
    yeah::save_vecstr_to_fn(ofn, lines);

    lines.clear();
    yeah::load_fn_to_vecstr(ofn, lines);
    yeah::print_vecstr(lines);

    return EXIT_SUCCESS;
}

