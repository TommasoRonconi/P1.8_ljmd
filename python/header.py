"""
@Authors:Jesus Espinoza, Herbert Nguruwe, Tommaso Ronconi, Matteo Zampieri
"""
from ctypes import *
import argparse
import sys 


#dynamic libraries
mpi_dso = CDLL("../Obj-parallel/libLJMD-mpi.so")
dso = CDLL("../Obj-serial/libLJMD.so")
omp_dso = CDLL("../Obj-parallel/libLJMD-omp.so")
momp = CDLL("../Obj-parallel/libLJMD-mpi-omp.so")

#inputfile = "argon_108.inp"
inputfile = sys.argv[1]

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


def init_array(array):
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
    print(_output.nfi, "\t", _output.temp, "\t", _output.ekin,
          "\t",  _output.epot, "\t", _output.ekin + _output.epot)
    ergfile.write("{:d} \t{:f} \t{:f}\t{:f}\t {:f}\n".format(
        _output.nfi, _output.temp, _output.ekin, _output.epot, _output.ekin + _output.epot))
    trajfile.write("{0}\n nfi={1} etot={2}\n".format(
        _output.natoms, _output.nfi, _output.ekin + _output.epot))
    for i in range(_output.natoms+1):
         trajfile.write("Ar  {:f} \t {:f} \t{:f}\n".format(
             _output.rx[i], _output.ry[i], _output.rz[i]))



#get elements from file to the list
conf_dir = "../examples/"
inp_path = conf_dir + inputfile
raw_list = read_inp(inp_path)
rest_path = conf_dir + raw_list[6]

print(raw_list)
#calculate indexes
num_atoms = int(raw_list[0])
r_start, r_end = 0, num_atoms
v_start, v_end = num_atoms, 2*num_atoms

#return data from file to lists
rx, ry, rz = read_rest(rest_path, r_start, r_end)
vx, vy, vz = read_rest(rest_path, v_start, v_end)

#element size
elem_size = c_double*num_atoms

#create empty elements
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


