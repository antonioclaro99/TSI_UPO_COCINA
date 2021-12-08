#include <stdio.h>
#include <omp.h>

int i=0;
int j=0;
int k=0;

#pragma omp threadprivate(k)

int main(void){

    omp_set_num_threads(3);        

	#pragma omp parallel private(j) shared(i)
    {
        j=k;
        i++;j++;k++;
        printf("TID %d: i=%d, j=%d, k=%d\n", omp_get_thread_num(),i,j,k);
    }

    return 0;
}
