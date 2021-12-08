/*

E1. Realice un programa de testeo de la primitiva sizeof de C. Para ello, lleve a cabo los 
siguientes pasos:

1.  Defina una variable para cada uno de los siguientes tipos (para las variables
dimensionales, utilice el tamaño que crea oportuno): carácter, entero, real, cadena, 
vector de enteros, matriz de reales, cubo de enteros, vector dinámico de enteros y 
matriz dinámica de reales. 

2.  Inicialice todas las variables.

3.  Aplique sizeof a cada una de las variables previamente definidas.

4.  Compruebe si realmente sizeof devuelve el valor esperado, esto es, 
el tamaño en bytes que ocupa cada variable.

*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ROWS 8
#define COLUMNS 3
#define DEEP 2
#define TAM 1024

int main(void){

    char ch='c';
    int i=0,j=0,k=0,ai=0;
    double n = 0.0, ad=0.0;

    int *pi=&ai;
    double *pd=&ad;
    

    char cadena[TAM] = "Esto es un ejemplo";
    int v[ROWS];
    double m[ROWS][COLUMNS];
    int c[ROWS][COLUMNS][DEEP];

    int *vd;
    double **md;

    *pi = 4;
    *pd = 2.0;
   
    for (i=0;i<ROWS;i++)
        v[i] = i;

    for (i=0;i<ROWS;i++)
        for (j=0;j<COLUMNS;j++)
            m[i][j] = 4.0;

    for (i=0;i<ROWS;i++)
        for (j=0;j<COLUMNS;j++)
            for (k=0;k<DEEP;k++)
                c[i][j][k] = k;

    vd = (int *) malloc(ROWS*sizeof(int)); 

    for (i=0;i<ROWS;i++)
        vd[i] = i*2;


    md = (double **) malloc(ROWS*sizeof(double *)); 
    
    for (i=0;i<ROWS;i++) 
         md[i] = (double *) malloc(COLUMNS*sizeof(double)); 

    for (i=0;i<ROWS;i++)
        for (j=0;j<COLUMNS;j++)
            md[i][j] = i*j;
    
    printf("\nVariables definidas:\n\n");
    printf("char ch = %c\n",ch);
    printf("int i = %d\n",i);
    printf("double n = %lf\n",n);
    printf("int *pi (contenido) = %d\n",*pi);
    printf("double *pd (contenido) = %lf\n",*pd);
    printf("char cadena [1024] = %s\n",cadena);
    
    printf("int v[5] = ");
    for (i=0;i<ROWS;i++) 
        printf("%3d", v[i]);
    printf("\n\n");

    printf("double m[5][5] = \n");
    for (i=0;i<ROWS;i++)
        for (j=0;j<COLUMNS;j++){
            printf("%4.1lf", m[i][j]);
            if (j==COLUMNS-1)
                printf("\n");
        }
    printf("\n");

    printf("int c[5][5][5] = \n");
    for (k=0;k<DEEP;k++){
        printf("\n");
        for (i=0;i<ROWS;i++)
            for (j=0;j<COLUMNS;j++){
                printf("%3d", c[i][j][k]);
                if (j==COLUMNS-1)
                    printf("\n");
            }
    }
    printf("\n");

    printf("int *vd = ");
    for (i=0;i<ROWS;i++) 
        printf("%3d", vd[i]);
    printf("\n\n");


    printf("double **md = \n");
    for (i=0;i<ROWS;i++)
        for (j=0;j<COLUMNS;j++){
            printf("%4.1lf", md[i][j]);
            if (j==COLUMNS-1)
                printf("\n");
        }
    printf("\n");


    printf("Sizeof de tipos genéricos:\n\n");
    printf("sizeof(char) = %d\n",sizeof(char));
    printf("sizeof(int) = %d\n",sizeof(int));
    printf("sizeof(double) = %d\n",sizeof(double));
    printf("sizeof(*int) = %d\n",sizeof(int*));
    printf("sizeof(*double) = %d\n\n",sizeof(double*));

    printf("Sizeof de variables de tipos genéricos:\n\n");
    printf("sizeof(ch) = %d\n",sizeof(ch));
    printf("sizeof(i) = %d\n",sizeof(i));
    printf("sizeof(n) = %d\n",sizeof(n));
    printf("sizeof(pi) = %d\n",sizeof(pi));
    printf("sizeof(*pi) = %d\n",sizeof(*pi));
    printf("sizeof(pd) = %d\n",sizeof(pd));
    printf("sizeof(*pd) = %d\n\n",sizeof(*pd));

    printf("Sizeof de cadenas de caracteres:\n\n");
    printf("sizeof(cadena) = %d\n",sizeof(cadena));
    printf("TAM*sizeof(char) = %d\n",TAM*sizeof(char));
    printf("strlen(cadena)*sizeof(char) = %d\n",strlen(cadena)*sizeof(char));
    printf("strlen(cadena) = %d\n\n",strlen(cadena));
    
    printf("Sizeof de arrays unidimensionales:\n\n");
    printf("sizeof(v) = %d\n",sizeof(v));
    printf("ROWS*sizeof(int) = %d\n\n",ROWS*sizeof(int));
    
    printf("Sizeof de arrays de dos dimensiones:\n\n");
    printf("sizeof(m) = %d\n",sizeof(m));
    printf("ROWS*COLUMNS*sizeof(double) = %d\n\n",ROWS*COLUMNS*sizeof(double));

    printf("Sizeof de arrays de tres dimensiones:\n\n");
    printf("sizeof(c) = %d\n",sizeof(c));
    printf("ROWS*COLUMNS*DEEP*sizeof(int) = %d\n\n",ROWS*COLUMNS*DEEP*sizeof(int));
    
    printf("Sizeof de arrays unidimensinales dinámicos:\n\n");
    printf("sizeof(vd) = %d\n",sizeof(vd));
    printf("ROWS*sizeof(int) = %d\n\n",ROWS*sizeof(int));

    printf("Sizeof de arrays de dos dimensiones dinámicos:\n\n");
    printf("sizeof(md) = %d\n",sizeof(md));
    printf("ROWS*COLUMNS*sizeof(double) = %d\n\n",ROWS*COLUMNS*sizeof(double));

    free(vd);

    for (i=0;i<ROWS;i++) 
            free(md[i]);

    free(md);


    return 0;
}
