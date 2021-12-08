#include <stdio.h>
#include <omp.h>



int main(int argc, char** argv){
   
    int i = 0;	

   printf("\nParallel #1: con copyprivate\n\n");
  
   #pragma omp parallel private(i) num_threads(3) 
   {
      
      #pragma omp single copyprivate(i)
      {
        // Only a single thread can read the input.
        printf("\n[thread %d] Read input\n",omp_get_thread_num());
	      scanf("%d",&i);
        printf("\n");
      }

      // Multiple threads in the team compute the results.
      printf("[thread %d] Compute results %d + 1\n",omp_get_thread_num(),i);
      i=i+1;                 	
   
      #pragma omp single
      // Only a single thread can write the output.
      printf("[thread %d] Write output %d\n",omp_get_thread_num(),i);
   
    }
    
     printf("\nOut of the parallel region: i = %d\n\n",i);

    printf("\nParallel #2: sin copyprivate\n\n");
  
   #pragma omp parallel private(i) num_threads(3) 
   {
      
      #pragma omp single
      {
        // Only a single thread can read the input.
        printf("\n[thread %d] Read input\n",omp_get_thread_num());
        scanf("%d",&i);
        printf("\n");
      }

      // Multiple threads in the team compute the results.
      printf("[thread %d] Compute results %d + 1\n",omp_get_thread_num(),i);
      i=i+1;                  
   
      #pragma omp single
      // Only a single thread can write the output.
      printf("[thread %d] Write output %d\n",omp_get_thread_num(),i);
   
    }
    
     printf("\nOut of the parallel region: i = %d\n\n",i);



     printf("\nParallel #3: i compartida\n\n");

     #pragma omp parallel shared(i) num_threads(3) 
   {
      
      #pragma omp single
      {
        // Only a single thread can read the input.
        printf("\n[thread %d] Read input\n",omp_get_thread_num());
        scanf("%d",&i);
        printf("\n");
      }

      // Multiple threads in the team compute the results.
      printf("[thread %d] Compute results %d + 1\n",omp_get_thread_num(),i);
      i=i+1;                  
   
      #pragma omp single
      // Only a single thread can write the output.
      printf("[thread %d] Write output %d\n",omp_get_thread_num(),i);
   
    }
    
     printf("\nOut of the parallel region: i = %d\n\n",i);

     return 0;
}
