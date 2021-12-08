#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv){

  int i = 0;
    
  #pragma omp parallel private(i) num_threads(3)
  {
    #pragma omp single copyprivate(i)
    {
      printf("Read input\n");
      scanf("%d",&i);
    }
      
    printf("compute results %d +1\n",i);
    i=i+1;                  
      
    #pragma omp single
    printf("write output %d\n",i);
    
  }

  return 0;
}
