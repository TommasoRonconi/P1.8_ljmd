#ifndef __VELVERLET__
#define __VELVERLET__

#include <data_structure.h>
#include <compute_force.h>

/* velocity verlet */
static void velverlet_first_half(mdsys_t *sys);
static void velverlet_second_half(mdsys_t *sys);

#endif 