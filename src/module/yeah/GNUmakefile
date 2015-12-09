
#CC := icc #-mmic
#CXX := icpc #-mmic
CC := gcc
CXX := g++
#CC := clang
#CXX := clang++

OPTFLAGS := -O3 -fPIC


#MODULE := ${HOME}/app/module
#HEADPATH += -I$(MODULE)
#LIBPATH += -L$(MODULE)/lib
#LINKFLAGS +=



SRC_C += ./c/mkdir.c
SRC_C += ./c/timing.c
SRC_C += ./c/sleep.c

#SRC_CPP += ./cpp/timer.cpp
#SRC_CPP += ./cpp/misc.cpp

SRC_OPENCL += ./opencl/$(wildcard *.c)

OBJ_C := $(SRC_C:.c=.o)
OBJ_CPP := $(SRC_CPP:.cpp=.o)
OBJ_OPENCL := $(SRC_OPENCL:.c=.o)


#all: libc libcpp
all: libc


%.o: %.c
	$(CC) $(OPTFLAGS) $(HEADPATH) -c $< -o $@

%.o: %.cpp
	$(CXX) $(OPTFLAGS) $(HEADPATH) -c $< -o $@


libc: $(OBJ_C)
	ar rcs ../lib/libyeahc.a $(OBJ_C)

libcpp: $(OBJ_C) $(OBJ_CPP)
	ar rcs ../lib/libyeahcpp.a $(OBJ_C) $(OBJ_CPP)

echo:
	@echo $(OBJ_C)
	@echo $(OBJ_CPP)

clean:
	$(RM) $(OBJ_C) $(OBJ_CPP)

