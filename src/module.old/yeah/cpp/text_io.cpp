#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <yeah/cpp/text_io.hpp>


namespace yeah {

void print_vecstr(const std::vector<std::string> &lines)
{
    /*
    const int n = lines.size();  // number of lines
    for (int i = 0; i < n; ++i) {
    std::cout << lines[i] << std::endl;
    }
    */

    for (auto i = lines.begin(); i != lines.end(); i++)
        std::cout << *i << std::endl;
}


void load_fn_to_vecstr(const std::string fnpath,
                       std::vector<std::string> &lines)
{
    std::ifstream ifn(fnpath.c_str());
    if (!ifn.is_open()) {
        std::cout << "Failed to open " << fnpath << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;
    while (getline(ifn, line)) {
        lines.push_back(line);
    }
    ifn.close();
}



void save_vecstr_to_fn(const std::string fnpath,
                       const std::vector<std::string> &lines)
{
    std::ofstream ofn(fnpath.c_str());
    if (!ofn.is_open()) {
        std::cout << "Failed to open " << fnpath << std::endl;
        exit(EXIT_FAILURE);
    }

    for (auto i = lines.begin(); i != lines.end(); i++)
        ofn << *i << std::endl;
    ofn.close();
}

}

