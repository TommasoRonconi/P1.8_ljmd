# -*- Makefile -*-
SHELL=/bin/sh

CC=gcc

# <<<<<<< HEAD
exe_name = $(dirR)/ljmd-serial.x

dirR = $(PWD)
dirI = $(dirR)/include
dirL = $(dirR)/src

CFLAGS=-Wall -Wextra -g -O3 -ffast-math -fomit-frame-pointer -I$(dirI)
LDLIBS=-lm -Wl,-rpath,$(dirL)

# list of source files
# =======
# dirI=../include

# CFLAGS=-Wall -g -O3 -ffast-math -fomit-frame-pointer -I$(dirI) 
# LDLIBS=-lm

# # list of source files
# SRC=ljmd.c 
# VPATH=../src
# OBJ=$(SRC:%.c=%.o)
# >>>>>>> origin/velverlet_time_integration

# SRC = $(dirI)/.c

VPATH=$(dirL)

OBJ = $(dirL)/velverlet_time_integration.o $(dirL)/output.o $(dirL)/input.o $(dirL)/utilities_ljmd.o $(dirL)/compute_force.o $(dirL)/ljmd.o

default: $(exe_name)

clean:
	rm -f *.mod *.o $(dirR)/ljmd-serial.x $(OBJ) $(dirL)/*~ $(dirI)/*~

# linker rule
$(exe_name): $(OBJ)
	$(CC) -o $@ $(CFLAGS) $^ $(LDLIBS)

# <<<<<<< HEAD
# general rule

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# pre-requisites

$(dirL)/ljmd.o: ljmd.c $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirL)/velverlet_time_integration.o: $(dirI)/velverlet_time_integration.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirL)/compute_force.o: $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirL)/utilities_ljmd.o: $(dirI)/utilities_ljmd.h

$(dirL)/input.o: $(dirI)/input.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h
# =======
# # compilation pattern rule for objects
# %.o: %.c $(dirI)/velverlet_time_integration.h
# 	$(CC) -c $(CFLAGS) $<
# >>>>>>> origin/velverlet_time_integration

$(dirL)/output.o: $(dirI)/output.h $(dirI)/data_structure.h
