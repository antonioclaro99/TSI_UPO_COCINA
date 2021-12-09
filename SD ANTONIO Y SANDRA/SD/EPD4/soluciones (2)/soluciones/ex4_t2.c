
#include <omp.h>
#include <stdio.h>

#define N 10

void main(void)
{
/* 
########## SEGUNDO TEST ##########
Incluimos una directiva critical para actualización de la variable sump
*/

    printf("\n**** TEST #2 ****\n\n");
   
    int i=0,sums=0,sump=0,sumLocal=0,a[N];
    
    for (i = 0; i < N; i++) a[i] = i;    
    for (i=0;i<N;i++) sums +=a[i];

    #pragma omp parallel private (sumLocal) num_threads(8)
    {
        sumLocal = 0;

        #pragma omp for 
        for (i=0;i<N;i++) sumLocal+=a[i];

        #pragma omp critical
        {
            sump+= sumLocal;
            printf("[TID=%d] Sección crítica --> sumLocal=%d, sum=%d\n", omp_get_thread_num(),sumLocal,sump);
        }
     
    }

    printf("\nSUMA SECUENCIAL = %d\n", sums);
    printf("SUMA PARALELO   = %d\n", sump);
    if(sums==sump) printf("OK\n\n"); else printf("ERROR\n\n");

}