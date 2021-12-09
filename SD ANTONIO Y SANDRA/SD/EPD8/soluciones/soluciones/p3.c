#include <stdio.h>
#include <mpi.h>
#include <omp.h>
#include <math.h>

#define SIZE 10
#define MASTERPID 0	

int main(int argc, char **argv) {

	 // ** Declaración de variables 
	float X[SIZE], Y[SIZE], Xlocal[SIZE], Ylocal[SIZE], sumaParcial=0.0,sumaTotal=0.0;
	int pid, prn, i, splitSize, restSize, info; 
  	
  	// ** Inicio del entorno MPI 
  	MPI_Init(&argc,&argv); 
  	//MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &info);

  	// ** Obtención del PID 
  	MPI_Comm_rank(MPI_COMM_WORLD,&pid); 
  
  	// ** Obtención del número de PRN 
  	MPI_Comm_size(MPI_COMM_WORLD,&prn); 
    
    // ** Calcular el tamaño de los vectores parciales en splitSize
   	splitSize = SIZE/prn;
	restSize = SIZE%prn; 

	// ** Inicialización de los vectores X e Y globales por parte del master
	if (pid == MASTERPID) {

		printf("\n[%d] X = ", pid);
		for (i = 0; i < SIZE;i++)  {
			X[i] = i+1;
			printf("%4.0f", X[i]);
		}

		printf("\n[%d] Y = ", pid);
		for (i = 0; i < SIZE;i++)  {
			Y[i] = SIZE-i;
			printf("%4.0f", Y[i]);
			
		}

		printf("\n[%d] Split size = %d, Rest = %d\n\n", pid,splitSize,restSize);

	}

	// ** Reparto del vector X
    MPI_Scatter(X, splitSize,MPI_FLOAT,Xlocal, splitSize, MPI_FLOAT, MASTERPID, MPI_COMM_WORLD); 
   
   	// ** Reparto del vector Y
    MPI_Scatter(Y,splitSize, MPI_FLOAT,Ylocal, splitSize, MPI_FLOAT, MASTERPID,  MPI_COMM_WORLD); 

	printf("\n[%d] X local = ", pid); 
	for (i = 0; i < splitSize;i++)  
		printf("%4.0f", Xlocal[i]);
	
	printf("\n[%d] Y local = ", pid); 
	for (i = 0; i < splitSize;i++)  
		printf("%4.0f", Ylocal[i]);
	printf("\n");
   	
   	// ** Cálculo del sumatorio local en paralelo
   	#pragma omp parallel for reduction(+:sumaParcial)
    for (i=0;i<splitSize;i++){
    	sumaParcial += pow(Xlocal[i]-Ylocal[i],2);
    	printf("[%d,%d] Iteración %d, Suma parcial = %.0f\n", pid, omp_get_thread_num(),i,sumaParcial);
    } 

    printf("\n[%d] Suma parcial = %.0f\n", pid,sumaParcial); 
    	 
    // ** Reducción de resultados
	MPI_Reduce(&sumaParcial,&sumaTotal,1,MPI_FLOAT,MPI_SUM,MASTERPID,MPI_COMM_WORLD); 
 
    // ** Si sobran elementos en el reparto, cálculo del resto de componentes por parte del master
    if (pid == MASTERPID) {

    	if(restSize!=0){

    		printf("\n[%d] Resto X = ", pid);
			for (i=SIZE-restSize;i<SIZE;i++)  printf("%5.0f", X[i]);

			printf("\n[%d] Resto Y = ", pid);
			for (i = SIZE-restSize;i<SIZE;i++)  printf("%5.0f", Y[i]);
			
			printf("\n");
			
			#pragma omp parallel for reduction(+:sumaTotal) 
			for (i=SIZE-restSize;i<SIZE;i++){
				sumaTotal += pow(X[i]-Y[i],2);
    			printf("[%d,%d] Iteración %d, Suma parcial = %.0f\n", pid, omp_get_thread_num(),i,sumaTotal);
			} 
		    		
    	}

		printf("\n[%d] Suma total = %.0f, Distancia euclídea = %.5f", pid,sumaTotal,sqrt(sumaTotal));
		
		printf("\n");
		
    }

    MPI_Finalize();
    
    return 0;
}
