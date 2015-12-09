TARGET_GPU := 0
TARGET_CPU := 1
TARGET_MIC := 2
TARGET_DEVICE := $(TARGET_CPU)
DMARCRO := -DTARGET_GPU=$(TARGET_GPU) -DTARGET_CPU=$(TARGET_CPU) -DTARGET_MIC=$(TARGET_MIC) -DTARGET_DEVICE=$(TARGET_DEVICE) $(MAKEMACRO)


ifeq ($(TARGET_DEVICE), $(TARGET_CPU))
	EXE := dock_cpu
#	EXE := dock_mic_native
	MPICXX := icpc #-mmic
	CXX := icpc #-mmic
	FC := ifort #-mmic

#	MPICXX := tau_cxx.sh
#	CXX := tau_cxx.sh
#	FC := tau_f90.sh
#
#	MPICXX := g++
#	CXX := g++
#	FC := gfortran
else ifeq ($(TARGET_DEVICE), $(TARGET_MIC))
	EXE := dock_mic_offload
	MPICXX := icpc
	CXX := icpc
	FC := ifort
endif



OBJ += dock.o
OBJ += load.o
OBJ += data.o
OBJ += rmsd.o
OBJ += util.o
OBJ += util_optimize_soa.o
OBJ += util_print.o
OBJ += host_launcher.o

HEADPATH += -I. -I../common -I../server
LIBPATH += #-Wl,-rpath=/usr/local/compilers/Intel/cluster_studio_xe_2013.1.046/composer_xe_2013_sp1.2.144/compiler/lib/mic
LINKFLAGS += -lyeahc -lm -lrt


FLAGS += $(DMARCRO) $(HEADPATH)
FLAGS += -Wall
FLAGS += -openmp
#FLAGS += -vec-guard-write
#FLAGS += -no-vec # disable SIMD code generation
#FLAGS += -no-simd # ignore SIMD pragmas
FLAGS += -O3
#FLAGS += -fast
#FLAGS += -vec-threshold0   # should consistantly turn this off thoughout the benchmarks
FLAGS += -fno-fnalias -ansi-alias -fargument-noalias
#FLAGS += -mavx



LINKFLAGS += -openmp
#LINKFLAGS += -lpapi




default: $(EXE)

buildlib:
	cd modules/yeah && make clean
	cd modules/yeah && make

$(EXE): $(OBJ)
	$(MPICXX) $(LIBPATH) $(OBJ) -o $@ $(LINKFLAGS)

dock.o: dock.C
	$(MPICXX) $(FLAGS) -c $< -o $@

load.o: ../server/load.C
	$(CXX) $(FLAGS) -c $< -o $@
data.o: ../server/data.C
	$(CXX) $(FLAGS) -c $< -o $@
util.o: ../server/util.C
	$(CXX) $(FLAGS) -c $< -o $@
util_print.o: ../common/util_print.C
	$(CXX) $(FLAGS) -c $< -o $@
util_optimize_soa.o: ../server/util_optimize_soa.C
	$(CXX) $(FLAGS) -c $< -o $@
host_launcher.o: ../client_cpu_mic/host_launcher.C
	$(CXX) $(FLAGS) -c $< -o $@
rmsd.o: ../server/rmsd.f
	$(FC) $(HEADPATH) -O3 -c $< -o $@


install: $(EXE)
	(cp $(EXE) ../../bin/)

run: $(EXE)
	cd ../../data && ../src/nompi_cpu_mic/$(EXE) -nt 11

clean:
	@(rm -f ${EXE} *.o)
