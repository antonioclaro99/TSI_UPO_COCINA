#include <omp.h>
#include <stdio.h>
 
#define N 10
#define NTH 4
 
int main (void){
  
  int tid=0,i=0;
  omp_set_num_threads(NTH);
  
  printf("\nParallel #1: planificación estática, chunk size = 3\n\n");
  #pragma omp parallel private(tid)
  {
      tid = omp_get_thread_num();
 
      #pragma omp for schedule(static,3)
       for ( i = 0 ; i < N; i++){
      	printf("thread %d, iteracion %d\n",tid,i);
      } 
  }

  printf("\nParallel #2: planificación dinámica\n\n");
  #pragma omp parallel private(tid)
  {
      tid = omp_get_thread_num();
 
     #pragma omp for schedule(dynamic)
      for ( i = 0 ; i < N; i++){
       printf("thread %d, iteracion %d\n",tid,i);
      } 
  }

  printf("\nParallel #3: planificación guided\n\n");
  #pragma omp parallel private(tid)
  {
      tid = omp_get_thread_num();
 
      #pragma omp for schedule(guided)
      for ( i = 0 ; i < N; i++){
        printf("thread %d, iteracion %d\n",tid,i);
      } 
  }

  printf("\nParallel #3: planificación auto\n\n");
  #pragma omp parallel private(tid)
  {
      tid = omp_get_thread_num();
 
      #pragma omp for schedule(auto)
      for ( i = 0 ; i < N; i++){
       printf("thread %d, iteracion %d\n",tid,i);
      } 
  }

  return 0;

}
