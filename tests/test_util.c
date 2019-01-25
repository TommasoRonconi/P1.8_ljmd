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
	const int size1 = 10;

	/* Declare array to be tested qith azzero() */
	double *test_array1;
	
	/* Declare variable to test pbc() */
	double xx;
	const double boxbyxx = 200.0;

	/*---------- azzero() --------------*/
	/* Allocate memory */
	test_array1 = (double*) malloc(size1 * sizeof(*test_array1));
	
	printf("/--------- Testing for azzero() ---------/\n\n");
	printf("Initialize the array...\nPrint the array:\n\n");
	/* Initialize arrays */
	for(int ii = 0; ii < size1; ii++)
	{
		test_array1[ii] = ii * 2.0;
		printf("%f ", test_array1[ii]);
	}
	printf("\n\nZero out the array with azzero()...\nCheck the array:\n\n");

	/* Zero out the array with
		azzero(test_array1, size1) */
	azzero(test_array1, size1);

	for(int ii = 0; ii < size1; ++ii)
	{
		assert(test_array1[ii] == 0);
		printf("%f ", test_array1[ii]);
	}
	printf("\n\n");

	free(test_array1);


	/*---------- pbc() ---------------*/
	xx = 600.0;

	xx = pbc(xx, boxbyxx);

	/* The correct value for xx should be 200.0;
		Trying assert with the correct and
		an incorrect value */
	
	printf("/--------- Testing for pbc() ---------/\n\n");
	printf("Assert for correct value of xx(=200.0)\n");
	assert(xx == 200.0);
	printf("--------------------------------------\n");

	printf("Check: computed value of xx = %f\n", xx);

	/*printf("--------------------------------------\n");

	printf("assert for incorrect value of xx (=300.0)\n");
	assert(xx == 300.0);
	printf("--------------------------------------\n");*/
		
	return 0;
}