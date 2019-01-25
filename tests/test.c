/* 
 * simple lennard-jones potential MD code with velocity verlet.
 * units: Length=Angstrom, Mass=amu; Energy=kcal
 *
 * baseline c version.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <utilities_ljmd.h>
#include <data_structure.h>
#include <compute_force.h>
#include <input.h>
#include <output.h>
#include <velverlet_time_integration.h>
#include "myunittest.h"

int tests_run = 0;


test_sys gsys;

/* main */
int main(int argc, char **argv) 
{

  int nprint;
  char restfile[BLEN], trajfile[BLEN], ergfile[BLEN], line[BLEN];
  FILE *fp,*traj,*erg;
  mdsys_t sys;

  if ( populate_data(stdin, &line, &restfile, &trajfile, &ergfile, &sys, &nprint/* , BLEN */) ) return 1;
  
  // allocate_sys_arrays( gsys );
  allocate_sys_arrays( &sys );

  gsys.natoms = sys.natoms;
  gsys.mass = sys.mass;
  gsys.epsilon = sys.epsilon;
  gsys.sigma = sys.sigma;
  gsys.rcut = sys.rcut;
  gsys.box = sys.box;
  gsys.nsteps = sys.nsteps;

  // testing azzero
  double *tets_array = (double *) malloc( sys.natoms * sizeof(double) );
  azzero(tets_array,sys.natoms);
  gsys.azz_t = tets_array[rand()%sys.natoms];

  // testing pbc
  const double boxbyxx = 200;
  double xx = 650;
  xx = pbc(xx, boxbyxx);
  gsys.pbc_t = xx;

  /* read restart */
  fp = fopen(restfile, "r");
  readRestart(fp,&sys,restfile);

  /* initialize forces and energies.*/
  sys.nfi=0;
  force(&sys);
  ekin(&sys);
    
/* ======= */
    erg=fopen(ergfile,"w");
    traj=fopen(trajfile,"w");

    printf("Starting simulation with %d atoms for %d steps.\n",sys.natoms, sys.nsteps);
    printf("     NFI            TEMP            EKIN                 EPOT              ETOT\n");
    output(&sys, erg, traj);

    /**************************************************/
    /* main MD loop */
    for(sys.nfi=1; sys.nfi <= sys.nsteps; ++sys.nfi) {

        /* write output, if requested */
        if ((sys.nfi % nprint) == 0)
            output(&sys, erg, traj);

        
        velverlet_first_half(&sys); /* propagate system and recompute energies by one half step*/  
    	force(&sys); /* compute forces and potential energy */
        velverlet_second_half(&sys); /* propagate system and recompute energies by another half step*/  
        
		if (sys.nfi == 10)
		{
			// test_kinetic_energy = sys.ekin;
			// test_force = sys.fx[0];
			// test_rx = sys.rx[0];
			gsys.ekin = sys.ekin;
			gsys.fx = sys.fx[0];
			gsys.rx = sys.rx[0];
		}
        
        ekin(&sys);


    }
    /**************************************************/
    /* clean up: close files, free memory */
    fclose(erg);
    fclose(traj);

  	free_sys_arrays( &sys );
  	// free_sys_arrays( gsys );
    
    printf("Simulation Done.\n");
    /****************************************************/
    /* Unittesting */
	char *result = all_tests();
	if (result != 0) 
	{
		 printf("%s\n", result);
	}
	else
	{
		 printf("\n\nALL TESTS PASSED\n\n");
	}
	printf("\nTests run: %d\n", tests_run);


    return 0;
}
