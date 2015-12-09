TARGET_GPU := 0
TARGET_CPU := 1
TARGET_MIC := 2
TARGET_DEVICE := $(TARGET_GPU)
DMARCRO := -DTARGET_GPU=$(TARGET_GPU) -DTARGET_CPU=$(TARGET_CPU) -DTARGET_MIC=$(TARGET_MIC) -DTARGET_DEVICE=$(TARGET_DEVICE)


EXE := dock_server
OBJ := dock_server.o load.o data.o rmsd.o util.o util_optimize_soa.o util_print.o

HEADPATH += -I. -I../common -I../module
LIBPATH += -L../module/yeah
LINKFLAGS += -lyeahc -lm -lrt


MPICXX := mpiicpc
CXX := mpiicpc
FC := mpiifort

#MPICXX := mpicxx
#CXX := icpc
#FC := ifort

FLAGS += $(DMARCRO) $(HEADPATH)
FLAGS += -Wall -O3




default: $(EXE)

buildlib:
	cd modules/yeah && make clean
	cd modules/yeah && make

$(EXE): $(OBJ)
	$(MPICXX) $(LIBPATH) $(OBJ) -o $@ $(LINKFLAGS)

dock_server.o: dock_server.C
	$(MPICXX) $(FLAGS) -c $< -o $@

%.o: %.C
	$(CXX) $(FLAGS) -c $< -o $@

%.o: %.f
	$(FC) $(HEADPATH) -O3 -c $< -o $@

util_print.o: ../common/util_print.C
	$(CXX) $(FLAGS) -c $< -o $@

install: $(EXE)
	(cp $(EXE) ../../bin/)

run: $(EXE)
	cd ../../data && ../src/server/$(EXE)

clean:
	@(rm -f ${EXE} *.o)


