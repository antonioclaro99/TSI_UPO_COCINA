#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define THREADS 2
#define MULTI 1
              
void comprueba_parametros(int,  char** const, int*,int*,int*);

int main (int argc, char *argv[])  {

  int tid=0,nth=0,i=0,tamanyo=0,constante_a=0,constante_b=0,resultado=0;
  int *a;
  int *b;
  
  comprueba_parametros(argc,argv,&tamanyo,&constante_a,&constante_b);

  a = (int *) malloc(tamanyo*sizeof(int));
  b = (int *) malloc(tamanyo*sizeof(int)); 

  omp_set_num_threads(THREADS);

  printf("\n***** Inicialización de matrices *****\n");

  #pragma omp parallel private(tid,nth,i) if (MULTI)
  {
    
    tid = omp_get_thread_num();
    nth = omp_get_num_threads();

    #pragma omp for schedule(static) 
    for (i=0; i<tamanyo; i++){
      a[i] = constante_a;
      b[i] = constante_b;
      printf("[%d/%d] a[%d] = %d, b[%d] = %d\n",tid,nth,i,a[i],i,b[i]);
    }
  
  }

  printf("\n***** Cálculo del producto escalar *****\n");

  #pragma omp parallel private(tid,nth,i) if (MULTI)
  {
    
    tid = omp_get_thread_num();
    nth = omp_get_num_threads();

    #pragma omp for schedule(static) reduction(+:resultado)
    for (i=0; i<tamanyo; i++){
      resultado +=a[i]*b[i]; 
      printf("[%d/%d] a[%d]=%d, b[%d]=%d, a[%d]*b[%d]=%d, suma=%d\n",tid,nth,i,a[i],i,b[i],i,i,a[i]*b[i],resultado);
    }
  
  }
    
  printf("\nRESULTADO = %d\n\n",resultado);


}


void comprueba_parametros(int np, char** const param, int* tamanyo, int* constante_a, int* constante_b){

  if (np==4){
    *tamanyo = strtol(param[1],NULL,10); 
    *constante_a = strtol(param[2],NULL,10); 
    *constante_b = strtol(param[3],NULL,10); 
  }
  else{
    printf("Uso del comando: %s tamanyo constante_a constante_b\n", param[0]);
    exit(1);
  }

}




