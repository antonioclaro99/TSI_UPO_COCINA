#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <string.h>

#define TAM 1000

int main(int argc, char **argv)
{
    long *M1=(long *) malloc(TAM * TAM * sizeof(long));
    long *M2=(long *) malloc(TAM * TAM * sizeof(long));
    long *M3=(long *) malloc(TAM * TAM * sizeof(long));

    int paralelizar=1;
    if(argc ==2){
        paralelizar=strtol(argv[1],NULL,10);
    }

    int tid;

    omp_set_num_threads(9);
    int nth=0;
    int i=0, j=0, k=0;
    double inicio=omp_get_wtime();
    int offset = i * TAM + j;

#pragma omp parallel private(i,j,k,tid,offset) if(paralelizar)
    {
        tid=omp_get_thread_num();
        nth=omp_get_num_threads();
        #pragma omp for schedule(guided, 1)
            for (i = 0; i < TAM; i++)
            {
                printf("HILO %d/%d inicializa fila [%d]\n", tid,nth,i);
                for (j = 0; j < TAM; j++)
                {
                    offset = i * TAM + j;
                    M1[offset] = i*TAM + j +1;
                    M2[offset] = i*TAM + j +1;
                    M3[offset] = 0;
                }
            }

            
        #pragma omp for schedule(guided, 1)
        for (i = 0; i < TAM; i++)
        {
             printf("HILO %d/%d rellena RESULTADO: fila [%d]\n", tid,nth,i);
            for (j = 0; j < TAM; j++)
            {
                                   

                for (k = 0; k < TAM; k++)
                {
                        offset = i * TAM + j;
                        int offm3=offset;

                        offset = i * TAM + k;
                        int offm1=offset;

                        offset = k * TAM + j;
                        int offm2=offset;
                        M3[offm3] += M1[offm1] * M2[offm2];
                    
                }
            }
        }
    }

    //hay un hilo
    double fin=omp_get_wtime();
    double tiempo=fin-inicio;
    printf("\n");

            printf("\nM1 y M2 son iguales:\n");
            for (i = 0; i < TAM; i++)
            {
                printf("\n");
                for (j = 0; j < TAM; j++)
                {
                     offset = i * TAM + j;
                    printf("%d ", M1[offset]);
                }
            }

            printf("\n");

    printf("M3=M1*M2: TIEMPO TOTAL: %f",tiempo);

    for (int i = 0; i < TAM; i++)
    {
        printf("\n");
        for (int j = 0; j < TAM; j++)
        {
            offset = i * TAM + j;
            printf("%d ", M3[offset]);
        }
    }

    printf("\n");
    printf("M3=M1*M2: TIEMPO TOTAL: %f",tiempo);

    return 0;
}