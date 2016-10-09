
#ifndef _YEAH_MEASURING_SAMPLING_NVML_HPP_
#define _YEAH_MEASURING_SAMPLING_NVML_HPP_

#include <cstdio>
#include <cstdlib>

#include <nvidia/nvml.h>
#include <cuda_runtime_api.h>

#include <yeah/cuda/runtime/wrapper.h>
#include <yeah/cuda/nvml/wrapper.h>
#include <yeah/cuda/nvml/info.h>
#include <yeah/measuring/sampling/base.hpp>




namespace yeah {
namespace measuring {
namespace sampling {

class NvmlPower0 : public yeah::measuring::sampling::Base0<float> {
   protected:
    virtual void Sampling()
    {
        while (running == true) {
            unsigned int p;
            NVML_ERR(nvmlDeviceGetPowerUsage(nvml_device_prop.device, &p));
            const float power_watt = (float)p * 1e-3;
            event0.push_back(power_watt);
            SleepS(sampling_interval);
        }
    }

   public:
    int nd_cuda;
    unsigned int nd_nvml;
    int id_cuda;
    int id_nvml;
    nvmlDeviceProp nvml_device_prop;

    void Init(double sampling_frequency_, int id_cuda_)
    {
        sampling_frequency = sampling_frequency_;
        sampling_interval = 1 / sampling_frequency;
        id_cuda = id_cuda_;

        CUDA_ERR(cudaGetDeviceCount(&nd_cuda));
        if (nd_cuda < 1) {
            printf("no CUDA Device\n");
            exit(EXIT_FAILURE);
        }
        NVML_ERR(nvmlInit());
        NVML_ERR(nvmlDeviceGetCount(&nd_nvml));
        if (nd_nvml < 1) {
            NVML_ERR(nvmlShutdown());
            printf("no NVML Device\n");
            exit(EXIT_FAILURE);
        }
        //printf("number of devices: CUDA:%d NVMLDevice:%d\n", nd_cuda, nd_nvml);

        GetNvmlDeviceHandleByCudaID(&nvml_device_prop, id_cuda, &id_nvml,
                                    nd_nvml);
    }

    void Finalize()
    {
        NVML_ERR(nvmlShutdown());
    }
};


class NvmlPower : public NvmlPower0 {
   public:
    NvmlPower(double sampling_frequency_ = 99, int id_cuda = 0)
    {
        Clear();
        Init(sampling_frequency_, id_cuda);
    }

    ~NvmlPower()
    {
        Finalize();
    }
};

class NvmlPowerAuto : public NvmlPower0 {
   public:
    NvmlPowerAuto(double sampling_frequency_ = 99, int id_cuda = 0)
    {
        Clear();
        Init(sampling_frequency_, id_cuda);
        Start();
    }

    ~NvmlPowerAuto()
    {
        Stop();
        Calc();
        Print();
        Finalize();
    }
};




}
}
}

#endif
