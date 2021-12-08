#include <omp.h>
#include <stdio.h>

#define NRA 20                 
#define NCA 5                 
#define NCB 5                  

int main (int argc, char *argv[])  {

  int	tid=0,nth=0,i=0,j=0,k=0,chunk=10;
  double a[NRA][NCA],b[NCA][NCB],c[NRA][NCB];          

  #pragma omp parallel shared(a,b,c,nth,chunk) private(tid,i,j,k)
  {
    
    tid = omp_get_thread_num();
    if (tid == 0){
      nth = omp_get_num_threads();
      printf("[thread %d] NTH =  %d\n",tid,nth);
      printf("[thread %d] Inicialización de matrices\n",tid);
    }
    
    #pragma omp for schedule (static, chunk) 
    for (i=0; i<NRA; i++)
      for (j=0; j<NCA; j++)
        a[i][j]= i+j;
  
    #pragma omp for schedule (static, chunk)
    for (i=0; i<NCA; i++)
      for (j=0; j<NCB; j++)
        b[i][j]= i*j;
    #pragma omp for schedule (static, chunk)
    for (i=0; i<NRA; i++)
      for (j=0; j<NCB; j++)
        c[i][j]= 0;

    printf("[thread %d] Multiplicando matrices\n",tid);
  
    #pragma omp for schedule (static, chunk)
    for (i=0; i<NRA; i++){
      printf("[thread %d] Procesando la fila %d\n",tid,i);
      for(j=0; j<NCB; j++)       
        for (k=0; k<NCA; k++)
          c[i][j] += a[i][k] * b[k][j];
    }

  }   

  printf("\n***** Matrices *****\n\n");
  printf("Matriz A:\n");
  for (i=0; i<NCA; i++)
    for (j=0; j<NCB; j++){
      printf("%8.2f",a[i][j]);
      if (j==NCB-1)
        printf("\n");           
    }

  printf("\n");

  printf("Matriz B:\n");
  for (i=0; i<NRA; i++)
    for (j=0; j<NCA; j++){
      printf("%8.2f",a[i][j]);
      if (j==NCB-1)
        printf("\n");           
    }

  printf("\n***** Resultado *****\n\n");
  for (i=0; i<NRA; i++)
    for (j=0; j<NCB; j++){
      printf("%8.2f",c[i][j]);
      if (j==NCB-1)
        printf("\n");           
    }
  
  printf ("\nDone.\n");

}
