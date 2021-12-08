#include <stdio.h>
#include <omp.h>

void main(void) {
	
	int i, j, n=10;
	
	#pragma omp parallel private(n)
  	{
  		n += omp_get_thread_num();
    	printf("[TID %d] n=%d \n", omp_get_thread_num(), n);
  	}

	j = 100000;
 
	#pragma omp parallel for private(n)
 	for (i = 1; i <= j; i++)
 		n = i;
 
 	printf("\nITERACIONES=%d, n=%d \n\n", j,n);

 	return 0;

}
