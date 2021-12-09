#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char *argv[])
{

    MPI_File  fh;
    int pid, prn;

    float datos[24];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    MPI_Comm_size(MPI_COMM_WORLD, &prn);

    MPI_Aint lb, extent;
    MPI_Datatype etype, filetype, contig;
    MPI_Offset disp;
    MPI_Type_contiguous(1, MPI_FLOAT, &contig);
    lb = 0;
    extent = sizeof(float)+1;
    MPI_Type_create_resized(contig, lb, extent, &filetype);
    MPI_Type_commit(&filetype);
    disp = 2 * sizeof(int);
    etype = MPI_FLOAT;
    MPI_File_open(MPI_COMM_WORLD, "./datos_1X.txt",
                  MPI_MODE_RDWR, MPI_INFO_NULL, &fh);
    MPI_File_set_view(fh, disp, etype, filetype, "native",
                      MPI_INFO_NULL);
    MPI_File_read(fh, datos, 24*sizeof(float), MPI_FLOAT, MPI_STATUS_IGNORE);

    for (size_t i = 0; i < 24; i++)
    {
        printf("\nProceso[%d]: %5.2f \n",pid,datos[i]);
    }
    

    MPI_Finalize();

    return 0;
}