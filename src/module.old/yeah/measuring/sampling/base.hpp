#ifndef _YEAH_MEASURING_SAMPLING_BASE_HPP_
#define _YEAH_MEASURINGE_SAMPLING_BASE_HPP_


#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>

#include <yeah/c/sleep.h>

namespace yeah {
namespace measuring {
namespace sampling {

template <typename T0>
class Base0 {
   protected:
    std::thread thread;
    bool running;
    double sampling_frequency; // number of samples in a seconds
    double sampling_interval; // time between samples (in seconds)

    std::vector<T0> event0;
    T0 event0_integral;

    virtual void Sampling()
    {
        while (running == true) {
            printf("insert your measuring code here\n" );
            T0 a = (T0)2;
            event0.push_back(a);
            SleepS(sampling_interval);
        }
    }

    void Integrate()
    {
        T0 s = (T0)0;
        for (int i = 0; i < event0.size(); i++) {
            s += event0[i];
        }
        event0_integral = s * sampling_interval;
    }

   public:
    void Clear()
    {
        event0.clear();
        event0_integral = (T0)0;
    }

    void Init(double sampling_frequency_)
    {
        sampling_frequency = sampling_frequency_;
        sampling_interval = 1 / sampling_frequency;
    }

    void Start()
    {
        running = true;
        thread = std::thread([this] { Sampling(); });
    }

    void Stop()
    {
        running = false;
        thread.join();
    }

    void Calc()
    {
        Integrate();
    }

    void Print()
    {
        printf("samples: ");
        for (int i = 0; i < event0.size(); i++)
            std::cout << event0[i] << " ";
        printf("\n");
        printf("samples_integral: ");
        std::cout << event0_integral << std::endl;
    }

    std::vector<T0> GetSamples()
    {
        return event0;
    }

    T0 GetIntegral()
    {
        return event0_integral;
    }

    void Finalize()
    {
    }
};


template <typename T0>
class Base : public Base0<T0> {
   public:
    Base(double sampling_frequency_ = 99)
    {
        this->Clear();
        this->Init(sampling_frequency_);
    }

    ~Base()
    {
        //this->Calc();
        //this->Print();
        this->Finalize();
    }
};

template <typename T0>
class BaseAuto : public Base0<T0> {
   public:
    BaseAuto(double sampling_frequency_ = 99)
    {
        this->Clear();
        this->Init(sampling_frequency_);
        this->Start();
    }

    ~BaseAuto()
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
