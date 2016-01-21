include ../GNUmakefile.mk


EXE = server client_dummy client_cpu client_mic client_gpu
OBJ += load.o data.o rmsd.o util.o util_optimize_soa.o util_print.o


default: $(EXE)


server: server.o $(OBJ)
	$(CXX_MPI) $(LIBPATH) $^ -o $@ $(LINKFLAGS)

client_dummy: client_dummy.o
	$(CXX_MPI) $(LIBPATH) $^ -o $@ $(LINKFLAGS)



# to do: need to build for CPU/MIC with different flags


client_cpu: client_cpu_mic.o backend_cpu_mic.o util_print.o
	$(CXX_MPI) $(LIBPATH) $^ -o $@ $(LINKFLAGS)

client_mic: client_cpu_mic.o backend_cpu_mic.o util_print.o
	$(CXX_MPI) $(LIBPATH) $^ -o $@ $(LINKFLAGS)




client_gpu: client_gpu.o prepair.o backend_gpu.o util_print.o
	$(CXX_MPI) $(LIBPATH) $^ -o $@ $(LINKFLAGS) -lcudart


%.o: %.C
	$(CXX_MPI) $(CXXFLAGS_HOST) $(DMARCRO_GPU) -c $< -o $@




include ../GNUmakefile.common_rules

