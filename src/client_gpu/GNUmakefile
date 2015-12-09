TARGET_GPU := 0
TARGET_CPU := 1
TARGET_MIC := 2
TARGET_DEVICE := $(TARGET_GPU)
DMARCRO := -DTARGET_GPU=$(TARGET_GPU) -DTARGET_CPU=$(TARGET_CPU) -DTARGET_MIC=$(TARGET_MIC) -DTARGET_DEVICE=$(TARGET_DEVICE)



HOST := smic

ifeq ($(HOST), smic)
# module purge
# module load impi/4.1.3.048/intel64
# module load intel/14.0.2
# module load cuda/6.5
#	LIBPATH += -L/usr/local/packages/cuda/6.5/lib64
	HEADPATH += -I/usr/local/packages/cuda/6.5/include
	GPU := K20X
        NGPU := 1

else ifeq ($(HOST), shelob)
#	LIBPATH += -L/usr/local/packages/cuda/5.5.22/lib64
	GPU := K20X
        NGPU := 1

else ifeq ($(HOST), ece)
#	LIBPATH := -L/usr/local/cuda-6.5/lib64
	GPU := GTX780
        NGPU := 1

else ifeq ($(HOST), lasphi)
#	LIBPATH := -L/usr/local/cuda-7.0/lib64
	GPU := GTX980
        NGPU := 1
endif




# thread number restrictions:
# BDy <= BDx
# BDx % warpSize == 0
# BDY * BDx > MAXWEI
# BDy <= warpSize           (always true)
# BDY * BDx <= 1024   (always true)

ifeq ($(GPU), GTX780)
	DEVFLAGS := -gencode arch=compute_35,code=sm_35 -maxrregcount=54 -Xptxas -dlcm=ca
#	DEVFLAGS := -Xptxas -dlcm=ca
	GD := 24
	BD := 1024
else ifeq ($(GPU), K20X)
	DEVFLAGS := -gencode arch=compute_35,code=sm_35 -maxrregcount=58 -Xptxas -dlcm=ca
#	DEVFLAGS := -Xptxas -dlcm=ca # __launch_bounds__ is better
	GD := 28
	BD := 1024
else ifeq ($(GPU), GTX980)
	DEVFLAGS := -gencode arch=compute_35,code=sm_52 -maxrregcount=61 -Xptxas -dlcm=ca
	GD := 32
	BD := 512
else
	GD := 16
	BD := 512
endif


# CUDA warp parameters 
WARP_SZ := 32

WARPperB := $(shell echo $(BD)/$(WARP_SZ) | bc)
# rounding up to nearest power of 2
#BD_POWER2 := $(shell echo "from math import log; a=2**int(log($(BD),2)); print a" | python)

DMARCRO_GPU += -DGD=$(GD)
DMARCRO_GPU += -DBD=$(BD)
DMARCRO_GPU += -DWARPperB=$(WARPperB)
DMARCRO_GPU += -DNGPU=$(NGPU)







EXE := dock_client_gpu
OBJ_HOST := dock_client.o host_prepair.o util_print.o
OBJ_DEV := host_launcher.o

HEADPATH += -I. -I../common
#LIBPATH +=
LINKFLAGS += -lyeahc -lm -lrt


MPICXX := mpiicpc
HOSTFLAGS += -Wall -O3
HOSTFLAGS += $(HEADPATH)
HOSTFLAGS += $(DMARCRO) $(DMARCRO_GPU)

CXX_DEV := nvcc
DEVFLAGS += -O3
DEVFLAGS += -use_fast_math
DEVFLAGS += $(HEADPATH)
DEVFLAGS += $(DMARCRO) $(DMARCRO_GPU)
#DEVFLAGS += -Xptxas -v
#DEVFLAGS += -keep --keep-dir tmp -G --source-in-pt

LINKFLAGS += -lcudart


#HOSTFLAGS += -g
#DEVFLAGS += -g -G





default: $(EXE)

buildlib:
	cd modules/yeah && make clean
	cd modules/yeah && make

$(EXE): $(OBJ_HOST) $(OBJ_DEV)
	$(MPICXX) $(LIBPATH) $(OBJ_HOST) $(OBJ_DEV) -o $@ $(LINKFLAGS)

%.o: %.C
	$(MPICXX) $(HOSTFLAGS) -c $< -o $@

host_launcher.o: host_launcher.cu
	$(CXX_DEV) $(DEVFLAGS) -c $< -o $@

util_print.o: ../common/util_print.C
	$(MPICXX) $(HOSTFLAGS) -c $< -o $@


install: $(EXE)
	(cp $(EXE) ../../bin/)

run: $(EXE)
#	cd ../../bin && ../src/client_gpu/$(EXE)
	cd ../../bin; mpirun -np 1 ./dock_server : -np 1 ./dock_client_gpu

echo:
	@(echo BD $(BD))
	@(echo GD $(GD))
	@(echo WARPperB $(WARPperB))
	@(echo NGPU $(NGPU))


clean:
	@(rm -f ${EXE} *.o)


