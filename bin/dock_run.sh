#!/bin/sh -x
#mpirun -np 1 ../src/main_mpi/server : -np 1 ../src/main_mpi/client_dummy
mpirun -np 1 ../src/main_mpi/server : -np 1 ../src/main_mpi/client_gpu
#mpirun -np 1 ../src/main_mpi/server : -np 1 ../src/main_mpi/client_cpu

