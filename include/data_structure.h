#ifndef __DATA_STRUCTURE__
#define __DATA_STRUCTURE__

#include <stdlib.h>
#ifdef USE_MPI
#include <mpi.h>
#endif //USE_MPI

#if defined (_OPENMP)
#include <omp.h>
#endif

/* structure to hold the complete information 
 * about the MD system */
struct _mdsys
{
  int natoms, nfi, nsteps;
  double dt, mass, epsilon, sigma, box, rcut;
  double ekin, epot, temp;
  double *rx, *ry, *rz;
  double *vx, *vy, *vz;
#ifdef USE_MPI
  double *cx, *cy, *cz;
#endif //USE_MPI
  double *fx, *fy, *fz;

  /* variables to manage MPI parallelization */
  int rank, npes;

  /* variables to manage OpenMP parallelization */
  int nthreads;
};

typedef struct _mdsys mdsys_t;

/* Inititalization function */
void initialize ( mdsys_t * const sys );

/* Finalization function */
void finalize ();

/* function to allocate rx, ry, rz, vx, vy, vz, fx, fy, fz arrays on the heap */
void allocate_sys_arrays ( mdsys_t * const sys );

/* free rx, ry, rz, vx, vy, vz, fx, fy, fz arrays memory from the heap*/
void free_sys_arrays ( mdsys_t * const sys );

#endif //__DATA_STRUCTURE__
