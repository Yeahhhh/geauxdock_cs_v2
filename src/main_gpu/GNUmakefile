include ../GNUmakefile.mk



DMARCRO += -DTARGET_DEVICE=$(TARGET_GPU)


EXE := dock
OBJ += dock.o
OBJ += prepair.o backend_gpu.o
OBJ += load.o data.o rmsd.o util.o util_optimize_soa.o util_print.o


default: $(EXE)


$(EXE): $(OBJ)
	$(CXX_HOST) $(LIBPATH) $(OBJ) -o $@ $(LINKFLAGS) -lcudart

dock.o: ./dock.C
	$(CXX_HOST) $(CXXFLAGS_HOST) $(DMARCRO_GPU) -c $< -o $@

run: $(EXE)
	(cd ../../data && ../src/main_gpu/$(EXE) -nt $(GD))



include ../GNUmakefile.common_rules


