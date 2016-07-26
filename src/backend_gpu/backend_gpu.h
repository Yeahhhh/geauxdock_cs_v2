#ifndef BACKEND_GPU_H
#define BACKEND_GPU_H


#include <curand_kernel.h>
#include <geauxdock.h>



class Docker {
public:
    Complex *complex; // complex on host
    Record *record; // complex on host

    Complex *cd; // complex on device
    Record *rd; // record on device
    curandState *sd; // curand seed on device


    Docker();
    ~Docker();
    void run();
};



#endif


