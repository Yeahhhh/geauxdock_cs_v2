#include <cstdlib>
#include <iostream>
#include <string>

#include <yeah/cpp/string.hpp>


int
main (int argc, char ** argv)
{
    int a = 2;
    float b = 2.2;
    std::string s = "ss";

    s = yeah::num2string(a);
    std::cout << s << std::endl;

    s = yeah::num2string(b);
    std::cout << s << std::endl;

    return EXIT_SUCCESS;
}
