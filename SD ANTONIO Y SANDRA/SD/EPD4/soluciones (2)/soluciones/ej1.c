#include <omp.h>
#include <stdio.h>
#include <unistd.h>

void IncrementX(void);

int x = 0;  

int main(void) {

  printf("\n");	

	#pragma omp parallel num_threads(25)
  {
    #pragma omp critical
    {	   
      printf("[TID %d] incrementando x\n", omp_get_thread_num()); 
		  IncrementX();
    } 
    printf("[TID %d] hecho!, x=%d\n", omp_get_thread_num(),x);
 	}
	
  printf("\nVALOR FINAL DE x: %d\n\n",x);

  return 0;

}

void IncrementX() {

    int Temp; 
    Temp = x;
    sleep(1); 
    Temp = Temp + 1;
    x = Temp;
}