EXE := dock_client_dummy
OBJ := dock_client.o

HEADPATH += -I. -I../common


MPICXX := mpicxx
#MPICXX := mpiicpc
CXX := icpc

FLAGS += $(HEADPATH)
FLAGS += -Wall -O2



default: $(EXE)

buildlib:
	cd modules/yeah && make clean
	cd modules/yeah && make

$(EXE): $(OBJ)
	$(MPICXX) $(LIBPATH) $(OBJ) -o $@ $(LINKFLAGS)

dock_client.o: dock_client.C
	$(MPICXX) $(FLAGS) -c $< -o $@

install: $(EXE)
	(cp $(EXE) ../../bin/)

run: $(EXE)
	cd ../../data && ../src/client/$(EXE)

clean:
	@(rm -f ${EXE} *.o)


