# -*- Makefile -*-
SHELL=/bin/sh
############################################
# derived makefile variables
OBJ_SERIAL=$(SRC:src/%.f90=Obj-serial/%.o)
############################################

default: serial

serial:
	$(MAKE) dirR=$(PWD) $(MFLAGS) -C Obj-$@

parallel-MPI:
	$(MAKE) dirR=$(PWD) $(MFLAGS) -C Obj-$@

library:
	$(MAKE) dirR=$(PWD) $(MFLAGS) -C Obj-serial libLJMD

clean:
	$(MAKE) dirR=$(PWD) $(MFLAGS) -C Obj-parallel-MPI clean
	$(MAKE) dirR=$(PWD) $(MFLAGS) -C Obj-serial clean
	$(MAKE) $(MFLAGS) -C examples clean
	$(MAKE) $(MFLAGS) -C test-mpi clean
	$(MAKE) dirR=$(PWD) $(MFLAGS) -C tests clean

check: serial
	$(MAKE) $(MFLAGS) -C examples check

check-MPI: parallel-MPI
	$(MAKE) $(MFLAGS) -C test-mpi check

mytest: library
	$(MAKE) dirR=$(PWD) $(MFLAGS) -C tests run
