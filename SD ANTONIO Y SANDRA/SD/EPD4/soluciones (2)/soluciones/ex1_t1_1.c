#include <stdio.h>
#include <omp.h>

int i=1;
int j=2;
int k=3;

#pragma omp threadprivate(k)

void main(void){

	omp_set_num_threads(3);

/* 
########## PRIMER TEST PARTE 1 ##########
i = 2,3,4. Es compartida, por lo que cada thread incrementará su valor en uno.
j = 4. Es privada y muestra el valor de k puesto que hay un j=k al entrar en la región paralela.
k = 4. Al haberla declarado como threadprivate, cada hilo tiene su copia y la incrementa en uno.
*/
	
	printf("\n**** Test #1 parte 1 ****\n");
 
 	#pragma omp parallel private(j) shared(i) 
    {
    	j=k;
    	i++;j++;k++;           
        printf("TID %d: i=%d, j=%d, k=%d\n", omp_get_thread_num(),i,j,k);
    }

    printf("\n");

}