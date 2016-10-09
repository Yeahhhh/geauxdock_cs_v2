
#include <cstdio>
#include <cstdlib>

#include <nvidia/nvml.h>
#include <cuda_runtime_api.h>

#include <yeah/cuda/nvml/info.h>
#include <yeah/cuda/nvml/wrapper.h>
#include <yeah/cuda/runtime/wrapper.h>

int main()
{
    int nd_cuda;
    unsigned int nd_nvml;
    unsigned int nd_nvml_unit;
    cudaDeviceProp cuda_device_prop;
    nvmlDeviceProp nvml_device_prop;

    CUDA_ERR(cudaGetDeviceCount(&nd_cuda));
    NVML_ERR(nvmlInit());
    NVML_ERR(nvmlDeviceGetCount(&nd_nvml));
    NVML_ERR(nvmlUnitGetCount(&nd_nvml_unit));

    printf("number of devices: CUDA:%d NVMLDevice:%d NVMLUnit:%d\n", nd_cuda,
           nd_nvml, nd_nvml_unit);

    for (int id_cuda = 0; id_cuda < nd_cuda; ++id_cuda) {
        CUDA_ERR(cudaGetDeviceProperties(&cuda_device_prop, id_cuda));

        int id_nvml;
        GetNvmlDeviceHandleByCudaID(&nvml_device_prop, id_cuda, &id_nvml, nd_nvml);

        // Requires root/admin permissions
        // NVML_ERR (nvmlDeviceSetPowerManagementLimit (nvml_device_prop.device,
        // 180000));
        GetPrintNvmlDeviceProp(&nvml_device_prop, id_nvml, id_cuda);
    }

    NVML_ERR(nvmlShutdown());
    return EXIT_SUCCESS;
}
