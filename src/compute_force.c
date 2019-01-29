#include <compute_force.h>

#if defined (_OPENMP)
#include <omp.h>
#endif


// =======================================================================


/* static void ekin(mdsys_t *sys) */
void ekin(mdsys_t *sys)
{   
	int i;

	sys->ekin=0.0;
	for (i=0; i<sys->natoms; ++i) {
		sys->ekin += 0.5*mvsq2e*sys->mass*(sys->vx[i]*sys->vx[i] + sys->vy[i]*sys->vy[i] + sys->vz[i]*sys->vz[i]);
	}
	sys->temp = 2.0*sys->ekin/(3.0*sys->natoms-3.0)/kboltz;
	
}


// =======================================================================


/* static void force(mdsys_t *sys)  */
void force(mdsys_t *sys) 
{
  double r,ffac;
  double rx,ry,rz;
  int i, j;
  double epot = 0.0;
  double * fx, *fy, *fz;

  /* zero energy and forces */
#ifdef USE_MPI

  fx = sys->cx;
  fy = sys->cy;
  fz = sys->cz;

  /* communicate to all the processes previous step update of positions */
  MPI_Bcast( sys->rx, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD );
  MPI_Bcast( sys->ry, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD );
  MPI_Bcast( sys->rz, sys->natoms, MPI_DOUBLE, 0, MPI_COMM_WORLD );
  
#else
  /* sys->epot=0.0; */
  fx = sys->fx;
  fy = sys->fy;
  fz = sys->fz;
#endif //USE_MPI
  azzero( fx, sys->natoms );
  azzero( fy, sys->natoms );
  azzero( fz, sys->natoms );

  /* #if defined (_OPENMP) */
  /* #pragma omp parallel */
  /* sys->nthreads = omp_get_num_threads(); */
  /* #else */
  /* sys->nthreads = 1; */
  /* #endif */

  /* loop to compute forces */
#if defined (_OPENMP)
#pragma omp parallel for private(i, j, rx, ry, rz, r, ffac) reduction(+:epot)
#endif
  for( i = sys->rank; i < (sys->natoms); i += sys->npes ) {
    for(j=0; j < (sys->natoms); ++j) {

      /* particles have no interactions with themselves */
      if (i==j) continue;
            
      /* get distance between particle i and j */
      rx=pbc(sys->rx[i] - sys->rx[j], 0.5*sys->box);
      ry=pbc(sys->ry[i] - sys->ry[j], 0.5*sys->box);
      rz=pbc(sys->rz[i] - sys->rz[j], 0.5*sys->box);
      r = sqrt(rx*rx + ry*ry + rz*rz);
      
      /* compute force and energy if within cutoff */
      if (r < sys->rcut) {
	ffac = -4.0*sys->epsilon*(-12.0*pow(sys->sigma/r,12.0)/r
				  +6*pow(sys->sigma/r,6.0)/r);
	
	epot += 0.5*4.0*sys->epsilon*(pow(sys->sigma/r,12.0)
				      -pow(sys->sigma/r,6.0));
	fx[i] += rx/r*ffac;
	fy[i] += ry/r*ffac;
	fz[i] += rz/r*ffac;
      }
    }
  }  
    
#ifdef USE_MPI    
  MPI_Reduce( fx, sys->fx, sys->natoms, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD );
  MPI_Reduce( fy, sys->fy, sys->natoms, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD );
  MPI_Reduce( fz, sys->fz, sys->natoms, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD );
  MPI_Reduce( &epot, &sys->epot, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD );
#else
  sys->epot = epot;
#endif //USE_MPI
  
  return;

}


// =======================================================================
