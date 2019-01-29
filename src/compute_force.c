#include <compute_force.h>

/*Using Third Law of Newton*/
#ifdef THIRD_LAW
#define J_BEGIN() i+1	
#define HALF_FACTOR() 2
#else
#define J_BEGIN() 0
#define HALF_FACTOR() 1
#endif

/*Avoiding expensive math*/ 
#ifdef AVOID_MATH
#define FFAC() (12.0*c12*r6 - 6.0*c6)*r6*rinv
#define EPOT() 0.5*r6*(c12*r6 - c6)
#define  C12() 4.0*sys->epsilon*pow(sys->sigma,12.0)
#define  C6()  4.0*sys->epsilon*pow(sys->sigma,6.0)
#define  RRC() sys->rcut * sys->rcut
#define RR() rx*rx + ry*ry + rz*rz
#define R() sqrt(rr)
#define RINV() 1.0/r
#define R6() rinv*rinv*rinv*rinv*rinv*rinv
#else
#define FFAC() -4.0*sys->epsilon*(-12.0*pow(sys->sigma/rr,12.0)/rr + 6*pow(sys->sigma/rr,6.0)/rr)
#define EPOT() 0.5*4.0*sys->epsilon*(pow(sys->sigma/rr,12.0) - pow(sys->sigma/rr,6.0))
#define  C12() 0
#define  C6() 0
#define  RRC() sys->rcut
#define RR() sqrt(rx*rx + ry*ry + rz*rz)
#define R() rr
#define RINV() 0
#define R6() 0
#endif

// =======================================================================


/* static void ekin(mdsys_t *sys) */
void ekin(mdsys_t *sys)
{   
  int i;

  sys->ekin=0.0;
  for (i=0; i<sys->natoms; ++i) {
    sys->ekin += 0.5*mvsq2e*sys->mass * \
    (sys->vx[i]*sys->vx[i] + sys->vy[i]*sys->vy[i] + sys->vz[i]*sys->vz[i]);
  }
  sys->temp = 2.0*sys->ekin/(3.0*sys->natoms-3.0)/kboltz;
  
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
  double time1, time2;

  fx = sys->cx;
  fy = sys->cy;
  fz = sys->cz;

  time1 = MPI_Wtime();
  /* communicate to all the processes previous step update of positions */
  MPI_Bcast( sys->rx, sys->natoms, MPI_DOUBLE, 0, sys->comm );
  MPI_Bcast( sys->ry, sys->natoms, MPI_DOUBLE, 0, sys->comm );
  MPI_Bcast( sys->rz, sys->natoms, MPI_DOUBLE, 0, sys->comm );
  time2 = MPI_Wtime();
  sys->comm_time += time2 - time1;
  
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



  for( i = sys->rank; i < (sys->natoms); i += sys->npes ) {
    for(j=J_BEGIN(); j < (sys->natoms); ++j) {

      /* particles have no interactions with themselves */
      if (i==j) continue;
            
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
	
		// fx[i] += rx/r*ffac;
		// fy[i] += ry/r*ffac;
		// fz[i] += rz/r*ffac;


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
  time1 = MPI_Wtime();
  sys->force_time += time1 - time2;
  MPI_Reduce( fx, sys->fx, sys->natoms, MPI_DOUBLE, MPI_SUM, 0, sys->comm );
  MPI_Reduce( fy, sys->fy, sys->natoms, MPI_DOUBLE, MPI_SUM, 0, sys->comm );
  MPI_Reduce( fz, sys->fz, sys->natoms, MPI_DOUBLE, MPI_SUM, 0, sys->comm );
  MPI_Reduce( &epot, &sys->epot, 1, MPI_DOUBLE, MPI_SUM, 0, sys->comm );
  time2 = MPI_Wtime();
  sys->comm_time += time2 - time1;
#else
  /* sys->fx = fx; */
  /* sys->fy = fy; */
  /* sys->fz = fz; */
  sys->epot = epot;
#endif //USE_MPI


  return;
}


// =======================================================================
