#ifndef _YEAH_CPP_STRING_HPP_
#define _YEAH_CPP_STRING_HPP_


#include <string>
#include <sstream>


namespace yeah {

    template <typename T>
        std::string num2string (T a)
        {
            std::ostringstream oss;
            oss << a;
            return oss.str();
        }


}


#endif
