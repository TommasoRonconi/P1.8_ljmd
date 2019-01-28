# -*- Makefile -*-
SHELL=/bin/sh

MPIC = mpicc

exe_name = $(dirR)/ljmd-parallel-mpi.x

ES = so

dirR = $(PWD)/..
dirI = $(dirR)/include
dirL = $(dirR)/src
dirS = $(dirR)/Obj-parallel-MPI

CFLAGS0 = -std=c99 -Wall -Wextra -g -O3 -ffast-math -fomit-frame-pointer

C_FLAGS = $(CFLAGS0) -I$(dirI)
LD_FLAGS = -lm -Wl,-rpath,$(dirS)

VPATH=$(dirL)

# Objects:
OBJ_INTERFACE = $(dirS)/ljmd.o
OBJ = $(dirS)/velverlet_time_integration.o $(dirS)/output.o $(dirS)/input.o $(dirS)/compute_force.o $(dirS)/data_structure.o $(dirS)/utilities_ljmd.o

# Shared library:
LIB = $(dirS)/libLJMD-mpi.$(ES)

default: $(exe_name)

clean_garbage:
	rm -f *.mod *.o $(dirL)/*~ $(dirI)/*~ $(dirS)/*~

clean: clean_garbage
	rm -f $(dirR)/ljmd-parallel-mpi.x $(OBJ) $(OBJ_INTERFACE) $(LIB)

# linker rule
$(exe_name): $(OBJ_INTERFACE) libLJMD 
	$(MPIC) -o $@ $(OBJ_INTERFACE) $(LD_FLAGS) -L$(dirS) -lLJMD-mpi

# general rule
$(dirS)/%.o: $(dirL)/%.c
	$(MPIC) $(C_FLAGS) -c -fPIC $< -o $@ -DUSE_MPI

libLJMD: $(OBJ)
	$(MPIC) $(C_FLAGS0) -shared -o $(LIB) $^

# pre-requisites
# .o
$(dirS)/ljmd.o: $(dirL)/ljmd.c $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirS)/velverlet_time_integration.o: $(dirI)/velverlet_time_integration.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirS)/compute_force.o: $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirS)/utilities_ljmd.o: $(dirI)/utilities_ljmd.h

$(dirS)/data_structure.o: $(dirI)/data_structure.h

$(dirS)/input.o: $(dirI)/input.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirS)/output.o: $(dirI)/output.h $(dirI)/data_structure.h
