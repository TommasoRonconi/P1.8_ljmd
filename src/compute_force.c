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
	double epot = 0.0;
	int i,j;

/* zero energy and forces */
	sys->epot=0.0;
	azzero(sys->fx,sys->natoms);
	azzero(sys->fy,sys->natoms);
	azzero(sys->fz,sys->natoms);

	#if defined (_OPENMP)
	double t_start = 0.0;
	double t_end = 0.0;
	#endif

	#if defined (_OPENMP)
	#pragma omp parallel
	sys->nthreads = omp_get_num_threads();
	#else
	sys->nthreads = 1;
	#endif

	#if defined (_OPENMP)
	t_start = omp_get_wtime();
	#pragma omp parallel for private(i, j, rx, ry, rz, r, ffac) reduction(+:epot)
	#endif
	for(i=0; i < (sys->natoms); ++i) {
		for(j=0; j < (sys->natoms); ++j) {
		
			/* particles have no interactions with themselves */
			if (i==j) continue;
			
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

	#if defined (_OPENMP)
	t_end = omp_get_wtime();
	sys->time_omp += (t_end - t_start);
	#endif

	sys->epot = epot;

	return;
}


// =======================================================================
