
TARGET_GPU := 0
TARGET_CPU := 1
TARGET_MIC := 2

MARCRO_TARGET += -DTARGET_GPU=$(TARGET_GPU) -DTARGET_CPU=$(TARGET_CPU) -DTARGET_MIC=$(TARGET_MIC)
#MARCRO_TARGET += -DTARGET_DEVICE=$(TARGET_CPU)
#MARCRO_TARGET += -DTARGET_DEVICE=$(TARGET_MIC)
#MARCRO_TARGET += -DTARGET_DEVICE=$(TARGET_GPU)





#HOST := smic
HOST := gnuhost

ifeq ($(HOST), intelhost)
	COMPILER_HOST := intel
	BUILD_CPU := 1
	BUILD_MIC := 1
	BUILD_GPU := 0

else ifeq ($(HOST), gnuhost)
	COMPILER_HOST := gnu
	BUILD_CPU := 1
	BUILD_MIC := 0
	BUILD_GPU := 0

else ifeq ($(HOST), gpuhost)
	COMPILER_HOST := gnu
#	GPU := CC35
	GPU := CC50
#	GPU := CC52
#	GPU := CC61
	BUILD_CPU := 0
	BUILD_MIC := 0
	BUILD_GPU := 1

else ifeq ($(HOST), smic)
	COMPILER_HOST := intel
	#COMPILER_HOST := gnu
	GPU := CC35
	BUILD_CPU := 1
	BUILD_MIC := 1
	BUILD_GPU := 1

else ifeq ($(HOST), yourhost)
	COMPILER_HOST := gnu
	GPU := CC52
	BUILD_CPU := 0
	BUILD_MIC := 0
	BUILD_GPU := 1
endif





# CUDA execution configurations
# speficied at compiling time to optimize code generation
# BperMP: active blocks per multiprocessor (of the Monte Carlo Kernel)
# TperB:  threads per block

# 2D thread block size restrictions:
# TperBX = 32, 64, 128, ... 1024
# TperBY <= TperBx
# TperBY * TperBX > MAXWEI
# TperBX * TperBY <= 1024   (always true)
# TperBX <= warpSize     (always true)


## Kepler Generation GPUs
ifeq ($(GPU), CC35)
	CXXFLAGS_DEV += -gencode arch=compute_35,code=sm_35

# the fastest config, requires "SMEM/block < 24KB"
	BperMP := 2
	TperB := 512

# if "SMEM/block > 24KB", use this config. (used in GeauxDock paper)
#	BperMP := 1
#	TperB := 1024

#	BperMP := 4
#	TperB := 256

## Maxwell Generation GPUs
else ifeq ($(GPU), CC50)
	CXXFLAGS_DEV += -gencode arch=compute_35,code=sm_50
	BperMP := 2
	TperB := 512

## Maxwell Generation GPUs
else ifeq ($(GPU), CC52)
	CXXFLAGS_DEV += -gencode arch=compute_35,code=sm_52
	BperMP := 4
	TperB := 256

# buggy but faster, need to debug
#	BperMP := 4
#	TperB := 288

## Pascal Generation GPUs
else ifeq ($(GPU), CC61)
	CXXFLAGS_DEV += -gencode arch=compute_35,code=sm_61
	BperMP := 4
	TperB := 256

else
	CXXFLAGS_DEV += -arch=compute_35
	BperMP := 2
	TperB := 512
endif


# CUDA warp parameters
#WARP_SZ := 32
# Threads Per Block
#WARPperB := $(shell echo $(TperB)/$(WARP_SZ) | bc)
# rounding up to nearest power of 2
#TperB_POWER2 := $(shell echo "from math import log; a=2**int(log($(TperB),2)); print a" | python)


MARCRO_GPU += -DBperMP=$(BperMP)
MARCRO_GPU += -DTperB=$(TperB)
MARCRO_GPU += -DENABLE_CUDA_LDG







ifeq ($(COMPILER_HOST), intel)
	CXX_MPI := mpiicpc
	CXX_HOST := icpc
	FC_HOST := ifort
	CXX_DEV := nvcc
else ifeq ($(COMPILER_HOST), gnu)
	CXX_MPI := mpicxx
	CXX_HOST := g++
	FC_HOST := gfortran
	CXX_DEV := nvcc
else ifeq ($(COMPILER_HOST), customized1)
	CXX_MPI := mpicxx
	CXX_HOST := g++
	FC_HOST := gfortran
	CXX_DEV := nvcc
endif





INTEL_REPORT_FLAGS += -vec-report
INTEL_REPORT_FLAGS += -par-report
INTEL_REPORT_FLAGS += -opt-report=3
INTEL_REPORT_FLAGS += -opt-report-phase=all
INTEL_REPORT_FLAGS += -opt-report-file=tmp/optrpt.txt




HEADPATH += -I. -I../common -I../frontend -I../backend_gpu -I../backend_cpu_mic -I../analysis -I../main_dataprepare

#LIBPATH += -Wl,-rpath=/usr/local/compilers/Intel/cluster_studio_xe_2013.1.046/composer_xe_2013_sp1.2.144/compiler/lib/mic

LINKFLAGS += -lm -lrt -lyeahc -lyeahcxx
#LINKFLAGS += -lpapi
#LINKFLAGS += -static
ifeq ($(COMPILER_HOST), intel)
	LINKFLAGS += -openmp
#	LINKFLAGS += $(INTEL_REPORT_FLAGS)
else
	LINKFLAGS += -fopenmp
endif





FCFLAGS_HOST += -O3



CXXFLAGS_HOST += $(HEADPATH) $(MARCRO_MAKE)
CXXFLAGS_HOST += -g							# should remove after debug

ifeq ($(COMPILER_HOST), intel)
	CXXFLAGS_HOST += -Wall
	CXXFLAGS_HOST += -O3
#	CXXFLAGS_HOST += -fast
#	CXXFLAGS_HOST += -fma
	CXXFLAGS_HOST += -ip -ipo
#	CXXFLAGS_HOST += -xAVX
#	CXXFLAGS_HOST += -xSSE4.2
#	CXXFLAGS_HOST += -no-vec -DNOVEC
#	CXXFLAGS_HOST += -vec-guard-write
#	CXXFLAGS_HOST += -no-simd # ignore SIMD pragmas, slow down 2%
#	CXXFLAGS_HOST += -vec-threshold0   # should consistantly turn this off thoughout the benchmarks
#	CXXFLAGS_HOST += -fp-model source
	CXXFLAGS_HOST += -fno-fnalias -ansi-alias -fargument-noalias
#	CXXFLAGS_HOST += -mavx
	CXXFLAGS_HOST += -openmp
	CXXFLAGS_HOST += -std=c++11
else ifeq ($(COMPILER_HOST), gnu)
	CXXFLAGS_HOST += -O3
	CXXFLAGS_HOST += -fopenmp
	CXXFLAGS_HOST += --std=c++11
	CXXFLAGS_HOST += -fomit-frame-pointer
#	CXXFLAGS_HOST += -floop-block
#	CXXFLAGS_HOST += -floop-interchange
#	CXXFLAGS_HOST += -floop-nest-optimize
#	CXXFLAGS_HOST += -floop-strip-mine
#	CXXFLAGS_HOST += -funroll-loops
#	CXXFLAGS_HOST += -funswitch-loops
# mute warnings
	#CXXFLAGS_HOST += -Wall
	CXXFLAGS_HOST += -Wno-unused-variable
	CXXFLAGS_HOST += -Wno-unknown-pragmas
else
	CXXFLAGS_HOST += -O3
	CXXFLAGS_HOST += -fopenmp
	CXXFLAGS_HOST += --std=c++11
endif



CXXFLAGS_DEV += $(HEADPATH) $(MARCRO_MAKE) $(MARCRO_GPU)
CXXFLAGS_DEV += -O3
CXXFLAGS_DEV += -use_fast_math
CXXFLAGS_DEV += -Xptxas -dlcm=ca
#CXXFLAGS_DEV += -D_FORCE_INLINES		# fixing CUDA 7.5 + GCC 5 compatibility issue

# for development purpose, making performance worse
#CXXFLAGS_DEV += -lineinfo
#CXXFLAGS_DEV += -Xptxas -v
#CXXFLAGS_DEV += -keep --keep-dir tmp -G --source-in-pt



