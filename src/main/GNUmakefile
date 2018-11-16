include ../GNUmakefile.common.mk



EXE += 2_check
#EXE += bench_1_splitdata
ifeq ($(BUILD_CPU), 1)
	EXE += 3_geauxdock_cpu
endif
ifeq ($(BUILD_MIC), 1)
	EXE += 3_geauxdock_mic
endif
ifeq ($(BUILD_GPU), 1)
	EXE += 3_geauxdock_gpu
endif

#EXE := runall

OBJ_FRONTEND += ../frontend/load.o
OBJ_FRONTEND += ../frontend/data.o
OBJ_FRONTEND += ../frontend/rmsd.o
OBJ_FRONTEND += ../frontend/frontend.o
OBJ_FRONTEND += ../common/util_print.o

default: $(EXE)
#default: runall


#CXX_HOST += -g


%.o: %.cpp
	$(CXX_HOST) $(CXXFLAGS_HOST) -c $< -o $@


3_geauxdock_cpu.o: 3_geauxdock.cpp
	$(CXX_HOST) $(CXXFLAGS_HOST) $(MARCRO_TARGET) -DTARGET_DEVICE=$(TARGET_CPU) -c $< -o $@

3_geauxdock_mic.o: 3_geauxdock.cpp
	$(CXX_HOST) $(CXXFLAGS_HOST) $(MARCRO_TARGET) -DTARGET_DEVICE=$(TARGET_MIC) -c $< -o $@

3_geauxdock_gpu.o: 3_geauxdock.cpp
	$(CXX_HOST) $(CXXFLAGS_HOST) $(MARCRO_TARGET) -DTARGET_DEVICE=$(TARGET_GPU) -c $< -o $@

2_check: 2_check.o ../frontend/util_optimize_soa_cpu.o $(OBJ_FRONTEND)
	$(CXX_HOST) $(LIBPATH) $^ -o $@ $(LINKFLAGS)

3_geauxdock_cpu: 3_geauxdock_cpu.o ../backend_cpu_mic/backend_cpu.o ../frontend/util_optimize_soa_cpu.o $(OBJ_FRONTEND)
	$(CXX_HOST) $(LIBPATH) $^ -o $@ $(LINKFLAGS)
	ln -sf $@ 3_geauxdock

3_geauxdock_mic: 3_geauxdock_mic.o ../backend_cpu_mic/backend_mic.o ../frontend/util_optimize_soa_mic.o $(OBJ_FRONTEND)
	$(CXX_HOST) $(LIBPATH) $^ -o $@ $(LINKFLAGS)
	ln -sf $@ 3_geauxdock

3_geauxdock_gpu: 3_geauxdock_gpu.o ../backend_gpu/backend_gpu.o ../frontend/util_optimize_soa_gpu.o $(OBJ_FRONTEND)
	$(CXX_HOST) $(LIBPATH) $^ -o $@ $(LINKFLAGS) -lcudart
	ln -sf $@ 3_geauxdock




bench_4_splitdata: bench_4_splitdata.o
	$(CXX_HOST) $(LIBPATH) $^ -o $@ $(LINKFLAGS)



run1: 1_mklist.py.sh
	./1_mklist.py.sh

run2: 2_check
	./2_check.sh

run3: 3_geauxdock_cpu
	./3_geauxdock_cpu a3.csv

runall:
	./1_mklist.py.sh
	./2_check.sh
	./3_geauxdock_gpu



include ../GNUmakefile.common.rules


