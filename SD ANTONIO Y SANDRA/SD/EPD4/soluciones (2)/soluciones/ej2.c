#include <stdio.h>
#include <omp.h>

void main(void) {

int i, j, n=10;

printf("\n");

//Solución: 
// #pragma omp parallel firstprivate(n)
#pragma omp parallel private(n)
{
 	n += omp_get_thread_num();
  printf("[TID %d] n=%d \n", omp_get_thread_num(), n);
}

j = 100000;
 

//Solución: 
// #pragma omp parallel for lastprivate(n)
#pragma omp parallel for private(n)
for (i = 1; i <= j; i++) n = i;

printf("\nITERACIONES=%d, n=%d \n\n", j,n);

}
