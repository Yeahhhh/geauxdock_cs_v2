include ../GNUmakefile.common.mk


EXE += server
EXE += client_dummy
ifeq ($(BUILD_CPU), 1)
	EXE += client_cpu
endif
ifeq ($(BUILD_MIC), 1)
	EXE += client_mic
endif
ifeq ($(BUILD_GPU), 1)
	EXE += client_gpu
endif



OBJ_FRONTEND += ../frontend/load.o
OBJ_FRONTEND += ../frontend/data.o
OBJ_FRONTEND += ../frontend/rmsd.o
OBJ_FRONTEND += ../frontend/frontend.o
OBJ_FRONTEND += ../common/util_print.o



default: $(EXE)


%.o: %.cpp
	$(CXX_MPI) $(CXXFLAGS_HOST) -c $< -o $@

client_cpu.o: client.cpp
	$(CXX_MPI) $(CXXFLAGS_HOST) $(MARCRO_TARGET) -DTARGET_DEVICE=$(TARGET_CPU) -c $< -o $@

client_mic.o: client.cpp
	$(CXX_MPI) $(CXXFLAGS_HOST) $(MARCRO_TARGET) -DTARGET_DEVICE=$(TARGET_MIC) -c $< -o $@

client_gpu.o: client.cpp
	$(CXX_MPI) $(CXXFLAGS_HOST) $(MARCRO_TARGET) -DTARGET_DEVICE=$(TARGET_GPU) -c $< -o $@





server: server.o $(OBJ)
	$(CXX_MPI) $(LIBPATH) $^ -o $@ $(LINKFLAGS)

client_dummy: client_dummy.o
	$(CXX_MPI) $(LIBPATH) $^ -o $@ $(LINKFLAGS)

client_cpu: client_cpu.o ../backend_cpu_mic/backend_cpu.o ../frontend/util_optimize_soa_cpu.o $(OBJ_FRONTEND)
	$(CXX_MPI) $(LIBPATH) $^ -o $@ $(LINKFLAGS)

client_mic: client_mic.o ../backend_cpu_mic/backend_mic.o ../frontend/util_optimize_soa_mic.o $(OBJ_FRONTEND)
	$(CXX_MPI) $(LIBPATH) $^ -o $@ $(LINKFLAGS)

client_gpu: client_gpu.o ../backend_gpu/backend_gpu.o ../frontend/util_optimize_soa_gpu.o $(OBJ_FRONTEND)
	$(CXX_MPI) $(LIBPATH) $^ -o $@ $(LINKFLAGS) -lcudart




include ../GNUmakefile.common.rules
