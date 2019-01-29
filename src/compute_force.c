#include <compute_force.h>
#include <potentials.h>

#if defined (_OPENMP)
#include <omp.h>
#endif

/*Using Third Law of Newton*/
#ifdef THIRD_LAW
#define J_BEGIN() i+1	
#define HALF_FACTOR() 2
#else
#define J_BEGIN() 0
#define HALF_FACTOR() 1
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

  return;
	
}


// =======================================================================


/* static void force(mdsys_t *sys)  */
void force(mdsys_t *sys) 
{
  double r, rr, rrc, ffac;
  double rx,ry,rz;
  int i, j;
  double epot = 0.0;
  double * fx, *fy, *fz;

  double c12, c6;
  double r6, rinv;

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

  c12 = C12(); 
  c6 = C6();
  rrc = RRC();

  /* loop to compute forces */
#if defined (_OPENMP)
#pragma omp parallel for private(i, j, rx, ry, rz, r, ffac) reduction(+:epot)
#endif
  for( i = sys->rank; i < (sys->natoms); i += sys->npes ) {
    for(j=J_BEGIN(); j < (sys->natoms); ++j) {
            
      /* get distance between particle i and j */
      rx=pbc(sys->rx[i] - sys->rx[j], 0.5*sys->box);
      ry=pbc(sys->ry[i] - sys->ry[j], 0.5*sys->box);
      rz=pbc(sys->rz[i] - sys->rz[j], 0.5*sys->box);     
      rr = RR();
      /* compute force and energy if within cutoff */
	  
      if (rr < rrc) {
	r = R();
	rinv=RINV(); 
	r6 = R6(); 

	ffac = FFAC();		
	epot += HALF_FACTOR()*EPOT();


#ifdef THIRD_LAW
	fx[i] += rx/r*ffac; fx[j] -= rx/r*ffac;
	fy[i] += ry/r*ffac; fy[j] -= ry/r*ffac;
	fz[i] += rz/r*ffac; fz[j] -= rz/r*ffac;
#else
	fx[i] += rx/r*ffac;
	fy[i] += ry/r*ffac;
	fz[i] += rz/r*ffac;
#endif

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
