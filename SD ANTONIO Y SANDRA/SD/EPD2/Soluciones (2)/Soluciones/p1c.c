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

// ** P1.c.1. Inclusión de librerías.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


// ** P1.c.2. Definición de macros.
#define TAM 1024
#define CIAO "ciao"
#define PUERTO_SERVIDOR 1100
#define IP_SERVIDOR "127.0.0.1"

int main(void) {

    // ** P1.c.3. Definición de variables relacionadas con el socket servidor.
    int socketServidor;
    struct sockaddr_in direccionSocketServidor;
    char datosRecibidos[TAM];

    // ** P1.c.4. Definición de variables para el envío de mensajes. 
    char datosAenviar[TAM]= "";
    int cierre = 0;


    // ** P1.c.5. Construcción del socket servidor.
    if((socketServidor=socket(AF_INET,SOCK_STREAM,0))<0){
       perror("ERROR AL CONSTRUIR EL SOCKET CLIENTE");
       exit(EXIT_FAILURE);
    }

    // ** P1.c.6. Construcción del sockaddr_in del socket del servidor.
    // Comprobación de formato de la dirección IP.    
    direccionSocketServidor.sin_family = AF_INET;
    direccionSocketServidor.sin_port = htons(PUERTO_SERVIDOR);
    if(inet_pton(AF_INET,IP_SERVIDOR,&direccionSocketServidor.sin_addr.s_addr)<=0){
        perror("ERROR EN LA IP DEL SERVIDOR");
        close(socketServidor);
        exit(EXIT_FAILURE);
    }

    // ** P1.c.7. Realizar conexión con el servidor.
    if(connect(socketServidor,(struct sockaddr *) &direccionSocketServidor,sizeof(direccionSocketServidor))<0){
        perror("ERROR EN LA CONEXIÓN CON EL SERVIDOR");
        close(socketServidor);
        exit(EXIT_FAILURE);
    }
    
    // ** P1.c.8. Mantenemos la conversación hasta enviar "ciao".
    while(cierre==0){

        // ** P1.c.9. Capturamos el mensaje de envío.
        printf("[CLIENTE] ");
        scanf("%s",datosAenviar);

        // ** P1.c.10. Enviamos mensaje.
        if(write(socketServidor,datosAenviar,sizeof(datosAenviar))<0){
            perror("ERROR AL ENVIAR DATOS AL SERVIDOR");
            close(socketServidor);
            exit(EXIT_FAILURE);
        }

        if (strcmp(datosAenviar,CIAO)==0){
            cierre=1;
        }
        else{
            // ** P1.c.11. Recepción de datos del servidor.
            if(read(socketServidor,datosRecibidos,sizeof(datosRecibidos))<0){
                    perror("ERROR AL RECIBIR DATOS DEL SERVIDOR");
                    close(socketServidor);
                    exit(EXIT_FAILURE);
            }

            printf("[SERVIDOR] %s\n", datosRecibidos);

        }

    }
    
    // ** P1.c.12. Cerramos el socket servidor.
    close(socketServidor);
       
    return EXIT_SUCCESS;
}
