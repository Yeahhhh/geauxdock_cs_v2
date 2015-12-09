#!/bin/sh -x
mpirun -np 1 ../src/server/dock_server : -np 1 ../src/client_cpu_mic/dock_client_cpu
