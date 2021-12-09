#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>
#include <math.h>

#define MASTERPID 0	
#define TAG 0	
#define PI 3.1415926535897932384626433832795029L
#define N 100

double f (double);

int main (int argc, char ** argv){

	int pid, prn, n, i;
	double x=0.0L, sumatorioParcial=0.0L, sumatorioGlobal=0.0L, piCalculado=0.0L;

	// ** Inicio del entorno MPI 
  	MPI_Init(&argc,&argv); 

  	// ** Obtención del PID 
  	MPI_Comm_rank(MPI_COMM_WORLD,&pid); 
  
  	// ** Obtención del número de PRN 
  	MPI_Comm_size(MPI_COMM_WORLD,&prn); 

  	// ** Parsero de n
	n = atoi(argv[1]);

	// ** Cálculo del sumatorio parcial en paralelo
    #pragma omp parallel for reduction (+:sumatorioParcial) 
	for (i=pid+1;i<=n;i+=prn) {
		x = (1.0L/(double)n)*(i-0.5L);
		sumatorioParcial+=f(x);
	}
			
	// ** Reducción en el sumatorio global
	MPI_Reduce(&sumatorioParcial,&sumatorioGlobal,1,MPI_DOUBLE,MPI_SUM,MASTERPID,MPI_COMM_WORLD);

	// ** Presentación de resultados
	if (pid == MASTERPID) {
		piCalculado = (1.0L/n)*sumatorioGlobal;
		printf ("pi = %.35lf, ERROR = %.35lf\n",piCalculado,fabs(piCalculado-PI)); 
	}
	
	// ** Finalización del entorno MPI
	MPI_Finalize ();

	return 0 ;

}

double f (double a) { 
	return 4.0L/(1.0L+pow(a,2)); 
}