#include <stdio.h>
#include <mpi.h>
#include <omp.h>

#define SIZE 20
#define MASTERPID 0	
 
int main(int argc, char **argv) {

	 // ** Declaración de variables 
	float A[SIZE], B[SIZE], Alocal[SIZE], Blocal[SIZE], Rlocal[SIZE], R[SIZE];
	int pid, prn, i, splitSize, restSize; 
  	
  	// ** Inicio del entorno MPI 
  	MPI_Init(&argc,&argv); 

  	// ** Obtención del PID 
  	MPI_Comm_rank(MPI_COMM_WORLD,&pid); 
  
  	// ** Obtención del número de PRN 
  	MPI_Comm_size(MPI_COMM_WORLD,&prn); 
    
    // ** Calcular el tamaño de los vectores parciales en splitSize
   	splitSize = SIZE/prn;
	restSize = SIZE%prn; 

	// ** Inicialización de los vectores A y B globales por parte del master
	if (pid == MASTERPID) {

		printf("\n[%d] Vector A = ", pid);
		for (i = 0; i < SIZE;i++)  {
			A[i] = i+1;
			printf("%4.0f", A[i]);
		}

		printf("\n[%d] Vector B = ", pid);
		for (i = 0; i < SIZE;i++)  {
			B[i] = i+SIZE;
			printf("%4.0f", B[i]);
			
		}

		printf("\n[%d] Split size = %d, Rest = %d\n\n", pid,splitSize,restSize);

	}

	// ** Reparto del vector A
    MPI_Scatter(A, splitSize,MPI_FLOAT, Alocal, splitSize, MPI_FLOAT, MASTERPID, MPI_COMM_WORLD); 
   
   	// ** Reparto del vector B
    MPI_Scatter(B,splitSize, MPI_FLOAT,Blocal, splitSize, MPI_FLOAT, MASTERPID,  MPI_COMM_WORLD); 

	printf("\n[%d] A local = ", pid); 
	for (i = 0; i < splitSize;i++)  
		printf("%4.0f", Alocal[i]);
	
	printf("\n[%d] B local = ", pid); 
	for (i = 0; i < splitSize;i++)  
		printf("%4.0f", Blocal[i]);
	printf("\n");
   	
   	// ** Cálculo del vector suma en paralelo
   	#pragma omp parallel for
    for (i=0;i<splitSize;i++){
    	Rlocal[i] = Alocal[i]+Blocal[i];
    	printf("[%d,%d] R[%d] = %.0f\n", pid, omp_get_thread_num(),i,Rlocal[i]);
    } 
    	 
    
    // ** Recolección de los resultados
	MPI_Gather(Rlocal, splitSize, MPI_FLOAT, R, splitSize, MPI_FLOAT, MASTERPID, MPI_COMM_WORLD);
 
    // ** Si sobran elementos en el reparto, cálculo del resto de componentes por parte del master
    if (pid == MASTERPID) {

    	if(restSize!=0){

    		printf("\n[%d] Resto del vector A = ", pid);
			for (i=SIZE-restSize;i<SIZE;i++)  printf("%5.0f", A[i]);

			printf("\n[%d] Resto del vector B = ", pid);
			for (i = SIZE-restSize;i<SIZE;i++)  printf("%5.0f", B[i]);
			
			printf("\n");
			
			#pragma omp parallel for	
			for (i=SIZE-restSize;i<SIZE;i++){
				R[i] = A[i]+B[i];
				printf("[%d,%d] R[%d] = %.0f\n", pid, omp_get_thread_num(),i,R[i]);
			} 
		    		
    	}

    	printf("\n[%d] Vector Suma = ", pid);
		for (i = 0; i < SIZE;i++)  
			printf("%4.0f", R[i]);

		printf("\n\n");
		
    }

    // ** Finalización del entorno MPI
    MPI_Finalize();
    
    return 0;
}
