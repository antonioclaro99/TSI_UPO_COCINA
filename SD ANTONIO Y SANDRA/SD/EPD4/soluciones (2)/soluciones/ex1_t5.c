#include <stdio.h>
#include <omp.h>

int i=1;
int j=2;
int k=3;

#pragma omp threadprivate(k)

void main(void){

    omp_set_num_threads(3);

/* 
########## QUINTO TEST ##########
Usamos la cláusula copyin para transferir el valor de la variable global k del master thread (k=3)
al resto de threads. Con esto, conseguimos la reproducción exacta de traza y resultado.
*/

    printf("\n**** Test #6 ****\n\n");
 
    #pragma omp parallel private(j) shared(i)
    {
        j=k;
        i++;j++;k++;           
        printf("TID %d: i=%d, j=%d, k=%d\n", omp_get_thread_num(),i,j,k);
    }

    printf("\nRESULTADO: i = %d, j = %d, k = %d\n\n",i,j,k);

    i=1;j=2;k=3;

    #pragma omp parallel private(j) shared(i) copyin(k)
    {
        j=k;
        i++;j++;k++;           
        printf("TID %d: i=%d, j=%d, k=%d\n", omp_get_thread_num(),i,j,k);
    }

    printf("\nRESULTADO: i = %d, j = %d, k = %d\n\n",i,j,k);

}