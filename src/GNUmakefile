.PHONY: module common frontend backend_cpu_mic backend_gpu main
all: module common frontend backend_cpu_mic backend_gpu main

module:
	@cd module/yeah && make -B
common:
	@cd $@ && make
frontend:
	@cd $@ && make
backend_cpu_mic:
	@cd $@ && make
backend_gpu:
	@cd $@ && make
main:
	@cd $@ && make

clean:
	@cd common && make clean
	@cd frontend && make clean
	@cd backend_cpu_mic && make clean
	@cd backend_gpu && make clean
	@cd main && make clean

