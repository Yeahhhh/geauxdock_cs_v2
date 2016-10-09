#include <yeah/c/timing.h>
#include <iostream>
#include <yeah/measuring/counting/timer.hpp>

#define N 100

void compute()
{
    double a = 0.234;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                a += 0.0001234;
            }
        }
    }
    std::cout << a << std::endl;
}

void func1()
{
    yeah::measuring::counting::TimerAuto t_auto("func1()");
    compute();
}

void func2()
{
    yeah::measuring::counting::Timer t0;
    t0.Start();
    compute();
    t0.Stop();
    t0.Print();

}

int main()
{
    func1();
    func2();
    std::cout << HostTimeNow() << std::endl;

    return 0;
}
