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

// **** E3.s.1.
// Inclusi�n de librer�as correctas.
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PUERTO_SERVIDOR 2100
#define NUMERO_CLIENTES_COLA 5

int main(int argc, char *argv[]) {

    int sd=0,sc=0,red[2],host[2],suma_host=0,suma_red=0,i=0;
    struct sockaddr_in server_addr;
    
    for (i=0;i<2;i++){
        red[i]=0;
        host[i]=0; 
    }

    // **** E3.s.2.
    // Construcci�n del socket servidor.
    sd = socket(PF_INET,SOCK_STREAM,0);

    if(sd < 0) {
        perror("Error al construir el socket servidor\n");
        exit(EXIT_FAILURE);
    }
    
    // **** E3.s.3.
    // Construcci�nn de la sockaddr_in.
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PUERTO_SERVIDOR);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // **** E3.s.4.
    // Realizar bind.
     if(bind(sd,(struct sockaddr *) &server_addr, sizeof(server_addr))<0){
        perror("Error al realizar el bind\n");
        close(sd);
        exit(EXIT_FAILURE);
    }
    
    // **** E3.s.5.
    // Realizar listen.
     if(listen(sd,NUMERO_CLIENTES_COLA)<0){
        perror("Error al realizar el listen\n");
        close(sd);
        exit(EXIT_FAILURE);
    }
    
    while (1){

        printf("Esperando conexi�n\n");
        
        // **** E3.s.6.
        // Aceptar conexi�n.
        sc = accept(sd, NULL, NULL);
        if(sc<0)
            perror("Error al realizar el accept\n");
        
        // **** E3.s.7.
        // Recepci�n del vector.
	    if(read(sc,red,sizeof(red))<0){
        	perror("Error al recibir datos del cliente\n");
            close(sc);
        }

        // **** E3.s.8.
        // Traza de los valores en red y en host
		printf("Recibido: %d, %d\n",red[0],red[1]);

		host[0]=ntohl(red[0]);
		host[1]=ntohl(red[1]);

		printf("[HOST] Recibido: %d, %d\n",host[0],host[1]);
        
        // **** E3.s.9.
        // Conversi�n de representaci�n
        suma_host = host[0] + host[1];
        suma_red = htonl(suma_host);

        printf("[HOST] Suma: %d\n",suma_host);
        printf("[RED] Suma: %d\n",suma_red);

        // **** E3.s.10.
        // Env�o de resultados en formato red
        if (write(sc,&suma_red,sizeof(suma_red)) < 0 ) {
              perror("Error al enviar datos del cliente\n");
              close(sc);
        }

        close(sc);
    }

    close (sd);

    return 0;
}
