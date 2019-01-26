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
#include <mpi.h>
#include <utilities_ljmd.h>
#include <data_structure.h>
#include <compute_force.h>
#include <input.h>
#include <output.h>
#include <velverlet_time_integration.h>

/* main */
int main( int argc, char **argv ) 
{

  int rank, npes;
  int nprint;
  char restfile[BLEN], trajfile[BLEN], ergfile[BLEN], line[BLEN];
  FILE *fp,*traj,*erg;
  mdsys_t sys;

  /* Initialize MPI */
  MPI_Init( &argc, &argv );
  MPI_Comm_size( MPI_COMM_WORLD, &npes );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  sys.rank = rank;
  sys.npes = npes;
  sys.comm = MPI_COMM_WORLD;
  printf( "Hello from process %d of %d\n", sys.rank, sys.npes );


  /* populate the data_structure with input data */
  if ( populate_data( stdin, &line, &restfile, &trajfile, &ergfile, &sys, &nprint ) ) return 1;

  /* allocate memory on the heap for retaining position/velocity/force infos on the sys struct */
  allocate_sys_arrays( &sys );

  /* read restart */
  if ( readRestart( &sys, restfile ) ) return 1;

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
    if ( ( ( sys.nfi % nprint ) == 0 ) && ( sys.rank == 0 ) ) output(&sys, erg, traj);

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
  MPI_Finalize();

  return 0;

}
