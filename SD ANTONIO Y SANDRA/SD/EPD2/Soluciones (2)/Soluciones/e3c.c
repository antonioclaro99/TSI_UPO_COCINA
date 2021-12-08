/*

E3. Programe una aplicación cliente/servidor con sockets para testar las funciones de conversión de 
representación binaria de enteros. El cliente leerá por la línea de comandos dos números enteros, 
los convertirá a representación en red, los almacenará en un vector de dos posiciones, lo enviará 
al servidor y, por último, recibirá del servidor la suma de ambos números. Por su parte, el servidor, 
recibirá el vector con los dos enteros, realizará el cambio de representación de red a host, sumará 
los dos valores y enviará el resultado al cliente. 

Tanto el cliente como para el servidor deberán mostrar los valores enteros recibidos/enviados en 
representación binaria en red y representación binaria en host con la idea de comparar los valores 
de los mismos en ambos casos.

Un ejemplo de ejecución de la aplicación sería:

>./cliente 20 50

[HOST] Sumandos: 20 , 50
[RED]  Sumandos: 335544320 , 838860800
[RED]  Resultado: 1174405120 
[HOST] Resultado: 70

>./servidor

Esperando conexión
Recibido: 335544320, 838860800
[HOST] Recibido: 20, 50
[HOST] Suma: 70
[RED] Suma: 1174405120

Consideraciones para realizar el ejercicio:

-	Utilice el código de la plantilla e2.c.
-	Estudie las funciones C para realizar el parseo de cadena de caracteres a enteros y el cambio 
de representación binaria. Estas son:

		o	stdlib.h: strtol.
		o	netinet/in.h: htons, htonl, ntohs, ntohl.

*/

// **** E3.c.1.
// Inclusión de librerías correctas.
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PUERTO_SERVIDOR 2100
#define IP_SERVIDOR "127.0.0.1"

int main(int argc, char* argv[]) {

    int i=0,c=0,sd=0,host[2],red[2],suma_host=0,suma_red=0;
    struct sockaddr_in server_addr;
    struct hostent *hp;
    
    for (i=0;i<2;i++){
        host[i]=0;
        red[i]=0; 
    }

    // **** E3.c.2.
    // Comprobar el correcto número de parámtros de la línea de comandos
    if (argc!=3){
        fprintf(stderr, "Uso: %s primer_sumando segundo_sumando\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    // **** E3.c.3.
    // Construcción del Socket del servidor.
    sd=socket(AF_INET,SOCK_STREAM,0);    
    if(sd<0){
        perror("Error al construir el socket servidor\n");
        exit(EXIT_FAILURE);
    }
   
    // **** E3.c.4.
    // Construcción de la sockaddr_in.
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PUERTO_SERVIDOR);    
    if (inet_pton(AF_INET,IP_SERVIDOR,&server_addr.sin_addr.s_addr)<=0){
        perror("Error en la IP del servidor\n");
        close(sd);
        exit(EXIT_FAILURE);
    }

    // **** E3.c.5.
    // Conexión a servidor.
    if (connect(sd,(struct sockaddr *) &server_addr,sizeof(server_addr))<0){
        perror("Error en la conexión con el servidor\n");
        close(sd);
        exit(EXIT_FAILURE);
    }

    // **** E3.c.6.
    // Parseo y conversión de formato de los parámetros de entrada
    host[0]=strtol(argv[1],NULL,10);
    host[1]=strtol(argv[2],NULL,10);

    red[0]=htonl(host[0]);
    red[1]=htonl(host[1]);

    printf("[HOST] Sumandos: %d , %d\n",host[0],host[1]);
    printf("[RED]  Sumandos: %d , %d\n",red[0],red[1]);
	
    
    // **** E3.c.7.
    // Envío de parámetros
    if (write(sd, red, sizeof(red))<0){
    	printf("Error en envío\n");
        close(sd);
        exit(EXIT_FAILURE);
    }
   	
   	// **** E3.c.8.
    // Recepción de resultados
    if (read(sd,&suma_red,sizeof(suma_red))<0){
		printf("Error en la recepción\n");
        close(sd);
        exit(EXIT_FAILURE);
	}

    // **** E3.c.9.
    // Presentación de resultados
	suma_host = ntohl(suma_red);

    printf("[RED]  Resultado: %d \n", suma_red);
    printf("[HOST] Resultado: %d \n", suma_host);

    
    close (sd);
    
    return 0;
}
