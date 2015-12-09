#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstdio>


#include <size.h>
#include <dock.h>
#include <util.h>
#include <util_optimize.h>
#include <util_print.h>
#include <toggle.h>
#include <load.h>

#include "../client_cpu_mic/host_launcher.h"
#include <yeah/c/timing.h>
#include <yeah/cpp/timer.hpp>






int main (int argc, char **argv)
{

#include "../common/server1.C"


  Record *record = (Record *) malloc (sizeof (Record) * MAX_REP);
  for (int i = 0; i < ncomplex; ++i) {
    Complex *job = complex + i;
    printf ("%s start docking\n", argv[0]);
    Dock (job, record);
  }
  free (record);


#include "../common/server2.C"

  return 0;
}


