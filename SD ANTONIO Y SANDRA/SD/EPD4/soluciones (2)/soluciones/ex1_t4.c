#include <stdio.h>
#include <omp.h>

int i=1;
int j=2;
int k=3;

#pragma omp threadprivate(k)

void main(void){

	omp_set_num_threads(3);

/* 
########## CUARTO TEST ##########
i. Sí se imprime lo esperado puesto que hemos puesto a 1 la vaiable y es compartida. 
Para esta variable, el experimento se reproduce ya que se repite la traza y el resultado.

j. Imprime en el resultado j=2, puesto que es una variable privada y no tenemos cláusula lastprivate 
para recuperar su valor. 
En la traza, tendrá os valores que k. Para esta variable, el experimento no se reproduce 
en el la traza pero sí en el resultado.

k. Los hilos 1 y 2 no verán el efecto de poner a tres la variable (k valdrá 5) puesto que esta 
asignación la realiza el master thread (hilo 0) en la región secuencial; por este hecho, los 
hilos 1 y 2 muestran k=5 mientras que el hilo 0 (master) muestra el valor 4 en la traza de la 
región paralela. El resultado final de k será cuatro puesto que se imprime el valor en la parte 
secuencial del código, es decir, el valor del hilo 0. El experimento no se reproduce 
en el la traza pero sí en el resultado.

*/

	printf("\n**** Test #4 ****\n\n");
 
 	#pragma omp parallel private(j) shared(i)
    {
    	j=k;
    	i++;j++;k++;           
        printf("TID %d: i=%d, j=%d, k=%d\n", omp_get_thread_num(),i,j,k);
    }

    printf("\nRESULTADO: i = %d, j = %d, k = %d\n\n",i,j,k);

	i=1;j=2;k=3;

	#pragma omp parallel private(j) shared(i)
    {
    	j=k;
    	i++;j++;k++;           
        printf("TID %d: i=%d, j=%d, k=%d\n", omp_get_thread_num(),i,j,k);
    }

    printf("\nRESULTADO: i = %d, j = %d, k = %d\n\n",i,j,k);

}