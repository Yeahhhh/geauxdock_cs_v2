#ifndef _YEAH_CUDA_RUNTIME_DATA_H_
#define _YEAH_CUDA_RUNTIME_DATA_H_

// page locked memory
// pined memory
//
// Linux: mlock, munlock

// 2 API calls: what are the differences?
// cudaHostAlloc (pointer, size, flag)
// cudaHostAllocPortable: The memory returned by this call will be considered as
// pinned memory by all CUDA contexts, not just the one that performed the
// allocation
// cudaMallocHost

// zero copy, hostmapped memory

#include <assert.h>
#include <cuda_runtime.h>
#include <yeah/cuda/runtime/wrapper.h>

namespace yeah {

namespace cuda {

template <typename T0>
class Data0 {
   public:
    T0 *dh;  // host
    T0 *dd;  // device
    T0 *du;  // unified
    size_t sz;
    int n;

    // Data0 (int num = 1) { this->Init (num); }
    //~Data0 () {}
    void Init(int num)
    {
        n = num;
        sz = sizeof(T0) * num;
    }

    // sync copy
    void H2Dsync()
    {
        CUDA_ERR(cudaMemcpy(dd, dh, sz, cudaMemcpyHostToDevice));
    }
    void D2Hsync()
    {
        CUDA_ERR(cudaMemcpy(dh, dd, sz, cudaMemcpyDeviceToHost));
    }
    // async copy
    void H2Dasync(cudaStream_t s = 0)
    {
        CUDA_ERR(cudaMemcpyAsync(dd, dh, sz, cudaMemcpyHostToDevice, s));
    }
    void D2Hasync(cudaStream_t s = 0)
    {
        CUDA_ERR(cudaMemcpyAsync(dh, dd, sz, cudaMemcpyDeviceToHost, s));
    }
};

/*
template <typename T0>
    class Data: public Data0 <T0>
{
public:
    Data (int num = 1) { this->Init (num); }
    ~Data () {}
};
*/

template <typename T0>
class DataDummy : public Data0<T0> {
   public:
    DataDummy(int num = 1)
    {
        this->Init(num);
    }
    ~DataDummy()
    {
    }
};

template <typename T0>
class DataNonPinned : public Data0<T0> {
   protected:
    void Alloc()
    {
        this->dh = (T0 *)malloc(this->sz);
        assert(this->dh != NULL);
        CUDA_ERR(cudaMalloc((void **)&this->dd, this->sz));
    }
    void Free()
    {
        CUDA_ERR(cudaFree(this->dd));
        free(this->dh);
    }

   public:
    DataNonPinned(int num = 1)
    {
        this->Init(num);
        this->Alloc();
    }
    ~DataNonPinned()
    {
        this->Free();
    }
};

template <typename T0>
class DataPinned : public Data0<T0> {
   protected:
    void Alloc()
    {
        CUDA_ERR(cudaMallocHost((void **)&this->dh, this->sz));
        assert(this->dh != NULL);
        CUDA_ERR(cudaMalloc((void **)&this->dd, this->sz));
    }
    void Free()
    {
        CUDA_ERR(cudaFree(this->dd));
        CUDA_ERR(cudaFreeHost(this->dh));
    }

   public:
    DataPinned(int num = 1)
    {
        this->Init(num);
        this->Alloc();
    }
    ~DataPinned()
    {
        this->Free();
    }
};

template <typename T0>
class DataHostMapped : public Data0<T0> {
   public:
};


// requirements
// > CUDA 6
// > Kepler
//
// need to call cudaDeviceSynchronize() after GPU kernel
template <typename T0>
class DataManaged : public Data0<T0> {
   protected:
    void Alloc()
    {
        CUDA_ERR(cudaMallocManaged((void **)&this->du, this->sz));
    }
    void Free()
    {
        CUDA_ERR(cudaFree(this->du));
    }

   public:
    DataManaged(int num = 1)
    {
        this->Init(num);
        this->Alloc();
    }
    ~DataManaged()
    {
        this->Free();
    }
};
}
}

#endif
