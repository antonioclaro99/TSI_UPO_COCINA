#include <stdio.h>
#include <omp.h>
#include <unistd.h> 

void main(void){
	
	int tid;
 
 /* 
########## SEGUNDO TEST ##########
Podemos observar que, antes del barrier, los threads impares pausan su ejecución hasta que 
los threads impares, que han sido retardados deliberadamente con sleep, llegan a la barrera
de sincronización. Después, todos prosiguen su ejecución.

Después del barrier, son los hilos pares los que, esta vez, esperan a los impares 
(retardados deliberadamente con sleep). Esta espera se debe a la barrera implicita de
OpenMP inserta, por defecto, en todas las regiones parallel.
*/

	printf("\n**** TEST #2 ****\n\n");

    #pragma omp parallel private(tid)
	{
		tid = omp_get_thread_num();
		
		if (tid%2 == 0) sleep(3); 
		printf("[TID %d] antes del barrier   ==> %.5f \n",omp_get_thread_num(), omp_get_wtime());
		
		#pragma omp barrier
		
		if (tid%2 != 0) sleep(3); 
		printf("[TID %d] después del barrier ==> %.5f\n",omp_get_thread_num(), omp_get_wtime());
	
	}

	printf("\nFuera de la región paralela\n\n");


}


