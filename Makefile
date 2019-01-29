# -*- Makefile -*-
SHELL=/bin/sh
############################################
# derived makefile variables
OBJ_SERIAL=$(SRC:src/%.f90=Obj-serial/%.o)
PREFIX=$(PWD)
nproc=1
############################################

default: serial parallel

serial:
	$(MAKE) dirR=$(PWD) dirEXE=$(PREFIX) $(MFLAGS) -C Obj-$@

parallel:
	$(MAKE) dirR=$(PWD) dirEXE=$(PREFIX) $(MFLAGS) -C Obj-parallel

library-serial:
	$(MAKE) dirR=$(PWD) $(MFLAGS) -C Obj-serial libLJMD

library-parallel-MPI:
	$(MAKE) dirR=$(PWD) $(MFLAGS) -C Obj-parallel libLJMD-MPI

library-parallel-OMP:
	$(MAKE) dirR=$(PWD) $(MFLAGS) -C Obj-parallel libLJMD-OMP

library-parallel-MPI-OMP:
	$(MAKE) dirR=$(PWD) $(MFLAGS) -C Obj-parallel libLJMD-MPI-OMP

clean:
	$(MAKE) dirR=$(PWD) $(MFLAGS) -C Obj-parallel clean
	$(MAKE) dirR=$(PWD) $(MFLAGS) -C Obj-serial clean
	$(MAKE) $(MFLAGS) -C examples clean
	$(MAKE) $(MFLAGS) -C test-mpi clean
	$(MAKE) dirR=$(PWD) $(MFLAGS) -C tests clean

check: serial
	$(MAKE) $(MFLAGS) -C examples check

check-MPI: parallel
	$(MAKE) $(MFLAGS) -C test-mpi check nproc=$(nproc)

mytest: library-serial
	$(MAKE) dirR=$(PWD) $(MFLAGS) -C tests run
