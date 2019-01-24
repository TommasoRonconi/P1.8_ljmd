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

OBJ = $(dirL)/utilities_ljmd.o $(dirL)/compute_force.o $(dirL)/ljmd.o

default: $(exe_name)

clean:
	rm -f *.mod *.o $(dirL)/ljmd-serial.x

# linker rule
$(exe_name): $(OBJ)
	$(CC) -o $@ $(CFLAGS) $^ $(LDLIBS)

# compilation pattern rule for objects

# general rule

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# pre-requisites

$(dirL)/ljmd.o: ljmd.c $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirL)/compute_force.o: $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirL)/utilities_ljmd.o: $(dirI)/utilities_ljmd.h
