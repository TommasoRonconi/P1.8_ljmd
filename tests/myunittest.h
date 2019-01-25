#define my_assert(message, test) 						 \
		do { if (!(test)) return message; } while (0)	 \

#define my_run_test(test)								 \
	do { char *message = test(); tests_run++; 			 \
		if (message) return message; } while (0)
 
extern int tests_run;
extern double test_mass, test_box;
extern double test_kinetic_energy;
extern double test_force;
extern double test_rx;


static char * test_populate_data()
{
	my_assert("\nERROR, sys.mass != 39.948 AMU", abs(test_mass - 39.948) < 0.03); 
	my_assert("\nERROR, sys.box_length != 17.1580 angstrom", abs(test_box - 17.1580) < 0.03); 
	return 0;
} 

static char * test_ekin()
{
	my_assert("\nERROR, energy(10*dt) = 25877625.29676397 kcal", abs(test_kinetic_energy - 25877625.29676397) < 0.03);
	return 0;
} 

static char * test_compute_force()
{
	my_assert("\nERROR, sys.fx = 0.000702695", abs(test_force - 0.000702695) < 0.03);
	my_assert("\nERROR, sys.rx[0] = 497.186 ", abs(test_rx - 497.186) < 0.03);
	return 0;
} 

 
static char * all_tests() 
{
	 my_run_test(test_populate_data);
	 my_run_test(test_ekin);
	 my_run_test(test_compute_force);
	 return 0;
}