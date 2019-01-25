#ifndef __UTILITIES_LJMD__
#define __UTILITIES_LJMD__

#define BLEN 200

/* a few physical constants */
static const double kboltz=0.0019872067;     /* boltzman constant in kcal/mol/K */
static const double mvsq2e=2390.05736153349; /* m*v^2 in kcal/mol */

/* helper function: zero out an array */
void azzero(double *d, const int n);

/* helper function: apply minimum image convention */
double pbc(double x, const double boxby2);

#endif //__UTITLITIES_LJMD__
