#include <data_structure.h>

void initialize ( mdsys_t * const sys ) {

#ifdef USE_MPI
  int * argc_dummy;
  char *** argv_dummy;
  MPI_Init( argc_dummy, argv_dummy );
  MPI_Comm_size( MPI_COMM_WORLD, &sys->npes );
  MPI_Comm_rank( MPI_COMM_WORLD, &sys->rank );
  /* sys.rank = rank; */
  /* sys.npes = npes; */
  sys->comm = MPI_COMM_WORLD;
#else
  sys->rank = 0;
  sys->npes = 1;  
#endif //USE_MPI
  sys->comm_time = 0.0;
  sys->force_time = 0.0;
  sys->overhead = 0.0;
  
  return;
  
}

void finalize () {

#ifdef USE_MPI
  MPI_Finalize();
#endif //USE_MPI
  
  return;
  
}

void allocate_sys_arrays ( mdsys_t * const sys ) {

  // allocate coordinates
  sys->rx = (double *) malloc( sys->natoms * sizeof(double) );
  sys->ry = (double *) malloc( sys->natoms * sizeof(double) );
  sys->rz = (double *) malloc( sys->natoms * sizeof(double) );

  // allocate velocities
  sys->vx = (double *) malloc( sys->natoms * sizeof(double) );
  sys->vy = (double *) malloc( sys->natoms * sizeof(double) );
  sys->vz = (double *) malloc( sys->natoms * sizeof(double) );

#ifdef USE_MPI
  // allocate support
  sys->cx = (double *) malloc( sys->natoms * sizeof(double) );
  sys->cy = (double *) malloc( sys->natoms * sizeof(double) );
  sys->cz = (double *) malloc( sys->natoms * sizeof(double) );
#endif //USE_MPI

  // allocate forces
  sys->fx = (double *) malloc( sys->natoms * sizeof(double) );
  sys->fy = (double *) malloc( sys->natoms * sizeof(double) );
  sys->fz = (double *) malloc( sys->natoms * sizeof(double) );
  
  return;

}

void free_sys_arrays ( mdsys_t * const sys ) {

  // free coordinates
  free( sys->rx );
  free( sys->ry );
  free( sys->rz );
  
  // free velocities
  free( sys->vx );
  free( sys->vy );
  free( sys->vz );
  
#ifdef USE_MPI
  // free support
  free( sys->cx );
  free( sys->cy );
  free( sys->cz );
#endif //USE_MPI
  
  // free forces
  free( sys->fx );
  free( sys->fy );
  free( sys->fz );
  
  return;

}
