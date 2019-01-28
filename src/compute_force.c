#include <compute_force.h>

#if defined (_OPENMP)
#include <omp.h>
#else
#define omp_get_wtime() 0
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
	double epot = 0;
	int i,j;

	#if defined (_OPENMP)
	#pragma omp parallel reduction(+:epot)
	#endif

	double *fx, *fy, *fz;
	
	#if defined (_OPENMP)
		int tid = omp_get_thread_num();
	#else
		int tid = 0;
	#endif

	fx=sys->fx + (tid*sys->natoms);
	fy=sys->fy + (tid*sys->natoms);
	fz=sys->fz + (tid*sys->natoms);

	/* zero energy and forces */
	sys->epot=0.0;
	azzero(fx,sys->natoms);
	azzero(fy,sys->natoms);
	azzero(fz,sys->natoms);
	// azzero(sys->fx,sys->natoms);
	// azzero(sys->fy,sys->natoms);
	// azzero(sys->fz,sys->natoms);

	


	for(i=0; i < (sys->natoms); ++i) {
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

				sys->fx[i] += rx/r*ffac;
				sys->fy[i] += ry/r*ffac;
				sys->fz[i] += rz/r*ffac;
			}
		}
	}

	sys->epot = epot;

	return;
}


// =======================================================================
