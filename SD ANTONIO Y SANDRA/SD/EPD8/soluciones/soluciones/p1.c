#include <stdio.h>
#include <mpi.h>
#include <omp.h>

#define SIZE 300

int main(int argc, char *argv[]) {
  
  // ** Declaración de variables 
  int pid, prn, length, tid, trn;
  char nombre[SIZE];

  // ** Inicio del entorno MPI 
  MPI_Init(&argc,&argv); 

  // ** Obtención del PID 
  MPI_Comm_rank(MPI_COMM_WORLD,&pid); 
  
  // ** Obtención del número de PRN 
  MPI_Comm_size(MPI_COMM_WORLD,&prn); 

  // ** Obtención del nombre del procesador
  MPI_Get_processor_name(nombre,&length);

  // ** Lanzamos los threads
  #pragma omp parallel private(tid, trn) num_threads(4)
  {
    trn = omp_get_num_threads();
    tid = omp_get_thread_num();
    printf("[%s] PID = %d/%d, TID = %d/%d\n",nombre, pid, prn, tid, trn);
  }

  // ** Finalizar el entorno MPI
  MPI_Finalize();

  return 0;
}
