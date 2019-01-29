#include <velverlet_time_integration.h>
#include <stdio.h>
/* velocity verlet */
/* static  */
void velverlet_first_half(mdsys_t *sys)
{
    int i;
    /* first part: propagate velocities by half and positions by full step */
    /* for (i = sys->offset; i<sys->nloc; ++i) */
    for (i = 0; i<sys->natoms; ++i)
    {
        sys->vx[i] += 0.5*sys->dt / mvsq2e * sys->fx[i] / sys->mass;
        sys->vy[i] += 0.5*sys->dt / mvsq2e * sys->fy[i] / sys->mass;
        sys->vz[i] += 0.5*sys->dt / mvsq2e * sys->fz[i] / sys->mass;
        sys->rx[i] += sys->dt*sys->vx[i];
        sys->ry[i] += sys->dt*sys->vy[i];
        sys->rz[i] += sys->dt*sys->vz[i];
    }
    /* MPI_Allgather( sys->vx + sys->offset, sys->nloc, MPI_DOUBLE, */
    /* 		   sys->vx + sys->offset, sys->nloc, MPI_DOUBLE, */
    /* 		   sys->comm ); */
    /* MPI_Allgather( sys->vy + sys->offset, sys->nloc, MPI_DOUBLE, */
    /* 		   sys->vy + sys->offset, sys->nloc, MPI_DOUBLE, */
    /* 		   sys->comm ); */
    /* MPI_Allgather( sys->vz + sys->offset, sys->nloc, MPI_DOUBLE, */
    /* 		   sys->vz + sys->offset, sys->nloc, MPI_DOUBLE, */
    /* 		   sys->comm ); */
    /* MPI_Allgather( sys->rx + sys->offset, sys->nloc, MPI_DOUBLE, */
    /* 		   sys->rx + sys->offset, sys->nloc, MPI_DOUBLE, */
    /* 		   sys->comm ); */
    /* MPI_Allgather( sys->ry + sys->offset, sys->nloc, MPI_DOUBLE, */
    /* 		   sys->ry + sys->offset, sys->nloc, MPI_DOUBLE, */
    /* 		   sys->comm ); */
    /* MPI_Allgather( sys->rz + sys->offset, sys->nloc, MPI_DOUBLE, */
    /* 		   sys->rz + sys->offset, sys->nloc, MPI_DOUBLE, */
    /* 		   sys->comm ); */
    
}


/* velocity verlet */
/* static  */
void velverlet_second_half(mdsys_t *sys)
{
    int i;
    /* second part: propagate velocities by another half step */
    /* for (i = sys->offset; i<sys->nloc; ++i)  */
    for (i = 0; i<sys->natoms; ++i) 
    {
        sys->vx[i] += 0.5*sys->dt / mvsq2e * sys->fx[i] / sys->mass;
        sys->vy[i] += 0.5*sys->dt / mvsq2e * sys->fy[i] / sys->mass;
        sys->vz[i] += 0.5*sys->dt / mvsq2e * sys->fz[i] / sys->mass;
    }
    /* MPI_Allgather( sys->vx + sys->offset, sys->nloc, MPI_DOUBLE, */
    /* 		   sys->vx + sys->offset, sys->nloc, MPI_DOUBLE, */
    /* 		   sys->comm ); */
    /* MPI_Allgather( sys->vy + sys->offset, sys->nloc, MPI_DOUBLE, */
    /* 		   sys->vy + sys->offset, sys->nloc, MPI_DOUBLE, */
    /* 		   sys->comm ); */
    /* MPI_Allgather( sys->vz + sys->offset, sys->nloc, MPI_DOUBLE, */
    /* 		   sys->vz + sys->offset, sys->nloc, MPI_DOUBLE, */
    /* 		   sys->comm ); */
    
}

mdsys_t *python_velverlet_second_half(mdsys_t *sys)
{
    int i;
    /* second part: propagate velocities by another half step */
    for (i = 0; i < sys->natoms; ++i)
    {
        sys->vx[i] += 0.5 * sys->dt / mvsq2e * sys->fx[i] / sys->mass;
        sys->vy[i] += 0.5 * sys->dt / mvsq2e * sys->fy[i] / sys->mass;
        sys->vz[i] += 0.5 * sys->dt / mvsq2e * sys->fz[i] / sys->mass;
    }
    return sys;
}
