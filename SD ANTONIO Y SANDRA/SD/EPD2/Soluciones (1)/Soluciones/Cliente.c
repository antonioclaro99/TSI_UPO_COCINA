#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#define TAM 1024
#define IP_SERVIDOR "127.0.0.1"
#define PUERTO_SERVIDOR 1100

int main(void){
	
    // Datos de envío
    char datosAenviar [TAM]= "## Test 1 ##";

    // Variables del para el socket del servidor.
    int socketServidor;
    struct sockaddr_in direccionSocketServidor;
    char datosRecibidos[TAM];

    // ***** Paso 1: construcción del socket servidor y tratamiento del error.

    if ((socketServidor=socket(AF_INET,SOCK_STREAM,0))<0){
       perror("ERROR AL CONSTRUIR EL SOCKET CLIENTE");
       exit(EXIT_FAILURE);
    }

    // ***** Paso 2: construcción del sockaddr_in del socket del servidor y tratamiento de errores.

    direccionSocketServidor.sin_family = AF_INET;
    direccionSocketServidor.sin_port = htons(PUERTO_SERVIDOR);
    if (inet_pton(AF_INET,IP_SERVIDOR,&direccionSocketServidor.sin_addr.s_addr)<=0){
        perror("ERROR EN LA IP DEL SERVIDOR");
        close(socketServidor);
        exit(EXIT_FAILURE);
    }

    // ***** Paso 3: realizar conexión con el servidor.
    if (connect(socketServidor,(struct sockaddr *) &direccionSocketServidor,sizeof(direccionSocketServidor))<0){
        perror("ERROR EN LA CONEXIÓN CON EL SERVIDOR");
        close(socketServidor);
        exit(EXIT_FAILURE);
    }

    printf("[CLIENTE] Enviando al servidor el mensaje: %s\n",datosAenviar);
    
    // ***** Paso 4: envío de datos al servidor y tratamiento del error.
     if (write(socketServidor,datosAenviar,sizeof(datosAenviar))<0) {
              perror("ERROR AL ENVIAR DATOS AL SERVIDOR");
              close(socketServidor);
              exit(EXIT_FAILURE);
    }

    // ***** Paso 5: recepción de datos del servidor y tratamiento del error.
    if(read(socketServidor,datosRecibidos,sizeof(datosRecibidos))<0) {
            perror("ERROR AL RECIBIR DATOS DEL SERVIDOR");
            close(socketServidor);
            exit(EXIT_FAILURE);
    }

     printf("[CLIENTE] Recibido el siguiente mensaje del servidor: %s\n",datosRecibidos);

    // ***** Paso 10: cierre del socket servidor.
    close(socketServidor);
    
    return EXIT_SUCCESS;
}
