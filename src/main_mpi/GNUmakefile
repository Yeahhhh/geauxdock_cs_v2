include ../GNUmakefile.common.mk


EXE = server client
#OBJ += load.o data.o rmsd.o util.o util_print.o


default: $(EXE)


server: server.o $(OBJ)
	$(CXX_MPI) $(LIBPATH) $^ -o $@ $(LINKFLAGS)

client: client.o
	$(CXX_MPI) $(LIBPATH) $^ -o $@ $(LINKFLAGS)


%.o: %.cpp
	$(CXX_MPI) $(CXXFLAGS_HOST) -c $< -o $@



include ../GNUmakefile.common.rules

