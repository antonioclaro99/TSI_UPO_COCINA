#include <stdio.h>
#include <omp.h>
#include <unistd.h> 

void main(void){
	
	int tid;
 
/* 
########## TERCER TEST ##########
Al quitar el barrier podemos observar cómo, pese a los retardos introducidos, la ejecución
de cada hilo es independiente y no está controlada, es decir, no podemos saber en qué orden
terminarán de ejecutarse los hilos.

Por otra parte, observamos que el efecto de la barrera implicita persiste puesto que los 
hilos que llegan a la misma, esperan a que el resto termine su ejecución.

*/

	printf("\n**** TEST #3 ****\n\n");

    #pragma omp parallel private(tid)
	{
		tid = omp_get_thread_num();
		
			if (tid%2 == 0) {
			sleep(3);
			printf("[TID %d, retardado] ==> %.5f \n",omp_get_thread_num(), omp_get_wtime());
		} 
		else{
			printf("[TID %d, normal]    ==> %.5f \n",omp_get_thread_num(), omp_get_wtime());
		}
		
		
		if (tid%2 != 0) {
			sleep(3);
			printf("[TID %d, retardado] ==> %.5f \n",omp_get_thread_num(), omp_get_wtime());
		} 
		else{
			printf("[TID %d, normal]    ==> %.5f \n",omp_get_thread_num(), omp_get_wtime());
		}
	
	}

	printf("\nFuera de la región paralela\n\n");

}


