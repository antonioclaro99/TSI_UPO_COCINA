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

// ** P2.c.1. Inclusión de librerías.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

// ** P2.c.2. Definición de macros.
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
#define PUERTO_SERVIDOR 1100
#define IP_SERVIDOR "127.0.0.1"

int main(int argc, char *argv[]) {
 
	// ** P2.c.3. Declaración de variables para el envío de tipos y datos.
	char tipo[TAM] = "";
    int ty = 0;
    int valorEntero = 1;
    double valorReal = 1.0;
    char valorCaracter = 'c';
    int valorVector [SIZE];
    double valorMatriz [SIZE][SIZE];
    int valorCubo [SIZE][SIZE][SIZE];
    double* vectorDinamico;
    double** matrizDinamica;

    // ** P2.c.4. Declaración de variables relacionadas con el socket servidor.
    int socketServidor;
    struct sockaddr_in direccionSocketServidor;
    char datosRecibidos[TAM];

    // ** P2.c.5. Declaración de variables auxiliares.
    int nr = 0, nc = 0;
    int i = 0, j = 0, k = 0;

    // ** P2.c.6. Inicialización de variables.
    for (i=0;i<SIZE;i++)
        valorVector[i] = i;

    for (i=0;i<SIZE;i++)
        for (j=0;j<SIZE;j++)
            valorMatriz[i][j] = 4.0;

    for (i=0;i<SIZE;i++)
        for (j=0;j<SIZE;j++)
            for (k=0;k<SIZE;k++)
                valorCubo[i][j][k] = k;

    // ** P2.c.7. Comprobar con argc que la llamada al comando se hizo correctamente
    // capturar el tipo en la variable ty para realizar, posteriormente, la casuística
    // y, para los casos de vector y matriz dinámica, parsear las dimensiones.
    if (argc>1){
    
        strcpy(tipo,argv[1]);   
        
        if (strcmp(tipo,ENTERO)==0){
            if (argc!=3){
                printf("Uso: %s %s valor\n",argv[0],ENTERO);
                exit(EXIT_FAILURE);
            }
            else{
                ty=1;
                valorEntero = strtol(argv[2],NULL,10);
            }
        }
        if (strcmp(tipo,REAL)==0){
            if (argc!=3){
                printf("Uso: %s %s valor\n",argv[0],REAL);
                exit(EXIT_FAILURE);
            }
            else{
                ty=2;
                valorReal = strtod(argv[2],NULL);
            }
        }
        if (strcmp(tipo,CARACTER)==0){
            if (argc!=3){
                printf("Uso: %s %s valor\n",argv[0],CARACTER);
                exit(EXIT_FAILURE);
            }            
            else{
                ty=3;
                valorCaracter = argv[2][0];
            }
        }
        else if (strcmp(tipo,VECTOR)==0){
            if (argc!=2){
                printf("Uso: %s %s\n",argv[0],VECTOR);
                exit(EXIT_FAILURE);
            }
             else
                ty=4;
        }
         else if (strcmp(tipo,MATRIZ)==0){
            if (argc!=2){
                printf("Uso: %s %s\n",argv[0],MATRIZ);
                exit(EXIT_FAILURE);
            }
             else
                ty=5;
        }
         else if (strcmp(tipo,CUBO)==0){
            if (argc!=2){
                printf("Uso: %s %s\n",argv[0],CUBO);
                exit(EXIT_FAILURE);
            } 
            else
                ty=6;
        }
        else if (strcmp(tipo,VDINAMICO)==0){
            if (argc!=3){
                printf("Uso: %s %s tamanyo\n",argv[0],VDINAMICO);
                exit(EXIT_FAILURE);
            }
            else{
                ty=7;
                nr = (int) strtol(argv[2],NULL,10);
            }
        }
        else if (strcmp(tipo,MDINAMICA)==0){
            if (argc!=4){
                printf("Uso: %s %s filas columnas\n",argv[0],MDINAMICA);
                exit(EXIT_FAILURE);
            }
            else{
                ty=8;
                nr = (int) strtol(argv[2],NULL,10);
                nc = (int) strtol(argv[3],NULL,10);
            }
        }

    }
    else{
        printf("Uso: %s tipo [valor] [tamanyo] [filas columnas]\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    
    // ** P2.c.8. Construcción del socket servidor.	
    if ((socketServidor=socket(AF_INET,SOCK_STREAM,0))<0){
       perror("ERROR AL CONSTRUIR EL SOCKET CLIENTE");
       exit(EXIT_FAILURE);
    }

    // ** P2.c.9. Construcción del sockaddr_in del socket del servidor.
    direccionSocketServidor.sin_family = AF_INET;
    direccionSocketServidor.sin_port = htons(PUERTO_SERVIDOR);
    if (inet_pton(AF_INET,IP_SERVIDOR,&direccionSocketServidor.sin_addr.s_addr)<=0){
        perror("ERROR EN LA IP DEL SERVIDOR");
        close(socketServidor);
        exit(EXIT_FAILURE);
    }

    // ** P2.c.10. Conexión con el servidor.
    // printf("Conectando con servidor\n");
    if (connect(socketServidor,(struct sockaddr *) &direccionSocketServidor,sizeof(direccionSocketServidor))<0){
        perror("ERROR EN LA CONEXIÓN CON EL SERVIDOR");
        close(socketServidor);
        exit(EXIT_FAILURE);
    }

    // ** P2.c.10. Enviamos el tipo.
    // printf("Envío del tipo\n");
    if(write(socketServidor,tipo,sizeof(tipo))<0){
      	perror("ERROR AL ENVIAR DATOS AL SERVIDOR");
        close(socketServidor);
        exit(EXIT_FAILURE);
    }

    // ** P2.c.10. Enviamos los datos en función del tipo.
	// printf("Envío de datos\n");
    if (ty==1){

        // Conversión de formato para enteros.
    	valorEntero = htons(valorEntero);

        // Enviamos el valor entero.
        if(write(socketServidor,&valorEntero,sizeof(valorEntero))<0){
        	perror("ERROR AL ENVIAR DATOS AL SERVIDOR");
            close(socketServidor);
            exit(EXIT_FAILURE);
        }
    }
    
   if (ty==2){

    	// Enviamos el valor real.
        if(write(socketServidor,&valorReal,sizeof(valorReal))<0){
        	perror("ERROR AL ENVIAR DATOS AL SERVIDOR");
           	close(socketServidor);
           	exit(EXIT_FAILURE);;
        }
      	// printf("REAL enviado\n");
    }
    
    if (ty==3){

    	// Enviamos el valor caracter.
        if(write(socketServidor,&valorCaracter,sizeof(valorCaracter))<0){
            perror("ERROR AL ENVIAR DATOS AL SERVIDOR");
            close(socketServidor);
            exit(EXIT_FAILURE);
        }

        // printf("CARACTER enviado\n");
    }
 	
 	if (ty==4){

        // Conversión de formato para el vector de enteros.    
 		for (i=0;i<SIZE;i++)
 			valorVector[i]=htonl(valorVector[i]);

 		// Enviamos los datos del vector.
        if(write(socketServidor,valorVector,sizeof(valorVector))<0){
        	perror("ERROR AL ENVIAR DATOS AL SERVIDOR");
            close(socketServidor);
            exit(EXIT_FAILURE);
        }

      	// printf("VECTOR enviado\n");
    }

    if (ty==5){

 		// Enviamos los datos de la matriz.
        if(write(socketServidor,valorMatriz,sizeof(valorMatriz))<0){
            perror("ERROR AL ENVIAR DATOS AL SERVIDOR");
            close(socketServidor);
           	exit(EXIT_FAILURE);
        }

      	// printf("MATRIZ enviado\n");
    }

    if (ty==6){

        // Conversión de formato para el vector de enteros.
    	for (i=0;i<SIZE;i++)
    		for (j=0;j<SIZE;j++)
    			for (k=0;k<SIZE;k++)
    				valorCubo[i][j][k] = htonl(valorCubo[i][j][k]);

		// Enviamos los datos del cubo.
     	if(write(socketServidor,valorCubo,sizeof(valorCubo))<0){
          	perror("ERROR AL ENVIAR DATOS AL SERVIDOR");
            close(socketServidor);
            exit(EXIT_FAILURE);
        }

       	// printf("CUBO enviado\n");
    }
		
	if (ty==7){
			
		// Reserva de memoria dinámica.
		vectorDinamico = (double *) malloc(nr*sizeof(double)); 
    	
        // Inicialización del vector.	
    	for (i=0;i<nr;i++)
    		vectorDinamico[i] = 10.0;

    	//printf("\n");
    	//for (i=0;i<nr;i++)
    	//	printf("%8.1lf",vectorDinamico[i]);
    	//printf("\n");

    	// Enviamos el tamaño del vector.
        if(write(socketServidor,&nr,sizeof(nr))<0){
        	perror("ERROR AL ENVIAR DATOS AL SERVIDOR");
           	close(socketServidor);
           	exit(EXIT_FAILURE);
        }

		// Enviamos los datos del vector.
       	if(write(socketServidor,vectorDinamico,nr*sizeof(double))<0){
        	perror("ERROR AL ENVIAR DATOS AL SERVIDOR");
           	close(socketServidor);
           	exit(EXIT_FAILURE);
        }

        // Liberamos la memoria anteriormente reservada
	    free(vectorDinamico);

    }

    if (ty==8){

        // Reserva de memoria dinámica.
        matrizDinamica = (double **) malloc(nr*sizeof(double *)); 
        
        for (i=0;i<nr;i++) 
            matrizDinamica[i] = (double *) malloc(nc*sizeof(double)); 

        // Inicialización de la matriz.
        for (i=0;i<nr;i++)
    		for (j=0;j<nc;j++)
    			matrizDinamica[i][j] = i*j;

    	// printf("NR = %d, NC = %d\n",nr,nc);
        // for (i=0;i<nr;i++)
        //     for (j=0;j<nc;j++){
        //          printf("%8.1lf", matrizDinamica[i][j]);
        //          if (j==nc-1)
        //          printf("\n");
        //  }
        // printf("\n"); 

    	// Enviamos el número de filas.
        if(write(socketServidor,&nr,sizeof(nr))<0){
        	perror("ERROR AL ENVIAR DATOS AL SERVIDOR");
           	close(socketServidor);
           	exit(EXIT_FAILURE);
        }

        // Enviamos el número de columnas.
        if(write(socketServidor,&nc,sizeof(nc))<0){
        	perror("ERROR AL ENVIAR DATOS AL SERVIDOR");
           	close(socketServidor);
           	exit(EXIT_FAILURE);
        }

		// Enviamos los datos de la matriz fila a fila.
		for (i=0;i<nr;i++){
			if(write(socketServidor,matrizDinamica[i],nc*sizeof(double))<0){
        		perror("ERROR AL ENVIAR DATOS AL SERVIDOR");
           		close(socketServidor);
           		exit(EXIT_FAILURE);
        	}		
		}
     
        // Liberamos la memoria anteriormente reservada.
        for (i=0;i<nr;i++) 
	    	free(matrizDinamica[i]);

	    free(matrizDinamica);

    }

    else{

        // En el caso de que el usuario haya introducido un tipo no soportado.			
		
        // Enviamos un dato cualquiera.
       	if(write(socketServidor,&valorEntero,sizeof(valorEntero))<0){
    	    perror("ERROR AL ENVIAR DATOS AL SERVIDOR");
            close(socketServidor);
           	exit(EXIT_FAILURE);
        }

    }

    // ** P2.c.11. Recepción de datos del servidor.
    if(read(socketServidor,datosRecibidos,sizeof(datosRecibidos))<0){
        perror("ERROR AL RECIBIR DATOS DEL SERVIDOR");
        close(socketServidor);
        exit(EXIT_FAILURE);
    }

    printf("\nMensaje recibido:\n\n%s\n\n", datosRecibidos);

    // ** P2.c.12. Cierre del socket servidor.
    close(socketServidor);
    
    return EXIT_SUCCESS;
}
