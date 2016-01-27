
include ../GNUmakefile.common.mk


EXE := dock
OBJ += dock.o
OBJ += backend_cpu.o
OBJ += util_optimize_soa_cpu.o
OBJ += load.o data.o rmsd.o util.o util_print.o

default: $(EXE)

$(EXE): $(OBJ)
	$(CXX_HOST) $(LIBPATH) $(OBJ) -o $@ $(LINKFLAGS)

dock.o: dock.C
	$(CXX_HOST) $(CXXFLAGS_HOST) -c $< -o $@



NT := 20 # number of temperatures passing to the runtime
include ../GNUmakefile.common.rules

