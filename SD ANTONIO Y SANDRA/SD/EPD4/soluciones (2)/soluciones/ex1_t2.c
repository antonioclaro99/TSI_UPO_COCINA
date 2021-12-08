#include <stdio.h>
#include <omp.h>

int i=1;
int j=2;
int k=3;

#pragma omp threadprivate(k)

void main(void){

	omp_set_num_threads(3);

/* 
########## SEGUNDO TEST ##########
i = 4. Ya que es una variable compartida y cada hilo ha incrementado su valor.
j = 2. Puesto que es una variable privada y no tenmos cláusula lastprivate para recuperar su valor.
k = 4. Es una variable threadpirvate, cada hilo tiene una copia de su valor y es incrementado; además,
es una variable global, por lo que al salir de la región paralela tendrá el valor establecido por el 
master thread.
*/

	printf("\n**** Test #2 ****\n");
 
 	#pragma omp parallel private(j) shared(i)  
    {
    	j=k;
    	i++;j++;k++;           
        printf("TID %d: i=%d, j=%d, k=%d\n", omp_get_thread_num(),i,j,k);
    }

    printf("\nRESULTADO: i = %d, j = %d, k = %d\n\n",i,j,k);

    printf("\n");

}