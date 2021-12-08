#include <stdio.h>
#include <omp.h>
#include <unistd.h>

int main(void){
	
	int tid;

	printf("Número de threads de la máquina = %d\n",omp_get_num_procs());
	
	#pragma omp parallel private(tid)
	{
		tid = omp_get_thread_num();
		
		if (tid%2==0) 
			sleep(3);
		
		#pragma omp barrier
		
		if (tid%2!=0) 
			sleep(3);
	} 

	return 0;
}
