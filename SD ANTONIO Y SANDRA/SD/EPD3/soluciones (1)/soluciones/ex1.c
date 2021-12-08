#include <stdio.h>
#include <omp.h>

#define TAM 5

int main(int argc, char** argv){
      
        int i=0,s=0,iteraciones=0,tid=0,nth=0,ini=0,fin=0;
             
        omp_set_num_threads(4);

        printf("\nPrimer parallel: ejecución secuencial\n\n");

        #pragma omp parallel shared(i,iteraciones) private(tid) num_threads(3) if(s==1)
               {
                tid=omp_get_thread_num();
                for(i=0; i<TAM; i++){                           
                        printf("thread %d: i=%d\n", tid,i);
                        iteraciones++;
                }
        }

        printf("ITERACIONES = %d\n",iteraciones);
        iteraciones=0;

        s=1;

        printf("\nSegundo parallel: i compartida\n\n");
        
        #pragma omp parallel shared(i,iteraciones) private(tid) num_threads(3) if(s==1)
               {
                tid=omp_get_thread_num();
                for(i=0; i<TAM; i++){				
                        printf("thread %d: i=%d\n", tid,i);
                        iteraciones++;
                }
        }

        printf("ITERACIONES = %d\n",iteraciones);
        iteraciones=0;

        printf("\nTercer parallel: i privada\n\n");

        #pragma omp parallel shared(iteraciones) private(i,tid) num_threads(3) if(s==1)
        {
                tid=omp_get_thread_num();
                for(i=0; i<TAM; i++){                           
                        printf("thread %d: i=%d\n", tid,i);
                        iteraciones++;
                }
        }

        printf("ITERACIONES = %d\n",iteraciones);
        iteraciones=0;

        
        printf("\nCuarto parallel: reparto de iteraciones con i compartida\n\n");

        #pragma omp parallel shared(i,iteraciones) private(tid,ini,fin,nth) num_threads(3) if(s==1)
        {              

              
        tid = omp_get_thread_num();
        nth = omp_get_num_threads();
        
  
        ini = tid * TAM / nth;
        fin = (tid+1) * TAM / nth;

        for (i=ini; i<fin; i++) {
                printf("thread %d: i=%d\n", tid,i);
                iteraciones++;
        }

        }

        printf("ITERACIONES = %d\n",iteraciones);
        iteraciones=0;
         
        printf("\nQuinto parallel: reparto de iteraciones con i privada\n\n");

        #pragma omp parallel shared(iteraciones) private(i,tid,ini,fin,nth) num_threads(3) if(s==1)
        {              

              
        tid = omp_get_thread_num();
        nth = omp_get_num_threads();
        
  
        ini = tid * TAM / nth;
        fin = (tid+1) * TAM / nth;
        
        //printf("thread %d: ini=%d, fin=%d\n", j,ini,fin);
      
        for (i=ini; i<fin; i++) {
                printf("thread %d: i=%d\n", tid,i);
                iteraciones++;
        }

        }

        printf("ITERACIONES = %d\n\n",iteraciones);
        

        return 0;

}
































