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
mdsys_t python_output(mdsys_t *ptr_sys)
{
    return *ptr_sys;
}

void open_python_output(const char *trajfile, const char *ergfile)
{
    printf("b4 seg\n");
    printf("%s",trajfile);
    printf("%s",ergfile);
    printf("after seg\n");
}