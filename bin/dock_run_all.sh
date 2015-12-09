#!/bin/sh -x

mpirun \
-np 1 ../src/server/dock_server : \
-np 1 ../src/client_cpu_mic/dock_client_mic_offload : \
-np 1 ../src/client_cpu_mic/dock_client_cpu : \
-np 1 ../src/client_gpu/dock_client_gpu

