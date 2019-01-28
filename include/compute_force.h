#ifndef __COMPUTE_FORCE__
#define __COMPUTE_FORCE__

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <utilities_ljmd.h>
#include <data_structure.h>

#if defined (_OPENMP)
#include <omp.h>
#else
#define omp_get_wtime() 0
#define omp_get_num_threads() 0
#define omp_get_thread_num() 0
#endif

/* compute kinetic energy */
// static void ekin ( mdsys_t * sys );
void ekin ( mdsys_t * sys );

/* compute forces */
void force ( mdsys_t * sys );


#endif //__COMPUTE_FORCE__
