# -*- Makefile -*-
SHELL=/bin/sh

CC=gcc

exe_name = $(dirR)/ljmd-serial.x

dirR = $(PWD)
dirI = $(dirR)/../include
dirL = $(dirR)/../src

CFLAGS=-Wall -Wextra -g -O3 -ffast-math -fomit-frame-pointer -I$(dirI)
LDLIBS=-lm -Wl,-rpath,$(dirL)


VPATH=$(dirL)

OBJ = velverlet_time_integration.o output.o input.o utilities_ljmd.o compute_force.o test.o data_structure.o
LIBS = velverlet_time_integration.so output.so input.so utilities_ljmd.so compute_force.so data_structure.so

default: $(exe_name)

clean:
	rm -f *.mod *.o $(dirR)/ljmd-serial.x $(OBJ) $(LIBS) $(dirL)/*~ $(dirI)/*~


$(exe_name): $(OBJ) $(LIBS)
	$(CC) -o $@ $(CFLAGS) $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -fPIC $< -o $@

%.so: %.o
	$(CC) -shared -o $@ $<

# pre-requisites
# .o
test.o: test.c $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h $(dirR)/myunittest.h

velverlet_time_integration.o: $(dirI)/velverlet_time_integration.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

compute_force.o: $(dirI)/compute_force.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

utilities_ljmd.o: $(dirI)/utilities_ljmd.h

input.o: $(dirI)/input.h $(dirI)/data_structure.h $(dirI)/utilities_ljmd.h

output.o: $(dirI)/output.h $(dirI)/data_structure.h

data_structure.o: $(dirI)/data_structure.h

# .so
velverlet_time_integration.so: velverlet_time_integration.o

compute_force.so: compute_force.o

utilities_ljmd.so: utilities_ljmd.o

input.so: input.o

output.so: output.o

data_structure.so: data_structure.o