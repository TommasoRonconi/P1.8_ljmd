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
#include <test.h>


//global 
mdsys_t *gsys;

/* velocity verlet */
static void velverlet(mdsys_t *sys)
{
    int i;

    /* first part: propagate velocities by half and positions by full step */
    for (i = 0; i < sys->natoms; ++i)
    {
        sys->vx[i] += 0.5 * sys->dt / mvsq2e * sys->fx[i] / sys->mass;
        sys->vy[i] += 0.5 * sys->dt / mvsq2e * sys->fy[i] / sys->mass;
        sys->vz[i] += 0.5 * sys->dt / mvsq2e * sys->fz[i] / sys->mass;
        sys->rx[i] += sys->dt * sys->vx[i];
        sys->ry[i] += sys->dt * sys->vy[i];
        sys->rz[i] += sys->dt * sys->vz[i];
    }

    /* compute forces and potential energy */
    force(sys);

    /* second part: propagate velocities by another half step */
    for (i = 0; i < sys->natoms; ++i)
    {
        sys->vx[i] += 0.5 * sys->dt / mvsq2e * sys->fx[i] / sys->mass;
        sys->vy[i] += 0.5 * sys->dt / mvsq2e * sys->fy[i] / sys->mass;
        sys->vz[i] += 0.5 * sys->dt / mvsq2e * sys->fz[i] / sys->mass;
    }
}

/* main */
int main(int argc, char **argv)
{
    int nprint;
    char restfile[BLEN], trajfile[BLEN], ergfile[BLEN], line[BLEN];
    FILE *fp, *traj, *erg;
    gsys=&sys;

    if (populate_data(stdin, &line, &restfile, &trajfile, &ergfile, &sys, &nprint))
        return 1;
    check_data();

    sys.rx = (double *)malloc(sys.natoms * sizeof(double));
    sys.ry = (double *)malloc(sys.natoms * sizeof(double));
    sys.rz = (double *)malloc(sys.natoms * sizeof(double));
    sys.vx = (double *)malloc(sys.natoms * sizeof(double));
    sys.vy = (double *)malloc(sys.natoms * sizeof(double));
    sys.vz = (double *)malloc(sys.natoms * sizeof(double));
    sys.fx = (double *)malloc(sys.natoms * sizeof(double));
    sys.fy = (double *)malloc(sys.natoms * sizeof(double));
    sys.fz = (double *)malloc(sys.natoms * sizeof(double));

    /* read restart */
    fp = fopen(restfile, "r");
    readRestart(fp, &sys, restfile);

    /* initialize forces and energies.*/
    sys.nfi = 0;
    force(&sys);
    ekin(&sys);

    erg = fopen(ergfile, "w");
    traj = fopen(trajfile, "w");

    printf("Starting simulation with %d atoms for %d steps.\n", sys.natoms, sys.nsteps);
    printf("     NFI            TEMP            EKIN                 EPOT              ETOT\n");
    output(&sys, erg, traj);

    /**************************************************/
    /* main MD loop */
    for (sys.nfi = 1; sys.nfi <= sys.nsteps; ++sys.nfi)
    {

        /* write output, if requested */
        /* Here we print the output at each step-number/nprint time step
     * Number of prints is defined in stdin by variable nprint
     */
        if ((sys.nfi % nprint) == 0)
            output(&sys, erg, traj);

        /* propagate system and recompute energies */
        velverlet(&sys);
        ekin(&sys);
    }
    /**************************************************/

    /* clean up: close files, free memory */
    printf("Simulation Done.\n");
    fclose(erg);
    fclose(traj);

    free(sys.rx);
    free(sys.ry);
    free(sys.rz);
    free(sys.vx);
    free(sys.vy);
    free(sys.vz);
    free(sys.fx);
    free(sys.fy);
    free(sys.fz);

    return 0;
}