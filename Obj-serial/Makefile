# -*- Makefile -*-
SHELL=/bin/sh

CC=gcc

exe_name = $(dirR)/ljmd-serial.x

dirR = $(PWD)
dirI = $(dirR)/include
dirL = $(dirR)/src

CFLAGS=-Wall -Wextra -g -O3 -ffast-math -fomit-frame-pointer -I$(dirI)
LDLIBS=-lm -Wl,-rpath,$(dirL)

# list of source files
# SRC = $(dirI)/.c

VPATH=$(dirL)

OBJ = $(dirL)/velverlet_time_integration.o $(dirL)/output.o $(dirL)/input.o $(dirL)/utilities_ljmd.o $(dirL)/compute_force.o $(dirL)/ljmd.o $(dirL)/data_structure.o

default: $(exe_name)

clean:
	rm -f *.mod *.o $(dirR)/ljmd-serial.x $(OBJ) $(dirL)/*~ $(dirI)/*~

# linker rule
$(exe_name): $(OBJ)
	$(CC) -o $@ $(CFLAGS) $^ $(LDLIBS)

# general rule
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# pre-requisites

$(dirL)/ljmd.o: ljmd.c $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirL)/velverlet_time_integration.o: $(dirI)/velverlet_time_integration.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirL)/compute_force.o: $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirL)/utilities_ljmd.o: $(dirI)/utilities_ljmd.h

$(dirL)/data_structure.o: $(dirI)/data_structure.h

$(dirL)/input.o: $(dirI)/input.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirL)/output.o: $(dirI)/output.h $(dirI)/data_structure.h
