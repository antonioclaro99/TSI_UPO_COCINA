/*

E3. Programe una aplicaci�n cliente/servidor con sockets para testar las funciones de conversi�n de 
representaci�n binaria de enteros. El cliente leer� por la l�nea de comandos dos n�meros enteros, 
los convertir� a representaci�n en red, los almacenar� en un vector de dos posiciones, lo enviar� 
al servidor y, por �ltimo, recibir� del servidor la suma de ambos n�meros. Por su parte, el servidor, 
recibir� el vector con los dos enteros, realizar� el cambio de representaci�n de red a host, sumar� 
los dos valores y enviar� el resultado al cliente. 

Tanto el cliente como para el servidor deber�n mostrar los valores enteros recibidos/enviados en 
representaci�n binaria en red y representaci�n binaria en host con la idea de comparar los valores 
de los mismos en ambos casos.

Un ejemplo de ejecuci�n de la aplicaci�n ser�a:

>./cliente 20 50

[HOST] Sumandos: 20 , 50
[RED]  Sumandos: 335544320 , 838860800
[RED]  Resultado: 1174405120 
[HOST] Resultado: 70

>./servidor

Esperando conexi�n
Recibido: 335544320, 838860800
[HOST] Recibido: 20, 50
[HOST] Suma: 70
[RED] Suma: 1174405120

Consideraciones para realizar el ejercicio:

-	Utilice el c�digo de la plantilla e2.c.
-	Estudie las funciones C para realizar el parseo de cadena de caracteres a enteros y el cambio 
de representaci�n binaria. Estas son:

		o	stdlib.h: strtol.
		o	netinet/in.h: htons, htonl, ntohs, ntohl.

*/

// **** E3.c.1.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

    printf("HOLAAA");


 
    
    return 0;
}
