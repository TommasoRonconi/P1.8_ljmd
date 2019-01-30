# -*- Makefile -*-
SHELL=/bin/sh

#####################################################################
# Options:

OPT = -DTHIRD_LAW
POT_LJ = -DLJ_LESS_MATH
POT_MS = -DMORSE

#####################################################################

CC=gcc

ES = so

dirR = $(PWD)/..
dirI = $(dirR)/include
dirL = $(dirR)/src
dirS = $(dirR)/Obj-serial
dirEXE = $(dirR)

exe_name-LJ = $(dirEXE)/ljmd-serial-LJ.x
exe_name-MS = $(dirEXE)/ljmd-serial-MS.x

CFLAGS0 = -std=c99 -Wall -Wextra -g -O3 -fomit-frame-pointer -ffast-math

C_FLAGS = $(CFLAGS0) -I$(dirI) $(OPT)

LD_FLAGS = -lm -Wl,-rpath,$(dirS)

VPATH=$(dirL)

# Objects:
OBJ_INTERFACE = $(dirS)/ljmd.o
OBJ = $(dirS)/velverlet_time_integration.o $(dirS)/output.o $(dirS)/input.o  $(dirS)/data_structure.o $(dirS)/utilities_ljmd.o
OBJ_FORCE-LJ = $(dirS)/compute_force-LJ.o 
OBJ_FORCE-MS = $(dirS)/compute_force-MS.o 

# Shared library:
LIB-LJ = $(dirS)/libLJMD-LJ.$(ES)
LIB-MS = $(dirS)/libLJMD-MS.$(ES)

EXES = $(exe_name-LJ) $(exe_name-MS)
LIBS = $(LIB-LJ) $(LIB-MS)

default: $(EXES)


# linker rule
$(exe_name-LJ): $(OBJ_INTERFACE) libLJMD-LJ 
	$(CC) -o $@ $(OBJ_INTERFACE) $(LD_FLAGS) -L$(dirS) -lLJMD-LJ 
$(exe_name-MS): $(OBJ_INTERFACE) libLJMD-MS 
	$(CC) -o $@ $(OBJ_INTERFACE) $(LD_FLAGS) -L$(dirS) -lLJMD-MS 

# general rule
$(dirS)/%.o: $(dirL)/%.c
	$(CC) $(C_FLAGS) -c -fPIC $< -o $@
$(OBJ_FORCE-LJ): $(dirL)/compute_force.c
	$(CC) $(C_FLAGS) $(POT_LJ) -c -fPIC $< -o $@
$(OBJ_FORCE-MS): $(dirL)/compute_force.c
	$(CC) $(C_FLAGS) $(POT_MS) -c -fPIC $< -o $@

libLJMD-LJ: $(OBJ) $(OBJ_FORCE-LJ)
	$(CC) $(C_FLAGS0) $(POT_LJ) -shared -o $(LIB-LJ) $^

libLJMD-MS: $(OBJ) $(OBJ_FORCE-MS)
	$(CC) $(C_FLAGS0) $(POT_MS) -shared -o $(LIB-MS) $^

# pre-requisites
# .o
$(dirS)/compute_force-LJ.o: $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h $(dirI)/potentials.h

$(dirS)/compute_force-MS.o: $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h $(dirI)/potentials.h

$(dirS)/ljmd.o: $(dirL)/ljmd.c $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirS)/velverlet_time_integration.o: $(dirI)/velverlet_time_integration.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirS)/utilities_ljmd.o: $(dirI)/utilities_ljmd.h

$(dirS)/data_structure.o: $(dirI)/data_structure.h

$(dirS)/input.o: $(dirI)/input.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirS)/output.o: $(dirI)/output.h $(dirI)/data_structure.h


clean_garbage:
	rm -f *.mod *.o $(dirL)/*~ $(dirI)/*~ $(dirS)/*~

clean: clean_garbage
	rm -f  $(dirR)/ljmd-serial.x $(EXES) $(LIBS) $(OBJ) $(OBJ_INTERFACE) $(OBJ_FORCE-LJ) $(OBJ_FORCE-MS)
