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

// **** E3.s.1.
// Inclusión de librerías correctas.


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
    // Construcción del socket servidor.
  
    
    // **** E3.s.3.
    // Construcciónn de la sockaddr_in.


    // **** E3.s.4.
    // Realizar bind.
  
    
    // **** E3.s.5.
    // Realizar listen.
  
    
    while (1){

        printf("Esperando conexión\n");
        
        // **** E3.s.6.
        // Aceptar conexión.
     
        
        // **** E3.s.7.
        // Recepción del vector.
	 

        // **** E3.s.8.
        // Traza de los valores en red y en host
		printf("Recibido: %d, %d\n",red[0],red[1]);

	

		printf("[HOST] Recibido: %d, %d\n",host[0],host[1]);
        
        // **** E3.s.9.
        // Conversión de representación
   

        printf("[HOST] Suma: %d\n",suma_host);
        printf("[RED] Suma: %d\n",suma_red);

        // **** E3.s.10.
        // Envío de resultados en formato red
 
        close(sc);
    }

    close (sd);

    return 0;
}
