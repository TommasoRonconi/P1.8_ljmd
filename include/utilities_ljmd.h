#ifndef __UTILITIES_LJMD__
#define __UTILITIES_LJMD__

#define BLEN 200

/* a few physical constants */
const double kboltz;     /* boltzman constant in kcal/mol/K */
const double mvsq2e; /* m*v^2 in kcal/mol */

/* helper function: zero out an array */
void azzero(double *d, const int n);

/* helper function: apply minimum image convention */
double pbc(double x, const double boxby2);

#endif //__UTITLITIES_LJMD__
