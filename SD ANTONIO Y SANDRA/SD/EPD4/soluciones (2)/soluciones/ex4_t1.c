
#include <omp.h>
#include <stdio.h>

#define N 10

void main(void)
{
/* 
########## PRIMER TEST ##########
Se imprime ERROR porque no existe metodología de sincronización de escritura de la variable
sump por lo que habrá threads que no puedan actualizarla (exclusión mutua) por lo que 
la suma no será la correcta.
*/

    printf("\n**** TEST #1 ****\n\n");
   
    int i=0,sums=0,sump=0,sumLocal=0,a[N];
    
    for (i = 0; i < N; i++) a[i] = i;    
    for (i=0;i<N;i++) sums +=a[i];

    #pragma omp parallel private (sumLocal) num_threads(8)
    {
        sumLocal = 0;

        #pragma omp for 
        for (i=0;i<N;i++) sumLocal+=a[i];

        sump+= sumLocal;
        printf("[TID=%d] Sección crítica --> sumLocal=%d, sump=%d\n", omp_get_thread_num(),sumLocal,sump);
    }


    printf("\nSUMA SECUENCIAL = %d\n", sums);
    printf("SUMA PARALELO   = %d\n", sump);
    if(sums==sump) printf("OK\n\n"); else printf("ERROR\n\n");

}