
include ../GNUmakefile.common.mk


ifeq ($(BUILD_CPU), 1)
	OBJ += ../backend_cpu_mic/backend_cpu.o
endif
ifeq ($(BUILD_MIC), 1)
	OBJ += ../backend_cpu_mic/backend_mic.o
endif
default: $(OBJ)


include ../GNUmakefile.common.rules

