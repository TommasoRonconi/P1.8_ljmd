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

struct _test_sys
{
    int natoms, nfi, nsteps;
    double dt, mass, epsilon, sigma, box, rcut;
    double ekin, epot, temp;
    double rx, ry, rz;
    double vx, vy, vz;
    double fx, fy, fz;
    double azz_t, pbc_t;
};
typedef struct _test_sys test_sys;

extern test_sys gsys;
extern int tests_run;

static char *test_populate_data()
{
    my_assert("\nERROR, sys.mass != 39.948 AMU", abs(gsys.mass - 39.948) < 0.03);
    my_assert("\nERROR, sys.box_length != 17.1580 angstrom", abs(gsys.box - 17.1580) < 0.03);
    return 0;
}

static char *test_ekin()
{
    my_assert("\nERROR, energy(10*dt) = 25877625.29676397 kcal", abs(gsys.ekin - 25877625.29676397) < 0.03);
    return 0;
}

static char *test_compute_force()
{
    my_assert("\nERROR, sys.fx = 0.000702695", abs(gsys.fx - 0.000702695) < 0.03);
    my_assert("\nERROR, sys.rx[0] = 497.186 ", abs(gsys.rx - 497.186) < 0.03);
    return 0;
}

static char *test_azzero()
{
    my_assert("\nERROR, azzero() not working", gsys.azz_t == 0);
    return 0;
}

static char *test_pbc()
{
    my_assert("\nERROR, pbc() not working", abs(gsys.pbc_t + 150) < 0.03);
    return 0;
}

static char *check_data()
{
    my_assert("\nERROR number atoms is different", gsys.natoms == 3);
    my_assert("\nERROR mass is different from source", (abs(gsys.mass - 39.948) < 0.0001));
    my_assert("\nERROR epsilon is different from source", abs(gsys.epsilon - 0.2379) < 0.0001);
    my_assert("\nERROR sigma is diffrent from source", abs(gsys.sigma - 3.405) < 0.0001);
    my_assert("\nERROR rcut is diffrent from source", abs(gsys.rcut - 8.5) < 0.0001);
    my_assert("\nERROR box is diffrent from source", abs(gsys.box - 17.1580) < 0.0001);
    my_assert("\nERROR sigma is diffrent from source", gsys.nsteps == 20);
    return 0;
}

// static char * readRestart()
// {
// 	int i = 0;
// 	// mdsys_t *sys = &sys;
// 	FILE *fp = fopen("examples/argon_3.rest", "r");
// 	fscanf(fp, "%lf%lf%lf", gsys.rx, gsys.ry, gsys.rz);
// 	my_assert("\nERROR rx is not equal to source", abs(gsys.rx - 6.67103294321331) < 0.0001);
// 	my_assert("\nERROR ry is not equal to source", abs(gsys.ry - 10.6146871435653) < 0.0001);
// 	my_assert("\nERROR rz is not equal to source", abs(gsys.rz - 12.6336939877734) < 0.0001);

// 	i = 109;
// 	fscanf(fp, "%lf%lf%lf", gsys.rx, gsys.ry, gsys.rz);
// 	my_assert("\nERROR vx is not equal to source", abs(gsys.vx - 1.5643224621482283e-03) < 0.0001);
// 	my_assert("\nERROR vy is not equal to source", abs(gsys.vy - 4.8497508563925346e-04) < 0.0001);
// 	my_assert("\nERROR vz is not equal to source", abs(gsys.vz - 4.3352481732883966e-04) < 0.0001);
// }

static char *all_tests()
{
    my_run_test(test_populate_data);
    my_run_test(test_ekin);
    my_run_test(test_compute_force);
    my_run_test(test_azzero);
    my_run_test(test_pbc);
    my_run_test(check_data);
    // my_run_test(readRestart);
    return 0;
}

//---------------------------------------------------------