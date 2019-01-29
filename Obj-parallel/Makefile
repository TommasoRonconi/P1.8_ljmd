# -*- Makefile -*-
############################################################################
# Variables:

SHELL=/bin/sh

MPIC = mpicc
CC = gcc

ES = so

dirR = $(PWD)/..
dirI = $(dirR)/include
dirL = $(dirR)/src
dirS = $(dirR)/Obj-parallel
dirO-MPI = $(dirS)/MPI
dirO-OMP = $(dirS)/OpenMP
dirO-MPI-OMP = $(dirS)/MPI+OpenMP
dirEXE = $(dirR)

exe_name-mpi = $(dirEXE)/ljmd-parallel-mpi.x
exe_name-omp = $(dirEXE)/ljmd-parallel-omp.x
exe_name-mpi-omp = $(dirEXE)/ljmd-parallel-mpi-omp.x

CFLAGS0 = -std=c99 -Wall -Wextra -g -O3 -ffast-math -fomit-frame-pointer

C_FLAGS = $(CFLAGS0) -I$(dirI)
LD_FLAGS = -lm -Wl,-rpath,$(dirS)

VPATH=$(dirL)

# Objects:
OBJ_INTERFACE-MPI = $(dirO-MPI)/ljmd.o
OBJ-MPI = $(dirO-MPI)/velverlet_time_integration.o $(dirO-MPI)/output.o $(dirO-MPI)/input.o $(dirO-MPI)/compute_force.o $(dirO-MPI)/data_structure.o $(dirO-MPI)/utilities_ljmd.o
OBJ_INTERFACE-OMP = $(dirO-OMP)/ljmd.o
OBJ-OMP = $(dirO-OMP)/velverlet_time_integration.o $(dirO-OMP)/output.o $(dirO-OMP)/input.o $(dirO-OMP)/compute_force.o $(dirO-OMP)/data_structure.o $(dirO-OMP)/utilities_ljmd.o
OBJ_INTERFACE-MPI-OMP = $(dirO-MPI-OMP)/ljmd.o
OBJ-MPI-OMP = $(dirO-MPI-OMP)/velverlet_time_integration.o $(dirO-MPI-OMP)/output.o $(dirO-MPI-OMP)/input.o $(dirO-MPI-OMP)/compute_force.o $(dirO-MPI-OMP)/data_structure.o $(dirO-MPI-OMP)/utilities_ljmd.o

# Shared library:
LIB-MPI = $(dirS)/libLJMD-mpi.$(ES)
LIB-OMP = $(dirS)/libLJMD-omp.$(ES)
LIB-MPI-OMP = $(dirS)/libLJMD-mpi-omp.$(ES)

###############################################################################
# Rules:

default: $(exe_name-mpi) $(exe_name-omp) $(exe_name-mpi-omp)

clean_garbage:
	rm -f *.mod *.o $(dirL)/*~ $(dirI)/*~ $(dirS)/*~ $(dirO-MPI)/*~ $(dirO-OMP)/*~ $(dirO-MPI-OMP)/*~

clean: clean_garbage
	rm -f $(dirR)/ljmd-parallel-mpi.x $(OBJ-MPI) $(OBJ_INTERFACE-MPI) $(OBJ-OMP) $(OBJ_INTERFACE-OMP) $(OBJ-MPI-OMP) $(OBJ_INTERFACE-MPI-OMP) $(LIB-MPI) $(LIB-OMP) $(LIB-MPI-OMP)

# linker rules
$(exe_name-mpi): $(OBJ_INTERFACE-MPI) libLJMD-MPI 
	$(MPIC) -o $@ $(OBJ_INTERFACE-MPI) $(LD_FLAGS) -Wl,-rpath,$(dirO-MPI) -L$(dirS) -lLJMD-mpi
$(exe_name-omp): $(OBJ_INTERFACE-OMP) libLJMD-OMP
	$(CC) -o $@ $(OBJ_INTERFACE-OMP) $(LD_FLAGS) -Wl,-rpath,$(dirO-OMP) -fopenmp -L$(dirS) -lLJMD-omp
$(exe_name-mpi-omp): $(OBJ_INTERFACE-MPI-OMP) libLJMD-MPI-OMP 
	$(MPIC) -o $@ $(OBJ_INTERFACE-MPI-OMP) $(LD_FLAGS) -Wl,-rpath,$(dirO-MPI-OMP) -fopenmp -L$(dirS) -lLJMD-mpi-omp

# general rules
$(dirO-MPI)/%.o: $(dirL)/%.c
	$(MPIC) $(C_FLAGS) -c -fPIC $< -o $@ -DUSE_MPI
$(dirO-OMP)/%.o: $(dirL)/%.c
	$(CC) $(C_FLAGS) -fopenmp -c -fPIC $< -o $@
$(dirO-MPI-OMP)/%.o: $(dirL)/%.c
	$(MPIC) $(C_FLAGS) -fopenmp -c -fPIC $< -o $@ -DUSE_MPI

# libraries rules
libLJMD-MPI: $(OBJ-MPI)
	$(MPIC) $(C_FLAGS0) -shared -o $(LIB-MPI) $^
libLJMD-OMP: $(OBJ-OMP)
	$(CC) $(C_FLAGS0) -fopenmp -shared -o $(LIB-OMP) $^
libLJMD-MPI-OMP: $(OBJ-MPI-OMP)
	$(MPIC) $(C_FLAGS0) -fopenmp -shared -o $(LIB-MPI-OMP) $^

# pre-requisites
# .o
$(dirO-MPI)/ljmd.o: $(dirL)/ljmd.c $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirO-MPI)/velverlet_time_integration.o: $(dirI)/velverlet_time_integration.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirO-MPI)/compute_force.o: $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirO-MPI)/utilities_ljmd.o: $(dirI)/utilities_ljmd.h

$(dirO-MPI)/data_structure.o: $(dirI)/data_structure.h

$(dirO-MPI)/input.o: $(dirI)/input.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirO-MPI)/output.o: $(dirI)/output.h $(dirI)/data_structure.h

$(dirO-OMP)/ljmd.o: $(dirL)/ljmd.c $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirO-OMP)/velverlet_time_integration.o: $(dirI)/velverlet_time_integration.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirO-OMP)/compute_force.o: $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirO-OMP)/utilities_ljmd.o: $(dirI)/utilities_ljmd.h

$(dirO-OMP)/data_structure.o: $(dirI)/data_structure.h

$(dirO-OMP)/input.o: $(dirI)/input.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirO-OMP)/output.o: $(dirI)/output.h $(dirI)/data_structure.h

$(dirO-MPI-OMP)/ljmd.o: $(dirL)/ljmd.c $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirO-MPI-OMP)/velverlet_time_integration.o: $(dirI)/velverlet_time_integration.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirO-MPI-OMP)/compute_force.o: $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirO-MPI-OMP)/utilities_ljmd.o: $(dirI)/utilities_ljmd.h

$(dirO-MPI-OMP)/data_structure.o: $(dirI)/data_structure.h

$(dirO-MPI-OMP)/input.o: $(dirI)/input.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirO-MPI-OMP)/output.o: $(dirI)/output.h $(dirI)/data_structure.h
