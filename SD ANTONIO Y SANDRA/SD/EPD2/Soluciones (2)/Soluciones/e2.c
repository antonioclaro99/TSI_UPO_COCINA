/*
 
E2. El objetivo de este ejercicio es programar una aplicación que, dada la dirección IP de una 
máquina conectada a la red, obtenga sus URL asociadas. Teniendo esto en cuenta, un ejemplo 
de ejecución de la aplicación sería:

>./e2 80.58.61.254

Y la salida de este:

> La dirección IP 80.58.61.254 corresponde a la url 254.red-80-58-61.staticip.rima-tde.net
Sus alias son: 
La dirección IP 80.58.61.254 corresponde a la url 254.61.58.80.in-addr.arpa (50.53.52.46) 
Toral de alias encontrados = 1

Consideraciones para realizar el ejercicio:

-   Utilice el código de la plantilla e2.c.

-   Estudie las librerías de C y sus elementos necesarios para resolver el ejercicio. 
Estos son:

    o   arpa/inet.h: inet_aton.
    o   netdb.h: gethostbyaddr, struct hostent.
    o   netinet/in.h: struct in_addr.

-   En el sistema operativo Linux, esta información se puede obtener si ejecuta el comando 
nslookup [IP de la máquina]; asimismo, este comando admite la operación inversa, es decir, 
a partir de una URL, obtener la dirección IP,  nslookup [URL asociada a la máquina].
 
 */

// **** E2.1.
// Incluir las librerías correctas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>

int main(int argc, const char * argv[]) {
    
    struct in_addr addr;
    struct hostent *hp;
    char **p;
    struct in_addr in;
    int i = 0;
    
    // **** E2.2.
    // Comprobar con argc que la llamada al comnando se hizo correctamente.
    if (argc!=2){
        printf("Uso: %s direccion IP\n",argv[0]);
        exit(1);
    }
    
    // **** E2.3.
    // Hacer uso de inet_aton para cambiar el formato de notación de dirección IP a 
    // formato binario. El resultado se debe almacenar en la variable addr.    
    if (inet_aton(argv[1],&addr)==0){
        printf("\nLa direccion IP tiene que estar en notacion x.x.x.x\n");
        exit(2);
    }

    // **** E2.4.
    // Obtener una estructura hostent con la información del host mediante gethostbyaddr y
    // almacenar en hp.
    hp=gethostbyaddr(&addr,sizeof(addr),AF_INET);
    if (hp==NULL){
        printf("No se puede encontar la informacion sobre el equipo %s\n", argv[1]);
        exit(3);
    }
    
    printf("\nLa dirección IP %s corresponde a la url: %s\n\n", argv[1],hp->h_name);
	printf("Sus alias son: \n\n");

    // Recorrido de la estructura hostent para encontrar los alias.
    for (p=hp->h_aliases;*p!=NULL;p++){          
        printf("URL alias %d: %s\n",i+1,*p);
        i++;  
    }
    
    printf("\nToral de alias encontrados = %d\n\n",i);
    return(0);

}
