"""
@authors: Herbert Nguuruwe
@Team: Matteo, Thomaso, Jesus 

"""
from ctypes import *
import argparse

#dynamic libraries
mpi_dso = CDLL("../Obj-parallel/libLJMD-mpi.so")
dso = CDLL("../Obj-serial/libLJMD.so")

#Create struct
class _mdsys(Structure):
    """
    The struct class same structure from C.
    """
    _fields_ = [("natoms", c_int), ("nfi", c_int), ("nsteps", c_int), ("dt", c_double), ("mass", c_double),  ("epsilon", c_double),  ("sigma", c_double), ("box", c_double), ("rcut", c_double), ("ekin", c_double), ("epot", c_double), ("temp", c_double), ("rx", POINTER(c_double)), ("ry", POINTER(c_double)),("rz", POINTER(c_double)), ("vx", POINTER(c_double)), ("vy", POINTER(c_double)), ("vz", POINTER(c_double)), ("fx", POINTER(c_double)), ("fy", POINTER(c_double)), ("fz", POINTER(c_double)), ("rank", c_int), ("npes", c_int)]

#Create struct
class _mpi_mdsys(Structure):
    _fields_ = [("natoms", c_int), ("nfi", c_int), ("nsteps", c_int), ("dt", c_double), ("mass", c_double),  ("epsilon", c_double),  ("sigma", c_double), ("box", c_double), ("rcut", c_double), ("ekin", c_double), ("epot", c_double), ("temp", c_double), ("rx", POINTER(c_double)), ("ry", POINTER(c_double)),("rz", POINTER(c_double)), ("vx", POINTER(c_double)), ("vy", POINTER(c_double)), ("vz", POINTER(c_double)), ("cx", POINTER(c_double)), ("cy", POINTER(c_double)), ("cz", POINTER(c_double)), ("fx", POINTER(c_double)), ("fy", POINTER(c_double)), ("fz", POINTER(c_double)), ("rank", c_int), ("npes", c_int)]

#pass object type
dso.python_output.argtypes = [POINTER(_mdsys)]
dso.python_output.restype = _mdsys

#Read from input file
def read_inp(filename):
    """
    @param filename: file name to read from the inp file
    Read the file for input file 
    """
    list = []
    with open(filename, 'r') as f:
        for line in f:
            values = [s for s in line.split()]
            try:
                list.append(float(values[0]))
            except ValueError:
                list.append(values[0])
    f.closed
    return list

#Read from rest file
def read_rest(filename, start, end):
    """
    @param filename: file to read from
    @param start: starting point to read from 
    @param end: the end of file to read from
    """
    from itertools import islice
    x, y, z = [], [], []
    with open(filename, 'r') as f:
        for line in islice(f, start, end):
            values = [float(s) for s in line.split()]
            x.append(float(values[0]))
            y.append(float(values[1]))
            z.append(float(values[2]))
    f.closed
    return x, y, z

#load the array from a list to
#data structure array
def get_array(list2, array):
    """
    @param list: list to be passed to any array
    @param array: array to receive values from list
    """
    for i in range(len(list2)):
        array[i] = list2[i]
    return array

def init_force(array):
    """
    initialize all force vallues values to zero
    @param array: f{x|y|z}array values
    """
    for i in range(len(raw_list)):
        array[i] = 0.0
    return array

def handle_output(_output, trajfile, ergfile):
    """
    @param _output: returned data structure from c
    @param ergfile:  output to write energy  
    @param trajfile: output to trajectory file
    @description: Function will receive mdssys data
    structure to be printed in python
    """
    print(_output.nfi, "\t", _output.temp, "\t", _output.ekin, "\t",  _output.epot, "\t", _output.ekin + _output.epot)
    ergfile.write("{:d} \t{:f} \t{:f}\t{:f}\t {:f}\n".format(_output.nfi,_output.temp, _output.ekin, _output.epot, _output.ekin + _output.epot))
    #trajfile.write("{0}\n nfi={1} etot={2}\n".format(_output.natoms, _output.nfi, _output.ekin + _output.epot))
    # for i in range(_output.natoms+1):
    #      trajfile.write("Ar  {:f} \t {:f} \t{:f}\n".format(_output.rx[i], _output.ry[i], _output.rz[i]))


#get elements from file to the list
conf_dir = "../examples/"
inp_path = conf_dir + "argon_108.inp"

tmp_sys = _mpi_mdsys()
mpi_dso.initialize.argtypes = [POINTER(_mpi_mdsys)]
mpi_dso.initialize.restype = None
mpi_dso.initialize(byref(tmp_sys))


if (tmp_sys.rank == 0) :

    raw_list = read_inp(inp_path)
    rest_path = conf_dir + raw_list[6]
 
    #calculate indexes
    num_atoms = int(raw_list[0])
    r_start, r_end = 0, num_atoms
    v_start, v_end = num_atoms, 2*num_atoms

    #return data from file to lists
    rx, ry, rz = read_rest(rest_path, r_start, r_end)
    vx, vy, vz = read_rest(rest_path, v_start, v_end)

    #element size
    elem_size = c_double*num_atoms
    mpi_sys = _mpi_mdsys(natoms=int(raw_list[0]), mass=raw_list[1], epsilon=raw_list[2], sigma=raw_list[3], rcut=raw_list[4], box=raw_list[5], nsteps=int(raw_list[9]), dt=raw_list[10], nfi=0, ekin=0.0, epot=0.0, temp=0.0, rank=tmp_sys.rank, npes=tmp_sys.npes)

mpi_dso.broadcast_values.argtypes = [POINTER(_mpi_mdsys)]
mpi_dso.broadcast_values.restype = None
mpi_dso.broadcast_values(byref(mpi_sys))

#create empty elements
array_rx = (c_double * mpi_sys.natoms)()
array_ry = (c_double * mpi_sys.natoms)()
array_rz = (c_double * mpi_sys.natoms)()
array_vx = (c_double * mpi_sys.natoms)()
array_vy = (c_double * mpi_sys.natoms)()
array_vz = (c_double * mpi_sys.natoms)()
array_cx = (c_double * mpi_sys.natoms)()
array_cy = (c_double * mpi_sys.natoms)()
array_cz = (c_double * mpi_sys.natoms)()
array_fx = (c_double * mpi_sys.natoms)()
array_fy = (c_double * mpi_sys.natoms)()
array_fz = (c_double * mpi_sys.natoms)()

mpi_sys.rx = (c_double * mpi_sys.natoms)()
mpi_sys.ry = (c_double * mpi_sys.natoms)()
mpi_sys.rz = (c_double * mpi_sys.natoms)()
mpi_sys.vx = (c_double * mpi_sys.natoms)()
mpi_sys.vy = (c_double * mpi_sys.natoms)()
mpi_sys.vz = (c_double * mpi_sys.natoms)()
mpi_sys.cx = (c_double * mpi_sys.natoms)()
mpi_sys.cy = (c_double * mpi_sys.natoms)()
mpi_sys.cz = (c_double * mpi_sys.natoms)()
mpi_sys.fx = (c_double * mpi_sys.natoms)()
mpi_sys.fy = (c_double * mpi_sys.natoms)()
mpi_sys.fz = (c_double * mpi_sys.natoms)()

if (mpi_sys.rank == 0) :

    #load vectors from th r file
    array_rx = get_array(rx, array_rx)
    array_ry = get_array(ry, array_ry)
    array_rz = get_array(rz, array_rz)
    array_vx = get_array(vx, array_vx)
    array_vy = get_array(vy, array_vy)
    array_vz = get_array(vz, array_vz)
    array_fx = init_force(array_fx)
    array_fy = init_force(array_fy)
    array_fz = init_force(array_fz)
    array_cx = init_force(array_cx)
    array_cy = init_force(array_cy)
    array_cz = init_force(array_cz)
    mpi_sys.rx=array_rx
    mpi_sys.rx=array_ry
    mpi_sys.rx=array_rz
    mpi_sys.vx=array_vx
    mpi_sys.vy=array_vy
    mpi_sys.vz=array_vz
    mpi_sys.fx=array_fx
    mpi_sys.fy=array_fy
    mpi_sys.fz=array_fz
    mpi_sys.cx=array_cx
    mpi_sys.cy=array_cy
    mpi_sys.cz=array_cz

mpi_dso.broadcast_arrays.argtypes = [POINTER(_mpi_mdsys)]
mpi_dso.broadcast_arrays.restype = None
mpi_dso.broadcast_arrays(byref(mpi_sys))

mpi_sys.nfi = 0
nprint = 100

mpi_dso.force.argtypes = [POINTER(_mpi_mdsys)]
mpi_dso.force.restype = None
mpi_dso.force(byref(mpi_sys))
mpi_dso.ekin.argtypes = [POINTER(_mpi_mdsys)]
mpi_dso.ekin.restype = None
mpi_dso.ekin(byref(mpi_sys))

# buf = create_string_buffer(b"argon_108.xyz")
# buf1 = create_string_buffer(b"argon_108.dat")

if (mpi_sys.rank == 0):
    f1 = open("argon_108.xyz", 'a+')
    f2 = open("argon_108.dat", 'a+')
    print("Starting simulation with {0} atoms for {1} steps.\n".format(mpi_sys.natoms, mpi_sys.nsteps))
    print("     NFI            TEMP            EKIN                 EPOT              ETOT\n")
    handle_output(mpi_sys, f1, f2)

# mpi_mdsys.nfi = 1
# for i in range(mpi_mdsys.nfi, mpi_mdsys.nsteps+1):
#     if ((mpi_mdsys.nfi % nprint) == 0):
#         handle_output(mpi_mdsys, f1, f2)
#         mpi_dso.velverlet_first_half(byref(mpi_mdsys))
#         mpi_dso.force(byref(mpi_mdsys))
#         mpi_dso.velverlet_second_half(byref(mpi_mdsys))
#         mpi_dso.ekin(byref(mpi_mdsys))
    
# if (tmp_sys.rank == 0):
#     print("Simulation Done.\n")
#     f1.close()
#     f2.close()
#     print(":f\t:f\t:f\n", mpi_mdsys.overhead,mpi_mdsys.comm_time, mpi_mdsys.force_time)

# mdsys.nfi = 0
# nprint = 100
# mpi_dso.force(byref(mdsys))
# mpi_dso.ekin(byref(mdsys))
# dso.force(byref(mdsys))
# dso.ekin(byref(mdsys))

# print("Starting simulation with {0} atoms for {1} steps.\n".format(mdsys.natoms, mdsys.nsteps))
# print("     NFI            TEMP            EKIN                 EPOT              ETOT\n")

# f1 = open("argon_108.xyz", 'a+')
# f2 = open("argon_108.dat", 'a+')
# handle_output(mdsys, f1, f2)
# mdsys.nfi = 1
# for i in range(mdsys.nfi, mdsys.nsteps+1):
#     if ((mdsys.nfi % nprint) == 0):
#         handle_output(mdsys, f1, f2)
#         mpi_dso.velverlet_first_half(byref(mdsys))
#         mpi_dso.force(byref(mdsys))
#         mpi_dso.velverlet_second_half(byref(mdsys))
#         mpi_dso.ekin(byref(mdsys))
#     mdsys.nfi += 1
# mpi_dso.finalize()
# f2.close()
# f1.close()
# print("Simulation Done.\n")


#dso.python_output(byref(mdsys),'argon_108.xyz', 'argon_108.dat')
#dso.output(mdsys, 'argon_108.xyz', 'argon_108.dat')
#mpi_dso.free_sys_arrays(byref(mpi_sys))
mpi_dso.finalize()
