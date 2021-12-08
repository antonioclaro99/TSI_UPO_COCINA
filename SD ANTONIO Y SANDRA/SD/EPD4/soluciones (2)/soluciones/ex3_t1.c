#include <stdio.h>
#include <omp.h>
#include <unistd.h> 

void main(void){
	
	int tid;
 
 /* 
########## PRIMER TEST ##########
El número de threads que suele tener disponible un procesador multinúcleo es igual al número de cores 
multiplicado por dos.

En las regiones secuenciales se una, obviamente, un hilo de ejecución; mientras que en las 
regiones paralelas el compilador, por defecto, asigna el mayor número de hilos disponible.
*/	
	
	printf("\n**** TEST #1 ****\n\n");

	printf("Número de threads de la máquina = %d\n",omp_get_num_procs());
	
	#pragma omp parallel private(tid)
	{
		tid = omp_get_thread_num();
		if (tid%2 == 0) sleep(3); 
		#pragma omp barrier
		if (tid%2 != 0) sleep(3); 
	
	}

 

}


