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
    std::ifstream fn(fnpath.c_str());
    if (!fn.is_open()) {
        std::cout << "Failed to open " << fnpath << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;
    while (getline(fn, line)) {
        lines.push_back(line);
    }
    fn.close();
}



void save_vecstr_to_fn(const std::string fnpath,
                       const std::vector<std::string> &lines)
{
    std::fstream fn(fnpath.c_str(), std::fstream::out);
    if (!fn.is_open()) {
        std::cout << "Failed to open " << fnpath << std::endl;
        exit(EXIT_FAILURE);
    }

    for (auto i = lines.begin(); i != lines.end(); i++)
        fn << *i << std::endl;
    fn.close();
}



void save_vecstr_to_fn_append(const std::string fnpath,
                       const std::vector<std::string> &lines)
{
    std::fstream fn(fnpath.c_str(), std::fstream::out | std::fstream::app);
    if (!fn.is_open()) {
        std::cout << "Failed to open " << fnpath << std::endl;
        exit(EXIT_FAILURE);
    }

    for (auto i = lines.begin(); i != lines.end(); i++)
        fn << *i << std::endl;
    fn.close();
}


}
