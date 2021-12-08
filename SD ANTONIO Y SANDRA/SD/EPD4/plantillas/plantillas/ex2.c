#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 12

int main (void) {

	omp_set_num_threads(4);
	int   i; 
	float a[N], b[N], result=0.0;
 	
 	for (i=0; i < N; i++) 	{
		  a[i] = i * 1.0;
		  b[i] = i * 2.0;
	}
	
	#pragma omp parallel for default(none) schedule(static,3) reduction(+:result)  
	for (i=0; i < n; i++) 
		result = result + (a[i] * b[i]);
	
	printf("RESULTADO = %.1f\n",result);

	result 0;
}
