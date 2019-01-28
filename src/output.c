#include<stdio.h>
#include<data_structure.h>
#include <utilities_ljmd.h>

/* static  */
void output(mdsys_t *sys, FILE *erg, FILE *traj)
{
    int i;
    
    printf("% 8d % 20.8f % 20.8f % 20.8f % 20.8f\n", sys->nfi, sys->temp, sys->ekin, sys->epot, sys->ekin + sys->epot);
    fprintf(erg, "% 8d % 20.8f % 20.8f % 20.8f % 20.8f\n", sys->nfi, sys->temp, sys->ekin, sys->epot, sys->ekin + sys->epot);
    fprintf(traj, "%d\n nfi=%d etot=%20.8f\n", sys->natoms, sys->nfi, sys->ekin + sys->epot);
    for (i = 0; i < sys->natoms; ++i)
    {
        fprintf(traj, "Ar  %20.8f %20.8f %20.8f\n", sys->rx[i], sys->ry[i], sys->rz[i]);
    }
}
void python_output(mdsys_t *sys, const char *trajfile, const char *ergfile)
{
    int i;
    FILE *traj = fopen("argon_108.xyz", "a");
    FILE *erg = fopen("argon_108.dat", "a");
    printf("% 8d % 20.8f % 20.8f % 20.8f % 20.8f\n", sys->nfi, sys->temp, sys->ekin, sys->epot, sys->ekin + sys->epot);
    fprintf(erg, "% 8d % 20.8f % 20.8f % 20.8f % 20.8f\n", sys->nfi, sys->temp, sys->ekin, sys->epot, sys->ekin + sys->epot);
    fprintf(traj, "%d\n nfi=%d etot=%20.8f\n", sys->natoms, sys->nfi, sys->ekin + sys->epot);
    for (i = 0; i < sys->natoms; ++i)
    {
        fprintf(traj, "Ar  %20.8f %20.8f %20.8f\n", sys->rx[i], sys->ry[i], sys->rz[i]);
    }
}
