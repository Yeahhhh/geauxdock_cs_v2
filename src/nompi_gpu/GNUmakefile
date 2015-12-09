# smic:
# module purge
# module load impi/4.1.3.048/intel64
# module load intel/14.0.2

TARGET_GPU := 0
TARGET_CPU := 1
TARGET_MIC := 2
TARGET_DEVICE := $(TARGET_GPU)
DMARCRO := -DTARGET_GPU=$(TARGET_GPU) -DTARGET_CPU=$(TARGET_CPU) -DTARGET_MIC=$(TARGET_MIC) -DTARGET_DEVICE=$(TARGET_DEVICE) $(MAKEMACRO)





HOST := smic

ifeq ($(HOST), smic)
# module purge
# module load impi/4.1.3.048/intel64
# module load intel/14.0.2
# module load cuda/6.5
	CXX_HOST := icpc
	FC := ifort
	LIBPATH += -L/usr/local/packages/cuda/6.5/lib64
	HEADPATH += -I/usr/local/packages/cuda/6.5/include
	GPU := K20X
        NGPU := 1

else ifeq ($(HOST), shelob)
	CXX_HOST := g++
	FC := gfortran
	GPU := K20X
        NGPU := 2

else ifeq ($(HOST), ece)
	CXX_HOST := g++
	FC := gfortran
	GPU := GTX780
        NGPU := 1

else ifeq ($(HOST), lasphi)
	CXX_HOST := g++
	FC := gfortran
	GPU := GTX980
        NGPU := 1
endif




# 2D thread block size restrictions:
# BDX = 32, 64, 128, ... 1024
# BDY <= BDx
# BDY * BDX > MAXWEI
# BDX * BDY <= 1024   (always true)
# BDX <= warpSize     (always true)


#
# notes:
# __launch_bounds__ is better than -maxrregcount=64
# -maxrregcount=69 may generate 58 registers, this option is not safe
# lower maxrregcount usually get lower number of registers


ifeq ($(GPU), GTX780)
	DEVFLAGS += -gencode arch=compute_35,code=sm_35
	DEVFLAGS += -maxrregcount=69
	DEVFLAGS += -Xptxas -dlcm=ca
	GD := 12
	BD := 1024
	DMARCRO += -DENABLE_CUDA_LDG
else ifeq ($(GPU), K20X)
	DEVFLAGS += -gencode arch=compute_35,code=sm_35
	DEVFLAGS += -Xptxas -dlcm=ca
	GD := 14
	BD := 1024
	DMARCRO += -DENABLE_CUDA_LDG
else ifeq ($(GPU), GTX980)
	DEVFLAGS += -gencode arch=compute_35,code=sm_52
	DEVFLAGS += -maxrregcount=64
	DEVFLAGS += -Xptxas -dlcm=ca
	GD := 32
	BD := 512
	DMARCRO += -DENABLE_CUDA_LDG
else
	GD := 16
	BD := 512
endif



# CUDA warp parameters 
WARP_SZ := 32

# Threads Per Block
WARPperB := $(shell echo $(BD)/$(WARP_SZ) | bc)
# rounding up to nearest power of 2
#BD_POWER2 := $(shell echo "from math import log; a=2**int(log($(BD),2)); print a" | python)


DMARCRO_GPU += -DGD=$(GD)
DMARCRO_GPU += -DBD=$(BD)
DMARCRO_GPU += -DWARPperB=$(WARPperB)
DMARCRO_GPU += -DNGPU=$(NGPU)





EXE := dock
OBJ += dock.o host_prepair.o host_launcher.o
OBJ += load.o data.o rmsd.o util.o util_optimize_soa.o util_print.o

HEADPATH += -I. -I../common -I../server -I../client_gpu
#LIBPATH +=
LINKFLAGS += -lm -lrt -lyeahc


CXX_DEV := nvcc

HOSTFLAGS += -Wall -O3 $(HEADPATH) $(DMARCRO) $(DMARCRO_GPU)

DEVFLAGS += $(HEADPATH) $(DMARCRO) $(DMARCRO_GPU)
DEVFLAGS += -O3
DEVFLAGS += -use_fast_math

# bad for performance
#DEVFLAGS += -lineinfo

#DEVFLAGS += -Xptxas -v
#DEVFLAGS += -keep --keep-dir tmp -G --source-in-pt

LINKFLAGS += -lcudart




default: $(EXE)

buildlib:
	cd module/yeah && make clean
	cd module/yeah && make

$(EXE): $(OBJ)
	$(CXX_HOST) $(LIBPATH) $(OBJ) -o $@ $(LINKFLAGS)

dock.o: dock.C
	$(CXX_HOST) $(HOSTFLAGS) -c $< -o $@

load.o: ../server/load.C
	$(CXX_HOST) $(HOSTFLAGS) -c $< -o $@
data.o: ../server/data.C
	$(CXX_HOST) $(HOSTFLAGS) -c $< -o $@
util.o: ../server/util.C
	$(CXX_HOST) $(HOSTFLAGS) -c $< -o $@
util_print.o: ../common/util_print.C
	$(CXX_HOST) $(HOSTFLAGS) -c $< -o $@
util_optimize_soa.o: ../server/util_optimize_soa.C
	$(CXX_HOST) $(HOSTFLAGS) -c $< -o $@
rmsd.o: ../server/rmsd.f
	$(FC) -O3 -c $< -o $@

host_prepair.o: ../client_gpu/host_prepair.C
	$(CXX_HOST) $(HOSTFLAGS) -c $< -o $@
host_launcher.o: ../client_gpu/host_launcher.cu
	$(CXX_DEV) $(DEVFLAGS) -c $< -o $@



install: $(EXE)
	(cp $(EXE) ../../bin/)

run: $(EXE)
	cd ../../data && ../src/nompi_gpu/$(EXE) -nt $(GD)


echo:
	@(echo GD $(GD))
	@(echo BD $(BD))
	@(echo WARPperB $(WARPperB))
	@(echo NGPU $(NGPU))

clean:
	@(rm -f ${EXE} *.o)
