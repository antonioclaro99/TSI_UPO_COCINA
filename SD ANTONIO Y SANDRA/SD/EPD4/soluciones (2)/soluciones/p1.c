#include <stdio.h>
#include <math.h>
#include <time.h>
#include <omp.h>
#include <stdlib.h>

void main (void)
{

  double a=0.0, b=10.0, error=0.0, exact=0.49936338107645674464,pi = 3.141592653589793,total=0.0,wtime=0.0,wtime1=0.0, wtime2=0.0;
  int i, n = 1000000;
  double *x;

  printf("\nIntegral exacta = 0.49936338107645674464\n");

  x = (double*) malloc(n*sizeof(double));

  for (i=0;i<n;i++) x[i]=((double) (n-i-1)*a + (double)(i)*b)/(double)(n-1);
  
  wtime1 = omp_get_wtime();
  total = 0.0;

  #pragma omp parallel for private(i) shared(n,pi,x) reduction(+:total)
  for (i=0;i<n;i++) total += 50/(pi*(2500.0*x[i]*x[i]+1.0));
      
  wtime2 = omp_get_wtime();
  total = (b-a) * total/ (double)n;

  error = fabs(total-exact);
  wtime = wtime2-wtime1;

  printf("\n" );
  printf("Estimado           = %.20f\n",total);
  printf("Error              = %.20f\n",error);
  printf("Tempo de ejecución = %f\n\n",wtime);

}