#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv) {

  int i, j, tid, n;
  
  #pragma omp parallel private(i, j)
  {
  for (i = 0; i < 1000; i++) 
    for (j = 0; j < 1000; j++)
      tid = omp_get_thread_num();
  
  printf("Thread %d : My value of tid (thread id) is %d\n", omp_get_thread_num(), tid);
  }
  
  return 0;

}
