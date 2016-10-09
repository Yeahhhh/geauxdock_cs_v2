#ifndef _YEAH_CPP_COMPARE_HPP_
#define _YEAH_CPP_COMPARE_HPP_

#include <iostream>
#include <cmath>

namespace yeah {

    template <typename T>
        bool CompareResult (T * result, T * ref, const int n)
        {
            T error_norm = (T) 0.0;
            T ref_norm = (T) 0.0;

            for (int i = 0; i < n; ++i) {
                const float diff = result[i] - ref[i];
                error_norm += diff * diff;
                ref_norm += ref[i] * ref[i];
            }
            error_norm = std::sqrt (error_norm);
            ref_norm = std::sqrt (ref_norm);


            bool return_var = true;
            //  if (std::abs (ref_norm) < 1e-7)
            //    return_var = false;
            if ((error_norm / ref_norm) > 1e-2)
                return_var = false;

            std::cout << "Error Norm:  " << error_norm << "\n";
            std::cout << "Ref Norm:    " << ref_norm << "\n";
            if (return_var == true)
                std::cout << "PASS\n";
            else
                std::cout << "FAIL\n";

            return return_var;
        }

}

#endif

