
include ../GNUmakefile.common.mk


EXE := geauxdock
OBJ += geauxdock.o
OBJ += load.o data.o rmsd.o util.o util_print.o

default: $(EXE)

$(EXE): $(OBJ)
	$(CXX_HOST) $(LIBPATH) $(OBJ) -o $@ $(LINKFLAGS)

geauxdock.o: geauxdock.cpp
	$(CXX_HOST) $(CXXFLAGS_HOST) -c $< -o $@

include ../GNUmakefile.common.rules

test: geauxdock
	./geauxdock


