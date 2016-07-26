.PHONY: common frontend backend_cpu_mic backend_gpu main
all: common frontend backend_cpu_mic backend_gpu main

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

