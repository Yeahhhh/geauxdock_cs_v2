#ifndef _YEAH_MEASURING_SAMPLING_SHELL_MICSMC_HPP_
#define _YEAH_MEASURING_SAMPLING_SHELL_MICSMC_HPP_


#include <cstdio>
#include <cstdlib>

#include <yeah/measuring/sampling/base.hpp>


namespace yeah {
namespace measuring {
namespace sampling {

class ShellMicsmcPower0 : public yeah::measuring::sampling::Base0<float> {
   protected:

#define MAX_CHAR_PER_LINE_abc 1024

    float run_shell()
    {
        FILE *pipe;
        char line[MAX_CHAR_PER_LINE_abc];

        //char shell_cmd[] = "echo 3.33";
        //char shell_cmd[] = "uptime | awk '{print $13}'"; // load average in the last 15 minutes


        // measuring the power of Xeon Phi using MPSS micsmc command
        // It is not workth the effort to using MPSS libmicmgmt
        // because
        // (1) micsmc is using MPSS libmicmgmt
        // (2) libmicmgmt cannot be used to measure idle power, and is not very useful
        // PAPI micpower libaray might be a better choice

        char shell_cmd[] = "micsmc --freq | grep 'Total Power' | awk '{print $4}'";

        pipe = popen(shell_cmd, "r");
        if (pipe == NULL) {
            printf("Failed to run command\n" );
            exit(EXIT_FAILURE);
        }
        fgets(line, sizeof(line), pipe); // firt line of the shell output
        //printf("%s", line);
        pclose(pipe);

        float rv = atof(line);
        return rv;
    }

    virtual void Sampling()
    {
        while (running == true) {
            event0.push_back(run_shell());
            SleepS(sampling_interval);
        }
    }

   public:
};


class ShellMicsmcPower : public ShellMicsmcPower0 {
   public:
    ShellMicsmcPower(double sampling_frequency_ = 9)
    {
        this->Clear();
        this->Init(sampling_frequency_);
    }

    ~ShellMicsmcPower()
    {
        //this->Calc();
        //this->Print();
        this->Finalize();
    }
};

class ShellMicsmcPowerAuto : public ShellMicsmcPower0 {
   public:
    ShellMicsmcPowerAuto(double sampling_frequency_ = 9)
    {
        this->Clear();
        this->Init(sampling_frequency_);
        this->Start();
    }

    ~ShellMicsmcPowerAuto()
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
