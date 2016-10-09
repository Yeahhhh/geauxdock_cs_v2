HEADERS = $(wildcard *.cuh)
SRC = $(wildcard *.cpp)
#SRC = $(wildcard stream*.cu)
OBJ = $(SRC:.cpp=.o)
EXE = $(SRC:.cpp=)

LINKFLAGS += -lcudart
#LINKFLAGS += -lcudart_static
#LINKFLAGS += -lnvidia-ml
LINKFLAGS += -lpthread
LINKFLAGS += -lyeahc -lrt


#CXX = nvcc -O2
CXX = g++ -std=c++11 -O2
#CXX = g++-4.9 -O2

all: $(EXE)

% : %.cpp
	$(CXX) $(HEADPATH) $(LIBPATH) $< -o $@ $(LINKFLAGS)

nvmlinfo: nvmlinfo.cpp
	$(CXX) $(HEADPATH) $(LIBPATH) $< -o $@ $(LINKFLAGS) -lnvidia-ml


echo:
	@(echo $(HEADERS))
	@(echo $(SRC))
	@(echo $(OBJ))
	@(echo $(EXE))
clean:
#	$(RM) $(OBJ)
	$(RM) $(EXE)

