
#include <cstdio>
#include <cuda_runtime_api.h>
#include <yeah/cuda/runtime/info.h>
#include <yeah/cuda/runtime/wrapper.h>


void
GenerateCudaExeConfig (const cudaDeviceProp * const prop, cudaExeConfig * exe_config)
{
    const int blocks_per_mp =
        prop->major == 3 ? 1 :
        prop->major == 5 ? 2 :
        2; // default

    exe_config->gridDim = prop->multiProcessorCount * blocks_per_mp;

    exe_config->blockDim =
        prop->major == 3 ? 1024 :
        prop->major == 5 ? 512 :
        512; // default
}




void
PrintCudaExeConfig (const cudaExeConfig * const exe_config)
{
    printf ("<<< %d, %d >>>> \n",
            exe_config->gridDim, exe_config->blockDim);
}




int
main (int argc, char **argv)
{
  int nd;
  CUDA_ERR (cudaGetDeviceCount (&nd));

  printf ("CUDA devices: %d\n\n", nd);
  for (int d = 0; d < nd; ++d) {
    cudaDeviceProp prop;
    cudaExeConfig exe_config;
    CUDA_ERR(cudaGetDeviceProperties (&prop, d));

    GenerateCudaExeConfig (&prop, &exe_config);
    PrintCudaExeConfig (&exe_config);
  }

  CUDA_ERR (cudaDeviceReset());
  return 0;
}



