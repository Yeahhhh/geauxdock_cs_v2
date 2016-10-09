
#ifndef _YEAH_MEASURING_SAMPLING_PAPI_RAPL_HPP_
#define _YEAH_MEASURING_SAMPLING_PAPI_RAPL_HPP_


#include <cstdio>
#include <cstdlib>

#include <yeah/measuring/sampling/base.hpp>


namespace yeah {
namespace measuring {
namespace sampling {

class PapiRapl0 : public yeah::measuring::sampling::Base0<float> {
   protected:

    virtual void Sampling()
    {
        while (running == true) {
            printf("to be done\n" );
            event0.push_back(3.4f);
            SleepS(sampling_interval);
        }
    }

   public:
};


class PapiRapl : public PapiRapl0 {
   public:
    PapiRapl(double sampling_frequency_ = 9)
    {
        this->Clear();
        this->Init(sampling_frequency_);
    }

    ~PapiRapl()
    {
        //this->Calc();
        //this->Print();
        this->Finalize();
    }
};

class PapiRaplAuto : public PapiRapl0 {
   public:
    PapiRaplAuto(double sampling_frequency_ = 9)
    {
        this->Clear();
        this->Init(sampling_frequency_);
        this->Start();
    }

    ~PapiRaplAuto()
    {
        this->Stop();
        this->Calc();
        this->Print();
        this->Finalize();
    }
};

}
}
}


#endif
