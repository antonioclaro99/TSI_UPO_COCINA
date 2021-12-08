#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv){
	
	omp_set_num_threads(10);

	#pragma omp parallel private
	{
		int nthreads;
		int thread;

		thread = omp_get_thread_num();
		nthreads = omp_get_num_threads();
		
		printf("Hola Mundo soy el thread = %d de %d que somos\n",thread , nthreads);
		
		
	}
	
 	
 	return 0;
}
