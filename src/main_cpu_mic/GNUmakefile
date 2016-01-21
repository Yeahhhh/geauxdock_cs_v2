
include ../GNUmakefile.mk



TARGET_DEVICE := $(TARGET_CPU)
#TARGET_DEVICE := $(TARGET_MIC)




DMARCRO += -DTARGET_DEVICE=$(TARGET_DEVICE)

# this is for MIC native mode
ifeq ($(TARGET_DEVICE), $(TARGET_MIC))
#	FCFLAGS_HOST += -mmic
#	CXXFLAGS_HOST += -mmic
endif



EXE := dock
OBJ += dock.o
OBJ += backend_cpu_mic.o
OBJ += load.o data.o rmsd.o util.o util_optimize_soa.o util_print.o


default: $(EXE)

$(EXE): $(OBJ)
	$(CXX_HOST) $(LIBPATH) $(OBJ) -o $@ $(LINKFLAGS)

dock.o: dock.C
	$(CXX_HOST) $(CXXFLAGS_HOST) -c $< -o $@

run: $(EXE)
	(cd ../../data && ../src/main_cpu_mic/$(EXE) -nt 20)


include ../GNUmakefile.common_rules

