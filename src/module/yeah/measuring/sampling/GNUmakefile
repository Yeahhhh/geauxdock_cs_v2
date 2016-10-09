
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
EXE = $(SRC:.cpp=)

CXX = g++ -O2 -std=c++11


LINKFLAGS += -lpthread -lyeahc -lrt


all: $(EXE)

% : %.cpp
	$(CXX) $(HEADPATH) $(LIBPATH) $< -o $@ $(LINKFLAGS)

nvml: nvml.cpp
	$(CXX) $(HEADPATH) $(LIBPATH) $< -o $@ $(LINKFLAGS) -lcudart -lnvidia-ml





echo:
#	@(echo $(HEADERS))
	@(echo $(SRC))
	@(echo $(OBJ))
	@(echo $(EXE))
clean:
	$(RM) $(OBJ)
	$(RM) $(EXE)

