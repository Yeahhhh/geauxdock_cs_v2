// http://icl.cs.utk.edu/papi/docs/d7/d04/linux-micpower_8c.html


#ifndef _YEAH_MEASURING_SAMPLING_PAPI_MICPOWER_HPP_
#define _YEAH_MEASURING_SAMPLING_PAPI_MICPOWER_HPP_


#include <cstdio>
#include <cstdlib>

#include <yeah/measuring/sampling/base.hpp>


namespace yeah {
namespace measuring {
namespace sampling {

class PapiMicpower0 : public yeah::measuring::sampling::Base0<float> {
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


class PapiMicpower : public PapiMicpower0 {
   public:
    PapiMicpower(double sampling_frequency_ = 9)
    {
        this->Clear();
        this->Init(sampling_frequency_);
    }

    ~PapiMicpower()
    {
        //this->Calc();
        //this->Print();
        this->Finalize();
    }
};

class PapiMicpowerAuto : public PapiMicpower0 {
   public:
    PapiMicpowerAuto(double sampling_frequency_ = 9)
    {
        this->Clear();
        this->Init(sampling_frequency_);
        this->Start();
    }

    ~PapiMicpowerAuto()
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
