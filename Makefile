# -*- Makefile -*-
SHELL=/bin/sh
############################################
# derived makefile variables
OBJ_SERIAL=$(SRC:src/%.f90=Obj-serial/%.o)
PREFIX=$(PWD)
nproc=1
OPT = -DTHIRD_LAW
############################################

default: serial parallel

serial: library-serial
	$(MAKE) dirR=$(PWD) dirEXE=$(PREFIX) $(MFLAGS) -C Obj-$@

parallel: library-parallel-MPI library-parallel-OMP library-parallel-MPI-OMP
	$(MAKE) dirR=$(PWD) dirEXE=$(PREFIX) $(MFLAGS) -C Obj-parallel

library-serial: 
	$(MAKE) dirR=$(PWD) $(MFLAGS) -C Obj-serial libLJMD OPT=$(OPT)

library-parallel-MPI:
	$(MAKE) dirR=$(PWD) $(MFLAGS) -C Obj-parallel libLJMD-MPI OPT=$(OPT)

library-parallel-OMP:
	$(MAKE) dirR=$(PWD) $(MFLAGS) -C Obj-parallel libLJMD-OMP OPT=$(OPT)

library-parallel-MPI-OMP:
	$(MAKE) dirR=$(PWD) $(MFLAGS) -C Obj-parallel libLJMD-MPI-OMP OPT=$(OPT)

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
