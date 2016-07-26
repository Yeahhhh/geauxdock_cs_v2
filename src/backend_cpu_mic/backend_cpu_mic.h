#ifndef BACKEND_CPU_MIC_H
#define BACKEND_CPU_MIC_H

#include <geauxdock.h>



class Docker {
public:
    Complex *complex;
    Record *record;

    Docker();
    ~Docker();
    void run();
};



#endif


