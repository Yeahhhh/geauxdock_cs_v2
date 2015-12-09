#ifndef HOST_PREPAIR_H
#define HOST_PREPAIR_H

void SetDevice ();
void DeviceAlloc (Complex ** c, Record **r, curandState **s);
void DeviceFree (Complex ** c, Record **r, curandState **s);
void SetParaT (Complex * ch, ParaT ** pt);
void CopyH2D (Complex * ch, Complex ** cd, ParaT ** pt);

#endif


