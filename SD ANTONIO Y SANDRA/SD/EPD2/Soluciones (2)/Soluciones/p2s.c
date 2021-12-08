/*

P2. Programe una aplicación cliente/servidor que simule un servicio de representación textual 
de variables. Su funcionamiento será el siguiente:

-   Servidor:

    o   Primero recibirá del cliente el tipo de dato a representar. 
    Los tipos de datos soportados serán: entero, real (double), carácter, 
    vector (de enteros), matriz (de reales), cubo (de enteros), vector dinámico 
    (de reales) y matriz dinámica (de reales). 

    o   Después, según el tipo recibido, realizará lo siguiente:

        En el caso de enteros, reales, caracteres, matrices y cubos: recibirá los datos 
        por parte del cliente. Tenga en cuenta la conversión de representación binaria 
        para la recepción de valores enteros.

        En el caso de vectores dinámicos: recibirá primero el tamaño del vector y después 
        los datos.

        En el caso de matrices dinámicas: recibirá primero el número de filas, después 
        el número de columnas y, por último, los datos.

    o   Por último, construirá una cadena de caracteres, que represente adecuadamente el tipo y 
    los datos recibidos, y la enviará al cliente.

    o   Nota: en el caso en el que el tipo recibido no coincida con ningún tipo soportado, 
    recibirá los datos en una variable genérica y devolverá al cliente el mensaje 
    “Tipo no soportado”.

-   Cliente:

    o   Primero leerá por la línea de comando el tipo y el valor que el usuario quiere enviar 
    al servidor. 

        En el caso en el que el usuario quiera enviar un entero, real o carácter, deberá 
        especificar el valor a enviar. 

        >./cliente entero 50

        En el caso en el que el usuario quiera enviar un vector, una matriz o un cubo, 
        no tendrá que especificar nada más. El programa construirá sendos vectores (de enteros) 
        o matrices (de reales) de tamaño y valores fijos.

        >./cliente vector

        En el caso en el que el usuario quiera enviar un vector o una matriz dinámica, 
        deberá especificar el número de posiciones de cada dimensión. El programa construirá 
        sendos vectores (de reales) o matrices (de reales) con el tamaño especificado por el 
        usuario y los inicializará.

        >./cliente mdinamica 20 30

    o   Después, enviará al servidor lo siguiente:

        En el caso en el que el tipo introducido por el usuario sea entero, real, carácter, 
        matriz y cubo: primero enviará dicho tipo y después sus datos. Tenga en cuenta la 
        conversión de representación binaria para el envío de valores enteros.

        En el caso en el que el tipo introducido por el usuario sea vector dinámico: 
        primero enviará dicho tipo, después su tamaño y por último sus datos.

        En el caso en el que el tipo introducido por el usuario sea matriz dinámica: 
        primero enviará dicho tipo, después el número de filas, después el número de columnas 
        y por último sus datos.

    o   Por último, recibirá la cadena de caracteres del servidor y la imprimirá por pantalla.

*/

// ** P2.s.1. Inclusión de librerías.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

// ** P2.s.2. Definición de macros.
#define ENTERO "entero"
#define REAL "real"
#define CARACTER "caracter"
#define VECTOR "vector"
#define MATRIZ "matriz"
#define CUBO "cubo"
#define VDINAMICO "vdinamico"
#define MDINAMICA "mdinamica"
#define TAM 2024
#define SIZE 5
#define PUERTO 1100
#define CAPACIDAD_COLA 5

int main(void){

	// ** P2.s.3. Declaración de variables relacionadas con el socket servidor.	
    int socketServidor;
    struct sockaddr_in direccionSocketServidor; 
    char respuesta[TAM] = "";

    // ** P2.s.4. Declaración de variables relacionadas con los sockets
    // de los clientes atendidos. 
    int socketCliente;
    char tipoRecibido[TAM]="";

    // ** P2.s.5. Declaración de variables para el tratamiento y envío de
    // la respuesta.   
    double datoDouble = 0.0;
    int datoInt = 0;
    char datoChar = 'a';
    char datoString[TAM] = "";
    int datoVector [SIZE];
    double datoMatriz [SIZE][SIZE];
    int datoCubo [SIZE][SIZE][SIZE];
    void* datoVacio;
    double* vectorDinamico;
    double** matrizDinamica;
    int nr=0;
    int nc=0;

     // ** P2.s.6. Declaración de variables auxiliares.
    int i = 0, j = 0, k = 0;
    char aux[TAM] ="";

    // ** P2.s.7. Inicialización de variables.
    for (i=0;i<SIZE;i++)
    	datoVector[i] = -1;

    for (i=0;i<SIZE;i++)
    	for (j=0;j<SIZE;j++)
    		datoMatriz[i][j] = -1.0;

    for (i=0;i<SIZE;i++)
    	for (j=0;j<SIZE;j++)
    		for (k=0;k<SIZE;k++)
    			datoCubo[i][j][k] = -1.0;
	
    // ** P2.s.7. Construcción del socket servidor.
    socketServidor = socket(AF_INET,SOCK_STREAM,0);
    if(socketServidor<0) {
        perror("ERROR AL CONSTRUIR EL SOCKET SERVIDOR");
        exit(EXIT_FAILURE);
    }

    // ** P2.s.8. Construcción del sockaddr_in del socket del servidor.    
    direccionSocketServidor.sin_family = AF_INET;
    direccionSocketServidor.sin_port = htons(PUERTO);
    direccionSocketServidor.sin_addr.s_addr = INADDR_ANY;

    // ** P2.s.9. Realización del bind.
    if(bind(socketServidor,(struct sockaddr *) &direccionSocketServidor,sizeof(direccionSocketServidor))<0){
        perror("ERROR AL REALIZAR EL BIND");
        close(socketServidor);
        exit(EXIT_FAILURE);
    }

    // ** P2.s.10. Realización del listen.
    if(listen(socketServidor,CAPACIDAD_COLA)<0){
        perror("ERROR AL REALIZAR EL LISTEN");
        close(socketServidor);
        exit(EXIT_FAILURE);
    }

    // ** P2.s.11. Bucle de espera activa.
    while(1){

        printf("\nEsperando conexión.\n");
        
        // ** P2.s.12. Realización del accept.
        socketCliente = accept(socketServidor,NULL,NULL);
        if(socketCliente<0)
            perror("ERROR AL REALIZAR EL ACCEPT");

		// ** P2.s.13. Recibimos el tipo del dato a representar.
        if(read(socketCliente,tipoRecibido,TAM)<0) {
        	perror("ERROR AL RECIBIR DATOS DEL CLIENTE");
            close(socketCliente);
        }
		
		// printf("Tipo recibido = %s\n",tipoRecibido);

        // ** P2.s.14. Leemos el dato en función del tipo recibido.
        if (strcmp(tipoRecibido,ENTERO)==0){
        	 
        	// Recibimos el valor entero.
        	if(read(socketCliente,&datoInt,sizeof(datoInt))<0){
        		perror("ERROR AL RECIBIR DATOS DEL CLIENTE");
            	close(socketCliente);
        	}

        	// printf("ENTERO recibido\n"); 
            // Construimos la respuesta, realizando el cambio de represnetación. 	
        	sprintf(respuesta,"[%s] %d",ENTERO,ntohs(datoInt));
        
        }
        
        else if (strcmp(tipoRecibido,REAL)==0){

            // Recibimos el valor real.
        	if(read(socketCliente,&datoDouble,sizeof(datoDouble))<0){
        	   perror("ERROR AL RECIBIR DATOS DEL CLIENTE");
                close(socketCliente);
        	}

        	// printf("REAL recibido\n");
            // Construimos la respuesta.
        	sprintf(respuesta,"[%s] %lf",REAL,datoDouble);

        }

        else if (strcmp(tipoRecibido,CARACTER)==0){

            // Recibimos el valor caracter.
        	if(read(socketCliente,&datoChar,sizeof(datoChar))<0){
                perror("ERROR AL RECIBIR DATOS DEL CLIENTE");
            	close(socketCliente);
        	}

        	// printf("CARACTER recibido\n");
            // Construimos la respuesta.        	
        	sprintf(respuesta,"[%s] %c",CARACTER,datoChar);

        }

 		else if (strcmp(tipoRecibido,VECTOR)==0){

            // Recibimos los datos del vector.
        	if(read(socketCliente,datoVector,sizeof(datoVector))<0) {
        	   perror("ERROR AL RECIBIR DATOS DEL CLIENTE");
               close(socketCliente);
        	}

        	// Construimos la respuesta.
        	sprintf(respuesta,"[%s] ",VECTOR);
        	strcpy(aux,"");

        	for (i=0;i<SIZE;i++){
      			sprintf(aux,"%3d",ntohl(datoVector[i]));
       			strcat(respuesta,aux);
	       	}
        }
        
        else if (strcmp(tipoRecibido,MATRIZ)==0){

            // Recibimos los datos de la matriz.
        	if(read(socketCliente,datoMatriz,sizeof(datoMatriz))<0) {
        		perror("ERROR AL RECIBIR DATOS DEL CLIENTE");
            	close(socketCliente);
        	}

        	// printf("MATRIZ recibido\n");
            // Construimos la respuesta.			
			sprintf(respuesta,"[%s]\n\n",MATRIZ);
        	strcpy(aux,"");

        	for (i=0;i<SIZE;i++){
        		for (j=0;j<SIZE;j++){
      				sprintf(aux,"%3.lf",datoMatriz[i][j]);
      				strcat(respuesta,aux);
      				if (j==SIZE-1)
      					strcat(respuesta,"\n");
      			}
	       	}
        
        }
        
        else if (strcmp(tipoRecibido,CUBO)==0){
        	 
            // Recibimos los datos del cubo.
        	if(read(socketCliente,datoCubo,sizeof(datoCubo))<0) {
        		perror("ERROR AL RECIBIR DATOS DEL CLIENTE");
            	close(socketCliente);
        	}

			// printf("CUBO recibido\n");
            // Construimos la respuesta. 			
			sprintf(respuesta,"[%s]\n\n",CUBO);
        	strcpy(aux,"");

        	for (k=0;k<SIZE;k++){
    			strcat(respuesta,"\n");
        		for (i=0;i<SIZE;i++){
        			for (j=0;j<SIZE;j++){
      					sprintf(aux,"%3d",ntohl(datoCubo[i][j][k]));
      					strcat(respuesta,aux);
      					if (j==SIZE-1)
      						strcat(respuesta,"\n");  					
      					
      				}
      			}
	       	}

        	
        }

        else if (strcmp(tipoRecibido,VDINAMICO)==0){

        	// Recibimos el tamaño del vector dinámico.
         	if(read(socketCliente,&nr,sizeof(nr))<0) {
        		perror("ERROR AL RECIBIR DATOS DEL CLIENTE");
            	close(socketCliente);
        	}

        	// Reservamos memoria para los datos.
        	vectorDinamico = (double *) malloc(nr*sizeof(double)); 

        	// Recibimos los datos.
        	if(read(socketCliente,vectorDinamico,nr*sizeof(double))<0){
        		perror("ERROR AL RECIBIR DATOS DEL CLIENTE");
            	close(socketCliente);
        	}

        	//printf("TAM = %d\n",nr);
    		//for (i=0;i<nr;i++)
    		//	printf("%8.1lf",vectorDinamico[i]);
    		//printf("\n");

        	// printf("VDINAMICO recibido\n");
			// Construimos la respuesta. 
			sprintf(respuesta,"[%s] ",VDINAMICO);
        	strcpy(aux,"");

        	for (i=0;i<nr;i++){
      			sprintf(aux,"%8.1lf",vectorDinamico[i]);
       			strcat(respuesta,aux);
	       	}

	       	// Liberamos la memoria anteriormente reservada.
	       	free(vectorDinamico);
        
        }

         else if (strcmp(tipoRecibido,MDINAMICA)==0){

            // Recibimos el número de filas de la matriz dinámica.
            if(read(socketCliente,&nr,sizeof(nr))<0) {
                perror("ERROR AL RECIBIR DATOS DEL CLIENTE");
                close(socketCliente);
            }

            // Recibimos el número de columnas de la matriz dinámica.
            if(read(socketCliente,&nc,sizeof(nc))<0) {
                perror("ERROR AL RECIBIR DATOS DEL CLIENTE");
                close(socketCliente);
            }

            // Reservamos memoria para los datos.
            matrizDinamica = (double **) malloc(nr*sizeof(double *)); 
            for (i=0;i<nr;i++) 
                matrizDinamica[i] = (double *) malloc(nc*sizeof(double)); 

            // Recibimos los datos fila a fila.
            for (i=0;i<nr;i++){
				// printf("Recibiendo fila %d\n",i);
				if(read(socketCliente,matrizDinamica[i],nc*sizeof(double))<0){
                	perror("ERROR AL RECIBIR DATOS DEL CLIENTE");
                	close(socketCliente);
            	}
            }            

            // printf("NR = %d, NC = %d\n",nr,nc);
            // for (i=0;i<nr;i++)
            //     for (j=0;j<nc;j++){
           	//          printf("%8.1lf", matrizDinamica[i][j]);
           	//          if (j==nc-1)
           	//          printf("\n");
           	// 	}
           	// printf("\n");

            // Construimos la respuesta. 
            sprintf(respuesta,"[%s]\n\n",MDINAMICA);
            strcpy(aux,"");

            for (i=0;i<nr;i++){
                for (j=0;j<nc;j++){
                    sprintf(aux,"%8.1lf",matrizDinamica[i][j]);
                    strcat(respuesta,aux);
                    if (j==nc-1)
                        strcat(respuesta,"\n");
                }
            }

            // Liberamos la memoria anteriormente reservada.
            for (i=0;i<nr;i++) 
	    		free(matrizDinamica[i]);

	    	free(matrizDinamica);

        }

        else{

            // Si el tipo no está soportado.

            // Recibimos en un puntero a void para mantener la correspondencia read/write.
            if(read(socketCliente,&datoVacio,sizeof(datoVacio))<0){
        		perror("ERROR AL RECIBIR DATOS DEL CLIENTE");
            	close(socketCliente);
        	}

        	// Construimos la respuesta. 
           	sprintf(respuesta,"El tipo %s no está soportado\n",tipoRecibido);
        }
      
        // printf("Casuística realizada\n");

        //** P2.s.12. Envío de datos al cliente.
        if (write(socketCliente,respuesta,sizeof(respuesta))<0){
              perror("ERROR AL ENVIAR DATOS AL CLIENTE");
              close(socketCliente);
        }

        printf("Mensaje enviado\n\n");

        // Reiniciamos las variables de respuesta.
        strcpy(respuesta,"");
        strcpy(tipoRecibido,"");
        
		//** P2.s.13. Cierre de la conexión con el cliente.
        close(socketCliente);
    }

	//** P2.s.14. Cierre del socket servidor.
    close(socketServidor);
   
    return EXIT_SUCCESS;
}
