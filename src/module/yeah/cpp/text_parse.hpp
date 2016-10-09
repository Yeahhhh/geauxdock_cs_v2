#ifndef _YEAH_CPP_TEXT_PARSE_HPP_
#define _YEAH_CPP_TEXT_PARSE_HPP_


#include <iostream>
#include <string>
#include <vector>

namespace yeah {

void trim(std::string &s);
void print_tokens_csv(std::vector<std::string> tokens);
void print_tokens_table1(std::vector<std::string> tokens);
std::vector<std::string> tokenlize(std::string &line, char delim);

}

#endif
