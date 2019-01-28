# -*- Makefile -*-
SHELL=/bin/sh

CC=gcc

exe_name = $(dirR)/ljmd-serial.x

ES = so

dirR = $(PWD)
dirI = $(dirR)/include
dirL = $(dirR)/src
dirS = $(dirR)/Obj-serial

CFLAGS0 = -std=c99 -Wall -Wextra -g -O3 -ffast-math -fomit-frame-pointer -fopenmp

C_FLAGS = $(CFLAGS0) -I$(dirI)
LD_FLAGS = -lm -Wl,-rpath,$(dirL) -Wl,-rpath,$(dirS) -fopenmp

VPATH=$(dirL)

# Objects:
OBJ_INTERFACE = $(dirL)/ljmd.o
OBJ = $(dirL)/velverlet_time_integration.o $(dirL)/output.o $(dirL)/input.o $(dirL)/compute_force.o $(dirL)/data_structure.o $(dirL)/utilities_ljmd.o

# Shared library:
LIB = $(dirS)/libLJMD.$(ES)

default: $(exe_name)

clean_garbage:
	rm -f *.mod *.o $(dirL)/*~ $(dirI)/*~

clean: clean_garbage
	rm -f $(dirR)/ljmd-serial.x $(OBJ) $(OBJ_INTERFACE) $(LIB)

# linker rule
$(exe_name): $(OBJ_INTERFACE) libLJMD 
	$(CC) -o $@ $(OBJ_INTERFACE) $(LD_FLAGS) -L$(dirS) -lLJMD 

# general rule
%.o: %.c
	$(CC) $(C_FLAGS) -c -fPIC $< -o $@

libLJMD: $(OBJ)
	$(CC) $(C_FLAGS0) -shared -o $(LIB) $^

# pre-requisites
# .o
$(dirL)/ljmd.o: ljmd.c $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirL)/velverlet_time_integration.o: $(dirI)/velverlet_time_integration.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirL)/compute_force.o: $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirL)/utilities_ljmd.o: $(dirI)/utilities_ljmd.h

$(dirL)/data_structure.o: $(dirI)/data_structure.h

$(dirL)/input.o: $(dirI)/input.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirL)/output.o: $(dirI)/output.h $(dirI)/data_structure.h
