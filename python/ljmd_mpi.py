"""
@Authors:Jesus Espinoza, Herbert Nguruwe, Tommaso Ronconi, Matteo Zampieri
"""
from ctypes import *
import argparse
from header import * 

#Create struct
class _mpi_mdsys(Structure):
    _fields_ = [("natoms", c_int), ("nfi", c_int), ("nsteps", c_int), ("dt", c_double), ("mass", c_double), 
     ("epsilon", c_double),  ("sigma", c_double), ("box", c_double), ("rcut", c_double), ("ekin", c_double), 
     ("epot", c_double), ("temp", c_double), ("rx", POINTER(c_double)), ("ry", POINTER(c_double)),
     ("rz", POINTER(c_double)), ("vx", POINTER(c_double)), ("vy", POINTER(c_double)), ("vz", POINTER(c_double)), 
     ("cx", POINTER(c_double)), ("cy", POINTER(c_double)), ("cz", POINTER(c_double)), ("fx", POINTER(c_double)), 
     ("fy", POINTER(c_double)), ("fz", POINTER(c_double)), ("rank", c_int), ("npes", c_int)]

#passed as input file
inp_path = conf_dir + "argon_108.inp"

mpi_sys = _mpi_mdsys(natoms=0, mass=0.0, epsilon=0.00, sigma=0.0, rcut=0.0, box=0.0, nsteps=0, dt=0.0, nfi=0, ekin=0.0, epot=0.0, temp=0.0)
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
mpi_dso.velverlet_first_half.argtypes = [POINTER(_mpi_mdsys)]
mpi_dso.velverlet_second_half.argtypes = [POINTER(_mpi_mdsys)]

if (mpi_sys.rank == 0):
    f1 = open(raw_list[7], 'a+')
    f2 = open(raw_list[8], 'a+')
    print("Starting simulation with {0} atoms for {1} steps.\n".format(mpi_sys.natoms, mpi_sys.nsteps))
    print("     NFI            TEMP            EKIN                 EPOT              ETOT\n")
    handle_output(mpi_sys, f1, f2)

mpi_sys.nfi = 1

for i in range(1, mpi_sys.nsteps+1):
    if ((mpi_sys.nfi % nprint) == 0):
        if (mpi_sys.rank == 0):
            handle_output(mpi_sys, f1, f2)
    mpi_dso.velverlet_first_half(byref(mpi_sys))
    mpi_dso.force(byref(mpi_sys))
    mpi_dso.velverlet_second_half(byref(mpi_sys))
    mpi_dso.ekin(byref(mpi_sys))
    mpi_sys.nfi += 1

if (mpi_sys.rank == 0):
    print("Simulation Done.\n")
    f1.close()
    f2.close()

mpi_dso.finalize()
