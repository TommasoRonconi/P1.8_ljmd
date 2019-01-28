/* 
 * simple lennard-jones potential MD code with velocity verlet.
 * units: Length=Angstrom, Mass=amu; Energy=kcal
 *
 * version integrating both basic serial and MPI parallel version.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#ifdef USE_MPI
#include <mpi.h>
#endif //USE_MPI
#include <utilities_ljmd.h>
#include <data_structure.h>
#include <compute_force.h>
#include <input.h>
#include <output.h>
#include <velverlet_time_integration.h>

/* main */
int main( int argc, char **argv ) 
{

  //int rank, npes;
  int nprint;
  char restfile[BLEN], trajfile[BLEN], ergfile[BLEN], line[BLEN];
  FILE *traj,*erg;
  mdsys_t sys;

  /* Initialize */
  initialize( argc, argv, &sys );


  /* populate the data_structure with input data */
  if ( populate_data( stdin, &line, &restfile, &trajfile, &ergfile, &sys, &nprint ) ) {
#ifdef USE_MPI
    MPI_Abort( MPI_COMM_WORLD, 1 );
#endif //USE_MPI
    return 1;
  }

  /* allocate memory on the heap for retaining position/velocity/force infos on the sys struct */
  allocate_sys_arrays( &sys );

  /* read restart */
  if ( readRestart( &sys, restfile ) ) {
#ifdef USE_MPI
    MPI_Abort( MPI_COMM_WORLD, 2 );
#endif //USE_MPI
    return 2;
  }
  
  /* initialize forces and energies.*/
  sys.nfi=0;
  force( &sys );
  ekin( &sys );

  if ( sys.rank == 0 ) {
    
    /* Open the output files for energies and trajectories */
    erg = fopen( ergfile, "w" );
    traj = fopen( trajfile, "w" );

    /* Outputting on the defined files */
    printf("Starting simulation with %d atoms for %d steps.\n",sys.natoms, sys.nsteps);
    printf("     NFI            TEMP            EKIN                 EPOT              ETOT\n");
    output(&sys, erg, traj);
    
  }

  /**************************************************/
  /* main MD loop */
  for(sys.nfi=1; sys.nfi <= sys.nsteps; ++sys.nfi) {

    /* write output, if requested */
    if ( ( sys.rank == 0 ) && ( ( sys.nfi % nprint ) == 0 ) ) output(&sys, erg, traj);

    /* propagate system and recompute energies by one half step*/          
    velverlet_first_half(&sys);

    /* compute forces and potential energy */
    force(&sys);

    /* propagate system and recompute energies by another half step*/  
    velverlet_second_half(&sys); 

    /* Update kinetic energy */
    ekin(&sys);
    
  }
  /**************************************************/

  /* clean up: close files, free memory */
  if ( sys.rank == 0 ) {
    printf("Simulation Done.\n");
    fclose(erg);
    fclose(traj);
  }

  /* free memory allocated */
  free_sys_arrays( &sys );

  /* Finalize MPI */
  finalize();

  return 0;

}
