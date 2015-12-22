
TARGET_GPU := 0
TARGET_CPU := 1
TARGET_MIC := 2
TARGET_DEVICE := $(TARGET_CPU)
DMARCRO := -DTARGET_GPU=$(TARGET_GPU) -DTARGET_CPU=$(TARGET_CPU) -DTARGET_MIC=$(TARGET_MIC) -DTARGET_DEVICE=$(TARGET_DEVICE)


ifeq ($(TARGET_DEVICE), $(TARGET_CPU))
	EXE := dock_client_cpu
#	EXE := dock_client_mic_native
	MPICXX := mpiicpc #-mmic
	CXX_DEV := icpc #-mmic
else ifeq ($(TARGET_DEVICE), $(TARGET_MIC))
	EXE := dock_client_mic_offload
	MPICXX := mpiicpc
	CXX_DEV := icpc
endif



OBJ_HOST := dock_client.o
OBJ_DEV := host_launcher.o util_print.o

HEADPATH += -I. -I../common -I../client_cpu_mic
#LIBPATH += -Lx
LINKFLAGS += -lyeahc -lm -lrt


HOSTFLAGS += $(DMARCRO) $(HEADPATH)
HOSTFLAGS += -Wall -O3

DEVFLAGS += $(DMARCRO) $(HEADPATH)
DEVFLAGS += -Wall
DEVFLAGS += -O3
# DEVFLAGS += -ip -ipo -fma
# DEVFLAGS += -xAVX
DEVFLAGS += -fno-fnalias -ansi-alias -fargument-noalias
DEVFLAGS += -openmp
DEVFLAGS += -vec-threshold0
# DEVFLAGS += -no-vec

LINKFLAGS += -openmp
#LINKFLAGS += -opt-report=3
# LINKFLAGS += -opt-report-phase=vec
#LINKFLAGS += -opt-report-file=tmp/optrpt.txt





default: $(EXE)

buildlib:
	cd modules/yeah && make clean
	cd modules/yeah && make

$(EXE): $(OBJ_HOST) $(OBJ_DEV)
	$(MPICXX) $(LIBPATH) $(OBJ_HOST) $(OBJ_DEV) -o $@ $(LINKFLAGS)

dock_client.o: dock_client.C
	$(MPICXX) $(HOSTFLAGS) -c $< -o $@

util_print.o: ../common/util_print.C
	$(MPICXX) $(HOSTFLAGS) -c $< -o $@

host_launcher.o: host_launcher.C
	$(CXX_DEV) $(DEVFLAGS) -c $< -o $@


install: $(EXE)
	(cp $(EXE) ../../bin/)

run: $(EXE)
	cd ../../bin && ../src/client/$(EXE)

clean:
	@(rm -f ${EXE} *.o)


