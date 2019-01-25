#ifndef __TEST__
#define __TEST__
#include<data_structure.h>

#define my_assert(message, test) \
    do                           \
    {                            \
        if (!(test))             \
            return message;      \
    } while (0)

#define my_run_test(test)       \
    do                          \
    {                           \
        char *message = test(); \
        tests_run++;            \
        if (message)            \
            return message;     \
    } while (0)

extern int tests_run;
extern mdsys_t *sys;

static char * check_data()
{
    my_assert("\nERROR number atoms is different",sys->natoms == 108);
    my_assert("\nERROR mass is different from source",(abs(sys->mass - 39.948)<0.0001));
    my_assert("\nERROR epsilon is different from source",abs(sys->epsilon - 0.2379)<0.0001);
    my_assert("\ERROR sigma is diffrent from source",abs(sys->sigma - 3.405)<0.0001);
    my_assert("\ERROR rcut is diffrent from source",abs(sys->rcut - 8.5)< 0.0001);
    my_assert("\ERROR box is diffrent from source",abs(sys->box - 17.1580)<0.0001);
    my_assert("\ERROR sigma is diffrent from source",sys->nsteps == 10000);
    return 0;
}

static char * chek_zero_arrays()
{
    for(size_t i = 0; i < sys->natoms; i++)
    {
        my_assert("\nERROR fx is not equal to zero",sys->fx == 0);
        my_assert("\nERROR fy is not equal to zero",sys->fy == 0);
        my_assert("\nERROR fz is not equal to zero",sys->fz == 0);
    }
    
}

 static char * readRestart()
 {
     int i = 0;
     mdsys_t *sys = &sys;
     FILE *fp = fopen("examples/argon_108.rest", "r");
     fscanf(fp, "%lf%lf%lf", sys->rx + 0, sys.ry + i, sys.rz + i);
     my_assert("\nERROR rx is not equal to source", abs(sys.rx - 6.67103294321331) < 0.0001);
     my_assert("\nERROR ry is not equal to source", abs(sys.ry - 10.6146871435653) < 0.0001);
     my_assert("\nERROR rz is not equal to source", abs(sys.rz - 12.6336939877734) < 0.0001);

     i = 109;
     fscanf(fp, "%lf%lf%lf", sys.rx + i, sys.ry + i, sys.rz + i);
     my_assert("\nERROR vx is not equal to source", abs(sys.vx - 1.5643224621482283e-03) < 0.0001);
     my_assert("\nERROR vy is not equal to source", abs(sys.vy - 4.8497508563925346e-04) < 0.0001);
     my_assert("\nERROR vz is not equal to source", abs(sys.vz - 4.3352481732883966e-04) < 0.0001);
  }

  static char *all_tests()
  {
      my_run_test(check_data);
      my_run_test(chek_zero_arrays);
      my_run_test(readRestart);
      return 0;
  }

#endif