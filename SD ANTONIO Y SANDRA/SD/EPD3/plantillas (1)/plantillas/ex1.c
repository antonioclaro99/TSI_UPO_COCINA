#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv){
        
    int i=0,j=0,s=0;

    printf("[1] Parallel Execution\n[2] Sequential Execution\nChoice: ");
    scanf("%d", &s);

    omp_set_num_threads(4);
      
    #pragma omp parallel shared(i) private(j) num_threads(3) if(s==1)
    {
        j=omp_get_thread_num();
        for(i=0; i<5; i++) 
            printf("Execution of thread %d: i=%d\n", j,i);
                
    }

    return 0;
}

































