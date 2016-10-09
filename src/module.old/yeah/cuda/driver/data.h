
#ifndef _YEAH_CUDA_DRIVER_DATA_H_
#define _YEAH_CUDA_DRIVER_DATA_H_

#include <assert.h>
#include <cuda.h>
#include <yeah/cuda/driver/wrapper.h>

namespace yeah {

namespace cu {

template <typename T0>
class Data0 {
   public:
    T0 *dh;          // host
    CUdeviceptr dd;  // device
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
        CU_ERR(cuMemcpyHtoD(dd, dh, sz));
    }
    void D2Hsync()
    {
        CU_ERR(cuMemcpyDtoH(dh, dd, sz));
    }
    // async copy
    void H2Dasync(CUstream s = 0)
    {
        CU_ERR(cuMemcpyHtoDAsync(dd, dh, sz, s));
    }
    void D2Hasync(CUstream s = 0)
    {
        CU_ERR(cuMemcpyDtoHAsync(dh, dd, sz, s));
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
        CU_ERR(cuMemAlloc(&this->dd, this->sz));
    }
    void Free()
    {
        CU_ERR(cuMemFree(this->dd));
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
}
}

#endif
