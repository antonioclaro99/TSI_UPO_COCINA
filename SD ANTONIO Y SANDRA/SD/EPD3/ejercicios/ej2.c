#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
 
#define N 10
#define nthreads 4
 
int main (){
  
  int thread,i;

  omp_set_num_threads(nthreads);
  #pragma omp parallel private(thread)
  {
      thread = omp_get_thread_num();
      #pragma omp for schedule(static,2)
        for ( i = 0 ; i < N; i++)
          printf("Soy el thread %d ejecuto la iteracion %d\n",thread,i);
  }


  return 0;
  
}
