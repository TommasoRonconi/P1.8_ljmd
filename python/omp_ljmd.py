"""
@authors: Herbert Nguuruwe
@Team: Matteo, Thomaso, Jesus 

"""
from ctypes import *
from header import *
import argparse
import subprocess

#Create struct

#run from the number of threads possible

class _mdsys(Structure):
    """
    The struct class same structure from C.
    """
    _fields_ = [("natoms", c_int), ("nfi", c_int), ("nsteps", c_int), ("dt", c_double), ("mass", c_double),  ("epsilon", c_double),  ("sigma", c_double), ("box", c_double), ("rcut", c_double), ("ekin", c_double), ("epot", c_double), ("temp", c_double), ("rx", POINTER(c_double)), ("ry", POINTER(
        c_double)), ("rz", POINTER(c_double)), ("vx", POINTER(c_double)), ("vy", POINTER(c_double)), ("vz", POINTER(c_double)), ("fx", POINTER(c_double)), ("fy", POINTER(c_double)), ("fz", POINTER(c_double)), ("rank", c_int), ("npes", c_int), ("comm_time", c_double), ("force_time", c_double), ("overhead", c_double)]


mdsys = _mdsys(natoms=int(raw_list[0]), mass=raw_list[1], epsilon=raw_list[2], sigma=raw_list[3], rcut=raw_list[4], box=raw_list[5], nsteps=int(raw_list[9]), dt=raw_list[10], nfi=0, ekin=0.0, epot=0.0,temp=0.0, rx=array_rx, ry=array_ry, rz=array_rz, vx=array_vx, vy=array_vy, vz=array_vz, fx=array_fx, fy=array_fy, fz=array_fz, rank=0, npes=1, comm_time=0.0, force_time=0.0, overhead=0.0)

buf = create_string_buffer(b"argon_108.xyz")
buf1 = create_string_buffer(b"argon_108.dat")
mdsys.nfi = 0
nprint = 100
omp_dso.force(byref(mdsys))
omp_dso.ekin(byref(mdsys))
print("Starting simulation with {0} atoms for {1} steps.\n".format(
    mdsys.natoms, mdsys.nsteps))
print("     NFI            TEMP            EKIN                 EPOT              ETOT\n")

f1 = open("argon_108.xyz", 'a+')
f2 = open("argon_108.dat", 'a+')
handle_output(mdsys, f1, f2)
mdsys.nfi = 1
for i in range(mdsys.nfi, mdsys.nsteps+1):
    if ((mdsys.nfi % nprint) == 0):
        handle_output(mdsys, f1, f2)
        omp_dso.velverlet_first_half(byref(mdsys))
        omp_dso.force(byref(mdsys))
        omp_dso.velverlet_second_half(byref(mdsys))
        omp_dso.ekin(byref(mdsys))
    mdsys.nfi += 1
omp_dso.finalize()
f2.close()
f1.close()
print("Simulation Done.\n")
