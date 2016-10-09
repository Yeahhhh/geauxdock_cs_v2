

#HEADERS = $(wildcard *.cuh)
SRC = $(wildcard *.cpp)
#SRC = $(wildcard stream*.cpp)
OBJ = $(SRC:.cpp=.o)
EXE = $(SRC:.cpp=)

#LINKFLAGS += -lyeahc -lrt
LINKFLAGS += -lyeahopencl_cxx
LINKFLAGS += -lOpenCL

CXX = g++ -O2 $(HEADPATH) $(LIBPATH)

all: $(EXE)

% : %.cpp
	$(CXX) $< -o $@ $(LINKFLAGS)

echo:
	@(echo $(HEADERS))
	@(echo $(SRC))
	@(echo $(OBJ))
	@(echo $(EXE))
clean:
#	$(RM) $(OBJ)
	$(RM) $(EXE)

