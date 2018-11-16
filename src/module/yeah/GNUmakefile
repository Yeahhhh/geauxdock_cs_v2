
SRC_C = $(wildcard ./c/*.c)
SRC_CPP = $(wildcard ./cpp/[a-z]*.cpp)
SRC_OPENCL = $(wildcard ./opencl/*.c)

OBJ_C := $(SRC_C:.c=.o)
OBJ_CPP := $(SRC_CPP:.cpp=.o)
OBJ_OPENCL := $(SRC_OPENCL:.c=.o)





#HEADPATH += -Ix
#LIBPATH += -Lxx
#LINKFLAGS += -lxx





#CC := icc #-mmic
#CXX := icpc -std=c++11 #-mmic
CC := gcc
CXX := g++ -std=c++11
#CC := clang
#CXX := clang++ -std=c++11

CFLAGS := -O3 -fPIC
CXXFLAGS := -O3 -fPIC





all: libc libcxx
#all: libc libopencl libopencl_cxx


%.o: %.c
	$(CC) $(CFLAGS) $(HEADPATH) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(HEADPATH) -c $< -o $@

libc: $(OBJ_C)
	ar rcs ../lib/libyeahc.a $(OBJ_C)

libcxx: $(OBJ_CPP)
	ar rcs ../lib/libyeahcxx.a $(OBJ_CPP)

libopencl: $(OBJ_OPENCL)
	ar rcs ../lib/libyeahopencl.a $(OBJ_OPENCL)

libopencl_cxx:
	$(CXX) $(CXXFLAGS) $(HEADPATH) -c ./opencl/info.c -o ./opencl/info_cxx.o
	$(CXX) $(CXXFLAGS) $(HEADPATH) -c ./opencl/util.c -o ./opencl/util_cxx.o
	$(CXX) $(CXXFLAGS) $(HEADPATH) -c ./opencl/wrapper.c -o ./opencl/wrapper_cxx.o
	ar rcs ../lib/libyeahopencl_cxx.a ./opencl/*_cxx.o


echo:
	@echo $(SRC_C)
	@echo $(SRC_CPP)
	@echo $(SRC_OPENCL)
	@echo $(OBJ_C)
	@echo $(OBJ_CPP)
	@echo $(OBJ_OPENCL)

clean:
	$(RM) $(OBJ_C) $(OBJ_CPP) $(OBJ_OPENCL) ../lib/libyeah*



