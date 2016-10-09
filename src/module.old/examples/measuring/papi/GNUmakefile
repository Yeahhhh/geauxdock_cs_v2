SRC_C = $(wildcard *.c)
OBJ_C = $(SRC_C:.c=.o)
EXE_C = $(SRC_C:.c=)

SRC_CXX = $(wildcard *.cpp)
OBJ_CXX = $(SRC_CXX:.cpp=.o)
EXE_CXX = $(SRC_CXX:.cpp=)

OBJ = $(OBJ_C) $(OBJ_CXX)
EXE = $(EXE_C) $(EXE_CXX)


LINKFLAGS += -lyeahc -lrt
LINKFLAGS += -lpapi

CC = cc -std=c99 -O2
CXX = g++ -O2

all: $(EXE)

% : %.c
	$(CC) $(HEADPATH) $(LIBPATH) $< -o $@ $(LINKFLAGS)

% : %.cpp
	$(CXX) $(HEADPATH) $(LIBPATH) $< -o $@ $(LINKFLAGS)

echo:
	@(echo $(HEADERS))
	@(echo $(SRC))
	@(echo $(OBJ))
	@(echo $(EXE))
clean:
#	$(RM) $(OBJ)
	$(RM) $(EXE)

