#!/bin/sh -x
mpirun \
-machine hostfile \
-np 1 ./server : \
-np 10 ./client_cpu


