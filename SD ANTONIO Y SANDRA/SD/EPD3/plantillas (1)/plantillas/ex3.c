#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv){

        int j = 0, i = 0;
        omp_set_num_threads(3);
        
        #pragma omp parallel private(i)
        {
                #pragma omp sections
                {
                        #pragma omp section
                        {
                                for(i = 0; i < 5; i++) printf("Thread %d: block 1\n", omp_get_thread_num());
                        }
                        #pragma omp section
                        {
                                for(i = 0; i < 5; i++) printf("Thread %d: block 2\n",omp_get_thread_num());
                        }
                        #pragma omp section
                        {
                                for(i = 0; i < 5; i++) printf("Thread %d: block 3\n",  omp_get_thread_num());
                        }
                }
        }

        return 0;
}


