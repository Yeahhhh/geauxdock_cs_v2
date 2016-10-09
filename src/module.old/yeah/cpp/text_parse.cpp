#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <yeah/cpp/text_parse.hpp>

namespace yeah {

void trim(std::string &s)
{
    size_t p;
    p = s.find_first_not_of(" \t");
    s.erase(0, p);

    p = s.find_last_not_of(" \t");
    if (std::string::npos != p)
        s.erase(p + 1);
}


void print_tokens_csv(std::vector<std::string> tokens)
{
    if (tokens.size() > 1) {
        for (int i = 0; i < tokens.size() - 1; ++i)
            std::cout << tokens[i] << ",";
        std::cout << tokens[tokens.size() - 1] << std::endl;;
    }
}


void print_tokens_table1(std::vector<std::string> tokens)
{
    for (int i = 0; i < tokens.size(); ++i)
        std::cout << i << "\t" << tokens[i] << std::endl;
}



// usage:
// std::vector<std::string> tokens = tokenlize(lines, ',');
// std::vector<std::string> tokens = tokenlize(lines, ' ');
std::vector<std::string> tokenlize(std::string &line, char delim)
{
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string t;

    // std::cout << line << std::endl;

    while (getline(ss, t, delim)) {
        yeah::trim(t);
        tokens.push_back(t);
    }

    return tokens;
}




#if 0
std::istringstream iss(line);
std::vector<std::string> tokens;
while (iss) {
    std::string t;
    iss >> t;
    tokens.push_back(t);
}



#define NTOKEN 15
    const int n = tokens.size();
    if (n != NTOKEN) {
        std::cout << "number of tokens is wrong" << std::endl;
        exit(EXIT_FAILURE);
    }
#endif


}
