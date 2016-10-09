include ../GNUmakefile.common.mk

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
EXE = $(SRC:.cpp=)

default: $(EXE)


%: %.cpp
	$(CXX_HOST) $(CXXFLAGS_HOST) $< -o $@ $(LINKFLAGS)


include ../GNUmakefile.common.rules


