/* A test to verify that azzero() and pbc() work: 
	azzero() zeroes out an array;
	pbc() apply minimum image convention */

#include <stdio.h>
#include <stdlib.h>
#include "utilities_ljmd.c"
#include <assert.h>


int main()
{
	
	/* Define different sizes for the arrays */
	const int size1 = 100;
	const int size2 = 70;
	int size_new;

	/* Declare arrays to be tested */
	double *test_array1, *test_array2;
	
	/* Declare variable to test pbc() */
	double xx;
	const double boxbyxx = 200.0;

	/*---------- azzero() --------------*/
	/* Allocate memory */
	test_array1 = (double*) malloc(size1 * sizeof(*test_array1));
	test_array2 = (double*) malloc(size1 * sizeof(*test_array2));

	/* Initialize arrays */
	for(int ii = 0; ii < size1; ii++)
	{
		test_array1[ii] = ii * 2.0;
	}

	for(int jj = 0; jj < size1; jj++)
	{
		test_array2[jj] = jj * 3.0;
	}

	/* Zero out the arrays
		azzero(test_array1, size1) works properly
		azzero(test_array2, size2) rightly gives error */
	azzero(test_array1, size1);

	/*azzero(test_array2, size1);*/

	azzero(test_array2, size1);

	for(int ii = 0; ii < size1; ++ii)
	{
		assert(test_array1[ii] == 0);
		assert(test_array2[ii] == 0);
	}	

	free(test_array2);
	free(test_array1);

	/*---------- pbc() ---------------*/
	xx = 600.0;

	xx = pbc(xx, boxbyxx);
	printf("%f\n", xx);

	return 0;
}