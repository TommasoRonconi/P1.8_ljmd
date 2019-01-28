"""
working on the python interface
"""
from ctypes import *


#impotrt DSo
dso = CDLL("../Obj-serial/libLJMD.so")

#Create struct
class _mdsys(Structure):
    _fields_ = [("natoms", c_int), ("nfi", c_int), ("nsteps", c_int), ("dt", c_double), ("mass", c_double),  ("epsilon", c_double),  ("sigma", c_double), ("box", c_double), ("rcut", c_double), ("ekin", c_double), ("epot", c_double),("temp", c_double), ("rx", POINTER(c_double)), ("ry", POINTER(c_double)), ("rz", POINTER(c_double)), ("vx", POINTER(c_double)), ("vy", POINTER(c_double)), ("vz", POINTER(c_double)), ("fx", POINTER(c_double)), ("fy", POINTER(c_double)), ("fz", POINTER(c_double))]


#pass object type
dso.test.argtypes = [POINTER(_mdsys)]


#Read from input file
def read_inp(filename):
    """
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


def output(print_mdsys, ergfile, trajfile):
    print(print_mdsys.nfi, " ", print_mdsys.temp, " ",
          print_mdsys.ekin, "", print_mdsys.epot, "", print_mdsys.epot)
# printf("% 8d % 20.8f % 20.8f % 20.8f % 20.8f\n", sys->nfi, sys->temp, sys->ekin, sys->epot, sys->ekin + sys->epot)
    with open(ergfile,"w") as f:
        f.write()

#get elements from file to the list
list = read_inp("../examples/argon_108.inp")

#calculate indexes
num_atoms = int(list[0])
r_start, r_end = 0, num_atoms
v_start, v_end = num_atoms, 2*num_atoms

#load the array from a list to
#data structure array
def get_array(list, array):
    """
    """
    for i in range(len(list)):
        array[i] = list[i]
    return array


def init_force(array):
    """
    """
    for i in range(len(list)):
        array[i] = 0.0
    return array


#return data from file to lists
rx, ry, rz = read_rest("../examples/argon_108.rest", r_start, r_end)
vx, vy, vz = read_rest("../examples/argon_108.rest", v_start, v_end)

#element size
elem_size = c_double*num_atoms

#create empty elements
array_rx = elem_size()
array_ry = elem_size()
array_rz = elem_size()
array_vx = elem_size()
array_vy = elem_size()
array_vz = elem_size()
array_fx = elem_size()
array_fy = elem_size()
array_fz = elem_size()

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

# mdsys = _mdsys(natoms=108, nfi=100, nsteps=1000, mass=600, epsilon=200, sigma=78, rcut=90.00, box=500,
#  dt = 8.9, ekin = 0.0, epot = 0.0, temp = 0.0, rx=array_rx,
# ry = array_ry, rz=array_rz, vx=array_vx, vy=array_vy, vz=array_vz)

mdsys = _mdsys(natoms=int(list[0]), mass=list[1], epsilon=list[2], sigma=list[3], rcut=list[4], box=list[5],
               nsteps=int(list[9]), dt=list[10], nfi=0, ekin=0.0, epot=0.0, temp=0.0, rx=array_rx,ry=array_ry,
               rz=array_rz, vx=array_vx, vy=array_vy, vz=array_vz, fx=array_fx, fy=array_fy, fz=array_fz)


for i in range(10):
    print('{0}   {1}  {2}\n'.format(mdsys.fx[i], mdsys.fy[i], mdsys.fz[i]))

print("\n\n\n")
dso.velverlet_first_half(byref(mdsys))
for i in range(10):
    print('{0}   {1}  {2}\n'.format(mdsys.rx[i], mdsys.ry[i], mdsys.rz[i]))
    print("\n\n")
    print('{0}   {1}  {2}\n'.format(mdsys.rx[i], mdsys.ry[i], mdsys.rz[i]))


# print(mdsys.natoms)
# print(mdsys.mass)
# print(mdsys.epsilon)
# print(mdsys.sigma)
# print(mdsys.rcut)
# print(mdsys.box)
# print(mdsys.nsteps)
# print(mdsys.dt)
# print(mdsys.rx[0])

#dso.test(byref(mdsys))
# dso.azzero(mdsys.fx, mdsys.natoms)
# dso.azzero(mdsys.fy, mdsys.natoms)
# dso.azzero(mdsys.fz, mdsys.natoms)
# print("Starting simulation with {} atoms for {} steps.\n",
#       mdsys.natoms, mdsys.nsteps)
# print("     NFI            TEMP            EKIN                 EPOT              ETOT\n")
# dso.python_output(byref(mdsys), 'argon_108.xyz', 'argon_108.dat')
# dso.force(byref(mdsys))
# dso.ekin(byref(mdsys))
# mdsys.nfi = 1
# nprint =100
# for i in range(mdsys.nfi,mdsys.nsteps):
#     if ((mdsys.nfi % nprint) == 0):
#         dso.python_output(byref(mdsys), 'argon_108.xyz', 'argon_108.dat')
#         dso.velverlet_first_half(byref(mdsys))
#         dso.force(byref(mdsys))
#         dso.velverlet_second_half(byref(mdsys))
#         dso.ekin(byref(mdsys))

# print("Simulation Done.\n")


#dso.python_output(byref(mdsys),'argon_108.xyz', 'argon_108.dat')
#dso.output(mdsys, 'argon_108.xyz', 'argon_108.dat')
