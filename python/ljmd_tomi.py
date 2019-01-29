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
    _fields_ = [("natoms", c_int), ("nfi", c_int), ("nsteps", c_int), ("dt", c_double), ("mass", c_double),  ("epsilon", c_double),  ("sigma", c_double), ("box", c_double), ("rcut", c_double), ("ekin", c_double), ("epot", c_double), ("temp", c_double), ("rx", POINTER(c_double)), ("ry", POINTER(c_double)),("rz", POINTER(c_double)), ("vx", POINTER(c_double)), ("vy", POINTER(c_double)), ("vz", POINTER(c_double)), ("fx", POINTER(c_double)), ("fy", POINTER(c_double)), ("fz", POINTER(c_double)), ("rank", c_int), ("npes", c_int), ("comm_time", c_double), ("force_time", c_double), ("overhead", c_double)]

#Create struct
class _mpi_mdsys(Structure):
    _fields_ = [("natoms", c_int), ("nfi", c_int), ("nsteps", c_int), ("dt", c_double), ("mass", c_double),  ("epsilon", c_double),  ("sigma", c_double), ("box", c_double), ("rcut", c_double), ("ekin", c_double), ("epot", c_double), ("temp", c_double), ("rx", POINTER(c_double)), ("ry", POINTER(c_double)),("rz", POINTER(c_double)), ("vx", POINTER(c_double)), ("vy", POINTER(c_double)), ("vz", POINTER(c_double)), ("cx", POINTER(c_double)), ("cy", POINTER(c_double)), ("cz", POINTER(c_double)), ("fx", POINTER(c_double)), ("fy", POINTER(c_double)), ("fz", POINTER(c_double)), ("rank", c_int), ("npes", c_int), ("comm_time", c_double), ("force_time", c_double), ("overhead", c_double)]

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

# init arrays
def init_array(array):
    """
    initialize all force vallues values to zero
    @param array: f{x|y|z}array values
    """
    for i in range(len(raw_list)):
        array[i] = 0.0
    return array

#handle the output 
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
    trajfile.write("{0}\n nfi={1} etot={2}\n".format(_output.natoms, _output.nfi, _output.ekin + _output.epot))
    for i in range(_output.natoms+1):
         trajfile.write("Ar  {:f} \t {:f} \t{:f}\n".format(_output.rx[i], _output.ry[i], _output.rz[i]))


#get elements from file to the list
conf_dir = "../examples/"
inp_path = conf_dir + "argon_108.inp"


mpi_sys = _mpi_mdsys(natoms=0, mass=0.0, epsilon=0.00, sigma=0.0, rcut=0.0, box=0.0, nsteps=0, dt=0.0, nfi=0, ekin=0.0, epot=0.0, temp=0.0)
tmp_sys = _mpi_mdsys()
elem_size = c_double*108
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
    mpi_sys = _mpi_mdsys(natoms=int(raw_list[0]), mass=raw_list[1], epsilon=raw_list[2], sigma=raw_list[3], rcut=raw_list[4], box=raw_list[5], nsteps=int(raw_list[9]), dt=raw_list[10], nfi=0, ekin=0.0, epot=0.0, temp=0.0, rank=tmp_sys.rank, npes=tmp_sys.npes, comm_time=0.0, force_time=0.0, overhead=0.0)
    
mpi_dso.broadcast_values(byref(mpi_sys))


#create empty elements
elem_size = c_double*108
array_rx = elem_size()
array_ry = elem_size()
array_rz = elem_size()
array_vx = elem_size()
array_vy = elem_size()
array_vz = elem_size()
array_cx = elem_size()
array_cy = elem_size()
array_cz = elem_size()
array_fx = elem_size()
array_fy = elem_size()
array_fz = elem_size()


if (tmp_sys.rank == 0):
    #load vectors from th r file
    array_rx = get_array(rx, array_rx)
    array_ry = get_array(ry, array_ry)
    array_rz = get_array(rz, array_rz)
    array_vx = get_array(vx, array_vx)
    array_vy = get_array(vy, array_vy)
    array_vz = get_array(vz, array_vz)
    array_fx = init_array(array_fx)
    array_fy = init_array(array_fy)
    array_fz = init_array(array_fz)
    array_cx = init_array(array_cx)
    array_cy = init_array(array_cy)
    array_cz = init_array(array_cz)
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

print(mpi_sys.rank," " ,mpi_sys.vx[0])
mpi_dso.broadcast_arrays(byref(mpi_sys))
print(mpi_sys.mass)
nprint = 100

mpi_dso.force(byref(mpi_sys))
mpi_dso.ekin(byref(mpi_sys))
if(tmp_sys.rank == 0):
    f1 = open("argon_108.xyz", 'a+')
    f2 = open("argon_108.dat", 'a+')
    print("Starting simulation with {0} atoms for {1} steps.\n".format( mpi_sys.natoms, mpi_sys.nsteps))
    print("     NFI            TEMP            EKIN                 EPOT              ETOT\n")
    handle_output(mpi_sys, f1, f2)

mpi_sys.nfi = 1
for i in range(mpi_sys.nfi, tmp_sys.nsteps+1):
    if ((mpi_sys.nfi % nprint) == 0):
        handle_output(mpi_sys, f1, f2)
        mpi_dso.velverlet_first_half(byref(mpi_sys))
        mpi_dso.force(byref(tmp_sys))
        mpi_dso.velverlet_second_half(byref(mpi_sys))
        mpi_dso.ekin(byref(mpi_sys))

if (tmp_sys.rank == 0):
    print("Simulation Done.\n")
    f1.close()
    f2.close()
    print(":f\t:f\t:f\n", mpi_sys.overhead,mpi_sys.comm_time, mpi_sys.force_time)

mpi_dso.finalize()
