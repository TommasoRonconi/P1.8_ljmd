import argparse

parser = argparse.ArgumentParser(prog="ljmd.py", description="Used to calculate distance between particles:", epilog="The program is implemented using omp, mpi and serial verion. You are alo able to run mpi and openmp using the momp.")
parser.add_argument("-i", "--inputfile", help="The file you read you input from from. It contains program settings e.g number of atoms", dest='input_file', required=True)
parser.add_argument("-r", "--restfile", help="The file you read you input from from. It contains your arrays, rx, ry,rz e.g number of atoms", dest='rest_file', required=True)
parser.add_argument("-t", "--test", help="You are able to run tests using this command. You have to set to true or false of the value", dest='test',action="store_true")
parser.add_argument("-v",'--version', action='version', version='%(prog)s 1.0')

group = parser.add_mutually_exclusive_group()
group.add_argument("-s", "--serial", action="store_true", help="run with serial version only", default=True)
group.add_argument("-m", "--mpi", action="store_true", help="run with mpi only")
group.add_argument("-o", "--omp", action="store_true", help="run with omp only")
group.add_argument("-mo", "--mop", action="store_true", help="run with omp + mpi ")
args=parser.parse_args()

print(args.test)




