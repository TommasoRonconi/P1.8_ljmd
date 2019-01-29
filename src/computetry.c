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
	double *fx, *fy, *fz;
	int i,j;
	int tid;

	#if defined (_OPENMP)
	#pragma omp parallel
	#endif

	#if defined (_OPENMP)
		tid = omp_get_thread_num();
		sys->nthreads = omp_get_num_threads();
	#else
		tid = 0;
		sys->nthreads = 1;
	#endif

	// #pragma omp for private(i)
	// for(i = 0; i < sys->nthreads; i++)
	// printf("Hello from thread number %d", tid);

	// fx=sys->fx + (tid*sys->natoms);
	// fy=sys->fy + (tid*sys->natoms);
	// fz=sys->fz + (tid*sys->natoms);

	/* zero energy and forces */
	sys->epot=0.0;
	// azzero(fx,sys->natoms);
	// azzero(fy,sys->natoms);
	// azzero(fz,sys->natoms);
	azzero(sys->fx,sys->natoms);
	azzero(sys->fy,sys->natoms);
	azzero(sys->fz,sys->natoms);

	for(i=0; i < (sys->natoms); ++i) {
	// for(i=0; i < (sys->natoms - 1); i += sys->nthreads) {
		for(j=0; j < (sys->natoms); ++j) {
		// for(j=0; j < (sys->natoms - 1); j += sys->nthreads) {

			/* particles have no interactions with themselves */
			if (i==j) continue;
			// int ii = i+tid;
			// int jj = j+tid;
			// if(ii == jj) continue;

			// if(ii >= (sys->nthreads-1) || jj >= (sys->nthreads-1)) break;
			
			// double rx1=sys->rx[ii];			
			// double ry1=sys->ry[ii];			
			// double rz1=sys->rz[ii];			
			// double rx2=sys->rx[jj];			
			// double ry2=sys->ry[jj];			
			// double rz2=sys->rz[jj];			
			/* get distance between particle i and j */
			// rx=pbc(rx1 - rx2, 0.5*sys->box);
			// ry=pbc(ry1 - ry2, 0.5*sys->box);
			// rz=pbc(rz1 - rz2, 0.5*sys->box);
			rx=pbc(sys->rx[i] - sys->rx[j], 0.5*sys->box);
			ry=pbc(sys->ry[i] - sys->ry[j], 0.5*sys->box);
			rz=pbc(sys->rz[i] - sys->rz[j], 0.5*sys->box);
			r = sqrt(rx*rx + ry*ry + rz*rz);
			
			/* compute force and energy if within cutoff */
			if (r < sys->rcut) {
				ffac = -4.0*sys->epsilon*(-12.0*pow(sys->sigma/r,12.0)/r
					+6*pow(sys->sigma/r,6.0)/r);
								
				sys->epot += 0.5*4.0*sys->epsilon*(pow(sys->sigma/r,12.0)
						 -pow(sys->sigma/r,6.0));

				#if defined (_OPENMP)
				#pragma omp barrier
				#endif

				int k = 1 + (sys->natoms / sys->nthreads);
				int fromidx = tid * k;
				int toidx = fromidx + k;
				int m;

				if(toidx > sys->natoms) toidx = sys->natoms;

				#if defined (_OPENMP)
				#pragma omp parallel for private(k, m)
				#endif

				for(k=1; k < sys->nthreads; ++k){
					int offs = k * sys->natoms;
					for(m=fromidx; m < toidx; ++m){
						
						sys->fx[m] += sys->fx[offs+m];
						sys->fy[m] += sys->fy[offs+m];
						sys->fz[m] += sys->fz[offs+m];

						
					}
				}
				sys->fx[i] += rx/r*ffac;
				sys->fy[i] += ry/r*ffac;
				sys->fz[i] += rz/r*ffac;
			}
		}
	}

	// sys->epot = epot;

	return;
}


// =======================================================================
