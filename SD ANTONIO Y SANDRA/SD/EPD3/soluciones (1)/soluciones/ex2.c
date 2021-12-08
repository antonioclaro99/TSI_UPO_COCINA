#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv){
   
        int i=0,tid=0,s=0;

        printf("\n********** PRIMERA CUESTIÓN **********\n");

        printf("\nNTH = 6, schedule(static,5), i por defecto\n");

        #pragma omp parallel private(tid) num_threads(6)
        {
                
                
                #pragma omp for schedule(static,5)
                for(i=0; i<20; i++){
                        tid=omp_get_thread_num();
                        printf("thread %d: i=%d\n",tid,i);
                }
                printf("thread %d: I'm done!\n",omp_get_thread_num());
        }

        printf("Final value of i = %d\n\n",i);

        printf("\n********** SEGUNDA CUESTIÓN **********\n");
        printf("\nNTH = 4, schedule(dynamic,5), nowait, lastprivate(i)\n");

        #pragma omp parallel private(tid) num_threads(4)
        {
                #pragma omp for schedule(dynamic,5) nowait lastprivate(i)
                for(i=0; i<20; i++){
                        tid=omp_get_thread_num();
                        printf("thread %d: i=%d\n", tid,i);
                }
                printf("thread %d: I'm done!\n",omp_get_thread_num());
        }

        printf("Final value of i = %d\n",i);

        printf("\nNTH = 4, schedule(static,5), nowait, lastprivate(i)\n");

        #pragma omp parallel private(tid) num_threads(4)
        {
                #pragma omp for schedule(static,5) nowait lastprivate(i)
                for(i=0; i<20; i++){
                        tid=omp_get_thread_num();
                        printf("thread %d: i=%d\n", tid,i);
                }
                printf("thread %d: I'm done!\n",omp_get_thread_num());
        }

        printf("\nFinal value of i = %d\n\n",i);     

        printf("\n********** TERCERA CUESTIÓN **********");
        printf("\n** ¿ cuál es la diferencia entre static y dynamic a la hora de repartir la carga ? **\n");
        

        
        printf("\nNTH = 2, schedule(static,5), nowait, lastprivate(i)\n");
        #pragma omp parallel private(tid) num_threads(2)
        {
                #pragma omp for schedule(static,5) nowait lastprivate(i)
                for(i=0; i<20; i++){
                        tid=omp_get_thread_num();
                        printf("thread %d: i=%d\n", tid,i);
                }
                printf("thread %d: I'm done!\n",omp_get_thread_num());
        }

        printf("Final value of i = %d\n\n",i);   
        

        printf("\nNTH = 2, schedule(dynamic,5), nowait, lastprivate(i)\n");
        #pragma omp parallel private(tid) num_threads(2)
        {
                #pragma omp for schedule(dynamic,5) nowait lastprivate(i)
                for(i=0; i<20; i++){
                        tid=omp_get_thread_num();
                        printf("thread %d: i=%d\n", tid,i);
                }
                printf("thread %d: I'm done!\n",omp_get_thread_num());
        }

        printf("Final value of i = %d\n\n",i);

        return 0;

}