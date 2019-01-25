# -*- Makefile -*-
SHELL=/bin/sh

CC=gcc

exe_name = $(dirR)/ljmd-serial.x

ES = so

dirR = $(PWD)
dirI = $(dirR)/include
dirL = $(dirR)/src
dirO =

CFLAGS0 = -std=c99 -Wall -Wextra -g -O3 -ffast-math -fomit-frame-pointer

C_FLAGS = $(CFLAGS0) -I$(dirI)
LD_FLAGS = -lm -Wl,-rpath,$(dirL)

VPATH=$(dirL)

OBJ = $(dirL)/velverlet_time_integration.o $(dirL)/output.o $(dirL)/input.o $(dirL)/utilities_ljmd.o $(dirL)/compute_force.o $(dirL)/data_structure.o $(dirL)/ljmd.o

LIBS = $(dirL)/velverlet_time_integration.so $(dirL)/output.so $(dirL)/input.so $(dirL)/utilities_ljmd.so $(dirL)/compute_force.so  $(dirL)/data_structure.so

default: $(exe_name)

clean:
	rm -f *.mod *.o $(dirR)/ljmd-serial.x $(OBJ) $(LIBS) $(dirL)/*~ $(dirI)/*~

# linker rule
$(exe_name): $(OBJ) $(LIBS)
	$(CC) -o $@ $(C_FLAGS) $^ $(LD_FLAGS)

# general rule
%.o: %.c
	$(CC) $(C_FLAGS) -c -fPIC $< -o $@

%.so: %.o
	$(CC) $(C_FLAGS0) -shared -fPIC -o $@ $<

# pre-requisites
# .o
$(dirL)/ljmd.o: ljmd.c $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirL)/velverlet_time_integration.o: $(dirI)/velverlet_time_integration.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirL)/compute_force.o: $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirL)/utilities_ljmd.o: $(dirI)/utilities_ljmd.h

$(dirL)/data_structure.o: $(dirI)/data_structure.h

$(dirL)/input.o: $(dirI)/input.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

$(dirL)/output.o: $(dirI)/output.h $(dirI)/data_structure.h

# .so

# $(dirL)/velverlet_time_integration.so: velverlet_time_integration.o

# $(dirL)/compute_force.so: compute_force.o

# $(dirL)/utilities_ljmd.so: utilities_ljmd.o

# $(dirL)/input.so: input.o

# $(dirL)/output.so: output.o
