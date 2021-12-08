#include <omp.h>
#include <stdio.h>

#define N 10

int main(int argc, char **argv) {

  int i=0, j=0, tid=0;

  printf("\nParallel #1: erróneo\n\n");
 
  #pragma omp parallel private(i, j)
  {
    for (i = 0; i < N; i++) 
      for (j = 0; j < N; j++) {
        tid = omp_get_thread_num();
	  	}
    printf("Get = %d, TID = %d\n", omp_get_thread_num(), tid);
  }
  
  printf("\nParallel #2: correcto\n\n");

  #pragma omp parallel private(i, j, tid)
  {
    for (i = 0; i < N; i++) 
      for (j = 0; j < N; j++) {
        tid = omp_get_thread_num();
      }
    printf("Get = %d, TID = %d\n", omp_get_thread_num(), tid);
  }
 
  return 0;
 
}
