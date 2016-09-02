include ../GNUmakefile.common.mk

SRC = $(wildcard *.cpp)
#OBJ = $(SRC:.cpp=.o)
EXE = $(SRC:.cpp=)

#EXE += unittest1
#EXE += unittest2
#EXE += unittest3

OBJ_FRONTEND += ../frontend/load.o
OBJ_FRONTEND += ../frontend/data.o
OBJ_FRONTEND += ../frontend/rmsd.o
OBJ_FRONTEND += ../frontend/frontend.o
OBJ_FRONTEND += ../common/util_print.o

default: $(EXE)
#default: runx


#CXX_HOST += -g


%.o: %.cpp
	$(CXX_HOST) $(CXXFLAGS_HOST) -c $< -o $@

test0_loadprotein: test0_loadprotein.o ../frontend/util_optimize_soa_gpu.o $(OBJ_FRONTEND)
	$(CXX_HOST) $(LIBPATH) $^ -o $@ $(LINKFLAGS)

test1_loadlhm: test1_loadlhm.o ../frontend/util_optimize_soa_gpu.o $(OBJ_FRONTEND)
	$(CXX_HOST) $(LIBPATH) $^ -o $@ $(LINKFLAGS)

test2_loadligand: test2_loadligand.o ../frontend/util_optimize_soa_gpu.o $(OBJ_FRONTEND)
	$(CXX_HOST) $(LIBPATH) $^ -o $@ $(LINKFLAGS)

test3_loadligandlhm: test3_loadligandlhm.o ../frontend/util_optimize_soa_gpu.o $(OBJ_FRONTEND)
	$(CXX_HOST) $(LIBPATH) $^ -o $@ $(LINKFLAGS)

test5_loadall: test5_loadall.o ../frontend/util_optimize_soa_gpu.o $(OBJ_FRONTEND)
	$(CXX_HOST) $(LIBPATH) $^ -o $@ $(LINKFLAGS)

test9_dock: test9_dock.o ../backend_gpu/backend_gpu.o ../frontend/util_optimize_soa_gpu.o $(OBJ_FRONTEND)
	$(CXX_HOST) $(LIBPATH) $^ -o $@ $(LINKFLAGS) -lcudart



include ../GNUmakefile.common.rules



