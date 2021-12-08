#include <omp.h>
#include <stdio.h>
#include <unistd.h>

void IncrementX(void);

int x = 0; 

int main(void){

	// **** Inicio de la region paralela
   	printf("[TID %d] incrementando x\n", omp_get_thread_num()); 
   	IncrementX();
   	printf("[TID %d] hecho!, x=%d\n", omp_get_thread_num(),x);
	// **** Fin de la region paralela
		
 	printf("\nVALOR FINAL DE x: %d",x);

 	return 0;
}

void IncrementX(void){

    int Temp; 
    Temp = x;
    sleep(1); 
    Temp = Temp + 1;
    x = Temp;

}
