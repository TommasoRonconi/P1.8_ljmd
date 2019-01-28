#include <compute_force.h>


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
  int i,j;

  /* zero energy and forces */
  sys->epot=0.0;
  azzero(sys->fx,sys->natoms);
  azzero(sys->fy,sys->natoms);
  azzero(sys->fz,sys->natoms);

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
                
	sys->epot += 0.5*4.0*sys->epsilon*(pow(sys->sigma/r,12.0)
					   -pow(sys->sigma/r,6.0));

	sys->fx[i] += rx/r*ffac;
	sys->fy[i] += ry/r*ffac;
	sys->fz[i] += rz/r*ffac;
      }
    }
  }

  return;
}


// =======================================================================

void test(mdsys_t *ptr_sys)
{
  mdsys_t sys = *ptr_sys;
  printf("I am printing from c mass: %d: \n", ptr_sys->natoms);
  printf("I am printing from c mass:%g: \n", ptr_sys->mass);
  printf("I am printing from c epsilon %g: \n", ptr_sys->epsilon);
  printf("I am printing from c sigma %g: \n", ptr_sys->sigma);
  printf("I am printing from c rcut %g: \n", ptr_sys->rcut);
  printf("I am printing from c box %g: \n", ptr_sys->box);
  printf("I am printing from c nsteps %d: \n", ptr_sys->nsteps);
  printf("I am printing from c dt:%g: \n", ptr_sys->dt);

  for (int i = 0; i < 4; ++i)
  {

    printf("%lf  \n", ptr_sys->rx[i]);
  }
  printf("\n\n");
  printf("Velocity:: \n\n");

  for (int i = 0; i < 4; ++i)
  {
    printf("%.10lf \t %.10lf \t%.10lf \n", sys.vx[i], sys.vy[i], sys.vz[i]);
  }
  azzero(sys.vx, 4);
  azzero(sys.rx, 4);
  azzero(sys.vy, 4);
  azzero(sys.ry, 4);
  azzero(sys.vz, 4);
  azzero(sys.rz, 4);

  printf("Afrter zeroing:\n\n");
  for (int i = 0; i < 4; ++i)
  {
    printf("%.10lf \t %.10lf \t%.10lf \n", sys.rx[i], sys.ry[i], sys.rz[i]);
  }
  printf("\n\n");
  printf("Velocity:: \n\n");

  for (int i = 0; i < 4; ++i)
  {
    printf("%.10lf \t %.10lf \t%.10lf \n", sys.vx[i], sys.vy[i], sys.vz[i]);
  }
}
