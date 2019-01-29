#ifndef __INPUT__
#define __INPUT__

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#ifdef USE_MPI
#include <mpi.h>
#endif //USE_MPI
#include <ctype.h>
#include <utilities_ljmd.h>
#include<data_structure.h>

int get_a_line(FILE *fp, char *buf);

int populate_data(FILE * fp, char (*line)[BLEN], char (*restfile)[BLEN], char (*trajfile)[BLEN], char (*ergfile)[BLEN], mdsys_t * sys, int * nprint);

void broadcast_values ( mdsys_t * sys );

int readRestart( mdsys_t * sys, char restfile[BLEN] );

void broadcast_arrays ( mdsys_t * sys );


#endif //__INPUT__
