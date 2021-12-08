/*

P1. Programe una aplicación cliente/servidor que simule un chat entre ambas partes. 

Para ello, el cliente deberá conectarse al servidor, con el que quiera conversar, 
mediante una IP que obtendrá por la línea de comandos. Una vez obtenida la conexión, 
entrará en un ciclo de envío y recepción de mensajes con el servidor hasta que envíe 
la palabra clave “ciao”, momento en que se terminará la conversación y, por ende, 
la ejecución del cliente. 

Por su parte, el servidor, una vez recibida la conexión del cliente, entrará, del 
mismo modo, en un ciclo de envío y recepción de mensajes con el cliente hasta que 
reciba la palabra clave “ciao”, momento en que cerrará la conexión con éste y se 
volverá a poner a la espera de una nueva conexión. 

Requisitos del problema:

-   Los mensajes de envío y recepción serán cadenas de caracteres que introducirá 
el usuario por teclado.

-   Los mensajes enviados entre cliente y servidor no admitirán espacios en 
blanco ni caracteres no registrados en el código ASCII. Por ejemplo, para enviar el mensaje “Hola, ¿ qué tal ?” el usuario deberá escribir “Holaquetal?”.

*/

// ** P1.s.1. Inclusión de librerías.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

// ** P1.s.2. Definición de macros.
#define TAM 1024
#define CIAO "ciao"
#define PUERTO_SERVIDOR 1100
#define CLIENTES_EN_COLA 5

int main(void){

	// ** P1.s.3. Definición de variables relacionadas con el socket servidor.
    int socketServidor;
    struct sockaddr_in direccionSocketServidor; 
    char respuesta[TAM] = "";
    int cierre = 0;

    // ** P1.s.4. Definición de variables relacionadas con los sockets.
    // de los clientes atendidos. 
    int socketCliente;
	char datosRecibidos[TAM];
    char auxiliar[TAM];
    int longitudRecibida;
	
    // ** P1.s.5. Construcción del socket servidor
    socketServidor = socket(PF_INET,SOCK_STREAM,0);
    if(socketServidor < 0) {
        perror("ERROR AL CONSTRUIR EL SOCKET SERVIDOR");
        exit(EXIT_FAILURE);
    }

    // ** P1.s.6. Construcción del sockaddr_in del socket del servidor.    
    direccionSocketServidor.sin_family = AF_INET;
    direccionSocketServidor.sin_port = htons(PUERTO_SERVIDOR);
    direccionSocketServidor.sin_addr.s_addr = INADDR_ANY;

    // ** P1.s.7. Realización del bind.
    if(bind(socketServidor,(struct sockaddr *)&direccionSocketServidor,sizeof(direccionSocketServidor))<0){
        perror("ERROR AL REALIZAR EL BIND");
        close(socketServidor);
        exit(EXIT_FAILURE);
    }

    // ** P1.s.8. Realización del listen.
    if(listen(socketServidor,CLIENTES_EN_COLA)<0){
        perror("ERROR AL REALIZAR EL LISTEN");
        close(socketServidor);
        exit(EXIT_FAILURE);
    }

    // ** P1.s.9. Bucle de espera activa.
    while(1){

        printf("\nEsperando conexión.\n");
        
         // ** P1.s.10. Aceptamos conexiones.
        socketCliente = accept(socketServidor,NULL,NULL);

        if(socketCliente < 0)
            perror("ERROR AL REALIZAR EL ACCEPT");
     

        cierre=0;

        // ** P1.s.11. Mantenemos la conversación hasta recibir "ciao".
        while(cierre==0){
            
            strcpy(respuesta, "");
            
            // ** P1.s.11. Recepción de datos del cliente.
            if(read(socketCliente,datosRecibidos,sizeof(datosRecibidos))<0){
                perror("ERROR AL RECIBIR DATOS DEL CLIENTE");
                close(socketCliente);
            }

            // ** P1.s.12. Enviamos mensaje.
            printf("[CLIENTE] %s\n", datosRecibidos);

            if (strcmp(datosRecibidos,CIAO)==0){
                cierre=1;
            }
            else{
                
                // ** P1.s.13. Capturamos el mensaje de respuesta.
                printf("[SERVIDOR] ");
                scanf("%s",respuesta);

                // ** P1.s.14. Envío de datos al cliente.
                if (write(socketCliente,&respuesta,sizeof(respuesta))<0){
                    perror("ERROR AL ENVIAR DATOS AL CLIENTE");
                    close(socketCliente);
                }
                             
            }
       
       }
	
        strcpy(respuesta, "");

        // ** P1.s.14. Cerramos conexión con el cliente.
        close(socketCliente);
    }

    // ** P1.s.15. Cerramos el socket servidor.
	close(socketServidor);
   
    return EXIT_SUCCESS;
}
