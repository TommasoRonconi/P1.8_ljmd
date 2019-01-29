#ifndef __DATA_STRUCTURE__
#define __DATA_STRUCTURE__

#include <stdlib.h>

#if defined (_OPENMP)
#include <omp.h>
#endif

/* structure to hold the complete information 
 * about the MD system */
struct _mdsys
{	
	int nthreads;
    int natoms, nfi, nsteps;
    double time_omp;
    double dt, mass, epsilon, sigma, box, rcut;
    double ekin, epot, temp;
    double *rx, *ry, *rz;
    double *vx, *vy, *vz;
    double *fx, *fy, *fz;
};

typedef struct _mdsys mdsys_t;

/* function to allocate rx, ry, rz, vx, vy, vz, fx, fy, fz arrays on the heap */
void allocate_sys_arrays ( mdsys_t * const sys );

/* free rx, ry, rz, vx, vy, vz, fx, fy, fz arrays memory from the heap*/
void free_sys_arrays ( mdsys_t * const sys );

#endif //__DATA_STRUCTURE__
