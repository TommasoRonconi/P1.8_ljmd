
#ifndef __POTENTIALS__
#define __POTENTIALS__

#include <data_structure.h>

/*Avoiding expensive math*/ 
#ifdef LJ_LESS_MATH

#define FFAC() (12.0*c12*r6 - 6.0*c6)*r6*rinv
#define EPOT() 0.5*r6*(c12*r6 - c6)
#define  C12() 4.0*sys->epsilon*pow(sys->sigma,12.0)
#define  C6()  4.0*sys->epsilon*pow(sys->sigma,6.0)
#define  RRC() sys->rcut * sys->rcut
#define RR() rx*rx + ry*ry + rz*rz
#define R() sqrt(rr)
#define RINV() 1.0/r
#define R6() rinv*rinv*rinv*rinv*rinv*rinv


#elif MORSE


// #define FFAC() sys->epsilon*(1-exp(-1*sys->sigma*rr))*(1-exp(-1*sys->sigma*rr))
// #define EPOT() -0.5*sys->epsilon*(1-exp(-1*sys->sigma*rr))*(sys->sigma*exp(-1*sys->sigma*rr))
#define FFAC() 0
#define EPOT() 0
#define  C12() 0
#define  C6() 0
#define  RRC() sys->rcut
#define RR() sqrt(rx*rx + ry*ry + rz*rz)
#define R() rr
#define RINV() 0
#define R6() 0


#else

#define FFAC() -4.0*sys->epsilon*(-12.0*pow(sys->sigma/rr,12.0)/rr + 6*pow(sys->sigma/rr,6.0)/rr)
#define EPOT() 0.5*4.0*sys->epsilon*(pow(sys->sigma/rr,12.0) - pow(sys->sigma/rr,6.0))
#define  C12() 0
#define  C6() 0
#define  RRC() sys->rcut
#define RR() sqrt(rx*rx + ry*ry + rz*rz)
#define R() rr
#define RINV() 0
#define R6() 0


#endif


#endif //__COMPUTE_FORCE__
