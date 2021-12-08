#include <omp.h>
#include <stdio.h>
#define N 10000

int main(void) {

	int i=0,sums=0,sump=0,sumLocal=0,a[N];
    
  for (i = 0; i < N; i++) 
    a[i] = i;    
  
  for (i=0;i<N;i++) 
    sums +=a[i];

   #pragma omp parallel private (sumLocal) num_threads(8)
   {
     	sumLocal = 0;

     	#pragma omp for 
     	for (i=0;i<N;i++) sumLocal+=a[i];
         sump+= sumLocal;
   }

	printf("\nSUMA SECUENCIAL = %d\n", sums);
  printf("SUMA PARALELO   = %d\n", sump);
  
  if(sums==sump) 
    printf("OK\n\n"); 
  else 
    printf("ERROR\n\n");

  return 0;
  
}
