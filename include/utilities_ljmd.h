#ifndef __UTILITIES_LJMD__
#define __UTILITIES_LJMD__

/* a few physical constants */
// extern 
const double kboltz;     /* boltzman constant in kcal/mol/K */
// extern 
const double mvsq2e; /* m*v^2 in kcal/mol */

/* helper function: zero out an array */
// static 
void azzero(double *d, const int n);

/* helper function: apply minimum image convention */
// static 
double pbc(double x, const double boxby2);

#endif //__UTITLITIES_LJMD__
