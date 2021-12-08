#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 12

void main (void)  {

	omp_set_num_threads(4);

	int   i;
	float a[N], b[N], result= 0.0;
	
	for (i=0; i < N; i++)
	  {
		  a[i] = i * 1.0;
		  b[i] = i * 2.0;
	  }
	
/* 
########## PRIMER TEST ##########
No compila puesto que, al establecer la cláusula default(none), debemos especificar el explícitamente
al ámbito de las variables a y b. 

El compilador no arroja errores sobre las variables i ni result puesto que i es privada por defecto 
al ser el índice del bucle en la directiva for y result la variable de reducción en la cláusula reduction.

Para solucionar el problema, simplemente quitamos la cláusula default(none).
*/

	// #pragma omp parallel for default(none) schedule(static,3) reduction(+:result)
	// for (i=0; i < N; i++) result = result + (a[i] * b[i]);
	// printf("RESULTADO = %.1f\n",result);
	

/* 
########## SEGUNDO TEST ##########
El bucle secuencial ejecuta las iteraciones en orden y las sumas parciales de cada ciclo 
depende directamente del ciclo anterior.

En el bucle paralelizado, las iteraciones se dividen en trozos de 3 ciclos (4 trozos en total) y son
asignados a cada hilo para que lo ejecuten de manera independiente y paralela. Las sumas parciales 
de cada ciclo son dependientes para el chunk asignado a un hilo pero independientes entre los hilos.

Al final del bucle todos los threads sumarán el valor de sus variables result para actualizar la 
copia global del master thread.
*/

	printf("\n**** TEST #2 ****\n\n");
	
	result = 0.0;
	
	printf("Secuencial:\n");  

	#pragma omp parallel for schedule(static,3) reduction(+:result) if(0)
	
	for (i=0; i < N; i++){
		result = result + (a[i] * b[i]);
		printf("TID %d: i = %d, sumando %.1f\n",omp_get_thread_num(),i,result);
	}
	
	printf("RESULTADO = %.1f\n",result);

	printf("\nParalelo:\n"); 
	result = 0.0;

	#pragma omp parallel for schedule(static,3) reduction(+:result) if(1)
	
	for (i=0; i < N; i++){
		result = result + (a[i] * b[i]);
		printf("TID %d: i = %d, sumando %.1f\n",omp_get_thread_num(),i,result);
	}
	
	printf("RESULTADO = %.1f\n",result);

/* 
########## TERCER TEST ##########
Podemos observar que cada hilo actualiza el valor de result de manera independiente.
Esto se debe a que al establecer result como variable reduction, por defecto, cada hilo 
tendrá su propia copia de result para procesarla de manera independiente. 
Al final del bucle todos los threads sumarán el valor de sus variables result para actualizar la 
copia global del master thread.
*/

	printf("\n**** TEST #3 ****\n\n");
	
	result = 0.0;
	
	#pragma omp parallel for schedule(static,3) reduction(+:result) if(1)	
	for (i=0; i < N; i++){
		printf("TID %d: i = %d, result = %.1f\n",omp_get_thread_num(),i,result);
		result = result + (a[i] * b[i]);
		printf("TID %d: i = %d, sumando %.1f\n",omp_get_thread_num(),i,result);
	}
	
	printf("RESULTADO = %.1f\n",result);


	printf("\n");



}