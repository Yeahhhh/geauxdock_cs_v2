#include <stdio.h>

#include <yeah/opencl/cl.h>
#include <yeah/opencl/util.h>


int
main()
{
  cl_device_id d;
  d = opencl_choose_device(CL_DEVICE_TYPE_CPU);
  //d = opencl_choose_device(CL_DEVICE_TYPE_GPU);
  //d = opencl_choose_device(CL_DEVICE_TYPE_ACCELERATOR);
  printf("Choose device %i\n", d);

  return 0;
}
