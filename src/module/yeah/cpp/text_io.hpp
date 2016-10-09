#ifndef _YEAH_CPP_TEXT_IO_HPP_
#define _YEAH_CPP_TEXT_IO_HPP_


#include <fstream>
#include <iostream>
#include <string>
#include <vector>


namespace yeah {

void print_vecstr(const std::vector<std::string> &lines);
void load_fn_to_vecstr(const std::string fnpath, std::vector<std::string> &lines);
void save_vecstr_to_fn(const std::string fnpath, const std::vector<std::string> &lines);
void save_vecstr_to_fn_append(const std::string fnpath, const std::vector<std::string> &lines);

}


#endif
