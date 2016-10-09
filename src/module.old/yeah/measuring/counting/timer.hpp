#ifndef _YEAH_MEASURING_COUNTING_TIMER_HPP_
#define _YEAH_MEASURING_COUNTING_TIMER_HPP_

#include <yeah/c/timing.h>
#include <iostream>

// try switch to std::time

namespace yeah {
namespace measuring {
namespace counting {

class Timer {
   public:
    double t1;  // start time
    double t2;  // stop time
    double ts;  // span, elapsed time
    int n;      // counter


    Timer()
    {
        t1 = t2 = ts = 0;
        n = 0;
    }
    void Start()
    {
        t1 = HostTimeNow();
    }
    void Stop()
    {
        t2 = HostTimeNow();
        ts += t2 - t1;
        n++;
    }
    void Reset()
    {
        t1 = t2 = ts = 0;
        n = 0;
    }
    double Span()
    {
        return ts;
    }
    int Count()
    {
        return n;
    }
    void Print()
    {
        std::cout << "span (s): " << ts << "\tcounter: " << n << std::endl;
    }
};

// usage:
// yeah::measuring::counting::TimerAuto t ("func ()");

class TimerAuto : public Timer {
   protected:
    std::string name;

   public:
    TimerAuto(const std::string& name1)
    {
        name = name1;
        Start();
    }

    ~TimerAuto()
    {
        Stop();
        std::cout << "TimerAuto: " << name << ": " << Span() << " s"
                  << std::endl;
    }
};
}
}
}

#endif
