#include <stdio.h>
#include <omp.h>

int i=1;
int j=2;
int k=3;

#pragma omp threadprivate(k)

void main(void){

	omp_set_num_threads(3);

/* 
########## PRIMER TEST PARTE 2 ##########
La variable j contiene basura al ser privada y no estar inicializada ni con firstprivate 
ni explícitamente en la región paralela.
*/	
	printf("\n**** Test #1 parte 2 ****\n");
 
 	#pragma omp parallel private(j) shared(i) 
    {
    	i++;j++;k++;           
        printf("TID %d: i=%d, j=%d, k=%d\n", omp_get_thread_num(),i,j,k);
    }

    printf("\n");

}