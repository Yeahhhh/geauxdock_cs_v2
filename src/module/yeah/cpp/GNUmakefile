
SRC = $(wildcard _*.cpp)
OBJ = $(SRC:.cpp=.o)
EXE = $(SRC:.cpp=)

#CXX = clang++ -O2 -std=c++11
CXX = g++ -O2 -std=c++11


LINKFLAGS += -lyeahc -lyeahcxx -lrt


all: $(EXE)

% : %.cpp
	$(CXX) $(HEADPATH) $(LIBPATH) $< -o $@ $(LINKFLAGS)


echo:
#	@(echo $(HEADERS))
	@(echo $(SRC))
	@(echo $(OBJ))
	@(echo $(EXE))
clean:
	$(RM) $(OBJ)
	$(RM) $(EXE)

