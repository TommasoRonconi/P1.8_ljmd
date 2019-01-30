# -*- Makefile -*-

SHELL=/bin/sh

#####################################################################
# Options:

OPT = -DTHIRD_LAW
POT_LJ = -DLJ_LESS_MATH
POT_MS = -DMORSE

############################################################################
# Variables:

MPIC = mpicc
CC = clang

ES = so

dirR = $(PWD)/..
dirI = $(dirR)/include
dirL = $(dirR)/src
dirS = $(dirR)/Obj-parallel
dirO-MPI = $(dirS)/MPI
dirO-OMP = $(dirS)/OpenMP
dirO-MPI-OMP = $(dirS)/MPI+OpenMP
dirEXE = $(dirR)

exe_name-mpi-LJ = $(dirEXE)/ljmd-parallel-mpi-LJ.x
exe_name-omp-LJ = $(dirEXE)/ljmd-parallel-omp-LJ.x
exe_name-mpi-omp-LJ = $(dirEXE)/ljmd-parallel-mpi-omp-LJ.x

exe_name-mpi-MS = $(dirEXE)/ljmd-parallel-mpi-MS.x
exe_name-omp-MS = $(dirEXE)/ljmd-parallel-omp-MS.x
exe_name-mpi-omp-MS = $(dirEXE)/ljmd-parallel-mpi-omp-MS.x

CFLAGS0 = -std=c99 -Wall -Wextra -g -O3 -ffast-math -fomit-frame-pointer

C_FLAGS = $(CFLAGS0) -I$(dirI) $(OPT)
LD_FLAGS = -lm -Wl,-rpath,$(dirS)

VPATH=$(dirL)

# Objects:
OBJ_INTERFACE-MPI = $(dirO-MPI)/ljmd.o
OBJ_INTERFACE-OMP = $(dirO-OMP)/ljmd.o
OBJ_INTERFACE-MPI-OMP = $(dirO-MPI-OMP)/ljmd.o

OBJ-MPI = $(dirO-MPI)/velverlet_time_integration.o $(dirO-MPI)/output.o $(dirO-MPI)/input.o  $(dirO-MPI)/data_structure.o $(dirO-MPI)/utilities_ljmd.o
OBJ-OMP = $(dirO-OMP)/velverlet_time_integration.o $(dirO-OMP)/output.o $(dirO-OMP)/input.o  $(dirO-OMP)/data_structure.o $(dirO-OMP)/utilities_ljmd.o
OBJ-MPI-OMP = $(dirO-MPI-OMP)/velverlet_time_integration.o $(dirO-MPI-OMP)/output.o $(dirO-MPI-OMP)/input.o $(dirO-MPI-OMP)/data_structure.o $(dirO-MPI-OMP)/utilities_ljmd.o

OBJ_FORCE_MPI-LJ = $(dirO-MPI)/compute_force-LJ.o 
OBJ_FORCE_OMP-LJ = $(dirO-OMP)/compute_force-LJ.o 
OBJ_FORCE_MPI-OMP-LJ = $(dirO-MPI-OMP)/compute_force-LJ.o 
OBJ_FORCE_MPI-MS = $(dirO-MPI)/compute_force-MS.o 
OBJ_FORCE_OMP-MS = $(dirO-OMP)/compute_force-MS.o 
OBJ_FORCE_MPI-OMP-MS = $(dirO-MPI-OMP)/compute_force-MS.o 



# Shared library:
LIB-MPI-LJ = $(dirS)/libLJMD-mpi-LJ.$(ES)
LIB-OMP-LJ = $(dirS)/libLJMD-omp-LJ.$(ES)
LIB-MPI-OMP-LJ = $(dirS)/libLJMD-mpi-omp-LJ.$(ES)

LIB-MPI-MS = $(dirS)/libLJMD-mpi-MS.$(ES)
LIB-OMP-MS = $(dirS)/libLJMD-omp-MS.$(ES)
LIB-MPI-OMP-MS = $(dirS)/libLJMD-mpi-omp-MS.$(ES)

###############################################################################
# Rules:
EXES = $(exe_name-mpi-LJ) $(exe_name-omp-LJ) $(exe_name-mpi-omp-LJ) $(exe_name-mpi-MS) $(exe_name-omp-MS) $(exe_name-mpi-omp-MS)
OBJS = $(OBJ-MPI)  $(OBJ-OMP) $(OBJ-MPI-OMP)
OBJ_FORCE = $(OBJ_FORCE_MPI-LJ) $(OBJ_FORCE_OMP-LJ) $(OBJ_FORCE_MPI-OMP-LJ) $(OBJ_FORCE_MPI-MS) $(OBJ_FORCE_OMP-MS) $(OBJ_FORCE_MPI-OMP-MS) 
LIBS = $(LIB-MPI-LJ) $(LIB-OMP-LJ) $(LIB-MPI-OMP-LJ) $(LIB-MPI-MS) $(LIB-OMP-MS) $(LIB-MPI-OMP-MS)
INTERFACES = $(OBJ_INTERFACE-MPI) $(OBJ_INTERFACE-OMP) $(OBJ_INTERFACE-MPI-OMP)

default: $(EXES)

$(dirO-MPI):
	mkdir -p $@

$(dirO-OMP):
	mkdir -p $@

$(dirO-MPI-OMP):
	mkdir -p $@

clean_garbage:
	rm -f *.mod *.o $(dirL)/*~ $(dirI)/*~ $(dirS)/*~ $(dirO-MPI)/*~ $(dirO-OMP)/*~ $(dirO-MPI-OMP)/*~


clean: clean_garbage
	rm -f $(EXES) $(OBJS) $(LIBS) $(INTERFACES) $(OBJ_FORCE)

# mkdMS
$(%):
	mkdir -p $(%)

# linker rules
$(exe_name-mpi-LJ): $(OBJ_INTERFACE-MPI) libLJMD-MPI-LJ 
	$(MPIC) -o $@ $(OBJ_INTERFACE-MPI) $(LD_FLAGS) -Wl,-rpath,$(dirO-MPI) -L$(dirS) -lLJMD-mpi-LJ
$(exe_name-omp-LJ): $(OBJ_INTERFACE-OMP) libLJMD-OMP-LJ
	$(CC) -o $@ $(OBJ_INTERFACE-OMP) $(LD_FLAGS) -Wl,-rpath,$(dirO-OMP) -fopenmp -L$(dirS) -lLJMD-omp-LJ
$(exe_name-mpi-omp-LJ): $(OBJ_INTERFACE-MPI-OMP) libLJMD-MPI-OMP-LJ 
	$(MPIC) -o $@ $(OBJ_INTERFACE-MPI-OMP) $(LD_FLAGS) -Wl,-rpath,$(dirO-MPI-OMP) -fopenmp -L$(dirS) -lLJMD-mpi-omp-LJ

$(exe_name-mpi-MS): $(OBJ_INTERFACE-MPI) libLJMD-MPI-MS 
	$(MPIC) -o $@ $(OBJ_INTERFACE-MPI) $(LD_FLAGS) -Wl,-rpath,$(dirO-MPI) -L$(dirS) -lLJMD-mpi-MS
$(exe_name-omp-MS): $(OBJ_INTERFACE-OMP) libLJMD-OMP-MS
	$(CC) -o $@ $(OBJ_INTERFACE-OMP) $(LD_FLAGS) -Wl,-rpath,$(dirO-OMP) -fopenmp -L$(dirS) -lLJMD-omp-MS
$(exe_name-mpi-omp-MS): $(OBJ_INTERFACE-MPI-OMP) libLJMD-MPI-OMP-MS 
	$(MPIC) -o $@ $(OBJ_INTERFACE-MPI-OMP) $(LD_FLAGS) -Wl,-rpath,$(dirO-MPI-OMP) -fopenmp -L$(dirS) -lLJMD-mpi-omp-MS


# general rules
$(dirO-MPI)/%.o: $(dirL)/%.c $(dirO-MPI)
	$(MPIC) $(C_FLAGS) -c -fPIC $< -o $@ -DUSE_MPI
$(OBJ_FORCE_MPI-LJ): $(dirL)/compute_force.c $(dirO-MPI)
	$(MPIC) $(C_FLAGS) $(POT_LJ) -c -fPIC $< -o $@ -DUSE_MPI
$(OBJ_FORCE_MPI-MS): $(dirL)/compute_force.c $(dirO-MPI)
	$(MPIC) $(C_FLAGS) $(POT_MS) -c -fPIC $< -o $@ -DUSE_MPI

$(dirO-OMP)/%.o: $(dirL)/%.c $(dirO-OMP)
	$(CC) $(C_FLAGS)  -fopenmp -c -fPIC $< -o $@
$(OBJ_FORCE_OMP-LJ): $(dirL)/compute_force.c $(dirO-OMP)
	$(CC) $(C_FLAGS) $(POT_LJ) -fopenmp -c -fPIC $< -o $@
$(OBJ_FORCE_OMP-MS): $(dirL)/compute_force.c $(dirO-OMP)
	$(CC) $(C_FLAGS) $(POT_MS) -fopenmp -c -fPIC $< -o $@

$(dirO-MPI-OMP)/%.o: $(dirL)/%.c $(dirO-MPI-OMP)
	$(MPIC) $(C_FLAGS) -fopenmp -c -fPIC $< -o $@ -DUSE_MPI
$(OBJ_FORCE_MPI-OMP-LJ): $(dirL)/compute_force.c $(dirO-MPI-OMP)
	$(MPIC) $(C_FLAGS) $(POT_LJ) -fopenmp -c -fPIC $< -o $@ -DUSE_MPI
$(OBJ_FORCE_MPI-OMP-MS): $(dirL)/compute_force.c $(dirO-MPI-OMP)
	$(MPIC) $(C_FLAGS) $(POT_MS) -fopenmp -c -fPIC $< -o $@ -DUSE_MPI


# libraries rules
libLJMD-MPI-LJ: $(OBJ-MPI) $(OBJ_FORCE_MPI-LJ) 
	$(MPIC) $(C_FLAGS0) -shared -o $(LIB-MPI-LJ) $^
libLJMD-OMP-LJ: $(OBJ-OMP) $(OBJ_FORCE_OMP-LJ)
	$(CC) $(C_FLAGS0) -fopenmp -shared -o $(LIB-OMP-LJ) $^
libLJMD-MPI-OMP-LJ: $(OBJ-MPI-OMP) $(OBJ_FORCE_MPI-OMP-LJ)
	$(MPIC) $(C_FLAGS0) $(POT_LJ) -fopenmp -shared -o $(LIB-MPI-OMP-LJ) $^

libLJMD-MPI-MS: $(OBJ-MPI) $(OBJ_FORCE_MPI-MS)
	$(MPIC) $(C_FLAGS0) -shared -o $(LIB-MPI-MS) $^
libLJMD-OMP-MS: $(OBJ-OMP) $(OBJ_FORCE_OMP-MS)
	$(CC) $(C_FLAGS0) -fopenmp -shared -o $(LIB-OMP-MS) $^
libLJMD-MPI-OMP-MS: $(OBJ-MPI-OMP) $(OBJ_FORCE_MPI-OMP-MS)
	$(MPIC) $(C_FLAGS0) -fopenmp -shared -o $(LIB-MPI-OMP-MS) $^


# pre-requisites
# .o
$(dirO-MPI)/compute_force-LJ.o: $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h $(dirI)/potentials.h

$(dirO-MPI)/compute_force-MS.o: $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h $(dirI)/potentials.h

$(dirO-MPI)/ljmd.o: $(dirL)/ljmd.c $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirO-MPI)/velverlet_time_integration.o: $(dirI)/velverlet_time_integration.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirO-MPI)/utilities_ljmd.o: $(dirI)/utilities_ljmd.h

$(dirO-MPI)/data_structure.o: $(dirI)/data_structure.h

$(dirO-MPI)/input.o: $(dirI)/input.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirO-MPI)/output.o: $(dirI)/output.h $(dirI)/data_structure.h



$(dirO-OMP)/ljmd.o: $(dirL)/ljmd.c $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirO-OMP)/velverlet_time_integration.o: $(dirI)/velverlet_time_integration.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirO-OMP)/compute_force-LJ.o: $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h $(dirI)/potentials.h

$(dirO-OMP)/compute_force-MS.o: $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h $(dirI)/potentials.h

$(dirO-OMP)/utilities_ljmd.o: $(dirI)/utilities_ljmd.h

$(dirO-OMP)/data_structure.o: $(dirI)/data_structure.h

$(dirO-OMP)/input.o: $(dirI)/input.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirO-OMP)/output.o: $(dirI)/output.h $(dirI)/data_structure.h



$(dirO-MPI-OMP)/ljmd.o: $(dirL)/ljmd.c $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirO-MPI-OMP)/velverlet_time_integration.o: $(dirI)/velverlet_time_integration.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirO-MPI-OMP)/compute_force-LJ.o: $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h $(dirI)/potentials.h

$(dirO-MPI-OMP)/compute_force-MS.o: $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h $(dirI)/potentials.h

$(dirO-MPI-OMP)/utilities_ljmd.o: $(dirI)/utilities_ljmd.h

$(dirO-MPI-OMP)/data_structure.o: $(dirI)/data_structure.h

$(dirO-MPI-OMP)/input.o: $(dirI)/input.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirO-MPI-OMP)/output.o: $(dirI)/output.h $(dirI)/data_structure.h
