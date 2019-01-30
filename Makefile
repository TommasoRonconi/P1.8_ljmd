# -*- Makefile -*-
SHELL=/bin/sh
############################################
# derived makefile variables
OBJ_SERIAL=$(SRC:src/%.f90=Obj-serial/%.o)
PREFIX=$(PWD)
nproc=1
OPT = -DTHIRD_LAW
POT_LJ = -DLJ_LESS_MATH
POT_MS = -DMORSE
############################################

default: serial parallel

#--------------------------------------------------------------------------
serial: library-serial
	$(MAKE) dirR=$(PWD) dirEXE=$(PREFIX) $(MFLAGS) -C Obj-serial

parallel: library-parallel-MPI library-parallel-OMP library-parallel-MPI-OMP
	$(MAKE) dirR=$(PWD) dirEXE=$(PREFIX) $(MFLAGS) -C Obj-parallel

library-serial: 
	$(MAKE) dirR=$(PWD) $(MFLAGS) -C Obj-serial libLJMD-LJ libLJMD-MS OPT=$(OPT)

library-parallel-MPI:
	$(MAKE) dirR=$(PWD) $(MFLAGS) -C Obj-parallel libLJMD-MPI-LJ libLJMD-MPI-MS OPT=$(OPT)

library-parallel-OMP:
	$(MAKE) dirR=$(PWD) $(MFLAGS) -C Obj-parallel libLJMD-OMP-LJ libLJMD-OMP-MS OPT=$(OPT)

library-parallel-MPI-OMP:
	$(MAKE) dirR=$(PWD) $(MFLAGS) -C Obj-parallel libLJMD-MPI-OMP-LJ libLJMD-MPI-OMP-MS OPT=$(OPT)

check-LJ: serial
	$(MAKE) $(MFLAGS) -C examples check

check-MPI-LJ: parallel
	$(MAKE) $(MFLAGS) -C test-mpi check nproc=$(nproc)

check-MS: serial
	$(MAKE) $(MFLAGS) -C examples check-morse

check-MPI-MS: parallel
	$(MAKE) $(MFLAGS) -C test-mpi check-morse nproc=$(nproc)

mytest: serial
	$(MAKE) dirR=$(PWD) $(MFLAGS) -C tests run

clean:
	$(MAKE) dirR=$(PWD) $(MFLAGS) -C Obj-parallel clean
	$(MAKE) dirR=$(PWD) $(MFLAGS) -C Obj-serial clean
	$(MAKE) $(MFLAGS) -C examples clean
	$(MAKE) $(MFLAGS) -C test-mpi clean
	$(MAKE) dirR=$(PWD) $(MFLAGS) -C tests clean
