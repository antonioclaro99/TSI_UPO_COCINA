#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI24 3.141592653589793238462643

void uso(char *);
double f(double); 

int main (int argc, char *argv[]) {

  int nth=0, tid=0, n=1000, i=0;
  double d=0.0, x=0.0, sum=0.0, pi=0.0;
  double starttime=0.0, stoptime=0.0;
  char c=' ';

  if (argc!=2) 
    uso(argv[0]);
  else
    n = strtol(argv[1],NULL,10); 
    
  d = 1.0/(double) n;

  #pragma omp parallel default(shared) private(nth,tid,x)
  {
    
    tid = omp_get_thread_num();
    
    if (tid == 0) {
      nth = omp_get_num_threads();
      starttime = omp_get_wtime();
    }

  #pragma omp for reduction(+:sum) 
    for (i=0; i<n; i++) {
      x = d*(double)i;
      sum += f(x) + f(x+d);
    }

  }  

  pi = d*sum*0.5;

  stoptime = omp_get_wtime();
  printf("PI calculado = %2.24f\n", pi);
  printf("PI \"exacto\" = %2.24f\n", PI24);
  printf("Error = %e\n", fabs(PI24-pi));
  printf("Tiempo de ejecución = %3.2fs\n", stoptime-starttime);
  printf("Precisión del reloj = %2.6fs \n\n", omp_get_wtick());

  return 0;
}

void uso(char *s) {
  printf("Uso: %s [intervalos]\n", s);
  exit(0);
}

double f(double x) {
  return (4.0 / (1.0 + x*x));
}

