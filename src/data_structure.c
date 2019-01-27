#include <data_structure.h>

void allocate_sys_arrays ( mdsys_t * const sys ) {

  // allocate coordinates
  sys->rx = (double *) malloc( sys->natoms * sizeof(double) );
  sys->ry = (double *) malloc( sys->natoms * sizeof(double) );
  sys->rz = (double *) malloc( sys->natoms * sizeof(double) );

  // allocate velocities
  sys->vx = (double *) malloc( sys->natoms * sizeof(double) );
  sys->vy = (double *) malloc( sys->natoms * sizeof(double) );
  sys->vz = (double *) malloc( sys->natoms * sizeof(double) );

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
  
  // free forces
  free( sys->fx );
  free( sys->fy );
  free( sys->fz );
  
  return;

}
