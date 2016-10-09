#ifndef _YEAH_CUDA_RUNTIME_INFO_H_
#define _YEAH_CUDA_RUNTIME_INFO_H_

#include <cuda_runtime.h>
#include <yeah/cuda/runtime/wrapper.h>

// /cuda/7.5/include/cuda_occupancy.h

struct cudaExeConfig {
    int blockDim;
    int gridDim;

    int gridDim_x;
    int gridDim_y;
    int gridDim_z;
    int blockDim_x;
    int blockDim_y;
    int blockDim_z;
};



// reference:
// nvidia/cuda7example/helper_cuda.h _ConvertSMVer2Cores_2
//
// https://developer.nvidia.com/cuda-gpus          NVIDIA GPU CUDA Compute Capabilities
// http://nouveau.freedesktop.org/wiki/CodeNames/
// https://en.wikipedia.org/wiki/CUDA
// cuda c programming guide                        5.4.1 Arithmetic Instructions, Appendix G Compute Capabilities

int FpUnitsPerMp(const cudaDeviceProp *const prop, const int flag)
{
    const int major = prop->major;
    const int minor = prop->minor;
    const int cc = (major << 4) + minor; // compute capability
    //const int is_geforce = strncmp("GeForce", prop->name, 7) == 0;

    int fp32units_per_mp = -1;
    int fp64units_per_mp = -1;
    int rv = -1; // return value

    typedef struct {
        int cc;  // 0xMm (hexidecimal notation), M Major, m minor
        int fp16;
        int fp32;
        int fp64;
    } sSMtoCores;


    // -2 means unknown
    sSMtoCores nGpuArchCoresPerSM[] = {
    //     cc, fp16, fp32, fp64
        {0x20,    0,   32,  16},  // Fermi Generation (CC 2.0) GF100 class
        {0x21,    0,   48,   4},  // Fermi Generation (CC 2.1) GF10x class
        {0x30,    0,  192,   8},  // Kepler Generation (CC 3.0) GK10x class, GeForce
        {0x32,    0,  192,   8},  // Kepler Generation (CC 3.2) GK10x class, GeForce
        {0x35,    0,  192,  64},  // Kepler Generation (CC 3.5) GK11x class, not GeForce
        {0x37,    0,  192,  64},  // Kepler Generation (CC 3.7) GK21x class, not GeForce
        {0x50,    0,  128,   4},  // Maxwell Generation (CC 5.0) GM10x class
        {0x52,    0,  128,   4},  // Maxwell Generation (CC 5.2) GM20x class
        {0x53,  256,  128,   4},  // Maxwell Generation (CC 5.3)
        {0x60,  128,   64,  32},  // Pascal Generation (CC 6.0) GP100,       Tesla
        {0x61,   -2,  128,  -2},  // Pascal Generation (CC 6.1) GP10x class, GeForce
        {-1,     -1,   -1,  -1}
    };

    int i = 0;
    while (nGpuArchCoresPerSM[i].cc != -1) {
        if (nGpuArchCoresPerSM[i].cc == cc) {
            fp32units_per_mp = nGpuArchCoresPerSM[i].fp32;
            fp64units_per_mp = nGpuArchCoresPerSM[i].fp64;
            break;
        }
        i++;
    }

    // an alternative implementation
    /*
       const int fp32units_per_mp =
       major == 1 ? 8 :
       major == 2 ? (minor == 0 ? 32 : 48) :
       major == 3 ? 192 :
       major == 5 ? 128 :
       major == 6 ? 64 :
       0; // default
     */

    /*
    const int fp64units_per_mp =
        major == 1 ? 1 : major == 2 ? (minor == 0 ? 16 : 4)
                       : major == 3 ? (minor < 3 || is_geforce ? 8 : 64)
                       : major == 5 ? 4 :  // all geforce
                         major == 6 ? 32 : 0;  // default
     */

    if (fp32units_per_mp == -1)
        printf("Fp32UnitsPerMp for CC %d.%d is undefined.\n", major, minor);
    if (fp64units_per_mp == -1)
        printf("Fp64UnitsPerMp for CC %d.%d is undefined.\n", major, minor);


    if (flag == 32)
        rv = fp32units_per_mp;
    else if (flag == 64)
        rv = fp64units_per_mp;
    else
        printf("flag %d is undefined.\n", flag);

    return rv;
}







// /opt/cuda/7.5/include/cuda_runtime_api.h
// http://docs.nvidia.com/cuda/cuda-c-programming-guide/#compute-capabilities
void PrintCudaDeviceProp(const cudaDeviceProp *const prop, const int d)
{
    if (prop->major == 9999 && prop->minor == 9999) {
        printf("device %d is invalid\n", d);
    }

    const char *NOorYES[] = {"NO", "YES"};  // 0-NO, 1-YES

    const int fp32units_per_mp = FpUnitsPerMp(prop, 32);
    const int fp64units_per_mp = FpUnitsPerMp(prop, 64);
    const float memory_tpers = 2 * prop->memoryClockRate; // transfers per second
    const float chip_bw_Bps = memory_tpers * 1e3 * (prop->memoryBusWidth >> 3);
    const float chip_fp32_flops = 1e3 * fp32units_per_mp * prop->clockRate * prop->multiProcessorCount;
    const float chip_fp64_flops = 1e3 * fp64units_per_mp * prop->clockRate * prop->multiProcessorCount;

    printf("GPU %d: %s (CC %d.%d)\n", d, prop->name, prop->major, prop->minor);
    // printf ("GPU %d:\n", d);
    // printf ("%s (CC %d.%d)\n", prop->name, prop->major, prop->minor);
    printf("---------------------------------------\n");
    printf("hardware restrictions\n");

    // core
    putchar('\n');
    printf("core clock rate \t\t%.2f GHz\n", (float)prop->clockRate * 1e-6);
    printf("MP/GPU \t\t\t\t%d\n", prop->multiProcessorCount);
    printf("FP32/MP \t\t\t%d\n", fp32units_per_mp);
    printf("FP64/MP \t\t\t%d\n", fp64units_per_mp);
    printf("FP32/GPU \t\t\t%d\n", fp32units_per_mp * prop->multiProcessorCount);
    printf("FP64/GPU \t\t\t%d\n", fp64units_per_mp * prop->multiProcessorCount);
    printf("RAW FP32 FLOPS/GPU \t\t%.2f TFLOPS/s\n", chip_fp32_flops * 1e-12);
    printf("RAW FP64 FLOPS/GPU \t\t%.2f TFLOPS/s\n", chip_fp64_flops * 1e-12);

    // memory
    putchar('\n');
    printf("memory transfer rate \t\t%.2f GT/s\n", memory_tpers * 1e-6);
    printf("memory bus width \t\t%d b\n", prop->memoryBusWidth);
    printf("memory bandwidth \t\t%.2f GiB/s\n", chip_bw_Bps / (float)(1 << 30));
    printf("num reg32/block \t\t%.2f Ki\n", (float)prop->regsPerBlock / (float)(1 << 10));
    printf("num reg32/MP \t\t\t%.2f Ki\n", (float)prop->regsPerMultiprocessor / (float)(1 << 10));
    printf("size scratchpad/block \t\t%.2f KiB\n", (float)prop->sharedMemPerBlock / (float)(1 << 10));
    printf("size scratchpad/MP \t\t%.2f KiB\n", (float)prop->sharedMemPerMultiprocessor / (float)(1 << 10));
    printf("size constant/GPU \t\t%.2f KiB\n", (float)prop->totalConstMem / (float)(1 << 10));
    printf("size L2 cache/GPU \t\t%.2f MiB\n", (float)prop->l2CacheSize / (float)(1 << 20));
    printf("size global/GPU \t\t%.2f GiB\n", (float)prop->totalGlobalMem / (float)(1 << 30));

    // ratio
    printf("\n");
    printf("FP32 FLOPS/memory BW ratio \t%.2f\n", 4 * chip_fp32_flops / chip_bw_Bps);
    printf("FP64 FLOPS/memory BW ratio \t%.2f\n", 8 * chip_fp64_flops / chip_bw_Bps);
    printf("num reg32/num FP32 unit ratio \t%.2f\n", (float)prop->regsPerMultiprocessor / fp32units_per_mp);
    printf("num reg64/num FP64 unit ratio \t%.2f\n", (float)prop->regsPerMultiprocessor / 2 / fp64units_per_mp);

    // feature
    putchar('\n');
    printf("unifiedAddressing \t\t%s\n", NOorYES[prop->unifiedAddressing]);
    printf("canMapHostMemory \t\t%s\n", NOorYES[prop->canMapHostMemory]);  // support cudaHostAlloc(), cudaHostGetDevicePointer()
    printf("concurrentKernels \t\t%s\n", NOorYES[prop->concurrentKernels]);  // simultaneously executing multiple kernels
    printf("deviceOverlap \t\t\t%s\n", NOorYES[prop->deviceOverlap]);  // overlaping kernel and memcpy
    printf("asyncEngineCount \t\t%d\n", prop->asyncEngineCount);  // overlaping kernel and memcpy // (single/bi-direction)
    printf("kernelExecTimeoutEnabled \t%s\n", NOorYES[prop->kernelExecTimeoutEnabled]);
    printf("streamPrioritiesSupported \t%s\n", NOorYES[prop->streamPrioritiesSupported]);
    printf("globalL1CacheSupported \t\t%s\n", NOorYES[prop->globalL1CacheSupported]);
    printf("localL1CacheSupported \t\t%s\n", NOorYES[prop->localL1CacheSupported]);
    printf("ECCEnabled \t\t\t%s\n", NOorYES[prop->ECCEnabled]);
    printf("computeMode \t\t\t%s\n", NOorYES[prop->computeMode]);
    printf("tccDriver \t\t\t%s\n", NOorYES[prop->tccDriver]); // if using Tesla driver
    //printf("managedMemSupported \t\t%s\n", NOorYES[prop->managedMemSupported]);



    // hardware
    putchar('\n');
    printf("integrated \t\t\t%s\n", NOorYES[prop->integrated]);
    printf("isMultiGpuBoard \t\t%s\n", NOorYES[prop->isMultiGpuBoard]);
    printf("pciBusID \t\t\t%d\n", prop->pciBusID);
    printf("pciDeviceID \t\t\t%d\n", prop->pciDeviceID);
    printf("pciDomainID \t\t\t%d\n", prop->pciDomainID);
    printf("multiGpuBoardGroupID \t\t%d\n", prop->multiGpuBoardGroupID);


    // restrictions by model
    putchar('\n');
    printf("warpSize \t\t\t%d\n", prop->warpSize);
    printf("maxThreadsPerBlock \t\t%d\n", prop->maxThreadsPerBlock);
    printf("maxThreadsPerMultiProcessor \t%d\n", prop->maxThreadsPerMultiProcessor);
    printf("memPitch \t\t\t%d\n", prop->memPitch);
    printf("maxThreadsDim \t\t\t%d %d %d\n", prop->maxThreadsDim[0], prop->maxThreadsDim[1], prop->maxThreadsDim[2]);
    printf("maxGridSize \t\t\t%d %d %d\n", prop->maxGridSize[0], prop->maxGridSize[1], prop->maxGridSize[2]);
    printf("textureAlignment \t\t%d\n", prop->textureAlignment);
    printf("texturePitchAlignment \t\t%d\n", prop->texturePitchAlignment);
    printf("surfaceAlignment \t\t%d\n", prop->surfaceAlignment);


    // how many shared memory banks ???
}

void GetPrintCudaDeviceProp(const int d)
{
    cudaDeviceProp prop;
    CUDA_ERR(cudaGetDeviceProperties(&prop, d));
    PrintCudaDeviceProp(&prop, d);
}

void GetPrintCurrentCudaDeviceProp()
{
    int d;
    cudaDeviceProp prop;
    CUDA_ERR(cudaGetDevice(&d));
    GetPrintCudaDeviceProp(d);
}

void PrintCudaFuncArributes(const cudaFuncAttributes *fa, const char *s)
{
    printf("static cuda kernel information for \"%s\"\n", s);
    printf("ptxVersion: \t\t\t%d\n", fa->ptxVersion);
    printf("binaryVersion: \t\t\t%d\n", fa->binaryVersion);
    printf("reg usage/T: \t\t\t%d\n", fa->numRegs);
    printf("lmem usage/T: \t\t\t%.2f KiB\n", (float)fa->localSizeBytes / (float)(1 << 10));
    printf("smem usage/TB: \t\t\t%.2f KiB\n", (float)fa->sharedSizeBytes / (float)(1 << 10));
    printf("cmem usage/grid: \t\t%.2f KiB\n", (float)fa->constSizeBytes / (float)(1 << 10));
    printf("max T per TB: \t\t\t%d\n", fa->maxThreadsPerBlock);
    putchar('\n');
}

// eg:
// GetPrintCudaFuncArributes ((void (*)) MyKernel, "MyKernel");

void GetPrintCudaFuncArributes(void(*func), const char *s)
{
    cudaFuncAttributes fa;
    CUDA_ERR(cudaFuncGetAttributes(&fa, func));
    PrintCudaFuncArributes(&fa, s);
}

// eg:
// GetPrint_potencial_occupancy ((void (*)) MyKernel, "MyKernel", 32, 512, 0);

void GetPrint_potencial_occupancy(void(*func), const char *s, const int bperg,
                                  const int tperb, const int dynamic_smem_sz)
{
    int d;
    cudaDeviceProp prop;
    CUDA_ERR(cudaGetDevice(&d));
    CUDA_ERR(cudaGetDeviceProperties(&prop, d));

    // report the potential maxium occupancy, given a execution configuration
    int threads_per_block = tperb;
    int active_blocks_per_mp;
    CUDA_ERR(cudaOccupancyMaxActiveBlocksPerMultiprocessor(
        &active_blocks_per_mp, func, threads_per_block, dynamic_smem_sz));
    printf("warp occupancy for exec config <<<..., %d>>:\n", threads_per_block);
    printf("active_blocks_per_mp: \t\t%d\n", active_blocks_per_mp);

    int active_warps_per_mp =
        threads_per_block * active_blocks_per_mp / prop.warpSize;
    int max_warps_per_mp = prop.maxThreadsPerMultiProcessor / prop.warpSize;
    float warp_occupancy = (float)active_warps_per_mp / (float)max_warps_per_mp;
    printf("warp_occupancy: \t\t%d/%d, %.3f\n", active_warps_per_mp,
           max_warps_per_mp, warp_occupancy);
    printf("\n");
}

// g++ found the fucntion prototype of
// "cudaOccupancyMaxActiveBlocksPerMultiprocessor"
// g++ can't find the fucntion prototype of "cudaOccupancyMaxPotentialBlockSize"
#if defined(__CUDACC__)  // compiled by NVCC

// eg:
// GetPrint_execconfig_max_occupancy ((void (*)) MyKernel, "MyKernel", 0);

// suggest a execution configuration that maximize the warps occupancy
void GetPrint_execconfig_max_occupancy(void(*func), const char *s,
                                       const int dynamic_smem_sz)
{
    int minimal_blocks_per_grid, threads_per_block;
    const int blocks_per_grid_upper_bound = 0;
    CUDA_ERR(cudaOccupancyMaxPotentialBlockSize(
        &minimal_blocks_per_grid, &threads_per_block, func, dynamic_smem_sz,
        blocks_per_grid_upper_bound));
    printf("suggested exec config:\t\t<<<%d(+), %d>>>\n",
           minimal_blocks_per_grid, threads_per_block);
    printf("\n");

    GetPrint_potencial_occupancy(func, s, minimal_blocks_per_grid,
                                 threads_per_block, 0);
}

void GetPrintCudaFuncArributes2(void(*func), const char *s, const int bperg,
                                const int tperb, const int dynamic_smem_sz)
{
    GetPrint_execconfig_max_occupancy(func, s, 0);
    // GetPrint_potencial_occupancy (func, s, 32, 512, 0);
    // GetPrint_potencial_occupancy (func, s, 32, 768, 0);
    // GetPrint_potencial_occupancy (func, s, 64, 512, 0);
    GetPrint_potencial_occupancy(func, s, bperg, tperb, dynamic_smem_sz);

    // GetPrintCurrentCudaDeviceProp ();
}

#endif

#endif
