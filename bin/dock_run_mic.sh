#!/bin/sh -x

export CPU_HOST=`hostname`
export SERVER_BIN=/home/yfang11/work/geauxdock_cs/src/server/dock_server
export CPU_BIN=/home/yfang11/work/geauxdock_cs/src/client_cpu_mic/dock_client_cpu
export MIC_BIN=/home/yfang11/work/geauxdock_cs/src/client_cpu_mic/dock_client_mic

export THREADS_HOST=4   # number of OpenMP threads spawned by each task on the host
export THREADS_MIC=240  # number of OpenMP threads spawned by each task on the MIC
export CPU_ENV="-env OMP_NUM_THREADS $THREADS_HOST"  # run-time environments for CPU binary
export MIC_ENV="-env OMP_NUM_THREADS $THREADS_MIC -env LD_LIBRARY_PATH $MIC_LD_LIBRARY_PATH"  # run-time environments for MIC binary

mpiexec.hydra \
-n 1 $SERVER_BIN : \
-n 1 -host mic0 $MIC_ENV ${MIC_BIN}


#-n 1 $CPU_ENV ${CPU_BIN} : \
#-n 1 mic0 $MIC_ENV ${MIC_BIN} : \
