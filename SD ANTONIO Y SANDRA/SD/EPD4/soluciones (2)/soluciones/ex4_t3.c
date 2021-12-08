
#include <omp.h>
#include <stdio.h>

#define N 10

void main(void)
{
/* 
########## TERCER TEST ##########
Incluimos una directiva atomic para actualización de la variable sump
*/

    printf("\n**** TEST #3 ****\n\n");
   
    int i=0,sums=0,sump=0,sumLocal=0,a[N];
    
    for (i = 0; i < N; i++) a[i] = i;    
    for (i=0;i<N;i++) sums +=a[i];

    #pragma omp parallel private (sumLocal) num_threads(8)
    {
        sumLocal = 0;

        #pragma omp for 
        for (i=0;i<N;i++) sumLocal+=a[i];
   
        #pragma omp atomic
        sump+= sumLocal;

        printf("[TID=%d] Después del atomic --> sumLocal=%d, sump=%d\n", omp_get_thread_num(),sumLocal,sump);

    }


    printf("\nSUMA SECUENCIAL = %d\n", sums);
    printf("SUMA PARALELO   = %d\n", sump);
    if(sums==sump) printf("OK\n\n"); else printf("ERROR\n\n");

}