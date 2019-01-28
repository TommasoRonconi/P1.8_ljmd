#ifndef __OUTPUT__
#define __OUTPUT__

#include <stdio.h>
#include <data_structure.h>
#include <utilities_ljmd.h>

// static 
void output(mdsys_t *sys, FILE *erg, FILE *traj);

void python_output(mdsys_t *sys, const char *trajfile, const char *ergfile);

#endif //__OUTPUT__
