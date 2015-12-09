#ifndef HOST_LAUNCHER_H
#define HOST_LAUNCHER_H

void InitCurand (curandState **s);

void Dock (Complex *ch,
           Record *rh,
           Complex **cd,
           Record **rd,
           ParaT **pt,
           curandState **curandstate_d);


#endif


