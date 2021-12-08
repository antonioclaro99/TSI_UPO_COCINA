#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PUERTO 1100
#define CAPACIDAD_COLA 10
#define TAM 1024
#define BIENVENIDA "Hola cliente, he recibido el mensaje = "

int main(void){

	// Variables del para el socket del servidor.
	
    int socketServidor;
    struct sockaddr_in direccionSocketServidor; 
    char resultadoOperacion[TAM] = BIENVENIDA;

	// Variables de los sockets de los clientes atendidos.  
    
    int socketCliente;
	struct sockaddr_in direccionSocketCliente;
	int tamanyoDireccionCliente;

	// Variables para el tratamiento de los datos recibidos por el cliente
	char datosRecibidos[TAM];
    char auxiliar[TAM];
	
    // ***** Paso 1: construcción del socket servidor y tratamiento del error.
 
    socketServidor = socket(AF_INET,SOCK_STREAM,0);

    if(socketServidor<0) {
        perror("ERROR AL CONSTRUIR EL SOCKET SERVIDOR");
        exit(EXIT_FAILURE);
    }

    // ***** Paso 2: construcción del sockaddr_in del socket del servidor.
    
    direccionSocketServidor.sin_family = AF_INET;
    direccionSocketServidor.sin_port = htons(PUERTO);
    direccionSocketServidor.sin_addr.s_addr = INADDR_ANY;

    // ***** Paso 3: realización del bind y tratamiento del error.

    if(bind(socketServidor,(struct sockaddr *) &direccionSocketServidor,sizeof(direccionSocketServidor))<0) {
        perror("ERROR AL REALIZAR EL BIND");
        close(socketServidor);
        exit(EXIT_FAILURE);
    }

    // ***** Paso 4: realización del listen y tratamiento del error.

    if(listen(socketServidor,CAPACIDAD_COLA)<0){
        perror("ERROR AL REALIZAR EL LISTEN");
        close(socketServidor);
        exit(EXIT_FAILURE);
    }

    // Bucle de espera activa.

    while(1){

        printf("\n[SERVIDOR] Esperando conexión de cliente\n");
        
        // ***** Paso 5: realización del accept y tratamiento del error.

        socketCliente = accept(socketServidor,(struct sockaddr *) &direccionSocketCliente, &tamanyoDireccionCliente);

        if(socketCliente<0){
            perror("ERROR AL REALIZAR EL ACCEPT");
            close(socketCliente);
        }


		// ***** Paso 6: recepción de datos del cliente y tratamiento del error.
        if(read(socketCliente,datosRecibidos,sizeof(datosRecibidos))<0){
        	perror("ERROR AL RECIBIR DATOS DEL CLIENTE");
            close(socketCliente);
        }

       // ***** Paso 7: realización de operación en servidor sobre los datos recibidos del cliente.
       printf("[SERVIDOR] Datos recibidos del cliente: %s\n",datosRecibidos);

       strcat(resultadoOperacion,datosRecibidos);
       sprintf(auxiliar, " con %ld caracteres", strlen(datosRecibidos));
       strcat(resultadoOperacion, auxiliar);

       printf("[SERVIDOR] Voy a enviar el siguiente mensaje: %s\n",resultadoOperacion);

       // ***** Paso 8: envío de datos al cliente y tratamiento del error.
        if (write(socketCliente,resultadoOperacion,sizeof(resultadoOperacion))<0){
              perror("ERROR AL ENVIAR DATOS AL CLIENTE");
              close(socketCliente);
        }

        strcpy(resultadoOperacion, BIENVENIDA);
        
		// ***** Paso 9: cierre del socket cliente.
        close(socketCliente);
    }

	// ***** Paso 10: cierre del socket servidor.
    close(socketServidor);
   
    return EXIT_SUCCESS;
}
