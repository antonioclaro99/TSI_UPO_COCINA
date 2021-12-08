#include <omp.h>
#include <stdio.h>

int main (int argc, char** argv){
 
int nth=0,tid=0;

omp_set_num_threads(10);

printf("\n");

#pragma omp parallel private(nth, tid)
{
 
  tid = omp_get_thread_num();
 
  nth = omp_get_num_threads();
 
  printf("Hola Mundo soy el thread = %d de %d en total.\n",tid, nth);

}

printf("\n");

return 0;

}
