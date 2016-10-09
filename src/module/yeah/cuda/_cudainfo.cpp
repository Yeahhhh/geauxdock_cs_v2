
#include <cstdio>
#include <cuda_runtime_api.h>
#include <yeah/cuda/runtime/info.h>
#include <yeah/cuda/runtime/wrapper.h>

int
main (int argc, char **argv)
{
  int nd;
  CUDA_ERR (cudaGetDeviceCount (&nd));

  printf ("CUDA devices: %d\n\n", nd);
  for (int d = 0; d < nd; ++d) {
    GetPrintCudaDeviceProp (d);
  }

  CUDA_ERR (cudaDeviceReset());
  return 0;
}

