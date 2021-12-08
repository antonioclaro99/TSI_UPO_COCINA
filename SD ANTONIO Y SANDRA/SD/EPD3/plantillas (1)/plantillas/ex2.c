#include <stdio.h>
#include <omp.h>

int main (int argc, char** argv) {
        
  int i=0, j=0, s=0, h=0;
  print("Specify the number of thread to run:  ");
  scanf("%d", &s);

  omp_set_num_threads(s);
  #pragma omp parallel private(j)
  {
    #pragma omp for schedule(static,5)
    for(i=0; i<20; i++){
      j=omp_get_thread_num();
      printf("Exectution of thread %d: i=%d\n", j,i);
    }
  
    printf("I'm done!\n");
  }
  
  printf("Final value of i: %d\n",i);

  return 0;

}
