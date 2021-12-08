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
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PUERTO_SERVIDOR 2100
#define IP_SERVIDOR "127.0.0.1"

int main(int argc, char* argv[]) {

    int i=0,c=0,sd=0,host[2],red[2],suma_host=0,suma_red=0;
    struct sockaddr_in server_addr;
    struct hostent *hp;

        int n1 =  0;
    int n2 =  0;

    n2 = sscanf(argv[1],"%d");
    printf("%d",n2);
    printf("HOLAAA");
    
    for (i=0;i<2;i++){
        host[i]=0;
        red[i]=0; 
    }

    // **** E3.c.2.
    // Comprobar el correcto n�mero de par�mtros de la l�nea de comandos
    if(argc !=2){
        printf("El numero de parametros es incorrecto, deben ser 2 numeros enteros");
        exit(1);
    }


    
    // **** E3.c.3.
    // Construcci�n del Socket del servidor.
    int sockfd;
    sockfd = socket ( AF_INET, SOCK_STREAM, 0 );

   
    // **** E3.c.4.
    // Construcci�n de la sockaddr_in.
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons ( PUERTO_SERVIDOR );
    server_addr.sin_addr.s_addr = inet_addr (IP_SERVIDOR);



    // **** E3.c.5.
    // Conexi�n a servidor.
    int conexion=connect ( sockfd, (struct sockaddr *) &server_addr, sizeof (server_addr) );
    if(!conexion){
        printf("No se ha podido conectar con el servidor");
        exit(1);
    }
    

    // **** E3.c.6.
    // Parseo y conversi�n de formato de los par�metros de entrada





    printf("[HOST] Sumandos: %d , %d\n",host[0],host[1]);
    printf("[RED]  Sumandos: %d , %d\n",red[0],red[1]);
	
    
    // **** E3.c.7.
    // Env�o de par�metros
   	
   	// **** E3.c.8.
    // Recepci�n de resultados

    // **** E3.c.9.
    // Presentaci�n de resultados

    printf("[RED]  Resultado: %d \n", suma_red);
    printf("[HOST] Resultado: %d \n", suma_host);

    
    close (sd);
    
    return 0;
}
