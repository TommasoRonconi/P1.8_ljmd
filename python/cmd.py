import subprocess
import argparse
import os

parser = argparse.ArgumentParser(prog="ljmd.py", description="Used to calculate distance between particles:", epilog="The program is implemented using omp, mpi and serial verion. You are alo able to run mpi and openmp using the momp.")
parser.add_argument("-i", "--inputfile", help="The mendatory file read by the program as input. It contains program settings e.g number of atoms", dest='input_file', required=True)
# parser.add_argument("-r", "--restfile", help="The file you read you input from from. It contains your arrays, rx, ry,rz e.g number of atoms", dest='rest_file', required=True)
parser.add_argument("-t", "--test", help="You are able to run tests using this command. You have to set to true or false of the value", dest='test',action="store_true")
parser.add_argument("-np", "--num_proc", help="set the number of processes for mpi if not 10 will be the default",dest='npes', action="store")
parser.add_argument("-nt", "--num_thre", help="set the number of threads for omp if not 10 will be the default",dest='nthre', action="store")
parser.add_argument("-v",'--version', action='version', version='%(prog)s 1.0')

group = parser.add_mutually_exclusive_group()
group.add_argument("-s", "--serial", action="store_true", help="run with serial version only",dest="serial")
group.add_argument("-m", "--mpi", action="store_true", help="run with mpi only", dest="mpi")
group.add_argument("-o", "--omp", action="store_true", help="run with omp only", dest="omp")
group.add_argument("-mo", "--momp", action="store_true", help="run with omp + mpi", dest="momp")
args=parser.parse_args()

args.npes = 10
args.nthre = 10
if not (args.npes):
    args.npes = 10

if not (args.nthre):
    args.npes = 10

if(args.serial):
    print("Use  serial", args.serial)
    subprocess.run(["python", "ljmd.py", args.input_file])
elif (args.mpi):
    print("Use  mpi", args.mpi)
    subprocess.Popen(['mpirun', '-np', '4'])
    subprocess.run(["mpirun", "-np", str(args.nproc), "python","ljmd.py", args.input_file])
elif (args.omp):
    print("Use  omp ")
    os.environ["OMP_NUM_THREADS"] = str(args.nthre)
    subprocess.run(["python", "ljmd.py", args.input_file])
elif (args.momp):
    print("Use  mpi + omp: ",args.momp)
    os.environ["OMP_NUM_THREADS"] = str(args.nthre)
    subprocess.run(["mpirun", "-np", str(args.nproc), "python","ljmd.py", args.input_file])
else:
    print("Just decided to run serial version.\n")
    subprocess.run(["python", "ljmd.py"])





