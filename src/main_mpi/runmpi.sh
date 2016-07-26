#!/bin/sh -x
mpirun \
-np 1 ./server : \
-np 10 ./client
#-np 1 ../src/main_mpi/client_mic
#-np 1 ../src/main_mpi/client_cpu
#-np 1 ../src/main_mpi/client_dummy : \


